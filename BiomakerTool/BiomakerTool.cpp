#include "BiomakerTool.h"
#include <QRect>
#include <QTime>
#include <iostream>
#include <fstream>
#include <QStackedWidget>
#include <QRadioButton>
using namespace std;
BiomakerTool::BiomakerTool(QWidget *parent)
	: QMainWindow(parent)
{
	bufImg = 0;
	ui.setupUi(this);
	this->setWindowState(Qt::WindowMaximized);
	parameterDock = new ParameterDock(this);
	parameterDock->setFixedWidth(parameterDock->width());
	//parameterDock->ui.tableWidget->setFixedWidth(parameterDock->width() - 50);
	QDockWidget * parameterMainDock = new QDockWidget(tr("Parameter control"), this);
	parameterMainDock->setWidget(parameterDock);
	addDockWidget(Qt::LeftDockWidgetArea, parameterMainDock);

	navigationGraphicsView = new NavigationGraphicsView(parameterDock->width() - 10, parameterDock->width() - 10, this);
	QDockWidget *navagationMainDock = new QDockWidget(tr("Navagation view"), this);
	navagationMainDock->setWidget(navigationGraphicsView);
	addDockWidget(Qt::LeftDockWidgetArea, navagationMainDock);

	//graphicsScene = new QGraphicsScene();
	local_graphics_view = new LocalGraphicsView();
	global_graphics_view = new GlobalGraphicsView();
	stackedWidget = new QStackedWidget;
	//setCentralWidget(local_graphics_view);
	stackedWidget->addWidget(local_graphics_view);
	stackedWidget->addWidget(global_graphics_view);
	setCentralWidget(stackedWidget);

	label_table_model = nullptr;
	label_table_model = nullptr;


	polygon_map.clear();
	circle_map.clear();


	connect(ui.action_tif, SIGNAL(triggered()), this, SLOT(on_slotOpenImage_triggered()));
	connect(local_graphics_view, SIGNAL(startPointChanged(QPointF)), this, SLOT(setShowImage(QPointF)));
	connect(ui.action_export, SIGNAL(triggered()), this, SLOT(on_slotExportMark_triggered()));
	connect(ui.action_exportnav, SIGNAL(triggered()), this, SLOT(on_slotExportNav_triggered()));
	connect(ui.action_mark, SIGNAL(triggered()), this, SLOT(on_slotImportMark_triggered()));
	connect(ui.action_nav, SIGNAL(triggered()), this, SLOT(on_slotImportNav_triggered()));
	connect(ui.actionExport_paths, SIGNAL(triggered()), this, SLOT(on_slotExportPaths_triggered()));
	connect(ui.action_paths, SIGNAL(triggered()), this, SLOT(on_slotImportPaths_triggered()));

	connect(parameterDock->ui.zoomInPushButtom, SIGNAL(clicked()), local_graphics_view, SLOT(setZoomIn()));
	connect(parameterDock->ui.zoomOutPushButtom, SIGNAL(clicked()), local_graphics_view, SLOT(setZoomOut()));

	connect(local_graphics_view, SIGNAL(sendZoomInState(bool)), navigationGraphicsView, SLOT(setZoomInState(bool)));
	connect(local_graphics_view, SIGNAL(sendMakerNumber(QVector<QVector<int>>*, QVector<QVector<int>>*)), navigationGraphicsView, SLOT(setMakerNumber(QVector<QVector<int>>*, QVector<QVector<int>>*)));
	connect(local_graphics_view, SIGNAL(sendPenType(int)), navigationGraphicsView, SLOT(setPenType(int)));

	connect(parameterDock->ui.zoomOutPushButtom, SIGNAL(clicked()), local_graphics_view, SLOT(setZoomOut()));

	connect(parameterDock->ui.redRadioButton, SIGNAL(clicked()), local_graphics_view, SLOT(setRedPen()));
	connect(parameterDock->ui.greenRadioButton, SIGNAL(clicked()), local_graphics_view, SLOT(setGreenPen()));
	connect(parameterDock->ui.blueRadioButton, SIGNAL(clicked()), local_graphics_view, SLOT(setBluePen()));
	connect(parameterDock->ui.yellowRadioButton, SIGNAL(clicked()), local_graphics_view, SLOT(setYellowPen()));
	connect(parameterDock->ui.blackRadioButton, SIGNAL(clicked()), local_graphics_view, SLOT(setBlackPen()));

	connect(parameterDock->ui.radioButton_is_circle_draw, &QRadioButton::toggled, [this](bool state)
	{
		global_graphics_view->setCircleDrawState(state);
		std::cout << "The circle draw state is :" << state << std::endl;
	});

	connect(local_graphics_view, SIGNAL(sendRedLabelNumbers(int)), parameterDock, SLOT(setRedLabelText(int)));
	connect(local_graphics_view, SIGNAL(sendGreenLabelNumbers(int)), parameterDock, SLOT(setGreenLabelText(int)));
	connect(local_graphics_view, SIGNAL(sendBlueLabelNumbers(int)), parameterDock, SLOT(setBlueLabelText(int)));
	connect(local_graphics_view, SIGNAL(sendYellowLabelNumbers(int)), parameterDock, SLOT(setYellowLabelText(int)));
	connect(local_graphics_view, SIGNAL(sendBlackLabelNumbers(int)), parameterDock, SLOT(setBlackLabelText(int)));
	connect(parameterDock->ui.radioButton_is_local_view_choosed, &QRadioButton::toggled, [this](bool is_checked)
	{
		if (is_checked)
		{
			this->stackedWidget->setCurrentIndex(0);
			std::cout << "Local graphics view." << std::endl;
		}

		else
		{
			this->stackedWidget->setCurrentIndex(1);
			updateGlobalRects();
			std::cout << "Global graphics view." << std::endl;
		}

	});
	connect(global_graphics_view, &GlobalGraphicsView::sendCircleNumberMap, 
		[this](const QMap<QGraphicsEllipseItem*, QString>& circle_number_map)
	{
		static int cnt = 0;
		for (auto i = 0; i < this->parameterDock->ui.tableWidget->rowCount();i++)
		{
			if (cnt==0)
			{
				this->parameterDock->ui.tableWidget->setItem(i, 0, new QTableWidgetItem(""));
				this->parameterDock->ui.tableWidget->setItem(i, 1, new QTableWidgetItem(""));
				
			}
			else
			{
				auto buf_item = this->parameterDock->ui.tableWidget->takeItem(i, 0);
				buf_item->setText("");
				this->parameterDock->ui.tableWidget->setItem(i, 0, buf_item);

				buf_item = this->parameterDock->ui.tableWidget->takeItem(i, 1);
				buf_item->setText("");
				this->parameterDock->ui.tableWidget->setItem(i, 1, buf_item);
			}
			
		}
		cnt = 1;

		int cluster_id = 1;
		int sum = 0;
		auto i = circle_number_map.constBegin();
		while (i != circle_number_map.constEnd()) {
			auto buf_item = this->parameterDock->ui.tableWidget->takeItem(cluster_id, 0);
			buf_item->setText(QString("%1").arg(cluster_id));
			this->parameterDock->ui.tableWidget->setItem(cluster_id, 0, buf_item);

			buf_item = this->parameterDock->ui.tableWidget->takeItem(cluster_id, 1);
			buf_item->setText(QString("%1").arg(i.value()));
			this->parameterDock->ui.tableWidget->setItem(cluster_id, 1, new QTableWidgetItem(QString("%1").arg(i.value())));

			sum += i.value().split(",")[0].toInt();
			++i;
			++cluster_id;
		}
		this->parameterDock->ui.tableWidget->setItem(0, 0, new QTableWidgetItem("sum"));
		this->parameterDock->ui.tableWidget->setItem(0, 1, new QTableWidgetItem(QString("%1").arg(sum)));

	});

	connect(global_graphics_view, &GlobalGraphicsView::sendShapeNumberMap, [this]
		(QMap<QGraphicsEllipseItem*, QString>& circle_number_map, 
			QMap<QGraphicsPathItem*, QString>& polygon_number_map)
	{
		//this->circle_map = circle_number_map;
		//this->polygon_map = polygon_number_map;
		//this->polygon_map.clear();

		//circle
		for(auto i1=circle_number_map.begin();i1!=circle_number_map.end();++i1)
		{
			if (!circle_map.contains(i1.key()))
			{
				circle_map[i1.key()] = { i1.value(), QString("Untitled") };
				qDebug() << i1.value();
			}
			else
			{
				circle_map[i1.key()] = { i1.value(),  circle_map[i1.key()].name };
			}
		}
		//polgyon
		for(auto i1=polygon_number_map.begin();i1!=polygon_number_map.end();++i1)
		{
			if(!polygon_map.contains(i1.key()))
			{
				polygon_map[i1.key()] = { i1.value(), QString("Untitled") };
				qDebug() << i1.value();
			}
			else
			{
				polygon_map[i1.key()] = { i1.value(),  polygon_map[i1.key()].name};
			}
		}

		static int cnt = 0;
		for (auto i = 0; i < this->parameterDock->ui.tableWidget->rowCount(); i++)
		{
			if (cnt == 0)
			{
				this->parameterDock->ui.tableWidget->setItem(i, 0, new QTableWidgetItem(""));
				this->parameterDock->ui.tableWidget->setItem(i, 1, new QTableWidgetItem(""));
			}
			else
			{
				auto buf_item = this->parameterDock->ui.tableWidget->takeItem(i, 0);
				buf_item->setText("");
				this->parameterDock->ui.tableWidget->setItem(i, 0, buf_item);

				buf_item = this->parameterDock->ui.tableWidget->takeItem(i, 1);
				buf_item->setText("");
				this->parameterDock->ui.tableWidget->setItem(i, 1, buf_item);
			}

		}
		cnt = 1;

		int cluster_id = 1;
		int sum = 0;
		auto i = circle_number_map.constBegin();
		while (i != circle_number_map.constEnd()) {
			auto buf_item = this->parameterDock->ui.tableWidget->takeItem(cluster_id, 0);
			//buf_item->setText(QString("circle_%1").arg(cluster_id));
			buf_item->setText(circle_map[i.key()].name);
			this->parameterDock->ui.tableWidget->setItem(cluster_id, 0, buf_item);

			buf_item = this->parameterDock->ui.tableWidget->takeItem(cluster_id, 1);
			//buf_item->setText(QString("%1").arg(i.value()));
			buf_item->setText(QString("%1").arg(circle_map[i.key()].number));
			//this->parameterDock->ui.tableWidget->setItem(cluster_id, 1, new QTableWidgetItem(QString("%1").arg(i.value())));
			this->parameterDock->ui.tableWidget->setItem(cluster_id, 1, new QTableWidgetItem(QString("%1").arg(circle_map[i.key()].number)));

			sum += i.value().split(",")[0].toInt();
			++i;
			++cluster_id;
		}

		auto num = 1;
		auto j = polygon_number_map.begin();
		while (j != polygon_number_map.end()) {
			auto buf_item = this->parameterDock->ui.tableWidget->takeItem(cluster_id, 0);
			//buf_item->setText(QString("polygon_%1").arg(num));
			buf_item->setText(polygon_map[j.key()].name);
			this->parameterDock->ui.tableWidget->setItem(cluster_id, 0, buf_item);

			buf_item = this->parameterDock->ui.tableWidget->takeItem(cluster_id, 1);
			//buf_item->setText(QString("%1").arg(j.value()));
			buf_item->setText(QString("%1").arg(polygon_map[j.key()].number));
			//this->parameterDock->ui.tableWidget->setItem(cluster_id, 1, new QTableWidgetItem(QString("%1").arg(j.value())));
			this->parameterDock->ui.tableWidget->setItem(cluster_id, 1, new QTableWidgetItem(QString("%1").arg(polygon_map[j.key()].number)));

			sum += j.value().split(",")[0].toInt();
			++j;
			++cluster_id;
			++num;
		}

		this->parameterDock->ui.tableWidget->setItem(0, 0, new QTableWidgetItem("sum"));
		this->parameterDock->ui.tableWidget->setItem(0, 1, new QTableWidgetItem(QString("%1").arg(sum)));

	});
	//数据高亮
	connect(global_graphics_view, &GlobalGraphicsView::sendSelectedShape, [this]
		(const QMap<QGraphicsEllipseItem*, QString>& circle_number_map,
			const QMap<QGraphicsPathItem*, QString>& polygon_number_map, QGraphicsItem* selectedItem)
	{
		if (selectedItem->type() == QGraphicsEllipseItem::Type)
		{
			auto buf_item = qgraphicsitem_cast<QGraphicsEllipseItem*>(selectedItem);
			int cluster_id = 1;
			auto i = circle_number_map.constBegin();
			while (i != circle_number_map.constEnd()) {
				if (buf_item == i.key())
				{
					this->parameterDock->ui.tableWidget->selectRow(cluster_id);
					break;
				}
				++i;
				++cluster_id;
			}
		}
		else
		{
			auto buf_item = qgraphicsitem_cast<QGraphicsPathItem*>(selectedItem);
			int cluster_id = 1 + circle_number_map.size();
			auto i = polygon_number_map.constBegin();
			while (i != polygon_number_map.constEnd()) {
				if (buf_item == i.key())
				{
					this->parameterDock->ui.tableWidget->selectRow(cluster_id);
					break;
				}
				++i;
				++cluster_id;
			}
		}
	});
	//选择标注体
	connect(parameterDock->ui.tableWidget, &QTableWidget::cellClicked, [this](int row, int column)
	{
		if (row > circle_map.size() + polygon_map.size() || row < 1) return;
		//auto buf_item = this->parameterDock->ui.tableWidget->itemAt(row, 0);

		if (row <= circle_map.size())
		{
			int cluster_id = 1;
			auto i = circle_map.constBegin();
			while (i != circle_map.constEnd()) {
				if (cluster_id==row)
				{
					global_graphics_view->setSelectedItem(i.key());
					//return;
					break;
				}
				++i;
				++cluster_id;
			}

			i = circle_map.begin();
			int buffer_id = 1;
			while (i != circle_map.end()) {
				circle_map[i.key()].name = this->parameterDock->ui.tableWidget->item(buffer_id, 0)->text();
				++i;
				++buffer_id;
			}

		}
		else
		{
			row -= circle_map.size();
			auto j = polygon_map.begin();
			int cluster_id = 1;
			while (j != polygon_map.end()) {
				if (cluster_id == row)
				{
					global_graphics_view->setSelectedItem(j.key());
					//return;
					break;
				}
				++j;
				++cluster_id;
			}

			j = polygon_map.begin();
			int buffer_id = circle_map.size()+1;
			while (j != polygon_map.end()) {
				polygon_map[j.key()].name = this->parameterDock->ui.tableWidget->item(buffer_id, 0)->text();
				++j;
				++buffer_id;
			}
			
		}
		//std::cout << "?? " << polygon_map.size() << std::endl;
	});


	connect(local_graphics_view, &LocalGraphicsView::sendPolygon, global_graphics_view, &GlobalGraphicsView::getPolygon);

	connect(parameterDock->ui.checkBox_region_painting, &QCheckBox::stateChanged,
		local_graphics_view, &LocalGraphicsView::setRegionState);

	connect(local_graphics_view, &LocalGraphicsView::sendLocalPolygon, global_graphics_view, &GlobalGraphicsView::getLocalPolygon);
	connect(global_graphics_view, &GlobalGraphicsView::sendRemoveCommand,
		local_graphics_view, &LocalGraphicsView::getRemovePolygon);
	connect(global_graphics_view, &GlobalGraphicsView::sendNewPolygonToLocalGraphicsView,
		local_graphics_view, &LocalGraphicsView::setNewPolygonFromGlobalGraphicsView);
	
}
void BiomakerTool::on_slotImportNav_triggered() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Navigation File", "./workspace", tr("Navigation (*.nav )"));
	if (fileName.isEmpty()) {
		return;
	}
	ifstream filei;
	filei.open(fileName.toStdString());
	int navHNumber, navWNumber;
	filei >> navHNumber >> navWNumber;
	if (local_graphics_view->zoomOutMakerNumber[0].size() != navHNumber ||
		local_graphics_view->zoomOutMakerNumber[0][0].size() != navWNumber) {
		qDebug() << "Load File Error!!!";
		filei.close();
		return;
	}
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < navHNumber; i++) {
			for (int j = 0; j < navWNumber; j++) {
				int count;
				filei >> count;
				local_graphics_view->zoomOutMakerNumber[k][i][j] += count;
			}
		}
	}
	emit local_graphics_view->sendMakerNumber(local_graphics_view->zoomOutMakerNumber, local_graphics_view->zoomInMakerNumber);
	filei.close();

}
void BiomakerTool::on_slotImportMark_triggered() {

	QStringList fileNames = QFileDialog::getOpenFileNames(this, "Open Mark File", "./workspace", tr("Marks (*.mark )"));
	if (fileNames.isEmpty()) {
		return;
	}
	QPen pen[5];
	pen[0] = QPen(Qt::red, 1.5, Qt::SolidLine, Qt::FlatCap);
	pen[1] = QPen(Qt::green, 1.5, Qt::SolidLine, Qt::FlatCap);
	pen[2] = QPen(Qt::blue, 1.5, Qt::SolidLine, Qt::FlatCap);
	pen[3] = QPen(Qt::yellow, 1.5, Qt::SolidLine, Qt::FlatCap);
	pen[4] = QPen(Qt::black, 1.5, Qt::SolidLine, Qt::FlatCap);


	auto items = local_graphics_view->graphicsScene->items();

	for (auto item : items)
	{
		if (item->type() == GraphicsRectItem::Type)
		{
			local_graphics_view->graphicsScene->removeItem(item);
			delete item;
		}
	}

	for (int i = 0; i < fileNames.size(); i++) {
		
		//create new rectItem for graphicview
		ifstream filei;
		filei.open((fileNames.at(i).toStdString()));
		int itemNumber = 0;
		int penType = 0;
		filei >> itemNumber >> penType;
		//ofstream fileo("./workspace/test.mark");
		int scene_width = local_graphics_view->width();
		int scene_height = local_graphics_view->height();
		
		int sx, sy, x, y, w, h;
		//Debug 20190516 扩大兼容性
		bool checked_state = true;
		for (int i = 0; i < itemNumber; i++) {

			filei >> sx >> sy >> x >> y >> w >> h;
			//qDebug() << sx << sy << x << y << w << h;
			QPoint startP(sx, sy);
			
			//兼容前后两版本的数据
			QPoint topleft(0, 0);

			/*if (!((x >= 0 && x < 3) && y == 0))
			{
				topleft = QPoint(x, y);
				checked_state = false;
			}
			else
			{
				checked_state = true;
			}*/

			
			QPoint offset(scene_width / 2, scene_height / 2);
			QPoint global_top_left = startP + topleft;
			QPoint global_start_point = global_top_left - offset;
			if (global_start_point.x()<0)
			{
				auto offset_x = global_start_point.x(); //负数
				global_start_point.setX(0);
				offset.setX(offset.x() + offset_x);
			}
			else if (global_start_point.x() + scene_width>=tiffWidth)
			{
				auto offset_x = global_start_point.x();
				global_start_point.setX(tiffWidth - scene_width - 1);
				offset_x = global_start_point.x() - offset_x; //负数
				offset.setX(offset.x() - offset_x);
			}
			if (global_start_point.y()<0)
			{
				auto offset_y = global_start_point.y();
				global_start_point.setY(0);
				offset.setY(offset.y() + offset_y);
			}
			else if (global_start_point.y() + scene_height >= tiffHeight)
			{
				auto offset_y = global_start_point.y();
				global_start_point.setY(tiffHeight - scene_height - 1);
				offset_y = global_start_point.y() - offset_y;
				offset.setY(offset.y() - offset_y);
			}
			//GraphicsRectItem* item = new GraphicsRectItem(startP, penType);
			GraphicsRectItem* item = new GraphicsRectItem(global_start_point, penType);

			//item->localTopLeft = topleft;
			item->localTopLeft = offset;
			if (checked_state)
			{
				if (x == 0)
				{
					item->check_state = Qt::Unchecked;
					item->setPen(pen[0]);
				}
				//2 错误 绿色
				else if (x == 2)
				{
					item->check_state = Qt::PartiallyChecked;
					item->setPen(pen[1]);
				}
				//1 正确 黑色
				else if (x == 1)
				{
					item->check_state = Qt::Checked;
					item->setPen(pen[4]);
				}
				else
				{
					QMessageBox msgBox;
					msgBox.setText("Error mark format. This version is not compatible with loaded mark file. You can load this file in lower version.");
					msgBox.exec();
					return;
				}
			}
			else
			{
				item->check_state = Qt::Unchecked;
				item->setPen(pen[0]);
			}
			//item->setRect(QRect(topleft+startP-local_graphics_view->startPoint,QSize(w,h)));
			item->setRect(QRect(global_top_left - local_graphics_view->startPoint, QSize(w, h)));
			//item->setPen(pen[penType-1]);
			local_graphics_view->graphicsScene->addItem(item);

			//fileo << global_start_point.x() << " " << global_start_point.y() << " " << item->localTopLeft.x() << " " << item->localTopLeft.y() << " " << w << " " << h << endl;
		}
		//fileo.close();
		filei.close();
		if (penType == 1) {
			local_graphics_view->redLabelNumber = 0;
			local_graphics_view->redLabelNumber += itemNumber;
			emit local_graphics_view->sendRedLabelNumbers(local_graphics_view->redLabelNumber);
		}
		else if (penType == 2) {
			local_graphics_view->greenLabelNumber = 0;
			local_graphics_view->greenLabelNumber += itemNumber;
			emit local_graphics_view->sendGreenLabelNumbers(local_graphics_view->greenLabelNumber);
		}
		else if (penType == 3) {
			local_graphics_view->blueLabelNumber = 0;
			local_graphics_view->blueLabelNumber += itemNumber;
			emit local_graphics_view->sendBlueLabelNumbers(local_graphics_view->blueLabelNumber);
		}
		else if (penType == 4) {
			local_graphics_view->yellowLabelNumber = 0;
			local_graphics_view->yellowLabelNumber += itemNumber;
			emit local_graphics_view->sendYellowLabelNumbers(local_graphics_view->yellowLabelNumber);
		}
		else if (penType == 5) {
			local_graphics_view->blackLabelNumber = 0;
			local_graphics_view->blackLabelNumber += itemNumber;
			emit local_graphics_view->sendBlackLabelNumbers(local_graphics_view->blackLabelNumber);
		}
		
	}
	updateGlobalRects();
	is_rect_loaded_from_file = true;
	local_graphics_view->setRectLoadedState(is_rect_loaded_from_file);
	//将对应的矩形区域数据存储到全局Map上
	local_scene_item_map.clear();
	local_scene_item_array.clear();
	auto local_items = local_graphics_view->graphicsScene->items();
	auto cluster_id = 0;
	for (auto local_item : local_items)
	{
		if (local_item->type() == GraphicsRectItem::Type) {
			local_scene_item_array.push_back(local_item);
			local_scene_item_map[local_item] = cluster_id++;
		}
	}
	//初始化listview视图
	initListView();
	is_init_list_view_show = true;
}
void BiomakerTool::on_slotImportPaths_triggered() {



	QString fileName = QFileDialog::getOpenFileName(this, "Open Paths File", "./workspace", tr("Paths (*.paths )"));
	if(fileName.isEmpty())
	{
		return;
	}

	if (!global_graphics_view)
	{
		QMessageBox msgBox;
		msgBox.setText("Please load marks first.");
		msgBox.exec();
		return;
	}
	ifstream filei;
	filei.open(fileName.toStdString());
	//polygon
	{
		//删除前面导入的数据
		for (auto item : global_graphics_view->graphicsScene->items()) {
			if (item->type() == QGraphicsPathItem::Type) {
				auto buf_item = qgraphicsitem_cast<QGraphicsPathItem*>(item);
				global_graphics_view->graphicsScene->removeItem(buf_item);
			}
		}
		int path_number, buf_length;
		double buf_x, buf_y;
		
		filei >> path_number;
		QMap<QGraphicsPathItem*, int> buf_map;
		for (auto i = 0; i < path_number; i++)
		{
			auto cur_ploygon = new QGraphicsPathItem();
			cur_ploygon->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::FlatCap));
			string buf_name;
			filei >> buf_length>>buf_name;
			filei >> buf_x >> buf_y;
			//Debug 20190727
			//QPointF start_point(buf_x / tiffReader->getGlobalFactor(), buf_y / tiffReader->getGlobalFactor());
			QPointF start_point(buf_x/ tiffReader->getGlobalWidthFactor(), buf_y/ tiffReader->getGlobalHeightFactor());
			auto cur_paint_path = QPainterPath();
			cur_paint_path.moveTo(start_point);

			for (auto j = 0; j < buf_length - 1; j++)
			{
				filei >> buf_x >> buf_y;
				//Debug 20190727
				//QPointF buf_point(buf_x / tiffReader->getGlobalFactor(), buf_y / tiffReader->getGlobalFactor());
				QPointF buf_point(buf_x / tiffReader->getGlobalWidthFactor(), buf_y / tiffReader->getGlobalHeightFactor());
				cur_paint_path.lineTo(buf_point);
			}
			cur_paint_path.lineTo(start_point);
			cur_ploygon->setPath(cur_paint_path);
			//buf_map[cur_ploygon] = 0;
			//global_graphics_view->graphicsScene->addItem(cur_ploygon);

			//将区域导入到local视图中
			//local_graphics_view->setNewPolygon(cur_paint_path, tiffReader->getGlobalFactor());
			local_graphics_view->setNewPolygon(cur_paint_path, tiffReader->getGlobalWidthFactor(),tiffReader->getGlobalHeightFactor());


			//找到第一个未命名的就是
			auto buf_path = global_graphics_view->exportPathItem();
			int buf_id = 1;


			auto buf_polygon = global_graphics_view->getCurPolgyon();

			polygon_map[buf_polygon].name = QString(buf_name.c_str());

			for(auto i= polygon_map.begin();i!=polygon_map.end();++i)
			{
				if(buf_polygon==i.key())
				{
					auto buf_item = this->parameterDock->ui.tableWidget->takeItem(circle_map.size() + buf_id, 0);
					buf_item->setText(QString(buf_name.c_str()));
					this->parameterDock->ui.tableWidget->setItem(circle_map.size() + buf_id, 0, buf_item);
					qDebug() << QString(buf_name.c_str());
					break;
				}
				buf_id++;
			}

			

			// for(auto i = buf_path.begin();i!=buf_path.end();++i)
			// {
			// 	if(polygon_map[i.key()].name=="Untitled")
			// 	{
			// 		polygon_map[i.key()].name = QString(buf_name.c_str());
			// 		qDebug() << polygon_map[i.key()].name<< circle_map.size() + buf_id;
			// 		//this->parameterDock->ui.tableWidget->item(circle_map.size() + buf_id, 0)->setText(QString(buf_name.c_str()));
			// 		
			// 		auto buf_item = this->parameterDock->ui.tableWidget->takeItem(circle_map.size() + buf_id, 0);
			// 		buf_item->setText(QString(buf_name.c_str()));
			// 		this->parameterDock->ui.tableWidget->setItem(circle_map.size() + buf_id, 0, buf_item);
			// 		break;
			// 	}
			// 	buf_id++;
			// }
			// for (auto i = buf_path.begin(); i != buf_path.end(); ++i)
			// {
			// 	qDebug() << polygon_map[i.key()].name;
			//}
		}
	}
	//circle
	//TODO
	{
		//删除前面导入的数据
		for (auto item : global_graphics_view->graphicsScene->items()) {
			if (item->type() == QGraphicsEllipseItem::Type) {
				auto buf_item = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
				auto rect = buf_item->rect();
				//if (rect.width() == 2)
				//{
					global_graphics_view->graphicsScene->removeItem(item);
					delete item;
				//}
			}
		}

		int circle_number;
		double buf_x, buf_y, buf_w, buf_h;
		filei >> circle_number;
		string buf_name;
		for (auto i = 0; i < circle_number; i++)
		{
			filei>> buf_name >> buf_x >> buf_y >> buf_w >> buf_h;
			//删除前面导入的数据
			auto cur_circle = new QGraphicsEllipseItem(QRectF(QPointF(buf_x / tiffReader->getGlobalWidthFactor(),
				buf_y / tiffReader->getGlobalHeightFactor()), 
				QSizeF(buf_w / tiffReader->getGlobalFactor(), buf_h / tiffReader->getGlobalWidthFactor())));
			cur_circle->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::FlatCap));
			//circle_items.push_back(cur_circle);
			global_graphics_view->graphicsScene->addItem(cur_circle);
			global_graphics_view->updataCircleMarkerNumber();

			//找到第一个未命名的就是
			int buf_id = 1;
			//auto buf_polygon = global_graphics_view->getCurCircle();

			circle_map[cur_circle].name = QString(buf_name.c_str());

			for (auto j = circle_map.begin(); j != circle_map.end(); ++j)
			{
				if (cur_circle == j.key())
				{
					auto buf_item = this->parameterDock->ui.tableWidget->takeItem(buf_id, 0);
					buf_item->setText(QString(buf_name.c_str()));
					this->parameterDock->ui.tableWidget->setItem( buf_id, 0, buf_item);
					qDebug() << QString(buf_name.c_str());
					break;
				}
				buf_id++;
			}
		}
		global_graphics_view->updataCircleMarkerNumber2();
	}

	filei.close();
	std::cout << "The paths file has been loaded." << std::endl;

	updateGlobalRects();
}
void BiomakerTool::on_slotExportNav_triggered() {
	QString exportPath = "./Result/";
	QString exportName;
	QImage outputImage;

	QList<QGraphicsItem*> items = local_graphics_view->graphicsScene->items();

	ofstream outfile;
	outfile.open("./workspace/navigation.nav");
	if (local_graphics_view->zoomOutMakerNumber) {
		outfile << local_graphics_view->zoomOutMakerNumber[0].size() << " " << local_graphics_view->zoomOutMakerNumber[0][0].size() << endl;
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < local_graphics_view->zoomOutMakerNumber[k].size(); i++) {
				for (int j = 0; j < local_graphics_view->zoomOutMakerNumber[k][i].size(); j++) {
					outfile << local_graphics_view->zoomOutMakerNumber[k][i][j] << endl;
				}
			}
		}
	}
	outfile.close();
}
void BiomakerTool::on_slotExportMark_triggered() {

	QString exportPath = "./Result/";
	QString exportName;
	QImage outputImage;
	//QVector<QRect>& captureRects = CaptureGraphicsItem::captureRects;
	int& loadedNum = CaptureGraphicsItem::loadedNum;

	QList<QGraphicsItem*> items = local_graphics_view->graphicsScene->items();

	bool isDebug = false;
	if (isDebug) {
		uint32* tiffData = tiffReader->getRawData();
		int nameindex = 0;
		for (int i = 0; i < items.size(); i++){
			QGraphicsItem *item = items[i];
			if (item->type() == GraphicsRectItem::Type) {
				GraphicsRectItem *rect = qgraphicsitem_cast<GraphicsRectItem*>(item);
				QRect captureRect = rect->rect().toAlignedRect();
				if (captureRect.width() <= 5 || captureRect.height() <= 5) continue;
				exportName = QString("%1.bmp").arg(nameindex++);
				outputImage = QImage(captureRect.width(), captureRect.height(), QImage::Format_RGB32);
				QPoint topLeft;
				if (rect->localTopLeft == QPoint(-1, -1))
					topLeft = captureRect.topLeft() + rect->startPoint;
				else 
					topLeft = rect->localTopLeft + rect->startPoint;

				uint32* testData = tiffReader->getLocalImage(topLeft, captureRect.height(), captureRect.width());
				for (tstrip_t i = 0; i < captureRect.height(); i++) {
					for (tstrip_t j = 0; j < captureRect.width(); j++) {
						outputImage.setPixel(j, i, testData[i*captureRect.width() + j]);
					}
				}

				//tstrip_t baseIndex = tiffWidth*topLeft.y() + topLeft.x();
				//for (tstrip_t i = 0; i < captureRect.height(); i++) {
				//	for (tstrip_t j = 0; j < captureRect.width(); j++) {
				//		outputImage.setPixel(j, i, tiffData[baseIndex + i*tiffWidth + +j]);
				//	}
				//}
				QImage swapImage = outputImage.rgbSwapped();
				swapImage.save(exportPath + exportName);
				//outputImage.invertPixels();
				//outputImage.save(exportPath + exportName);
			}
		}
	}
	//isDebug = false;
	//输出到文件中
	/************************************************************************/
	/* 
	xxx.dat(txt file)	xxx is the name of the first label
	----------------------------------
	line 1: The number of the first label(corresponding to the number of the red rectangles or the first non-empty label): r
			And the penType p
	
	line 2 to line (2+r):	The rectangles whoes coordinates in accord with the origin tif image. 
							For each line, the arrangement is: x y w h
							Where x is the x value of the left top coordinate point of a rectangle,
							y is the y value of the left top coordinate point of the rectangle,
							w is the width, and h is the height.

	An example in xxx.dat file:
	5 1
	41 20 2 4
	12 52 2 4
	52 99 2 4
	85 52 2 4
	41 99 2 4
	---------------------------------------


	xxx.dat(txt file)	xxx is the name of the second lable
	---------------------------------------
	line 1:	The number of the first label(as mentioned above)

	line 2:	as mentioned above

	*/
	/************************************************************************/
	if (!isDebug) {
		//ofstream outfile;
		//outfile.open("./biomaker_result.dat");
		if (!is_rect_loaded_from_file)
		{
			int redLabelNumber = 0;
			int greenLabelNumber = 0;
			int blueLabelNumber = 0;
			int yellowLabelNumber = 0;
			int blackLabelNumber = 0;
			QVector<GraphicsRectItem*> redRectItems;
			QVector<GraphicsRectItem*> greenRectItems;
			QVector<GraphicsRectItem*> blueRectItems;
			QVector<GraphicsRectItem*> yellowRectItems;
			QVector<GraphicsRectItem*> blackRectItems;
			for each (QGraphicsItem* item in items)
			{
				if (item->type() == GraphicsRectItem::Type) {
					GraphicsRectItem *rect = qgraphicsitem_cast<GraphicsRectItem*>(item);
					QRect captureRect = rect->rect().toAlignedRect();
					if (captureRect.width() <= 5 || captureRect.height() <= 5) continue;
					if (rect->penType == 1) {
						redLabelNumber++;
						redRectItems.push_back(rect);
					}
					else if (rect->penType == 2) {
						greenLabelNumber++;
						greenRectItems.push_back(rect);
					}
					else if (rect->penType == 3){
						blueLabelNumber++;
						blueRectItems.push_back(rect);
					}
					else if (rect->penType == 4) {
						yellowLabelNumber++;
						yellowRectItems.push_back(rect);
					}
					else {
						blackLabelNumber++;
						blackRectItems.push_back(rect);
					}
				}
			}
			//qDebug() << redLabelNumber << greenLabelNumber << blueLabelNumber << yellowLabelNumber << blackLabelNumber << endl;
			//只记录为不为空的矩形
			writeFile(redRectItems, parameterDock->ui.redLabelNameLineEdit->text());
			writeFile(greenRectItems, parameterDock->ui.greenLabelNameLineEdit->text());
			writeFile(blueRectItems, parameterDock->ui.blueLabelNameLineEdit->text());
			writeFile(yellowRectItems, parameterDock->ui.yellowLabelNameLineEdit->text());
			writeFile(blackRectItems, parameterDock->ui.blackLabelNameLineEdit->text());
			//qDebug() << parameterDock->ui.redLabelNameLineEdit->text();
			//qDebug() << parameterDock->ui.greenLabelNameLineEdit->text();
			//qDebug() << parameterDock->ui.blueLabelNameLineEdit->text();
			//qDebug() << parameterDock->ui.yellowLabelNameLineEdit->text();
			//qDebug() << parameterDock->ui.blackLabelNameLineEdit->text();

			QMessageBox msgBox;
			msgBox.setText("Mark file has been saved.");
			msgBox.exec();
		}
		else
		{
			//不需要导出数据
			//提示保存成功
			QMessageBox msgBox;
			msgBox.setText("Please export data in biomarker view.");
			msgBox.exec();
		}
	}
}
void BiomakerTool::on_slotExportPaths_triggered()
{
	auto paths = global_graphics_view->exportPathItem();
	auto number = paths.size();

	QMapIterator<QGraphicsPathItem*, QString> i(paths);
	ofstream outfile;
	outfile.open("./workspace/paths.paths");
	outfile << number  << endl;
	
	while (i.hasNext()) {
		i.next();
		auto buf_path = i.key()->path();

		outfile << buf_path.elementCount()<< " " << polygon_map[i.key()].name.toStdString()<<endl;
		for(auto j=0;j<buf_path.elementCount();j++)
		{
			QPointF pt = buf_path.elementAt(j); //get the value of the point at index i
			//Debug 20190727
			//outfile << pt.x()*tiffReader->getGlobalFactor() << " " << pt.y()*tiffReader->getGlobalFactor() << " ";
			outfile << pt.x()*tiffReader->getGlobalWidthFactor() << " " << pt.y()*tiffReader->getGlobalHeightFactor() << " ";
		}
		outfile << endl;
	}

	auto circles = global_graphics_view->exportCircleItem();

	QMapIterator<QGraphicsEllipseItem*, QString> j(circles);
	number = circles.size();
	outfile << number << endl;
	while (j.hasNext()) {
		j.next();
		auto buf_rect = j.key()->rect();
		auto buf_name = circle_map[j.key()].name.toStdString();
		//Debug 20190727
		//outfile << buf_rect.topLeft().x()*tiffReader->getGlobalFactor() << " " << buf_rect.topLeft().y()*tiffReader->getGlobalFactor() << " " << buf_rect.width()*tiffReader->getGlobalFactor() << " " << buf_rect.height()*tiffReader->getGlobalFactor() << endl;
		outfile<< buf_name <<" " << buf_rect.topLeft().x()*tiffReader->getGlobalWidthFactor() << " "<< buf_rect.topLeft().y()*tiffReader->getGlobalHeightFactor() <<" "
		<<buf_rect.width()*tiffReader->getGlobalWidthFactor() <<" "<<buf_rect.height()*tiffReader->getGlobalHeightFactor() <<endl;
	}
	outfile.close();
	std::cout << "The paths have been saved." << std::endl;
}

