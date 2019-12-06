#include "LocalGraphicsView.h"
#include <iostream>

LocalGraphicsView::LocalGraphicsView( QWidget *parent)
	: QGraphicsView(parent)
{
	//this->startPoint = QPoint(tiffWidth / 2 - 1, tiffHeight / 2 - 1);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//setCursor(Qt::PointingHandCursor);
	setRenderHint(QPainter::Antialiasing);

	//setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);
	//centerOn(0, 0);
	oldPoint = QPoint(0, 0);
	graphicsScene = new QGraphicsScene();
	rectTopLeft = QPoint(0, 0);
	isRectSeleted = false;
	isZoomIn = false;
	oldBuf = QPoint(0, 0);
	setScene(graphicsScene);
	

	redLabelNumber = 0;
	greenLabelNumber = 0;
	blueLabelNumber = 0;
	yellowLabelNumber = 0;
	blackLabelNumber = 0;
	penIndex = 1;

	redPen = QPen(Qt::red, 1.5, Qt::SolidLine, Qt::FlatCap);
	greenPen = QPen(Qt::green, 1.5, Qt::SolidLine, Qt::FlatCap);
	bluePen = QPen(Qt::blue, 1.5, Qt::SolidLine, Qt::FlatCap);
	yellowPen = QPen(Qt::yellow, 1.5, Qt::SolidLine, Qt::FlatCap);
	blackPen = QPen(Qt::black, 1.5, Qt::SolidLine, Qt::FlatCap);

	redDotPen = QPen(Qt::red, 1.5, Qt::DotLine, Qt::FlatCap);
	greenDotPen = QPen(Qt::green, 1.5, Qt::DotLine, Qt::FlatCap);
	blueDotPen = QPen(Qt::blue, 1.5, Qt::DotLine, Qt::FlatCap);
	yellowDotPen = QPen(Qt::yellow, 1.5, Qt::DotLine, Qt::FlatCap);
	blackDotPen = QPen(Qt::black, 1.5, Qt::DotLine, Qt::FlatCap);


	selected_circle = nullptr;
	cur_circle = nullptr;
	cur_ploygon = nullptr;
	selected_ploygon = nullptr;
}

void LocalGraphicsView::setTiffSize(int tiffWidth, int tiffHeight, int sceneWidth, int sceneHeight) {
	this->tiffWidth = tiffWidth;
	this->tiffHeight = tiffHeight;
	tiffRec = QRect(0, 0, tiffWidth, tiffHeight);
	boundingBox = QRect(0, 0, tiffWidth, tiffHeight);
	this->sceneWidth = sceneWidth;
	this->sceneHeight = sceneHeight;
	centerOn(sceneWidth / 2, sceneHeight / 2);
	//setTransformOriginPoint()
	this->startPoint = QPoint(tiffWidth / 2 - 1 - sceneWidth / 2 - 1, tiffHeight / 2 - 1 - sceneHeight / 2 - 1);
	oldPixmap = nullptr;
	pixmapItem = nullptr;
	//graphicsScene->addItem(captureGraphicsItem);

	circle_number_map.clear();
}
void LocalGraphicsView::setStartPoint(const QPointF& start_point)
{
	this->oldStartPoint = this->startPoint;
	//this->startPoint = start_point.toPoint();
	emit startPointChanged(start_point);
}
void LocalGraphicsView::updateImage(QPoint startP, QPixmap& pixmap) {

	//oldStartPoint = startP;
	QList<QGraphicsItem *> items = graphicsScene->items(); 
	qreal minZvalue = 1<<31;
	for (int i = 0; i < items.size();i++){
		QGraphicsItem *item = items[i];
		int type = item->type();
		minZvalue = qMin(item->zValue(), minZvalue);
		if (type == GraphicsRectItem::Type) {
			GraphicsRectItem *rect = qgraphicsitem_cast<GraphicsRectItem*>(item);
			//TODO:: 这里有问题
			QPoint offset = oldStartPoint - this->startPoint;
			if (this->startPoint != startP) {
				offset = this->startPoint - startP;
			}
			rect->setPos(rect->pos() + offset);
		}
		else if (item->type() == QGraphicsPixmapItem::Type) { 
			QGraphicsPixmapItem *scene = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
			graphicsScene->removeItem(scene);
			delete scene;
		}
		//Debug 20190726
		else if(item->type() == QGraphicsPathItem::Type)
		{
			QGraphicsPathItem *rect = qgraphicsitem_cast<QGraphicsPathItem*>(item);
			auto path = rect->path();
			QPoint offset = oldStartPoint - this->startPoint;
			if (this->startPoint != startP) {
				offset = this->startPoint - startP;
			}

			for(auto i=0;i< path.elementCount();i++)
			{
				QPointF result_point = path.elementAt(i)+offset;
				path.setElementPositionAt(i, result_point.x(), result_point.y());
			}
			rect->setPath(path);
		}
	}

	//当前的path
	
	if(cur_ploygon)
	{
		QPoint offset = oldStartPoint - this->startPoint;
		for (auto i = 0; i < cur_paint_path.elementCount(); i++)
		{
			QPointF result_point = cur_paint_path.elementAt(i) + offset;
			cur_paint_path.setElementPositionAt(i, result_point.x(), result_point.y());
		}
		cur_ploygon->setPath(cur_paint_path);
	}
	

	pixmapItem = graphicsScene->addPixmap(pixmap);
	pixmapItem->setZValue(minZvalue);

	this->startPoint = startP;
	graphicsScene->update();
}

