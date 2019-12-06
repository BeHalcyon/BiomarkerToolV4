#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BiomakerTool.h"
#include "ParameterDock.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <QDebug>
#include <TiffReader.h>
#include "LocalGraphicsView.h"
#include "NavigationGraphicsView.h"
#include "GlobalGraphicsView.h"
#include <qstackedwidget.h>
#include "labeltableview.h"
#include "labeltablemodel.h"

struct Region
{
	QString number = 0;
	QString name = "Untitled";
};

class BiomakerTool : public QMainWindow
{
	Q_OBJECT

public:
	BiomakerTool(QWidget *parent = Q_NULLPTR);
	~BiomakerTool();
	void setNavigationBackground();
	void updateGlobalRects();
	void setGlobalGraphicsImage();
	void initListView();
public slots:
	
	void on_slotOpenImage_triggered();
	void on_slotExportMark_triggered();
	void on_slotExportNav_triggered();
	void on_slotExportPaths_triggered();

	void on_slotExportMarkedTiff_triggered();

	void on_slotImportMark_triggered();
	
	void on_slotImportPaths_triggered();
	void on_slotImportNav_triggered();
	void setShowImage(QPointF);
	void setNavigationChoosedImage(QPointF);
	void writeFile(QVector<GraphicsRectItem*>&, QString filename);

private:
	Ui::BiomakerToolClass ui;
	ParameterDock *parameterDock;
	LocalGraphicsView* local_graphics_view;
	GlobalGraphicsView* global_graphics_view;
	QStackedWidget* stackedWidget;
	LabelTableView* label_table_view;
	LabelTableModel* label_table_model;

	QPushButton* button_find_next_unchecked;
	QPushButton* button_save_biomarker;

	QGraphicsScene* graphicsScene;
	QGraphicsItem* graphicsItem;
	TiffReader* tiffReader;
	int sceneWidth = 0;
	int sceneHeight = 0;
	int tiffWidth = 0;
	int tiffHeight = 0;
	NavigationGraphicsView* navigationGraphicsView;
	QImage *bufImg;
	QImage *global_graphics_image;
	float navigationWidth;
	float navigationHeight;
	QRect tiffBoundingBox;
	QImage navigationSwapImage;

	bool is_rect_loaded_from_file = false;
	QMap<QGraphicsItem*, int> local_scene_item_map;
	QVector<QGraphicsItem*> local_scene_item_array;

	bool is_init_list_view_show = false;
	QMap<QGraphicsEllipseItem*, Region> circle_map;
	QMap<QGraphicsPathItem*, Region> polygon_map;

	//Debug
	QMap<QGraphicsPathItem*, QString> polygon_name_map;
};
