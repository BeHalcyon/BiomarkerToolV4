/********************************************************************************
** Form generated from reading UI file 'Parameter.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETER_H
#define UI_PARAMETER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParameterDock
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_is_local_view_choosed;
    QRadioButton *radioButton_is_global_view_choosed;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *zoomOutPushButtom;
    QPushButton *zoomInPushButtom;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *checkBox_region_painting;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_36;
    QRadioButton *redRadioButton;
    QLineEdit *redLabelNameLineEdit;
    QLabel *label;
    QLineEdit *redLabelNumnerLineEdit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_37;
    QRadioButton *greenRadioButton;
    QLineEdit *greenLabelNameLineEdit;
    QLabel *label_2;
    QLineEdit *greenLabelNumberLineEdit;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_38;
    QRadioButton *blueRadioButton;
    QLineEdit *blueLabelNameLineEdit;
    QLabel *blueLabelNumberLabel;
    QLineEdit *blueLabelNumbeLineEdit;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_39;
    QRadioButton *yellowRadioButton;
    QLineEdit *yellowLabelNameLineEdit;
    QLabel *label_4;
    QLineEdit *yellowLabelNumberLineEdit;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_40;
    QRadioButton *blackRadioButton;
    QLineEdit *blackLabelNameLineEdit;
    QLabel *label_5;
    QLineEdit *blackLabelNumberLineEdit;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_4;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *radioButton_is_circle_draw;
    QRadioButton *radioButton_is_circle_draw_2;
    QTableWidget *tableWidget;
    QWidget *tab_3;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_5;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_7;

    void setupUi(QWidget *ParameterDock)
    {
        if (ParameterDock->objectName().isEmpty())
            ParameterDock->setObjectName(QString::fromUtf8("ParameterDock"));
        ParameterDock->resize(344, 846);
        ParameterDock->setMinimumSize(QSize(317, 0));
        verticalLayout_2 = new QVBoxLayout(ParameterDock);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(ParameterDock);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 274));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy);
        verticalLayoutWidget_3 = new QWidget(tab);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(9, 9, 301, 322));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox_3 = new QGroupBox(verticalLayoutWidget_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 50));
        groupBox_3->setMaximumSize(QSize(16777215, 50));
        horizontalLayoutWidget = new QWidget(groupBox_3);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 20, 281, 21));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton_is_local_view_choosed = new QRadioButton(horizontalLayoutWidget);
        radioButton_is_local_view_choosed->setObjectName(QString::fromUtf8("radioButton_is_local_view_choosed"));
        radioButton_is_local_view_choosed->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_is_local_view_choosed);

        radioButton_is_global_view_choosed = new QRadioButton(horizontalLayoutWidget);
        radioButton_is_global_view_choosed->setObjectName(QString::fromUtf8("radioButton_is_global_view_choosed"));
        radioButton_is_global_view_choosed->setChecked(false);

        horizontalLayout_2->addWidget(radioButton_is_global_view_choosed);


        horizontalLayout->addWidget(groupBox_3);


        verticalLayout_7->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox = new QGroupBox(verticalLayoutWidget_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 94));
        groupBox->setMaximumSize(QSize(16777215, 81));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        zoomOutPushButtom = new QPushButton(groupBox);
        zoomOutPushButtom->setObjectName(QString::fromUtf8("zoomOutPushButtom"));

        horizontalLayout_8->addWidget(zoomOutPushButtom);

        zoomInPushButtom = new QPushButton(groupBox);
        zoomInPushButtom->setObjectName(QString::fromUtf8("zoomInPushButtom"));

        horizontalLayout_8->addWidget(zoomInPushButtom);


        verticalLayout_10->addLayout(horizontalLayout_8);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));

        verticalLayout_10->addLayout(horizontalLayout_15);

        checkBox_region_painting = new QCheckBox(groupBox);
        checkBox_region_painting->setObjectName(QString::fromUtf8("checkBox_region_painting"));

        verticalLayout_10->addWidget(checkBox_region_painting);


        verticalLayout_3->addLayout(verticalLayout_10);


        horizontalLayout_3->addWidget(groupBox);


        verticalLayout_7->addLayout(horizontalLayout_3);

        groupBox_2 = new QGroupBox(verticalLayoutWidget_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 155));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_36 = new QLabel(groupBox_2);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setMinimumSize(QSize(28, 0));
        label_36->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        label_36->setMargin(0);

        horizontalLayout_9->addWidget(label_36);

        redRadioButton = new QRadioButton(groupBox_2);
        redRadioButton->setObjectName(QString::fromUtf8("redRadioButton"));
        redRadioButton->setChecked(true);

        horizontalLayout_9->addWidget(redRadioButton);

        redLabelNameLineEdit = new QLineEdit(groupBox_2);
        redLabelNameLineEdit->setObjectName(QString::fromUtf8("redLabelNameLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(redLabelNameLineEdit->sizePolicy().hasHeightForWidth());
        redLabelNameLineEdit->setSizePolicy(sizePolicy1);
        redLabelNameLineEdit->setMinimumSize(QSize(0, 0));

        horizontalLayout_9->addWidget(redLabelNameLineEdit);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_9->addWidget(label);

        redLabelNumnerLineEdit = new QLineEdit(groupBox_2);
        redLabelNumnerLineEdit->setObjectName(QString::fromUtf8("redLabelNumnerLineEdit"));
        redLabelNumnerLineEdit->setMinimumSize(QSize(0, 0));
        redLabelNumnerLineEdit->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_9->addWidget(redLabelNumnerLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_37 = new QLabel(groupBox_2);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setMinimumSize(QSize(28, 0));
        label_37->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));

        horizontalLayout_10->addWidget(label_37);

        greenRadioButton = new QRadioButton(groupBox_2);
        greenRadioButton->setObjectName(QString::fromUtf8("greenRadioButton"));

        horizontalLayout_10->addWidget(greenRadioButton);

        greenLabelNameLineEdit = new QLineEdit(groupBox_2);
        greenLabelNameLineEdit->setObjectName(QString::fromUtf8("greenLabelNameLineEdit"));

        horizontalLayout_10->addWidget(greenLabelNameLineEdit);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_10->addWidget(label_2);

        greenLabelNumberLineEdit = new QLineEdit(groupBox_2);
        greenLabelNumberLineEdit->setObjectName(QString::fromUtf8("greenLabelNumberLineEdit"));
        greenLabelNumberLineEdit->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_10->addWidget(greenLabelNumberLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_38 = new QLabel(groupBox_2);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setMinimumSize(QSize(28, 0));
        label_38->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 255);"));

        horizontalLayout_11->addWidget(label_38);

        blueRadioButton = new QRadioButton(groupBox_2);
        blueRadioButton->setObjectName(QString::fromUtf8("blueRadioButton"));

        horizontalLayout_11->addWidget(blueRadioButton);

        blueLabelNameLineEdit = new QLineEdit(groupBox_2);
        blueLabelNameLineEdit->setObjectName(QString::fromUtf8("blueLabelNameLineEdit"));

        horizontalLayout_11->addWidget(blueLabelNameLineEdit);

        blueLabelNumberLabel = new QLabel(groupBox_2);
        blueLabelNumberLabel->setObjectName(QString::fromUtf8("blueLabelNumberLabel"));

        horizontalLayout_11->addWidget(blueLabelNumberLabel);

        blueLabelNumbeLineEdit = new QLineEdit(groupBox_2);
        blueLabelNumbeLineEdit->setObjectName(QString::fromUtf8("blueLabelNumbeLineEdit"));
        blueLabelNumbeLineEdit->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_11->addWidget(blueLabelNumbeLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_39 = new QLabel(groupBox_2);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setMinimumSize(QSize(28, 0));
        label_39->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        horizontalLayout_12->addWidget(label_39);

        yellowRadioButton = new QRadioButton(groupBox_2);
        yellowRadioButton->setObjectName(QString::fromUtf8("yellowRadioButton"));

        horizontalLayout_12->addWidget(yellowRadioButton);

        yellowLabelNameLineEdit = new QLineEdit(groupBox_2);
        yellowLabelNameLineEdit->setObjectName(QString::fromUtf8("yellowLabelNameLineEdit"));

        horizontalLayout_12->addWidget(yellowLabelNameLineEdit);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_12->addWidget(label_4);

        yellowLabelNumberLineEdit = new QLineEdit(groupBox_2);
        yellowLabelNumberLineEdit->setObjectName(QString::fromUtf8("yellowLabelNumberLineEdit"));
        yellowLabelNumberLineEdit->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_12->addWidget(yellowLabelNumberLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_40 = new QLabel(groupBox_2);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setMinimumSize(QSize(28, 0));
        label_40->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        horizontalLayout_13->addWidget(label_40);

        blackRadioButton = new QRadioButton(groupBox_2);
        blackRadioButton->setObjectName(QString::fromUtf8("blackRadioButton"));

        horizontalLayout_13->addWidget(blackRadioButton);

        blackLabelNameLineEdit = new QLineEdit(groupBox_2);
        blackLabelNameLineEdit->setObjectName(QString::fromUtf8("blackLabelNameLineEdit"));

        horizontalLayout_13->addWidget(blackLabelNameLineEdit);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_13->addWidget(label_5);

        blackLabelNumberLineEdit = new QLineEdit(groupBox_2);
        blackLabelNumberLineEdit->setObjectName(QString::fromUtf8("blackLabelNumberLineEdit"));
        blackLabelNumberLineEdit->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_13->addWidget(blackLabelNumberLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_13);


        verticalLayout_7->addWidget(groupBox_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayoutWidget_4 = new QWidget(tab_2);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(10, 10, 301, 531));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        groupBox_4 = new QGroupBox(verticalLayoutWidget_4);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(217, 257));
        verticalLayoutWidget = new QWidget(groupBox_4);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 19, 281, 501));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        radioButton_is_circle_draw = new QRadioButton(verticalLayoutWidget);
        radioButton_is_circle_draw->setObjectName(QString::fromUtf8("radioButton_is_circle_draw"));
        radioButton_is_circle_draw->setChecked(false);

        horizontalLayout_14->addWidget(radioButton_is_circle_draw);

        radioButton_is_circle_draw_2 = new QRadioButton(verticalLayoutWidget);
        radioButton_is_circle_draw_2->setObjectName(QString::fromUtf8("radioButton_is_circle_draw_2"));
        radioButton_is_circle_draw_2->setChecked(true);

        horizontalLayout_14->addWidget(radioButton_is_circle_draw_2);


        verticalLayout_5->addLayout(horizontalLayout_14);

        tableWidget = new QTableWidget(verticalLayoutWidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1000)
            tableWidget->setRowCount(1000);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMaximumSize(QSize(16777215, 16777215));
        tableWidget->setAutoScrollMargin(25);
        tableWidget->setShowGrid(true);
        tableWidget->setSortingEnabled(false);
        tableWidget->setCornerButtonEnabled(true);
        tableWidget->setRowCount(1000);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(25);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout_5->addWidget(tableWidget);


        horizontalLayout_4->addWidget(groupBox_4);


        verticalLayout_8->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayoutWidget_5 = new QWidget(tab_3);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(10, 10, 301, 591));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox_5 = new QGroupBox(verticalLayoutWidget_5);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(0, 224));
        verticalLayoutWidget_2 = new QWidget(groupBox_5);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 20, 281, 551));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));

        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));

        verticalLayout_6->addLayout(horizontalLayout_7);


        horizontalLayout_5->addWidget(groupBox_5);


        verticalLayout_9->addLayout(horizontalLayout_5);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ParameterDock);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ParameterDock);
    } // setupUi

    void retranslateUi(QWidget *ParameterDock)
    {
        ParameterDock->setWindowTitle(QApplication::translate("ParameterDock", "Form", nullptr));
        groupBox_3->setTitle(QApplication::translate("ParameterDock", "View setting", nullptr));
        radioButton_is_local_view_choosed->setText(QApplication::translate("ParameterDock", "Local view", nullptr));
        radioButton_is_global_view_choosed->setText(QApplication::translate("ParameterDock", "Global view", nullptr));
        groupBox->setTitle(QApplication::translate("ParameterDock", "Local View Setting", nullptr));
        zoomOutPushButtom->setText(QApplication::translate("ParameterDock", "Zoom out(x2)", nullptr));
        zoomInPushButtom->setText(QApplication::translate("ParameterDock", "Zoom in(x2)", nullptr));
        checkBox_region_painting->setText(QApplication::translate("ParameterDock", "Region painting", nullptr));
        groupBox_2->setTitle(QApplication::translate("ParameterDock", "Pen Setting", nullptr));
        label_36->setText(QString());
        redRadioButton->setText(QString());
        redLabelNameLineEdit->setInputMask(QString());
        redLabelNameLineEdit->setPlaceholderText(QApplication::translate("ParameterDock", "The first label name", nullptr));
        label->setText(QApplication::translate("ParameterDock", "Number:", nullptr));
        redLabelNumnerLineEdit->setText(QApplication::translate("ParameterDock", "0", nullptr));
        label_37->setText(QString());
        greenRadioButton->setText(QString());
        greenLabelNameLineEdit->setPlaceholderText(QApplication::translate("ParameterDock", "The second label name", nullptr));
        label_2->setText(QApplication::translate("ParameterDock", "Number:", nullptr));
        greenLabelNumberLineEdit->setText(QApplication::translate("ParameterDock", "0", nullptr));
        label_38->setText(QString());
        blueRadioButton->setText(QString());
        blueLabelNameLineEdit->setPlaceholderText(QApplication::translate("ParameterDock", "The third label name", nullptr));
        blueLabelNumberLabel->setText(QApplication::translate("ParameterDock", "Number:", nullptr));
        blueLabelNumbeLineEdit->setText(QApplication::translate("ParameterDock", "0", nullptr));
        label_39->setText(QString());
        yellowRadioButton->setText(QString());
        yellowLabelNameLineEdit->setPlaceholderText(QApplication::translate("ParameterDock", "The fourth label name", nullptr));
        label_4->setText(QApplication::translate("ParameterDock", "Number:", nullptr));
        yellowLabelNumberLineEdit->setText(QApplication::translate("ParameterDock", "0", nullptr));
        label_40->setText(QString());
        blackRadioButton->setText(QString());
        blackLabelNameLineEdit->setPlaceholderText(QApplication::translate("ParameterDock", "The fifth label name", nullptr));
        label_5->setText(QApplication::translate("ParameterDock", "Number:", nullptr));
        blackLabelNumberLineEdit->setText(QApplication::translate("ParameterDock", "0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ParameterDock", "View", nullptr));
        groupBox_4->setTitle(QApplication::translate("ParameterDock", "Region information", nullptr));
        radioButton_is_circle_draw->setText(QApplication::translate("ParameterDock", "Circle", nullptr));
        radioButton_is_circle_draw_2->setText(QApplication::translate("ParameterDock", "polygon", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ParameterDock", "id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ParameterDock", "number", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ParameterDock", "Region", nullptr));
        groupBox_5->setTitle(QApplication::translate("ParameterDock", "Unprocessed biomarker information", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("ParameterDock", "biomarker", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParameterDock: public Ui_ParameterDock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETER_H