void LocalGraphicsView::setRectLoadedState(bool state)
{
	is_rect_item_loaded_from_file = state;
}

void LocalGraphicsView::setRectSelectedState(GraphicsRectItem* rect_item)
{
	//清除其他选中状态
	QList<QGraphicsItem*> items = graphicsScene->items();
	int cnt = 0;
	for each (QGraphicsItem* item in items)
	{
		if (item->type() == GraphicsRectItem::Type) {
			auto rectItem = qgraphicsitem_cast<GraphicsRectItem*>(item);
			rectItem->setPen(getOldPen(rectItem));
			cnt++;
		}
	}
	//设置选中状态
	rect_item->setPen(getOldDotPen(rect_item));
	selectedRectItem = rect_item;
	isRectSeleted = true;
	qDebug() << "rect number :" << cnt;
}

LocalGraphicsView::~LocalGraphicsView()
{
}

bool LocalGraphicsView::inBoundingBox(QPoint startPos) {
	
	QRect sceneRec = geometry();
	sceneRec.moveCenter(startPos);
	QRect tiffRec(0, 0, tiffWidth, tiffHeight);
	return tiffRec.contains(sceneRec);
}

// 上/下/左/右键向各个方向移动、加/减键进行缩放、空格/回车键旋转
void LocalGraphicsView::keyPressEvent(QKeyEvent *event)
{
	QPoint moveOffset;
	switch (event->key()) {
	case Qt::Key_Up:
		//translate(QPointF(0, -2));  // 上移
		moveOffset = QPoint(0, -yOffset);
		break;
	case Qt::Key_Down:
		//translate(QPointF(0, 2));  // 下移
		moveOffset = QPoint(0, yOffset);
		break;
	case Qt::Key_Left:
		//translate(QPointF(-2, 0));  // 左移
		moveOffset = QPoint(-xOffset, 0);
		break;
	case Qt::Key_Right:
		//translate(QPointF(2, 0));  // 右移
		moveOffset = QPoint(xOffset, 0);
		break;
	case Qt::Key_Plus:  // 放大
		//zoomIn();
		break;
	case Qt::Key_Minus:  // 缩小
		//zoomOut();
		break;
	case Qt::Key_Space:  // 逆时针旋转
		//rotate(-5);
		//break;
	//回车控制提交绘制的polygon
	case Qt::Key_Enter:  // 顺时针旋转
		//1.首尾相连形成闭合多边形

		cur_paint_path.lineTo(cur_paint_path.elementAt(0));
		cur_ploygon->setPath(cur_paint_path);
		
		//2.提交至global view

		emit sendLocalPolygon(polygon_region, cur_ploygon);

		cur_ploygon = nullptr;
		polygon_region.clear();
		break;
	case Qt::Key_Return:
		//rotate(5);
		break;
	case Qt::Key_Delete:
		if (isRectSeleted) {
			graphicsScene->removeItem(selectedRectItem);

			if (isZoomIn){
				int navigationX = (int)(((oldPoint/2 + startPoint).x() + 0)*1.0f / sceneWidth);
				int navigationY = (int)(((oldPoint/2 + startPoint).y() + 0)*1.0f / sceneHeight);
				zoomOutMakerNumber[penIndex - 1][navigationX][navigationY]--;

				emit sendMakerNumber(zoomOutMakerNumber, zoomInMakerNumber);
			}
			else {
				int navigationX = (int)(((oldPoint + startPoint).x() + 0)*1.0f / sceneWidth);
				int navigationY = (int)(((oldPoint + startPoint).y() + 0)*1.0f / sceneHeight);
				zoomOutMakerNumber[penIndex - 1][navigationX][navigationY]--;

				emit sendMakerNumber(zoomOutMakerNumber, zoomInMakerNumber);
			}


			int selectedRectPenIndex = selectedRectItem->penType;
			if (selectedRectPenIndex == 1 && redLabelNumber>=1) {
				redLabelNumber--;
				emit sendRedLabelNumbers(redLabelNumber);
			}
			else if (selectedRectPenIndex == 2 && greenLabelNumber>=1) {
				greenLabelNumber--;
				emit sendGreenLabelNumbers(greenLabelNumber);
			}
			else if (selectedRectPenIndex == 3 && blueLabelNumber>=1){
				blueLabelNumber--;
				emit sendBlueLabelNumbers(blueLabelNumber);
			}
			else if (selectedRectPenIndex == 4 && yellowLabelNumber>=1){
				yellowLabelNumber--;
				emit sendYellowLabelNumbers(yellowLabelNumber);
			}
			else if (selectedRectPenIndex==5&& blackLabelNumber) {
				blackLabelNumber--;
				emit sendBlackLabelNumbers(blackLabelNumber);
			}
		}
		else
		{
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
					//ploygon_items.removeOne(selected_ploygon);
					ploygon_number_map.remove(selected_ploygon);
					graphicsScene->removeItem(selected_ploygon);
					delete selected_ploygon;
					selected_ploygon = nullptr;
					//emit sendCircleNumberMap(circle_number_map);
					emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
				}
			}
		//break;
		}
		break;
	case Qt::Key_1:
		//非导入模式下按键无效
		if (is_rect_item_loaded_from_file)
		{
			//将其他框设置为实线
			/*auto items = graphicsScene->items();
			for (auto item : items)
			{
				if (item->type() == GraphicsRectItem::Type) {
					rectItem = qgraphicsitem_cast<GraphicsRectItem*>(item);
					auto cur_pen = rectItem->pen();
					cur_pen.setStyle(Qt::SolidLine);
					rectItem->setPen(cur_pen);
				}
			}*/
			if (isRectSeleted)
			{
				auto cur_pen = rectItem->pen();
				cur_pen.setColor(Qt::black);
				selectedRectItem->setPen(cur_pen);
				selectedRectItem->check_state = Qt::Checked;
				//修改对应栏目
				emit signal_SendCheckedState(selectedRectItem, 2);
			}
		}
		break;
	case Qt::Key_2:
		//非导入模式下按键无效
		if (is_rect_item_loaded_from_file)
		{
			//将其他框设置为实线
			if (isRectSeleted)
			{
				auto cur_pen = rectItem->pen();
				cur_pen.setColor(Qt::green);
				selectedRectItem->setPen(cur_pen);
				selectedRectItem->check_state = Qt::PartiallyChecked;
				//修改对应栏目
				emit signal_SendCheckedState(selectedRectItem, 1);
			}
		}
		//Debug 20190725
	case Qt::Key_Control:
		//is_control_key_push = true;
		//std::cout << is_control_key_push << std::endl;
		break;
	
	default:
		QGraphicsView::keyPressEvent(event);

	}
	QRect sceneRect = QRect(QPoint(startPoint + moveOffset), QSize(sceneWidth, sceneHeight));
	if (tiffRec.contains(sceneRect)) {
		oldStartPoint = startPoint;
		startPoint += moveOffset;
		emit startPointChanged(startPoint);
	}
	else {
		QPoint moveX = QPoint(moveOffset.x(), 0);
		QPoint moveY = QPoint(0, moveOffset.y());
		sceneRect = QRect(QPoint(startPoint - moveX), QSize(sceneWidth, sceneHeight));
		if (tiffRec.contains(sceneRect)) {
			oldStartPoint = startPoint;
			startPoint -= moveX;
			emit startPointChanged(startPoint);
		}
		else {
			sceneRect = QRect(QPoint(startPoint - moveY), QSize(sceneWidth, sceneHeight));
			if (tiffRec.contains(sceneRect)) {
				oldStartPoint = startPoint;
				startPoint -= moveY;
				emit startPointChanged(startPoint);
			}
		}

	}
	//oldPoint = m_lastMousePos;
	update();

}
//Debug 20190925
void LocalGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Control:
		//is_control_key_push = false;
		break;
	default:
		QGraphicsView::keyPressEvent(event);
	}
	std::cout << is_control_key_push << std::endl;
}

