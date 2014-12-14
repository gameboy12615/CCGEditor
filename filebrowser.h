#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QMainWindow>
#include <QModelIndex>

namespace Ui {
class FileBrowser;
}

class QTreeView;
class QFileSystemModel;
class QContextMenuEvent;
class QAction;
class QSplitter;

class FileBrowser : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileBrowser(QWidget *parent = 0);
    ~FileBrowser();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void renameFile();
    void removeFile();
    void fileRenameDone();
    void openFile();
    void zipFiles();
    void showFiles(QModelIndex);

private:
    void createWidgets();
    void createLayout();
    void createConnections();
    void createActions();

    QTreeView *dirView;
    QTreeView *fileView;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QSplitter *splitter;

    QAction *removeFileAction;
    QAction *removeFilesAction;
    QAction *zipFilesAction;
    QAction *renameFileAction;
    QAction *openFileAction;

};

#endif // FILEBROWSER_H
