#include "GlobalGraphicsView.h"
#include <iostream>
#include "GraphicsRectItem.h"
#include <QGraphicsItem>
#include <QDebug>
#include "PloygonArea.h"



GlobalGraphicsView::GlobalGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setRenderHint(QPainter::Antialiasing);

	graphicsScene = new QGraphicsScene();
	setScene(graphicsScene);

	circle_pen = QPen(QColor(Qt::red));
	circle_brush = QBrush(QColor(Qt::NoBrush));
	is_circle_selected = false;
	blackDotPen = QPen(Qt::black, 2, Qt::DotLine, Qt::FlatCap);
	blackPen = QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap);

	redDotPen = QPen(Qt::red, 2, Qt::DotLine, Qt::FlatCap);
	redPen = QPen(Qt::red, 2, Qt::SolidLine, Qt::FlatCap);
	selected_circle = nullptr;
	cur_circle = nullptr;
	cur_ploygon = nullptr;
	selected_ploygon = nullptr;

	circle_number_map.clear();

}

GlobalGraphicsView::~GlobalGraphicsView()
= default;

void GlobalGraphicsView::updateImage(QPixmap& pixmap)
{
	setSceneRect(0, 0, width(), height());
	graphicsScene->setSceneRect(0, 0, width(), height());
	graphicsScene->setBackgroundBrush(QBrush(Qt::white));
	centerOn(width() / 2, height() / 2);
	std::cout << "Width and height : " << width() << "\t" << height() << std::endl;
	pixmapItem = graphicsScene->addPixmap(pixmap);
	graphicsScene->update();
	//pixmapItem->setZValue(minZvalue);
}
void GlobalGraphicsView::updateRects(QList<QGraphicsItem*>& items, double factor)
{
	//erase all ellipse items
	for (auto& i : graphicsScene->items())
	{
		if (i->type() == QGraphicsEllipseItem::Type) {
			QGraphicsEllipseItem *item = qgraphicsitem_cast<QGraphicsEllipseItem*>(i);
			if (item->rect().width() == 2)
			{
				graphicsScene->removeItem(item);
				delete item;
			}
			
		}
	}

	const auto& brush = QBrush(QColor(Qt::black));
	for each (QGraphicsItem* item in items)
	{
		if (item->type() == GraphicsRectItem::Type) {
			GraphicsRectItem *rect = qgraphicsitem_cast<GraphicsRectItem*>(item);
			QPointF global_point = rect->startPoint + rect->localTopLeft;
			global_point /= factor;
			graphicsScene->addEllipse(QRectF(global_point, QSize(2, 2)), blackPen, brush);
		}
	}
	this->factor = factor;
	graphicsScene->update();
}

void GlobalGraphicsView::updateRects(QList<QGraphicsItem*>& items, double width_factor, double height_factor)
{
	//erase all ellipse items
	for (auto& i : graphicsScene->items())
	{
		if (i->type() == QGraphicsEllipseItem::Type) {
			QGraphicsEllipseItem *item = qgraphicsitem_cast<QGraphicsEllipseItem*>(i);
			if (item->rect().width() == 2)
			{
				graphicsScene->removeItem(item);
				delete item;
			}

		}
	}

	const auto& brush = QBrush(QColor(Qt::black));
	for each (QGraphicsItem* item in items)
	{
		if (item->type() == GraphicsRectItem::Type) {
			GraphicsRectItem *rect = qgraphicsitem_cast<GraphicsRectItem*>(item);
			QPointF global_point = rect->startPoint + rect->localTopLeft;
			//global_point /= factor;
			global_point.setX(global_point.x() / width_factor);
			global_point.setY(global_point.y() / height_factor);
			graphicsScene->addEllipse(QRectF(global_point, QSize(2, 2)), blackPen, brush);
		}
	}
	//this->factor = factor;
	this->width_factor = width_factor;
	this->height_factor = height_factor;
	graphicsScene->update();
}


void GlobalGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	if (is_circle_draw)
	{
		circleMouseMoveEvent(event);
	}
	else
	{
		ploygonMouseMoveEvent(event);
	}
	QGraphicsView::mouseMoveEvent(event);
}

void GlobalGraphicsView::mousePressEvent(QMouseEvent *event)
{
	//Debug 20190725
	//if(is_control_key_push)
	{
		if (is_circle_draw)
		{
			circleMousePressEvent(event);
		}
		else
		{
			ploygonMousePressEvent(event);
		}
	}
	
	QGraphicsView::mousePressEvent(event);
}

void GlobalGraphicsView::updataCircleMarkerNumber()
{
	if (mouse_button_type == 1)
	{
		QList<QGraphicsItem*> items = graphicsScene->items();
		int count = 0;
		if (is_circle_selected)
		{
			//cur_circle = selected_circle;
			for each (QGraphicsItem* item in items)
			{
				if (item->type() == QGraphicsEllipseItem::Type) {
					auto buf_item = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);

					auto buf_rect = buf_item->rect();
					if (buf_rect.width() < 5)
					{
						if (selected_circle&&selected_circle->contains(buf_rect.center()))
						{
							count++;
						}
					}
				}
			}
			auto circle_area = getCircleArea(selected_circle);
			circle_number_map[selected_circle] = QString("%1,%2").arg(count).arg(circle_area);

		}

	}

	else if (mouse_button_type == 0)
	{
		QList<QGraphicsItem*> items = graphicsScene->items();
		int count = 0;

		for each (QGraphicsItem* item in items)
		{
			if (item->type() == QGraphicsEllipseItem::Type) {
				auto buf_item = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);

				auto buf_rect = buf_item->rect();
				if (buf_rect.width() < 5)
				{
					if (cur_circle&&cur_circle->contains(buf_rect.center()))
					{
						count++;
					}
				}
			}
		}
		auto circle_area = getCircleArea(cur_circle);
		circle_number_map[cur_circle] = QString("%1,%2").arg(count).arg(circle_area);
		//circle_number_map[cur_circle] = count;

		if (cur_circle&&cur_circle->rect().width() < 2) {
			circle_items.removeOne(cur_circle);
			circle_number_map.remove(cur_circle);
			graphicsScene->removeItem(cur_circle);
			delete cur_circle;
			cur_circle = nullptr;
		}
	}


	auto i = circle_number_map.constBegin();
	while (i != circle_number_map.constEnd()) {
		auto& buf_item = i.key();
		if (buf_item)
			buf_item->setToolTip(QString("%1").arg(i.value()));
		++i;
	}

	//emit sendCircleNumberMap(circle_number_map);
	//emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
}

void GlobalGraphicsView::updataCircleMarkerNumber2()
{

	QList<QGraphicsItem*> items = graphicsScene->items();
	QList<QGraphicsEllipseItem*> circle_items;
	QList<QGraphicsEllipseItem*> point_items;
	circle_number_map.clear();
	//cur_circle = selected_circle;
	for each (QGraphicsItem* item in items)
	{
		if (item->type() == QGraphicsEllipseItem::Type) {
			auto buf_item = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);

			auto buf_rect = buf_item->rect();
			if (buf_rect.width() < 5)
			{
				point_items.push_back(buf_item);
			}
			else {
				circle_items.push_back(buf_item);
			}
		}
	}

	for (auto circle : circle_items) {
		auto count = 0;
		for (auto point : point_items) {
			if (circle&&circle->contains(point->rect().center()))
			{
				count++;
			}
		}
		auto circle_area = getCircleArea(circle);
		circle_number_map[circle] = QString("%1,%2").arg(count).arg(circle_area);
	}

	auto i = circle_number_map.constBegin();
	while (i != circle_number_map.constEnd()) {
		auto& buf_item = i.key();
		if (buf_item)
			buf_item->setToolTip(QString("%1").arg(i.value()));
		++i;
		//emit sendSelectedShape(circle_number_map, ploygon_number_map, buf_item);
	}
	//emit sendCircleNumberMap(circle_number_map);
	emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
}

