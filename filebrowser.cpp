#include "filebrowser.h"
#include <QTreeView>
#include <QHeaderView>
#include <QFileSystemModel>
#include <QDir>
#include <QItemSelectionModel>
#include <QAbstractItemView>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDebug>
#include <QModelIndexList>
#include <QList>
#include <QFile>
#include <exception>
#include <QDesktopServices>
#include <QProcess>
#include <QUrl>
#include <QFileDialog>
#include <QSplitter>
#include <QMessageBox>
#include <QtGlobal>
#include <QSizePolicy>

FileBrowser::FileBrowser(QWidget *parent)
	: QMainWindow(parent)
{
    createWidgets();
    createLayout();
    createActions();
    createConnections();
}

FileBrowser::~FileBrowser()
{

}

void FileBrowser::createWidgets()
{
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(QDir::homePath());
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setReadOnly(true);
    fileModel = new QFileSystemModel(this);
    fileModel->setReadOnly(true);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);

	QPalette palette;
	palette.setColor(QPalette::Base, QColor(200, 200, 200, 255));

    splitter = new QSplitter;
    dirView = new QTreeView(splitter);
    fileView = new QTreeView(splitter);

    dirView->setModel(dirModel);
    dirView->header()->setStretchLastSection(true);
    dirView->header()->setSortIndicator(0, Qt::AscendingOrder);
    dirView->header()->setSortIndicatorShown(true);
    dirView->header()->setSectionsClickable(true);

    QModelIndex index = dirModel->index(QDir::homePath());
    dirView->expand(index);
    dirView->scrollTo(index);
    dirView->resizeColumnToContents(0);
    dirView->setAnimated(false);
    dirView->setIndentation(20);
    dirView->setSortingEnabled(true);
    dirView->setExpandsOnDoubleClick(true);
	dirView->setMinimumWidth(100);
	dirView->setMaximumWidth(500);
	dirView->setPalette(palette);

    fileView->setModel(fileModel);
    fileView->setRootIndex(fileModel->setRootPath(dirModel->fileInfo(index).absoluteFilePath()));
    fileView->header()->setStretchLastSection(true);
    fileView->header()->setSortIndicator(0, Qt::AscendingOrder);
    fileView->header()->setSortIndicatorShown(true);
    fileView->header()->setSectionsClickable(true);
    fileView->resizeColumnToContents(0);
    fileView->setAnimated(false);
    fileView->setSortingEnabled(true);
    fileView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	fileView->setMinimumWidth(150);
	fileView->setMaximumWidth(500);
	fileView->setPalette(palette);
}

void FileBrowser::createLayout()
{
    setCentralWidget(splitter);
}

void FileBrowser::createActions()
{
    removeFileAction = new QAction(tr("&Remove File(s)"), this);
    removeFileAction->setShortcut(QKeySequence::Delete);

    zipFilesAction = new QAction(tr("&Zip File(s)"), this);

    renameFileAction = new QAction(tr("&Rename File..."), this);

    openFileAction = new QAction(tr("&Open File"), this);
    openFileAction->setShortcut(QKeySequence::Open);
}

void FileBrowser::contextMenuEvent(QContextMenuEvent *event)
{
    // declate contect menu for the file tree.
    QMenu menu(this);
    menu.addAction(openFileAction);
    menu.addAction(removeFileAction);
    menu.addAction(renameFileAction);
    menu.addAction(zipFilesAction);
    menu.exec(event->globalPos());
}

void FileBrowser::createConnections()
{
    connect(renameFileAction, SIGNAL(triggered()), this, SLOT(renameFile()));
    connect(removeFileAction, SIGNAL(triggered()), this, SLOT(removeFile()));
    connect(fileModel, SIGNAL(fileRenamed(QString, QString, QString)), this, SLOT(fileRenameDone()));
    auto stopEditingSlot = [&]() { fileModel->setReadOnly(true); };
    connect(fileView, &QTreeView::doubleClicked, stopEditingSlot);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(zipFilesAction, SIGNAL(triggered()), this, SLOT(zipFiles()));
    connect(dirView, SIGNAL(clicked(QModelIndex)), this,
            SLOT(showFiles(QModelIndex)));
}

void FileBrowser::renameFile()
{
    fileModel->setReadOnly(false);
    fileView->edit(fileView->currentIndex());
}

void FileBrowser::fileRenameDone()
{
    fileModel->setReadOnly(true);
}

void FileBrowser::removeFile()
{
    // remove one or multiple files at once
    // function will ask confirmation for the action
    QItemSelectionModel *selectionModel = fileView->selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();
    int numberOfFiles = 0;
    for (const auto &index : indexList) {
        QFileInfo file(fileModel->filePath(index));
        if (!file.isDir())
            numberOfFiles += 1;
    }
    int ret = QMessageBox::warning(
        this, tr("File Browser"),
        tr("You are about to remove %1 selected file(s)\n"
           "Are you sure you want to continue?")
            .arg(qRound(static_cast<qreal>(numberOfFiles / 4))),
        QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    switch (ret) {
    case QMessageBox::Ok:
        for (const auto &index : indexList) {
            QFileInfo file(fileModel->filePath(index));
            if (!file.isDir() && !fileModel->remove(index))
                qWarning("Could not remove file %s from the file system",
                         qPrintable(file.fileName()));
        }
        break;
    case QMessageBox::Cancel:
        return;
    default:
        break;
    }
}

void FileBrowser::openFile()
{
    QString fileName = fileModel->filePath(fileView->currentIndex());
    try
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
    catch (const std::exception &e)
    {
        qWarning("Unable to open file %s\n%s", qPrintable(fileName), qPrintable(e.what()));
    }
}

void FileBrowser::zipFiles()
{
    // zip selected files using qprocess and zip command
    QItemSelectionModel *selectionModel = fileView->selectionModel();
    QModelIndexList indexList = selectionModel->selectedIndexes();
    QProcess *myProcess = new QProcess(this);
    QStringList files;
    for (const auto &index : indexList) {
        QFileInfo file(fileModel->filePath(index));
        if (file.exists() && !files.contains(file.absoluteFilePath()))
            files.append(file.absoluteFilePath());
    }
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save zipped file"), "/home", tr("Zip files (*.zip)"));
    if (!fileName.isEmpty()) {
        myProcess->start("zip", QStringList() << fileName << files);
    }
}

void FileBrowser::showFiles(QModelIndex index)
{
    fileView->setRootIndex(fileModel->setRootPath(dirModel->fileInfo(index).absoluteFilePath()));
}