void BiomakerTool::on_slotExportMarkedTiff_triggered()
{
	const auto image_height = tiffReader->getHeight();
	const auto image_width = tiffReader->getWidth();
	//uint32* image_data = tiffReader->getGlobalGraphicsImage();
	uint32* image_data = tiffReader->getLocalImage(QPoint(0, 0), image_height, image_width);
	QImage image(reinterpret_cast<uchar*>(image_data), image_width, image_height, QImage::Format_RGB32);

	//_TIFFfree(image_data);

	// for(auto i=0;i<image_height;i++)
	// {
	// 	for(auto j=0;j<image_width;j++)
	// 	{
	// 		image.setPixel(j, i, image_data[i*image_width + j]);
	// 	}
	// }

	auto items = local_graphics_view->graphicsScene->items();

	double alpha = 0.5;
	for (auto item : items)
	{
		if (item->type() == GraphicsRectItem::Type)
		{
			auto cur_item = dynamic_cast<GraphicsRectItem*>(item);
			const auto & start_point = cur_item->startPoint;
			const auto global_topleft = cur_item->localTopLeft + start_point;

			auto foreground_color = cur_item->pen().color();

			auto rect = cur_item->rect();

			for(auto i= global_topleft.x();i< global_topleft.x() + rect.width();i++)
			{
				for (auto j = global_topleft.y(); j < global_topleft.y() + rect.height(); j++)
				{
					auto background_color = image.pixelColor(i, j);

					background_color.setRgb((alpha*background_color.red() + (1-alpha) * foreground_color.red())/ 2,
						(alpha*background_color.green() + (1 - alpha) *foreground_color.green())/ 2,
						(alpha*background_color.blue() + (1 - alpha) *foreground_color.blue() )/ 2);

					image.setPixelColor(i, j, background_color);
				}
			}

		}
	}

	image.rgbSwapped().save("./workspace/export_png.png",nullptr);
	qDebug() << "The tiff file has been saved.";

	_TIFFfree(image_data);
}