QRect LocalGraphicsView::getRect(const QPointF &beginPoint, const QPointF& endPoint)
{
	int x, y, width, height;
	width = qAbs(beginPoint.x() - endPoint.x());
	height = qAbs(beginPoint.y() - endPoint.y());
	x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
	y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

	QRect selectedRect = QRect(x, y, width, height);
	if (selectedRect.width() == 0)
	{
		selectedRect.setWidth(1);
	}
	if (selectedRect.height() == 0)
	{
		selectedRect.setHeight(1);
	}
	return selectedRect;

}
// 平移
void LocalGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		m_lastMousePos = event->pos();
		QPoint moveOffset = m_lastMousePos - oldPoint;

		//拉近视角时将移速降低2倍
		if (isZoomIn) {
			moveOffset /= 2;
		}

		QRect sceneRect = QRect(QPoint(startPoint - moveOffset), QSize(sceneWidth, sceneHeight));
		if (tiffRec.contains(sceneRect)) {
			oldStartPoint = startPoint;
			startPoint -= moveOffset;
			emit startPointChanged(startPoint);
		}
		else {
			QPoint moveX = QPoint(moveOffset.x(), 0);
			QPoint moveY = QPoint(0, moveOffset.y());
			sceneRect = QRect(QPoint(startPoint - moveX), QSize(sceneWidth, sceneHeight));
			if (tiffRec.contains(sceneRect)) {
				oldStartPoint = startPoint;
				startPoint -= moveX;
				emit startPointChanged(startPoint);
			}
			else {
				sceneRect = QRect(QPoint(startPoint - moveY), QSize(sceneWidth, sceneHeight));
				if (tiffRec.contains(sceneRect)) {
					oldStartPoint = startPoint;
					startPoint -= moveY;
					emit startPointChanged(startPoint);
				}
			}
			
		}
		oldPoint = m_lastMousePos;
		update();
	}
	if (!is_region_painting_set&&event->buttons() & Qt::RightButton) {
		dragEndPoint = event->pos();
		QPoint buf = dragEndPoint - dragStartPoint;

		oldBuf = buf;
		if (isZoomIn) {
			dragEndPoint = dragEndPoint / 2 + QPoint(sceneWidth / 4, sceneHeight / 4);
			if (!(qAbs(rectTopLeft.x() - dragEndPoint.x()) <= 5 || qAbs(rectTopLeft.y() - dragEndPoint.y()) <= 5)) {
				rectItem->setRect(getRect(rectTopLeft, dragEndPoint));
				if (!rectItem->isCounted) {
					if (penIndex == 1) {
						redLabelNumber++;
						//qDebug() << "the red Label number is" << redLabelNumber;
						emit sendRedLabelNumbers(redLabelNumber);
					}
					else if (penIndex == 2) {
						greenLabelNumber++;
						emit sendGreenLabelNumbers(greenLabelNumber);
					}
					else if (penIndex == 3){
						blueLabelNumber++;
						emit sendBlueLabelNumbers(blueLabelNumber);
					}
					else if (penIndex == 4){
						yellowLabelNumber++;
						emit sendYellowLabelNumbers(yellowLabelNumber);
					}
					else {
						blackLabelNumber++;
						emit sendBlackLabelNumbers(blackLabelNumber);
					}
					rectItem->isCounted = true;

					//增加该区域的标记数量
					int navigationX = (int)(((rectTopLeft/2 + startPoint).x() + 0)*1.0f / sceneWidth);
					int navigationY = (int)(((rectTopLeft/2 + startPoint).y() + 0)*1.0f / sceneHeight);
					zoomOutMakerNumber[penIndex - 1][navigationX][navigationY]++;

					emit sendMakerNumber(zoomOutMakerNumber, zoomInMakerNumber);
				}
			}
		}
		else {
			if (!(qAbs(rectTopLeft.x() - dragEndPoint.x()) <= 3 || qAbs(rectTopLeft.y() - dragEndPoint.y()) <= 3)) {
				rectItem->setRect(getRect(rectTopLeft, dragEndPoint));
				if (!rectItem->isCounted) {
					if (penIndex == 1) {
						redLabelNumber++;
						//qDebug() << "the red Label number is" << redLabelNumber;
						emit sendRedLabelNumbers(redLabelNumber);
					}
					else if (penIndex == 2) {
						greenLabelNumber++;
						emit sendGreenLabelNumbers(greenLabelNumber);
					}
					else if (penIndex == 3){
						blueLabelNumber++;
						emit sendBlueLabelNumbers(blueLabelNumber);
					}
					else if (penIndex == 4){
						yellowLabelNumber++;
						emit sendYellowLabelNumbers(yellowLabelNumber);
					}
					else {
						blackLabelNumber++;
						emit sendBlackLabelNumbers(blackLabelNumber);
					}
					rectItem->isCounted = true;

					//增加该区域的标记数量
					int navigationX = (int)(((rectTopLeft + startPoint).x() + 0)*1.0f / sceneWidth);
					int navigationY = (int)(((rectTopLeft + startPoint).y() + 0)*1.0f / sceneHeight);
					zoomOutMakerNumber[penIndex-1][navigationX][navigationY]++;

					emit sendMakerNumber(zoomOutMakerNumber, zoomInMakerNumber);
				}
				
				
			}
		}

		//qDebug() << rectItem->rect();
		update();
	}
	if(is_region_painting_set)
	{
		// if (is_circle_draw)
		// {
		// 	circleMouseMoveEvent(event);
		// }
		// else
		// {
		// 	ploygonMouseMoveEvent(event);
		// }
	}

	QGraphicsView::mouseMoveEvent(event);
}

