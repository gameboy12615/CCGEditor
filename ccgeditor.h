#ifndef CCGEDITOR_H
#define CCGEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_ccgeditor.h"

class AppDelegate;
namespace Ui {
	class CCGEditor;
}

class CCGEditor : public QMainWindow
{
	Q_OBJECT

public:
	CCGEditor(QWidget *parent = 0);
	~CCGEditor();

	void setSceneWidget(QWidget *widget);
	void setHierarchyWidget(QWidget *widget);
	void setProjectWidget(QWidget *widget);
	void setInspectorWidget(QWidget *widget);

protected:
	void closeEvent(QCloseEvent *);

private slots:
    void on_actionOpen_Project_triggered();

private:
	Ui::CCGEditorClass	ui;
	AppDelegate			*_appDelegate;
	QWidget				*_sceneWidget;
	QWidget				*_hierarchyWidget;
	QWidget				*_projectWidget;
	QWidget				*_inspectorWidget;
};

#endif // CCGEDITOR_H