void BiomakerTool::writeFile(QVector<GraphicsRectItem*>& rectItems, QString qfilename) {
	if (!rectItems.isEmpty()) {
		ofstream outfile;
		QString filename = qfilename;
		if (qfilename.isNull()||qfilename.isEmpty()||qfilename.length()<1) {
			filename = QString("label%1").arg(rectItems[0]->penType);
		}
		outfile.open("./workspace/" + filename.toStdString() + ".mark");
		outfile << rectItems.size() <<" "<<rectItems[0]->penType<< endl;
		for (int i = 0; i < rectItems.size(); i++) {
			QRect captureRect = rectItems[i]->rect().toAlignedRect();

			if (rectItems[i]->localTopLeft != QPoint(-1,-1))
				//Debug 20190416
				//outfile << rectItems[i]->startPoint.x()<<" "<<rectItems[i]->startPoint.y()
				//	<< " " << rectItems[i]->localTopLeft.x() << " " << rectItems[i]->localTopLeft.y() << " " << captureRect.width() << " " << captureRect.height() << endl;
				outfile << rectItems[i]->startPoint.x() + rectItems[i]->localTopLeft.x() << " " << rectItems[i]->startPoint.y() + rectItems[i]->localTopLeft.y()
					<< " " << 0 << " " << 0 << " " << captureRect.width() << " " << captureRect.height() << endl;

			else {
				//Debug 20190416
				//outfile << rectItems[i]->startPoint.x() << " " << rectItems[i]->startPoint.y()
				//	<< " " << captureRect.topLeft().x() << " " << captureRect.topLeft().y() << " " << captureRect.width() << " " << captureRect.height() << endl;
				outfile << rectItems[i]->startPoint.x() + captureRect.topLeft().x() << " " << rectItems[i]->startPoint.y() + captureRect.topLeft().y()
						<< " " << 0 << " " << 0 << " " << captureRect.width() << " " << captureRect.height() << endl;

			}
		}
		outfile.close();
	}
}
BiomakerTool::~BiomakerTool() {
	//delete tiffReader;
}
void BiomakerTool::setNavigationBackground() {

	float navigationGraphicsViewWidth = parameterDock->width() - 10;
	float navigationGraphicsViewHeight = (parameterDock->width() - 10)*tiffHeight*1.0f / tiffWidth;

	navigationGraphicsView->setFixedWidth(navigationGraphicsViewWidth);
	float sclarFactor = sceneWidth*1.0f / tiffWidth;
	navigationGraphicsView->setFixedHeight(navigationGraphicsViewHeight);
	
	//QGraphicsView* navigationView = navigationDock->ui.local_graphics_view;
	uint32* tiffData = tiffReader->getRawData();

	navigationWidth = navigationGraphicsViewWidth;
	navigationHeight = navigationGraphicsViewHeight;
	
	int xblocklen = tiffWidth / navigationWidth;
	int yblocklen = tiffHeight / navigationHeight;

	uint32* navigationData = tiffReader->getNavigationData(navigationWidth, navigationHeight, xblocklen, yblocklen);

	QImage *navigationImage = new QImage( navigationWidth, navigationHeight, QImage::Format_RGB32);
	

	//qDebug() << "Biomaker xblocklen"

	
	for (tstrip_t i = 0; i < (int)navigationHeight; i++) {
		tstrip_t baseIndex = tiffWidth*i*yblocklen;
		for (tstrip_t j = 0; j < (int)navigationWidth; j++) {
			//navigationImage->setPixel(j, i, tiffData[baseIndex + j*xblocklen]);
			//Why the coordinate is fanle
			//navigationImage->setPixel(j, i, navigationData[j*(int)navigationHeight + i]);
			navigationImage->setPixel(j, i, navigationData[i*(int)navigationWidth + j]);
		}
	}
	//navigationImage->invertPixels();
	navigationSwapImage = navigationImage->rgbSwapped();
	navigationImage->save("a.bmp");
	free(navigationData);
	//QGraphicsScene* navigationScene = new QGraphicsScene();
	////navigationScene->addPixmap(QPixmap::fromImage(*navigationImage));
	navigationGraphicsView->setImage(&navigationSwapImage);
	float minWindowX = navigationWidth*sceneWidth / tiffWidth;
	float minWindowY = navigationWidth*sceneHeight / tiffWidth;

	navigationGraphicsView->setNavigationMinWindowSize(minWindowX,
		minWindowY);
	local_graphics_view->setNavigationWindowSize(navigationGraphicsViewWidth,
		navigationGraphicsViewHeight, sclarFactor);
	//set factor
	navigationGraphicsView->setFactor(navigationWidth*1.0f / tiffWidth);

	connect(navigationGraphicsView, SIGNAL(sendCenterPoint(QPointF)), this, SLOT(setNavigationChoosedImage(QPointF)));
	connect(local_graphics_view, SIGNAL(startPointChanged(QPointF)), navigationGraphicsView, SLOT(setShowNavigationMinWindow(QPointF)));

	navigationGraphicsView->show();
}