void LocalGraphicsView::mousePressEvent(QMouseEvent *event)
{
	// graphicsScene->removeItem(cur_ploygon);
	// delete cur_ploygon;
	// cur_ploygon = nullptr;
	//TODO

	if (/*!is_region_painting_set&&*/event->buttons() & Qt::LeftButton) {
		bool isRectHad = false;
		QList<QGraphicsItem*> items = graphicsScene->items();


		for each (QGraphicsItem* item in items)
		{
			if (item->type() == GraphicsRectItem::Type) {
				rectItem = qgraphicsitem_cast<GraphicsRectItem*>(item);

				if (!isRectHad&&rectItem->isUnderMouse()) {

					isRectHad = true;
					rectItem->setPen(getOldDotPen(rectItem));
					isRectSeleted = true;
					selectedRectItem = rectItem;
					if (is_rect_item_loaded_from_file)
					{
						emit signal_SendCurrentRectItem(item);
					}
					continue;

				}
				if (isRectSeleted || !rectItem->isUnderMouse()) {
					rectItem->setPen(getOldPen(rectItem));
				}
			}
		}

		//if (isRectSeleted) {
		//	selectedRectItem->setPen(getOldPen(selectedRectItem));
		//	isRectSeleted = false;
		//}

		if (!isRectHad) {
			isRectSeleted = false;

		}
		oldPoint = event->pos();
	}
	//判断该点是否在rect里面，如果在，记录该item
	if (!is_region_painting_set&&event->buttons()& Qt::RightButton) {
		isRectSeleted = false;
		if (isZoomIn) {
			if (!isRectSeleted) {
				rectTopLeft = event->pos();
				rectTopLeft = rectTopLeft / 2 + QPoint(sceneWidth / 4, sceneHeight / 4);
				//qDebug() << "isZoomIn RecTopLeft Point is: " << rectTopLeft;
				rectItem = new GraphicsRectItem(startPoint, penIndex);
				rectItem->setPen(getPen(penIndex));
				graphicsScene->addItem(rectItem);
			}
		}
		else {
			if (!isRectSeleted) {
				rectTopLeft = event->pos();
				//qDebug() << "isZoomOut RecTopLeft Point is: " << rectTopLeft;
				rectItem = new GraphicsRectItem(startPoint, penIndex);

				rectItem->setPen(getPen(penIndex));
				graphicsScene->addItem(rectItem);
			}
		}
	}


	//交互
	if (is_region_painting_set)
	{
		localPloygonMousePressEvent(event);
		// if (is_circle_draw)
		// {
		// 	circleMousePressEvent(event);
		// }
		// else
		// {
		// 	ploygonMousePressEvent(event);
		// }
	}
	QGraphicsView::mousePressEvent(event);
}

