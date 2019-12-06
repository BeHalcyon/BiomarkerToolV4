#include "PloygonArea.h"
#include <QGraphicsPathItem>
#include <QStack>
#include <QSet>
#include <QPoint>
#include <set>

uint qHash(const QPoint&p)
{
	return p.y() * 1000000 + p.x();
}

PloygonArea::PloygonArea(QGraphicsPathItem* item, double width_factor, double height_factor, int tiff_width, int tiff_height)
{
	path = item->path();
	for(auto i=0;i<path.elementCount();i++)
	{
		QPointF buf_point = path.elementAt(i);
		path.setElementPositionAt(i, buf_point.x()*width_factor, buf_point.y()*height_factor);
	}
	this->tiff_width = tiff_width;
	this->tiff_height = tiff_height;
}

PloygonArea::~PloygonArea()
{
}

int PloygonArea::getArea()
{
	QPointF p1 = path.elementAt(0);
	QPointF p2 = path.elementAt(1);
	QPointF p3 = path.elementAt(2);

	auto seed_point = ((p1 + p2 + p3)/3).toPoint();

	int area_count = 0;
	QStack<QPoint> point_stack;
	QSet<QPoint> accessed_point;
	//只需要找一个种子点
	if(path.contains(seed_point))
	{
		point_stack.push(seed_point);
		while(!point_stack.empty())
		{
			const auto top_point = point_stack.top();
			point_stack.pop();

			accessed_point.insert(top_point);

			area_count++;
			for(auto i=0;i<4;i++)
			{
				auto p = top_point + getEightNeighborhoodOffset(i);
				if (p.x() >= tiff_width || p.x() < 0 || p.y() >= tiff_height || p.y() < 0) continue;
				//是否已经访问过
				if (accessed_point.contains(p)) continue;

				if (!path.contains(p)) continue;

				point_stack.push(p);
				area_count++;
			}
		}
	}
	return area_count;
}


size_t PloygonArea::calArea()
{

	int size = path.elementCount();

	if (size < 3) return 0;

	double Area = 0;

	for (int i = 0; i < size; ++i)
	{
		QPointF p1 = path.elementAt(i);
		QPointF p2 = path.elementAt((i+1)%size);
		QPointF p3 = path.elementAt((i - 1 + size) % size);
		Area += p1.x() * double(p2.y()-p3.y());
	}

	Area = size_t(0.5 + fabs(double(Area) / 2.0));

	return Area;
}


QPoint PloygonArea::getEightNeighborhoodOffset(int index) const
{

	if (index == 0) return QPoint(-1,0);
	if (index == 1) return QPoint(0,-1);
	if (index == 2) return QPoint(1,0);
	if (index == 3) return QPoint(0,1);

	//if (index == 4) return -histogram_dimension - 1;
	//if (index == 5) return -histogram_dimension + 1;
	//if (index == 6) return histogram_dimension + 1;
	//if (index == 7) return histogram_dimension - 1;

	return QPoint(0,0);
}