size_t GlobalGraphicsView::getCircleArea(QGraphicsEllipseItem* item)
{
	auto r = item->rect().width() / 2*width_factor;
	return static_cast<size_t>(3.1415926535898 * r * r + 0.5);
}

void GlobalGraphicsView::updatePolygonMarkerNumber()
{
	QList<QGraphicsItem*> items = graphicsScene->items();
	int count = 0;
	ploygon_number_map.clear();
	for each (QGraphicsItem* item in items)
	{
		if (item->type() == QGraphicsPathItem::Type) {
			auto buf_item = qgraphicsitem_cast<QGraphicsPathItem*>(item);
			int count_number = getRectCountInPolygon(buf_item->path());

			int area_count = getPolygonArea(buf_item);
			//Debug 20190808
			//ploygon_number_map[buf_item] = count_number;
			ploygon_number_map[buf_item] = QString("%1,%2").arg(count_number).arg(area_count);
			//std::cout << "Number : " << count_number << std::endl;
		}
	}
	
}

void GlobalGraphicsView::updateMarkerNumber()
{
	if (is_circle_draw)
	{
		updataCircleMarkerNumber();
	}
	else
	{
		updatePolygonMarkerNumber();
	}
	emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
}

void GlobalGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{

	if (is_circle_draw)
	{
		circleMouseReleaseEvent(event);
	}
	else
	{
		ploygonMouseReleaseEvent(event);
	}
	QGraphicsView::mouseReleaseEvent(event);
}

void GlobalGraphicsView::keyPressEvent(QKeyEvent *event)
{
	QPoint moveOffset;
	switch (event->key()) {
	case Qt::Key_Delete:
		if (is_circle_draw)
		{
			if (is_circle_selected) {

				circle_items.removeOne(selected_circle);
				circle_number_map.remove(selected_circle);
				graphicsScene->removeItem(selected_circle);
				delete selected_circle;
				selected_circle = nullptr;
				//emit sendCircleNumberMap(circle_number_map);
				emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
			}
		}
		else
		{
			if (is_ploygon_selected)
			{

				if(local_path_items.contains(selected_ploygon))
				{
					emit sendRemoveCommand(local_path_items[selected_ploygon]);
					local_path_items.remove(selected_ploygon);
				}

				//ploygon_items.removeOne(selected_ploygon);
				ploygon_number_map.remove(selected_ploygon);
				graphicsScene->removeItem(selected_ploygon);
				delete selected_ploygon;
				selected_ploygon = nullptr;
				//emit sendCircleNumberMap(circle_number_map);
				emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
			}
		}
		break;
	//Debug 20190725
	case Qt::Key_Control:
		is_control_key_push = true;
		break;

	default:
		QGraphicsView::keyPressEvent(event);
	}
	std::cout << is_control_key_push << std::endl;
}

void GlobalGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Control:
		is_control_key_push = false;
	default:
		QGraphicsView::keyPressEvent(event);
	}
	std::cout << is_control_key_push << std::endl;
}

void GlobalGraphicsView::circleMouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::RightButton) {

		const QPointF cur_position = event->pos();
		if (cur_circle)
		{
			auto center_point = cur_circle->rect().center();
			double radius = sqrt(pow((cur_position.x() - center_point.x()), 2) + pow((cur_position.y() - center_point.y()), 2));
			QPointF offset(radius, radius);
			cur_circle->setRect(QRectF(center_point - offset, center_point + offset));
			//auto& start_point = cur_circle->rect().topLeft();
			//auto min_radius = std::min(abs(cur_position.x() - start_point.x()), abs(cur_position.y() - start_point.y()));
			//cur_circle->setRect(QRectF(start_point, cur_position));
		}
		update();
	}
	else if (event->buttons() & Qt::LeftButton)
	{
		//old_point = event->pos();
		if (is_circle_selected&&selected_circle)
		{
			static QPointF old_move(0, 0);
			const auto offset = event->pos() - old_point;
			std::cout << "Event offset : " << offset.x() << "\t" << offset.y() << std::endl;
			//selected_circle->moveBy((offset - old_move).x(), (offset - old_move).y());
			auto width = selected_circle->rect().width();

			selected_circle->setRect(QRectF(old_top_left + event->pos() - old_point, QSizeF(width, width)));
			old_move = offset;

			cur_circle = selected_circle;
			//updateMarkerNumber();
		}
	}
}

