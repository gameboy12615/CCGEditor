#include "ccgeditor.h"
#include "filebrowser.h"
#include "Classes/AppDelegate.h"
#include "Classes/QtPort/CCQGLView.h"

#include <QTimer>
#include <QDockWidget>

CCGEditor::CCGEditor(QWidget *parent)
	: QMainWindow(parent),
	_appDelegate(NULL),
	_sceneWidget(NULL)
{
	ui.setupUi(this);
	setProjectWidget(new FileBrowser(this));
}

CCGEditor::~CCGEditor()
{

}

void CCGEditor::closeEvent(QCloseEvent *)
{
	cocos2d::Director::getInstance()->end();
	qApp->quit();
}

void CCGEditor::setSceneWidget(QWidget *widget)
{
	_sceneWidget = widget;

	if (_sceneWidget)
	{
		ui.SceneWidget->setWidget(_sceneWidget);
		setCentralWidget(ui.SceneWidget);
	}
}

void CCGEditor::setHierarchyWidget(QWidget *widget)
{
	_hierarchyWidget = widget;

	if (_hierarchyWidget)
	{
		ui.HierarchyWidget->setWidget(_hierarchyWidget);
	}
}

void CCGEditor::setProjectWidget(QWidget *widget)
{
	_projectWidget = widget;

	if (_projectWidget)
	{
		_projectWidget->setWindowFlags(Qt::Widget);
		ui.ProjectWidget->setWidget(_projectWidget);
	}
}

void CCGEditor::setInspectorWidget(QWidget *widget)
{
	_inspectorWidget = widget;

	if (_inspectorWidget)
	{
		ui.InspectorWidget->setWidget(_inspectorWidget);
	}
}

void CCGEditor::on_actionOpen_Project_triggered()
{
	int i = 10;
}
