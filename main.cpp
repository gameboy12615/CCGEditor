#include "ccgeditor.h"
#include <QtWidgets/QApplication>

#include "Classes/AppDelegate.h"
#include "Classes/QtPort/CCQGLView.h"
#include "cocos2d.h"

USING_NS_CC;

int main(int argc, char *argv[])
{
	AppDelegate app(argc, argv);
	return cocos2d::CCQApplication::getInstance()->run();
}