void GlobalGraphicsView::circleMousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::RightButton) {
		const QPointF circle_center = event->pos();
		cur_circle = new QGraphicsEllipseItem(QRectF(circle_center, QSizeF(0, 0)));
		cur_circle->setPen(redPen);
		circle_items.push_back(cur_circle);
		graphicsScene->addItem(cur_circle);
		//circle_number_map.insert(cur_circle, 0);
		circle_number_map[cur_circle] = QString("0,0");
		mouse_button_type = 0;
		//selected_circle = cur_circle;
	}
	else if (event->buttons() & Qt::LeftButton)
	{
		//old_point = event->pos();
		if (selected_circle)
		{
			selected_circle->setPen(redPen);
		}
		bool isRectHad = false;
		QList<QGraphicsItem*> items = graphicsScene->items();
		const QPointF circle_center = event->pos();
		for each (QGraphicsItem* item in items)
		{
			old_point = event->pos();

			if (item->type() == QGraphicsEllipseItem::Type) {
				auto buf_item = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);

				if (buf_item->rect().width() < 5) continue;
				if (!buf_item->contains(circle_center)) continue;
				if (!isRectHad&&buf_item->isUnderMouse()){

					isRectHad = true;
					buf_item->setPen(redDotPen);
					
					is_circle_selected = true;
					selected_circle = buf_item;
					old_top_left = selected_circle->rect().topLeft();

					emit sendSelectedShape(circle_number_map, ploygon_number_map, selected_circle);
					//old_top_left = this->mapToScene(old_top_left.toPoint());
					//continue;
					break;
				}
				if (is_circle_selected || !buf_item->isUnderMouse()) {
					buf_item->setPen(redDotPen);
					emit sendSelectedShape(circle_number_map, ploygon_number_map, buf_item);
				}
			}
		}

		if (!isRectHad) {
			is_circle_selected = false;
			selected_circle = nullptr;
			for each (QGraphicsItem* item in items)
			{
				if (item->type() == QGraphicsEllipseItem::Type) {
					auto buf_item = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
					if (buf_item->rect().width() < 5) continue;
					buf_item->setPen(redPen);
				}
			}
		}

		mouse_button_type = 1;
	}
	else
	{
		mouse_button_type = 2;
	}
}

void GlobalGraphicsView::circleMouseReleaseEvent(QMouseEvent* event)
{
	//if (event->buttons() & Qt::RightButton) {
	//if (mouse_button_type == 0) {
	updateMarkerNumber();
	//}
}

void GlobalGraphicsView::ploygonMouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::RightButton) {
		if (cur_ploygon)
		{
			const QPointF cur_point = event->pos();

			const auto last_path_position = cur_paint_path.currentPosition();

			if ((cur_point - last_path_position).manhattanLength() < 5) return;

			else
			{
				point_count++;
				cur_paint_path.lineTo(cur_point);
				cur_ploygon->setPath(cur_paint_path);
			}
			
		}
	}
}

int GlobalGraphicsView::getRectCountInPolygon(QPainterPath graphics_path)
{
	int count = 0;
	QList<QGraphicsItem*> items = graphicsScene->items();
	for each (QGraphicsItem* item in items)
	{
		if (item->type() == QGraphicsEllipseItem::Type) {
			auto buf_item = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
			if (buf_item->rect().width() == 2)
			{
				if (graphics_path.contains(buf_item->rect().topLeft()))
				{
					count++;
				}
			}
		}
	}
	return count;
}

