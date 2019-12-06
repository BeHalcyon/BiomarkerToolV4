#include "GraphicsRectItem.h"

GraphicsRectItem::GraphicsRectItem(QPoint startPoint,int penIndex,QPoint localTopLeft)
{
	this->startPoint = startPoint;
	this->penType = penIndex;
	this->localTopLeft = localTopLeft;
}

GraphicsRectItem::~GraphicsRectItem()
{
}
