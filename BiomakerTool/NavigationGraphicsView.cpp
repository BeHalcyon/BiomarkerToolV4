#include "NavigationGraphicsView.h"

NavigationGraphicsView::NavigationGraphicsView(int width, int height, QWidget *parent)
	: QGraphicsView(parent)
{
	this->width = width;
	this->height = height;
	setGeometry(0, 0, width, height);

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setRenderHint(QPainter::Antialiasing);
	navigationScene = new QGraphicsScene();
	setScene(navigationScene);
	isRectItemSelected = false;

	isZoomIn = false;

	this->zoomOutMakerNumber = nullptr;
	this->zoomInMakerNumber = nullptr;

	//pen[0] = QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap);
	//pen[1] = QPen(Qt::green, 1, Qt::SolidLine, Qt::FlatCap);
	//pen[2] = QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap);
	//pen[3] = QPen(Qt::yellow, 1, Qt::SolidLine, Qt::FlatCap);
	//pen[4] = QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap);
}

void NavigationGraphicsView::setImage(QImage* image) {
	this->image = image;
	navigationScene->addPixmap(QPixmap::fromImage(*image));
	startPoint = QPoint(geometry().x() / 2, geometry().y() / 2);
	update();
}

void NavigationGraphicsView::setNavigationMinWindowSize(float minWindowWidth, float minWindowHeight) {
	this->minWindowWidth = minWindowWidth;
	this->minWindowHeight = minWindowHeight;
	//navigationMinItem = new NavigationMinItem(QRectF(0, 0, width, height), startPoint, minWindowWidth, minWindowHeight);
	boundingBox = QRectF(0, 0, image->width(), image->height());
	offset = QPointF(minWindowWidth / 2, minWindowHeight / 2);
	
	QRectF navagationRect = QRectF(QPointF(image->width() / 2 - minWindowWidth / 2, image->height() / 2 - minWindowHeight / 2), QSize(minWindowWidth, minWindowHeight));

	navigationItem = new QGraphicsRectItem(navagationRect);
	navigationItem->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
	navigationScene->addItem(navigationItem);
	

	for (float x = 0; x <= image->width(); x += minWindowWidth) {
		for (float y = 0; y <= image->height(); y += minWindowHeight) {
			navigationScene->addRect(x, y, minWindowWidth, minWindowHeight, QPen(Qt::black, 0.2, Qt::SolidLine, Qt::FlatCap));
		}
	}

	//for (int x = 0; x <= image->width(); x += minWindowWidth)
	//	navigationScene->addLine(x, 0, x, image->height(), QPen(Qt::black, 0.5, Qt::SolidLine, Qt::FlatCap));

	//for (int y = 0; y <= image->height(); y += minWindowHeight)
	//	navigationScene->addLine(0, y, image->width(), y, QPen(Qt::black, 0.5, Qt::SolidLine, Qt::FlatCap));

	update();
}

NavigationGraphicsView::~NavigationGraphicsView()
{
}
void NavigationGraphicsView::setFactor(float factor) {
	this->factor = factor;
}

void NavigationGraphicsView::mousePressEvent(QMouseEvent *event) {
	QPointF curPoint = event->pos();
	if (event->buttons()&Qt::LeftButton) {
		oldPoint = curPoint;
		QPoint integerPoint = curPoint.toPoint();

		//确定显示到某个方格内
		if (!isZoomIn) {
			float xCoord = (int)(curPoint.x() / minWindowWidth);
			float yCoord = (int)(curPoint.y() / minWindowHeight);
			xCoord *= minWindowWidth;
			yCoord *= minWindowHeight;
			rectItemStartPoint = QPointF(xCoord, yCoord);
			if (oldRecItemStartPoint == rectItemStartPoint) return;
			currentBox = QRectF(rectItemStartPoint, QSize(minWindowWidth, minWindowHeight));
		}
		else {
			float xCoord = (int)(integerPoint.x() / (minWindowWidth / 2));
			float yCoord = (int)(integerPoint.y() / (minWindowHeight / 2));
			xCoord *= minWindowWidth / 2;
			yCoord *= minWindowHeight / 2;
			//中心点更换了
			rectItemStartPoint = QPointF(xCoord, yCoord);
			if (oldRecItemStartPoint == rectItemStartPoint) return;
			currentBox = QRectF(rectItemStartPoint, QSize(minWindowWidth / 2, minWindowHeight / 2));
		}

		if (boundingBox.contains(currentBox)) {
			
			navigationItem->setRect(currentBox);
			oldRecItemStartPoint = rectItemStartPoint;

			emit sendCenterPoint(rectItemStartPoint);
			update();
		}
	}
}
void NavigationGraphicsView::mouseReleaseEvent(QMouseEvent *event){

}

QRect NavigationGraphicsView::getRect(const QPoint &beginPoint, const QPoint& endPoint)
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
void NavigationGraphicsView::setShowNavigationMinWindow(QPointF globalPoint) {
	rectItemStartPoint.setX(globalPoint.x()*1.0f *factor);
	rectItemStartPoint.setY(globalPoint.y()*1.0f *factor);

	if (isZoomIn) {
		currentBox = QRectF(rectItemStartPoint + QPointF(minWindowWidth / 4.0, minWindowHeight / 4.0), QSize(minWindowWidth / 2, minWindowHeight / 2));
	}
	else
		currentBox = QRectF(rectItemStartPoint, QSize(minWindowWidth, minWindowHeight));

	navigationItem->setRect(currentBox);
	//navigationItem->setPen(pen[penType-1]);
	update();
}
void NavigationGraphicsView::setZoomInState(bool state) {
	if (isZoomIn != state) {
		this->isZoomIn = state;
		QList<QGraphicsItem*> items = navigationScene->items();
		for each (QGraphicsItem* item in items)
		{
			if (item->type() == QGraphicsRectItem::Type) {
				QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem*>(item);
				if (rect == navigationItem) continue;
				navigationScene->removeItem(item);
				items.removeOne(item);
				delete item;
			}
		}
		if (isZoomIn) {

			for (float x = 0; x <= image->width(); x += minWindowWidth/2) {
				for (float y = 0; y <= image->height(); y += minWindowHeight / 2) {
					navigationScene->addRect(x, y, minWindowWidth/2, minWindowHeight/2, QPen(Qt::black, 0.2, Qt::SolidLine, Qt::FlatCap));
				}
			}

			QPointF buffer = rectItemStartPoint + QPointF(minWindowWidth / 4.0, minWindowHeight / 4.0);
			currentBox = QRectF(buffer, QSize(minWindowWidth / 2, minWindowHeight / 2));
			if (boundingBox.contains(currentBox))
				navigationItem->setRect(currentBox);
		}
		else {
			for (float x = 0; x <= image->width(); x += minWindowWidth) {
				for (float y = 0; y <= image->height(); y += minWindowHeight) {
					navigationScene->addRect(x, y, minWindowWidth, minWindowHeight, QPen(Qt::black, 0.2, Qt::SolidLine, Qt::FlatCap));
				}
			}

			QPointF buffer = rectItemStartPoint - QPointF(minWindowWidth / 4.0, minWindowHeight / 4.0);
			currentBox = QRectF(buffer, QSize(minWindowWidth, minWindowHeight));
			if (boundingBox.contains(currentBox))
				navigationItem->setRect(currentBox);
			setMakerNumber(nullptr, nullptr);
		}
	}


	update();
}