size_t GlobalGraphicsView::getPolygonArea(QGraphicsPathItem* item)
{
	auto ploygon_area = PloygonArea(item, width_factor, height_factor,
		pixmapItem->boundingRect().width()*width_factor, pixmapItem->boundingRect().height()*height_factor);
	return ploygon_area.calArea();
}

void GlobalGraphicsView::ploygonMousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::RightButton) {
		start_point = event->pos();
		cur_ploygon = new QGraphicsPathItem();
		//ploygon_items.push_back(cur_ploygon);
		cur_ploygon->setPen(redPen);
		cur_paint_path = QPainterPath();
		cur_paint_path.moveTo(start_point);
		cur_ploygon->setPath(cur_paint_path);
		graphicsScene->addItem(cur_ploygon);
		point_count = 0;
		clicked_polygon_type = 0;
	}
	else if (event->buttons() & Qt::LeftButton)
	{
		clicked_polygon_type = 1;
		if (selected_ploygon)
		{
			selected_ploygon->setPen(redPen);
		}
		const auto letf_clicked_point = event->pos();
		bool isRectHad = false;
		QList<QGraphicsItem*> items = graphicsScene->items();
		
		for each (QGraphicsItem* item in items)
		{
			old_point = event->pos();

			if (item->type() == QGraphicsPathItem::Type) {
				auto buf_item = qgraphicsitem_cast<QGraphicsPathItem*>(item);

				if (buf_item->boundingRect().width() < 5) continue;
				if (!buf_item->path().contains(letf_clicked_point)) continue;
				if (!isRectHad&&buf_item->isUnderMouse()){

					isRectHad = true;
					buf_item->setPen(redDotPen);
					is_ploygon_selected = true;
					selected_ploygon = buf_item;
					emit sendSelectedShape(circle_number_map, ploygon_number_map, buf_item);
					//old_top_left = selected_circle->rect().topLeft();
					//old_top_left = this->mapToScene(old_top_left.toPoint());
					//continue;
					break;
				}
				if (is_ploygon_selected || !buf_item->isUnderMouse()) {
					buf_item->setPen(redDotPen);
					emit sendSelectedShape(circle_number_map, ploygon_number_map, buf_item);
				}
			}
		}

		if (!isRectHad) {
			is_ploygon_selected = false;
			selected_ploygon = nullptr;
			for each (QGraphicsItem* item in items)
			{
				if (item->type() == QGraphicsPathItem::Type) {
					auto buf_item = qgraphicsitem_cast<QGraphicsPathItem*>(item);
					if (buf_item->boundingRect().width() < 5) continue;
					buf_item->setPen(redPen);
				}
			}
		}
		
	}
	else
	{
		clicked_polygon_type = 2;
	}
}

void GlobalGraphicsView::ploygonMouseReleaseEvent(QMouseEvent* event)
{
	if (clicked_polygon_type==0&&cur_ploygon != nullptr)
	{
		//将不符合的点删去
		if (point_count < 5)
		{
			graphicsScene->removeItem(cur_ploygon);
			delete cur_ploygon;
			cur_ploygon = nullptr;
			return;
		}
		//cur_paint_path.lineTo(start_point);
		if (!cur_ploygon->path().isEmpty())
		{
			auto buf = cur_ploygon->path();
			buf.lineTo(start_point);
			cur_ploygon->setPath(buf);
		}
		std::cout << "test" << std::endl;
		//统计个数
		updateMarkerNumber();

		//send to local graphics view
		buf_item = new QGraphicsPathItem();
		buf_item->setPen(redPen);

		auto buf_path = cur_ploygon->path();
		for(auto i=0;i<cur_ploygon->path().elementCount();i++)
		{
			QPointF buf = buf_path.elementAt(i);
			//Debug 20190727
			//buf_path.setElementPositionAt(i, buf.x()*factor, buf.y()*factor);
			buf_path.setElementPositionAt(i, buf.x()*width_factor, buf.y()*height_factor);
		}
		buf_item->setPath(buf_path);
		emit sendNewPolygonToLocalGraphicsView(buf_item);
		local_path_items[cur_ploygon] = buf_item;
	}
}