void LocalGraphicsView::localPloygonMousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::RightButton) {

		if(polygon_region.empty())
		{
			start_point = event->pos();
			cur_ploygon = new QGraphicsPathItem();
			//ploygon_items.push_back(cur_ploygon);
			cur_ploygon->setPen(redPen);
			cur_paint_path = QPainterPath();
			cur_paint_path.moveTo(start_point);
			cur_ploygon->setPath(cur_paint_path);
			graphicsScene->addItem(cur_ploygon);
			//point_count = 0;
			//clicked_polygon_type = 0;
			polygon_region.push_back(startPoint + start_point);
		}else
		{
			auto buf_point = event->pos();
			cur_paint_path.lineTo(buf_point);
			cur_ploygon->setPath(cur_paint_path);
			polygon_region.push_back(startPoint + buf_point);
		}
	}
}


void LocalGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{

	//if (isRectSeleted) {
//
	//	rectItem->setPen(QPen(Qt::red, 0.9, Qt::SolidLine, Qt::FlatCap));
	//	rectItem->update();
	//	isRectSeleted = false;

	//}
	if(is_region_painting_set)
	{
		// if (is_circle_draw)
		// {
		// 	circleMouseReleaseEvent(event);
		// }
		// else
		// {
		// 	ploygonMouseReleaseEvent(event);
		// }
	}

	QGraphicsView::mouseReleaseEvent(event);
}

