#pragma once
#include "ui_Parameter.h"
#include <QTableWidgetItem>
#include "QWidget"
#include <QDebug>

class ParameterDock : public QWidget {
	Q_OBJECT
public:
	ParameterDock(QWidget *parent = Q_NULLPTR);

public slots:
	void setRedLabelText(int number){
		ui.redLabelNumnerLineEdit->setText(QString("%1").arg(number));
		//update();
	}
	void setGreenLabelText(int number){
		ui.greenLabelNumberLineEdit->setText(QString("%1").arg(number));
		//update();
	}
	void setBlueLabelText(int number){
		ui.blueLabelNumbeLineEdit->setText(QString("%1").arg(number));
		//update();
	}
	void setYellowLabelText(int number){
		ui.yellowLabelNumberLineEdit->setText(QString("%1").arg(number));
		//update();
	}
	void setBlackLabelText(int number){
		ui.blackLabelNumberLineEdit->setText(QString("%1").arg(number));
		//update();
	}
public:
	Ui::ParameterDock ui;
};