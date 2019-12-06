#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <ui_Navigation.h>
class NavigationDock : public QGraphicsView
{
	Q_OBJECT

public:
	NavigationDock(QWidget *parent=nullptr);
	~NavigationDock();

	Ui::NavigationDock ui;
};
