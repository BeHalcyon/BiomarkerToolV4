#pragma once
#include <QPainter>
class QGraphicsPathItem;

class PloygonArea
{
public:
	PloygonArea(QGraphicsPathItem* item, double width_factor, double height_factor, int tiff_width, int tiff_height);
	~PloygonArea();

	int getArea();
	size_t calArea();
	QPoint getEightNeighborhoodOffset(int index) const;

private:
	QPainterPath path;
	int tiff_width;
	int tiff_height;
};