// 放大/缩小
void LocalGraphicsView::wheelEvent(QWheelEvent *event)
{
	return;
	// 滚轮的滚动量
	QPoint scrollAmount = event->angleDelta();
	// 正值表示滚轮远离使用者（放大），负值表示朝向使用者（缩小）
	scrollAmount.y() > 0 ? zoomIn() : zoomOut();
}

// 放大
void LocalGraphicsView::zoomIn()
{
	return;
	zoom(1 + m_zoomDelta);
}

// 缩小
void LocalGraphicsView::zoomOut()
{
	return;
	zoom(1 - m_zoomDelta);
}

// 缩放 - scaleFactor：缩放的比例因子
void LocalGraphicsView::zoom(float scaleFactor)
{
	return;
	// 防止过小或过大
	qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < 0.07 || factor > 100)
		return;

	scale(scaleFactor, scaleFactor);
	m_scale *= scaleFactor;
}

// 平移
void LocalGraphicsView::translate(QPointF delta)
{
	return;
	// 根据当前 zoom 缩放平移数
	delta *= m_scale;
	delta *= m_translateSpeed;

	// view 根据鼠标下的点作为锚点来定位 scene
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	QPoint newCenter(tiffWidth / 2 - delta.x(), tiffWidth / 2 - delta.y());
	centerOn(mapToScene(newCenter));

	// scene 在 view 的中心点作为锚点
	setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void LocalGraphicsView::circleMouseMoveEvent(QMouseEvent* event)
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

void LocalGraphicsView::circleMousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::RightButton) {
		const QPointF circle_center = event->pos();
		cur_circle = new QGraphicsEllipseItem(QRectF(circle_center, QSizeF(0, 0)));
		cur_circle->setPen(redPen);
		circle_items.push_back(cur_circle);
		graphicsScene->addItem(cur_circle);
		//circle_number_map.insert(cur_circle, 0);
		circle_number_map[cur_circle] = 0;
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
				if (!isRectHad&&buf_item->isUnderMouse()) {

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

void LocalGraphicsView::circleMouseReleaseEvent(QMouseEvent* event)
{
	if(cur_circle)
	{
		emit sendCircle(cur_circle, startPoint);
	}

	//if (event->buttons() & Qt::RightButton) {
	//if (mouse_button_type == 0) {
	updateMarkerNumber();
	//}
}

void LocalGraphicsView::ploygonMouseMoveEvent(QMouseEvent* event)
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

void LocalGraphicsView::ploygonMousePressEvent(QMouseEvent* event)
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
		if (selected_ploygon!=nullptr)
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
				if (!isRectHad&&buf_item->isUnderMouse()) {

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

void LocalGraphicsView::ploygonMouseReleaseEvent(QMouseEvent* event)
{
	if (clicked_polygon_type == 0 && cur_ploygon != nullptr)
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
		//updateMarkerNumber();

		emit sendPolygon(cur_ploygon, startPoint);


	}
}

void LocalGraphicsView::getRemovePolygon(QGraphicsPathItem* item)
{
	if(item)
	{
		graphicsScene->removeItem(item);
	}
}

void LocalGraphicsView::setNewPolygon(QPainterPath painter_path, double factor)
{
	//获取原始坐标位置信息
	QVector<QPointF> path_origin;
	for(auto i=0;i< painter_path.elementCount();i++)
	{

		auto buf_path2 = static_cast<QPointF>(painter_path.elementAt(i))*factor;
		auto buf_path = buf_path2 - startPoint;
		painter_path.setElementPositionAt(i, buf_path.x(), buf_path.y());
		path_origin.push_back(buf_path2);
	}
	auto buf_path_item =  new QGraphicsPathItem();
	buf_path_item->setPen(redPen);
	buf_path_item->setPath(painter_path);
	graphicsScene->addItem(buf_path_item);

	emit sendLocalPolygon(path_origin, buf_path_item);
	update();
}
//Debug 20190727
void LocalGraphicsView::setNewPolygon(QPainterPath painter_path, double width_factor,double height_factor)
{
	//获取原始坐标位置信息
	QVector<QPointF> path_origin;
	for (auto i = 0; i < painter_path.elementCount(); i++)
	{

		auto buf_path2 = static_cast<QPointF>(painter_path.elementAt(i));
		//Debug 20190727
		buf_path2.setX(buf_path2.x()*width_factor);
		buf_path2.setY(buf_path2.y()*height_factor);
		auto buf_path = buf_path2 - startPoint;
		painter_path.setElementPositionAt(i, buf_path.x(), buf_path.y());
		path_origin.push_back(buf_path2);
	}
	auto buf_path_item = new QGraphicsPathItem();
	buf_path_item->setPen(redPen);
	buf_path_item->setPath(painter_path);
	graphicsScene->addItem(buf_path_item);

	emit sendLocalPolygon(path_origin, buf_path_item);
	update();
}


void LocalGraphicsView::setNewPolygonFromGlobalGraphicsView(QGraphicsPathItem*& item)
{
	auto buf_path = (item)->path();
	for (auto i = 0; i < buf_path.elementCount(); i++)
	{
		QPointF buf = buf_path.elementAt(i) - startPoint;
		buf_path.setElementPositionAt(i, buf.x(), buf.y());
	}
	(item)->setPath(buf_path);
	graphicsScene->addItem((item));
}

int LocalGraphicsView::getRectCountInPolygon(QPainterPath graphics_path)
{
	int count = 0;
	QList<QGraphicsItem*> items = graphicsScene->items();
	for each (QGraphicsItem* item in items)
	{
		if (item->type() == GraphicsRectItem::Type) {
			auto buf_item = qgraphicsitem_cast<GraphicsRectItem*>(item);
			if (buf_item->rect().width() > 2)
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


void LocalGraphicsView::updateMarkerNumber()
{
	if (is_circle_draw)
	{
		updataCircleMarkerNumber();
	}
	else
	{
		updatePolygonMarkerNumber();
		//emit sendPolygonMarker(startPoint,)
	}
	emit sendShapeNumberMap(circle_number_map, ploygon_number_map);
}

void LocalGraphicsView::updataCircleMarkerNumber()
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
			circle_number_map[selected_circle] = count;

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
		circle_number_map[cur_circle] = count;

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

}

void LocalGraphicsView::updatePolygonMarkerNumber()
{
	QList<QGraphicsItem*> items = graphicsScene->items();
	int count = 0;
	ploygon_number_map.clear();
	for each (QGraphicsItem* item in items)
	{
		if (item->type() == QGraphicsPathItem::Type) {
			auto buf_item = qgraphicsitem_cast<QGraphicsPathItem*>(item);
			int count_number = getRectCountInPolygon(buf_item->path());
			ploygon_number_map[buf_item] = count_number;
			//std::cout << "Number : " << count_number << std::endl;
		}
	}

}