void BiomakerTool::updateGlobalRects()
{
	QList<QGraphicsItem*> items = local_graphics_view->graphicsScene->items();
	QList<QGraphicsItem*> buffer_items;
	for(auto i=0;i<items.size();i++)
	{
		if(items[i]->type()==GraphicsRectItem::Type)
		{
			if (qgraphicsitem_cast<GraphicsRectItem*>(items[i])->check_state == Qt::Checked)
			{
				buffer_items.push_back(items[i]);
			}
		}
		
	}
	//global_graphics_view->updateRects(items, tiffReader->getGlobalFactor());
	global_graphics_view->updateRects(buffer_items, tiffReader->getGlobalFactor());
	global_graphics_view->updateRects(buffer_items, tiffReader->getGlobalWidthFactor(),tiffReader->getGlobalHeightFactor());
}

void BiomakerTool::setGlobalGraphicsImage()
{
	if (!tiffReader) {
		std::cout << "Please load global graphics image first." << std::endl;
		return;
	}
	auto rect = local_graphics_view->geometry();
	auto image_width = rect.width();
	auto image_height = rect.height();
	global_graphics_view->setFixedWidth(image_width);
	global_graphics_view->setFixedHeight(image_height);

	if (image_width*1.0f / image_height < tiffWidth*1.0f / tiffHeight)
	{
		image_height = (tiffHeight*1.0f / tiffWidth)*image_width;
	}
	else
	{
		image_width = (tiffWidth*1.0f / tiffHeight)*image_height;
	}
	std::cout << "Image width : " << image_width << "\t Image height : " << image_height << std::endl;

	uint32* global_graphics_image_data = tiffReader->getGlobalGraphicsImage(image_height, image_width);
	global_graphics_image = new QImage(image_width, image_height, QImage::Format_RGB32);
	for (tstrip_t i = 0; i < image_height; i++) {
		for (tstrip_t j = 0; j < image_width; j++) {
			bufImg->setPixel(j, i, global_graphics_image_data[i*image_width + j]);
		}
	}
	const auto swap_image = bufImg->rgbSwapped();
	
	global_graphics_view->updateImage(QPixmap::fromImage(swap_image));

	updateGlobalRects();
}

