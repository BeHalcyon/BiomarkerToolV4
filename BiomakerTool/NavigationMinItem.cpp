#include "NavigationMinItem.h"

NavigationMinItem::NavigationMinItem(){

}
NavigationMinItem::NavigationMinItem(QRectF boundingBox, QPointF startPoint, int sliderRecWidth, int sliderRecHeight)
{
	this->boundingBox = boundingBox;
	this->startPoint = startPoint;
	this->sliderRecHeight = sliderRecHeight;
	this->sliderRecWidth = sliderRecWidth;
	currentBox = QRectF(startPoint, QSize(sliderRecWidth, sliderRecHeight));
	offset = QPointF(-sliderRecWidth / 2, -sliderRecHeight / 2);
	startPoint += offset;

}

void NavigationMinItem::setShowNavigationMinWindow(QPoint globalPoint) {
	startPoint.setX(globalPoint.x()*1.0f *factor);
	startPoint.setY(globalPoint.y()*1.0f *factor);
	currentBox = QRectF(startPoint, QSize(sliderRecWidth, sliderRecHeight));
	update();
}

NavigationMinItem::~NavigationMinItem()
{
}