void GlobalGraphicsView::setSelectedItem(QGraphicsEllipseItem* item)
{
	if (selected_circle)
	{
		selected_circle->setPen(redPen);
	}
	if(selected_ploygon)
	{
		selected_ploygon->setPen(redPen);
	}
	selected_circle = item;
	selected_circle->setPen(redDotPen);
}


void GlobalGraphicsView::setSelectedItem(QGraphicsPathItem* item)
{
	if (selected_circle)
	{
		selected_circle->setPen(redPen);
	}
	if (selected_ploygon)
	{
		selected_ploygon->setPen(redPen);
	}
	selected_ploygon = item;
	selected_ploygon->setPen(redDotPen);
	
}

QMap<QGraphicsPathItem*, QString>& GlobalGraphicsView::exportPathItem()
{
	return ploygon_number_map;
}

QMap<QGraphicsEllipseItem*, QString>& GlobalGraphicsView::exportCircleItem()
{
	return circle_number_map;
}

void GlobalGraphicsView::getPolygon(QGraphicsPathItem* buf_ploygon, const QPoint& point)
{
	//trans to global view.

	this->cur_ploygon = new QGraphicsPathItem();

	this->cur_ploygon->setPen(redPen);
	cur_paint_path = QPainterPath();
	
	const auto& path = buf_ploygon->path();
	QPointF start_point = path.elementAt(0); //get the value of the point at index i
	//Debug 20190727
	//start_point = (start_point + point) / factor;
	start_point = (start_point + point);
	start_point.setX(start_point.x() / width_factor);
	start_point.setY(start_point.y() / height_factor);
	cur_paint_path.moveTo(start_point);
	for(auto i=1;i< path.elementCount();i++)
	{
		QPointF pt = path.elementAt(i); //get the value of the point at index i
		//Debug 20190727
		//auto local = (pt + point) / factor;
		auto local = (pt + point);
		local.setX(local.x() / width_factor);
		local.setY(local.y()/height_factor);
		cur_paint_path.lineTo(local);
		//qDebug() << local;
	}
	cur_paint_path.lineTo(start_point);
	this->cur_ploygon->setPath(cur_paint_path);
	graphicsScene->addItem(this->cur_ploygon);

	updatePolygonMarkerNumber();
	emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
}

void GlobalGraphicsView::getCircle(QGraphicsEllipseItem* buf_circle, const QPoint& point)
{
	//trans to global view.

	//TODO
	emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
}

void GlobalGraphicsView::getLocalPolygon(const QVector<QPointF>& vector, QGraphicsPathItem* path_item)
{

	//trans to global view.

	this->cur_ploygon = new QGraphicsPathItem();

	this->cur_ploygon->setPen(redPen);
	cur_paint_path = QPainterPath();

	if(!vector.empty())
	{
		//Debug 20190727
		//cur_paint_path.moveTo(vector[0] / factor);
		cur_paint_path.moveTo(QPointF(vector[0].x()/width_factor,vector[0].y()/height_factor));
		for(auto i=1;i<vector.size();i++)
		{
			cur_paint_path.lineTo(QPointF(vector[i].x() / width_factor, vector[i].y() / height_factor));
		}
		cur_paint_path.lineTo(QPointF(vector[0].x() / width_factor, vector[0].y() / height_factor));

		cur_ploygon->setPath(cur_paint_path);
		graphicsScene->addItem(this->cur_ploygon);

		local_path_items[cur_ploygon] = path_item;

		updatePolygonMarkerNumber();
		emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
	}
	//std::cout << "test" << endl;

}
QGraphicsPathItem* GlobalGraphicsView::getCurPolgyon() const
{
	return cur_ploygon;
}