void BiomakerTool::initListView()
{
	if (!is_rect_loaded_from_file)
	{
		//不需要list view
		std::cout << "The list view is not used." << std::endl;
		return;
	}
	//0.
	if (!is_init_list_view_show)
	{
		label_table_view = new LabelTableView(this);
		label_table_model = new LabelTableModel(this);
		label_table_view->setModel(label_table_model);
	}

	QVector<TableItem> table_items;
	auto local_items = local_graphics_view->graphicsScene->items();
	auto cluster_id = 0;
	std::cout << "The number of graphics scene items is : " << local_scene_item_array.size() << std::endl;
	for (auto i = 0; i < local_scene_item_array.size();i++)
	{
		auto local_item = local_scene_item_array[i];
		const auto rectItem = qgraphicsitem_cast<GraphicsRectItem*>(local_item);
		auto global_top_left = rectItem->startPoint + rectItem->localTopLeft;
		auto rect = rectItem->rect().toAlignedRect();
		table_items.push_back({ i, local_item, QString("(%1, %2), (%3, %4)").arg(global_top_left.x()).arg(global_top_left.y())
			.arg(rect.width()).arg(rect.height()), rectItem->check_state });
	}
	if (!is_init_list_view_show)
		label_table_model->addData(table_items);
	else
	{
		label_table_model->setUserAddCheckStateRole(true);
		for (int i = 0; i < table_items.size(); i++)
		{
			const auto idx = label_table_model->index(i, 0);
			label_table_model->setData(idx, table_items[i].name, Qt::DisplayRole);
			label_table_model->setData(idx, table_items[i].state, Qt::CheckStateRole);
			label_table_model->setData(idx, table_items[i].id, Qt::UserRole);
		}
		label_table_model->setUserAddCheckStateRole(false);
	}
	//label_table_model->ad
	if (!is_init_list_view_show)
	{
		button_find_next_unchecked = new QPushButton(this);
		button_find_next_unchecked->setText("next unchecked");
		button_save_biomarker = new QPushButton(this);
		button_save_biomarker->setText("save biomarker");
		parameterDock->ui.horizontalLayout_6->addWidget(button_find_next_unchecked);
		parameterDock->ui.horizontalLayout_6->addWidget(button_save_biomarker);
		parameterDock->ui.horizontalLayout_7->addWidget(label_table_view);
	}
	

	//设置点击事件
	connect(button_find_next_unchecked, &QPushButton::clicked, [this]()
	{
		//对应某个view的响应事件

		QModelIndex model_index;
		int i;
		for (i = 0; i < local_scene_item_array.size(); i++)
		{
			model_index = this->label_table_model->index(i, 0);
			auto checked_state = this->label_table_model->data(model_index, Qt::CheckStateRole);
			if ((Qt::CheckState)checked_state.toInt() == Qt::Unchecked)
			{
				break;
			}
		}
		if (i >= local_scene_item_array.size())
		{
			//提示保存成功
			QMessageBox msgBox;
			msgBox.setText("All the biomarkers have been checked.");
			msgBox.exec();
		}
		this->label_table_view->setCurrentIndex(model_index);
		this->label_table_view->selectRow(model_index.row());

		emit label_table_view->clicked(model_index);

	});
	//Debug 20190622
	connect(button_save_biomarker, &QPushButton::clicked, [this]()
	{
		QModelIndex model_index;
		QVector<QGraphicsItem*> right_item_array;
		QVector<QGraphicsItem*> error_item_array;
		QVector<QGraphicsItem*> unchecked_item_array;

		QList<QGraphicsItem*> items = local_graphics_view->graphicsScene->items();
		
		for (auto i = 0; i < local_scene_item_array.size(); i++)
		{
			model_index = this->label_table_model->index(i, 0);
			if (model_index.data(Qt::CheckStateRole).toInt()==Qt::Checked)
			{
				right_item_array.push_back(local_scene_item_array[model_index.data(Qt::UserRole).toInt()]);
			}
			else if (model_index.data(Qt::CheckStateRole).toInt() == Qt::PartiallyChecked)
			{
				error_item_array.push_back(local_scene_item_array[model_index.data(Qt::UserRole).toInt()]);
			}
			else if (model_index.data(Qt::CheckStateRole).toInt() == Qt::Unchecked)
			{
				unchecked_item_array.push_back(local_scene_item_array[model_index.data(Qt::UserRole).toInt()]);
			}
		}
		for (auto item : items)
		{
			if (item->type() == GraphicsRectItem::Type) {
				GraphicsRectItem *rect = qgraphicsitem_cast<GraphicsRectItem*>(item);
				QRect captureRect = rect->rect().toAlignedRect();
				if (captureRect.width() <= 5 || captureRect.height() <= 5) continue;

				bool is_new_label = true;
				for (auto i = 0; i < local_scene_item_array.size(); i++)
				{
					model_index = this->label_table_model->index(i, 0);
					if (local_scene_item_array[model_index.data(Qt::UserRole).toInt()] == item)
					{
						is_new_label = false;
						break;
					}
				}
				if(is_new_label)
				{
					right_item_array.push_back(item);
				}
			}
			
		}

		ofstream checked_file("./workspace/checked_result.mark");
		checked_file << right_item_array.size()+error_item_array.size()+unchecked_item_array.size() <<" "<< 1 << endl;
		for (auto& i : right_item_array)
		{
			auto rect_item = qgraphicsitem_cast<GraphicsRectItem*>(i);
			auto& start_point = rect_item->startPoint;
			auto& local_left_top = rect_item->localTopLeft;
			QRect captureRect = rect_item->rect().toAlignedRect();

			QPoint topLeft;
			if (local_left_top == QPoint(-1, -1))
				topLeft = captureRect.topLeft() + start_point;
			else
				topLeft = local_left_top + start_point;

			auto rect = rect_item->rect().toAlignedRect();
			const auto width = rect.width();
			const auto height = rect.height();
			checked_file << topLeft.x() << " " << topLeft.y() << " " << 1<< " " << 0<< " "
				<< width << " " << height << endl;
		}

		//checked_file << error_item_array.size() <<2<< endl;
		for (auto& i : error_item_array)
		{
			auto rect_item = qgraphicsitem_cast<GraphicsRectItem*>(i);
			auto& start_point = rect_item->startPoint;
			auto& local_left_top = rect_item->localTopLeft;
			auto rect = rect_item->rect().toAlignedRect();
			const auto width = rect.width();
			const auto height = rect.height();
			checked_file << start_point.x() + local_left_top.x() << " " << start_point.y() + local_left_top.y() << " " << 2 << " " << 0 << " "
				<< width << " " << height << endl;

		}

		for (auto& i : unchecked_item_array)
		{
			auto rect_item = qgraphicsitem_cast<GraphicsRectItem*>(i);
			auto& start_point = rect_item->startPoint;
			auto& local_left_top = rect_item->localTopLeft;
			auto rect = rect_item->rect().toAlignedRect();
			const auto width = rect.width();
			const auto height = rect.height();
			checked_file << start_point.x() + local_left_top.x() << " " << start_point.y() + local_left_top.y() << " " << 0 << " " << 0 << " "
				<< width << " " << height << endl;

		}
		checked_file.close();
		
		//提示保存成功
		QMessageBox msgBox;
		msgBox.setText("The checked biomarkers have been saved.");
		msgBox.exec();

	});
	//1. 把list数组传递进去,标签利用index表示

	//选中list数据后展示对应的窗体
	connect(label_table_view, &QTableView::clicked, [this](const QModelIndex &idx)
	{
		//对应某个view的响应事件
		const auto r = idx.row();
		auto id = label_table_model->data(idx,Qt::UserRole);
		const auto index = id.toInt();
		static int old_id = -1;
		//if (index == old_id) return;
		//else old_id = index;
		const auto item = local_scene_item_array[index];
		const auto rect_item = qgraphicsitem_cast<GraphicsRectItem*>(item);

		//设置局部坐标的位置信息及背景
		auto start_point = rect_item->startPoint;
		const auto local_top_left = rect_item->localTopLeft;
		//qDebug() << start_point;
		local_graphics_view->setStartPoint(start_point);
		start_point = start_point + local_top_left;
		//setShowImage(start_point);
		//QPointF local_point;
		//local_point.setX(start_point.x()*1.0f*navigationWidth / tiffWidth);
		//local_point.setY(start_point.y()*1.0f*navigationWidth / tiffWidth);
		//设置导航视图位置
		//setNavigationChoosedImage(local_point);

		//设置该矩形选中状态
		local_graphics_view->setRectSelectedState(rect_item);
	});
	//auto select_model = new QItemSelectionModel();
	//this->label_table_view->setSelectionModel(select_model);
	//选中矩形区域后将listview中的数据高亮显示
	connect(local_graphics_view, &LocalGraphicsView::signal_SendCurrentRectItem, [this](QGraphicsItem* item)
	{
		//对应某个view的响应事件
		auto item_index = local_scene_item_map[item];
		QModelIndex model_index;
		int i;
		for (i = 0; i < local_scene_item_array.size(); i++)
		{
			model_index = this->label_table_model->index(i, 0);
			auto index = this->label_table_model->data(model_index, Qt::UserRole);
			if (index == item_index) break;
		}
		this->label_table_view->setCurrentIndex(model_index);
		//this->label_table_view->selectionModel()->setCurrentIndex(model_index, QItemSelectionModel::SelectCurrent);
		this->label_table_view->selectRow(model_index.row());
		//this->label_table_view->selectColumn(0);
		//emit this->label_table_view->clicked(model_index);
		//qDebug() << "index : " << item_index;
	});

	connect(local_graphics_view, &LocalGraphicsView::signal_SendCheckedState, [this](GraphicsRectItem* item, int state)
	{
		auto origin_item = qgraphicsitem_cast<QGraphicsItem*>(item);

		auto item_index = local_scene_item_map[origin_item];
		QModelIndex model_index;
		int i;
		for (i = 0; i < local_scene_item_array.size(); i++)
		{
			model_index = this->label_table_model->index(i, 0);
			auto index = this->label_table_model->data(model_index, Qt::UserRole);
			if (index == item_index) break;
		}
		this->label_table_view->setCurrentIndex(model_index);
		this->label_table_model->setData(model_index, state-1, Qt::CheckStateRole);
		//this->label_table_view->selectionModel()->setCurrentIndex(model_index, QItemSelectionModel::SelectCurrent);
		this->label_table_view->selectRow(model_index.row());

	});
	//响应tableview点击后对应local view的颜色改变事件
	connect(label_table_model, &LabelTableModel::modelsignal_SendCheckedState, [this](const QModelIndex& idx, Qt::CheckState state)
	{
		//对应某个view的响应事件
		const auto r = idx.row();
		auto id = this->label_table_model->data(idx, Qt::UserRole);
		const auto index = id.toInt();

		const auto item = this->local_scene_item_array[index];
		const auto rect_item = qgraphicsitem_cast<GraphicsRectItem*>(item);

		auto cur_pen = rect_item->pen();
		cur_pen.setStyle(Qt::DotLine);
		if (state == Qt::PartiallyChecked)
		{
			cur_pen.setColor(Qt::green);
		}
		else if (state == Qt::Checked)
		{
			cur_pen.setColor(Qt::black);
		}
		rect_item->setPen(cur_pen);
		rect_item->check_state = state;
	});

	
}

void BiomakerTool::on_slotOpenImage_triggered(){
	QString fileName = QFileDialog::getOpenFileName(this, 
		"open image file", ".", tr("Images (*.tif *.tiff )"));

	if (fileName.isEmpty()) {
		return;
	}

	//Waring: QImage/QImageReader/QPixMap不支持高分辨率tiff图像，采用libtiff库配置。
	if (tiffReader) {
		//delete tiffReader;
	}
	tiffReader = new TiffReader(fileName);
	tiffWidth = tiffReader->getWidth();
	tiffHeight = tiffReader->getHeight();
	tiffBoundingBox = QRect(0, 0, tiffWidth, tiffHeight);
	
	QRect rect = local_graphics_view->geometry();

	//qDebug() << rect.width() << rect.height() << rect.center();
	sceneWidth = rect.width();
	sceneHeight = rect.height();
	local_graphics_view->setTiffSize(tiffWidth, tiffHeight, sceneWidth, sceneHeight);
	
	setNavigationBackground();


	bufImg = new QImage(sceneWidth, sceneHeight, QImage::Format_RGB32);
	
	QPoint centerPoint = QPoint(tiffWidth / 2 - 1, tiffHeight / 2 - 1);
	QPoint startPoint = centerPoint - QPoint(sceneWidth / 2 - 1, sceneHeight / 2 - 1);
	setShowImage(startPoint);

	//set global view
	setGlobalGraphicsImage();


	//Debug 20191120
	connect(ui.actionExport_tif, &QAction::triggered, this, &BiomakerTool::on_slotExportMarkedTiff_triggered);
}
void BiomakerTool::setShowImage(QPointF startPoint) {

	//QImage *testImage = new QImage(sceneWidth, sceneHeight, QImage::Format_RGB32);

	uint32* testData = tiffReader->getLocalImage(startPoint, sceneHeight, sceneWidth);
	for (tstrip_t i = 0; i < sceneHeight; i++) {
		for (tstrip_t j = 0; j < sceneWidth; j++) {
			bufImg->setPixel(j, i, testData[i*sceneWidth + j]);
		}
	}

	QImage swapImage = bufImg->rgbSwapped();
	//bufImg->invertPixels();
	//qDebug() << starttime.elapsed() << endl;
	local_graphics_view->updateImage(startPoint.toPoint(), QPixmap::fromImage(swapImage));
	local_graphics_view->show();

}
void BiomakerTool::setNavigationChoosedImage(QPointF localPoint) {

	//this startPoint represents the navigation choosed local index, which need to be transformed into global index.
	QPoint globalPoint;

	//qDebug() << tiffWidth*1.0f / navigationWidth << tiffHeight*1.0f / navigationHeight;
	int x = (localPoint.x() *tiffWidth / navigationWidth);
	int y = (localPoint.y() *tiffWidth / navigationWidth);

	globalPoint.setX((int)x);
	globalPoint.setY((int)y);
	//qDebug() << navigationWidth*1.0f / tiffWidth << navigationHeight*1.0f/tiffHeight << localPoint << globalPoint;
	if (tiffBoundingBox.contains(QRect(globalPoint, QSize(sceneWidth, sceneHeight)))){
		uint32* tiffData = tiffReader->getRawData();

		uint32* testData = tiffReader->getLocalImage(globalPoint, sceneHeight, sceneWidth);
		for (tstrip_t i = 0; i < sceneHeight; i++) {
			for (tstrip_t j = 0; j < sceneWidth; j++) {
				bufImg->setPixel(j, i, testData[i*sceneWidth + j]);
			}
		}

		//tstrip_t baseIndex = tiffWidth*globalPoint.y() + globalPoint.x();
		//for (tstrip_t i = 0; i < sceneHeight; i++) {
		//	for (tstrip_t j = 0; j < sceneWidth; j++) {
		//		bufImg->setPixel(j, i, tiffData[baseIndex + i*tiffWidth + j]);
		//	}
		//}
		QImage swapImage = bufImg->rgbSwapped();
		local_graphics_view->updateImage(globalPoint, QPixmap::fromImage(swapImage));
	}
}
