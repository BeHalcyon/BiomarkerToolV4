#pragma once

#include <QGraphicsView>
#include <QMouseEvent>
class GlobalGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	GlobalGraphicsView(QWidget *parent = nullptr);
	~GlobalGraphicsView();

	void updateImage(QPixmap& pixmap);
	void updateRects(QList<QGraphicsItem*>& items, double factor);
	void updateRects(QList<QGraphicsItem*>& items, double width_factor, double height_factor);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

	void updataCircleMarkerNumber();
	void updataCircleMarkerNumber2();
	size_t getCircleArea(QGraphicsEllipseItem* item);
	void updatePolygonMarkerNumber();
	void updateMarkerNumber();
	void mouseReleaseEvent(QMouseEvent* event) override;

	
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;

	void circleMouseMoveEvent(QMouseEvent* event);
	void circleMousePressEvent(QMouseEvent* event);
	void circleMouseReleaseEvent(QMouseEvent* event);

	void ploygonMouseMoveEvent(QMouseEvent* event);
	int getRectCountInPolygon(QPainterPath graphics_path);
	size_t getPolygonArea(QGraphicsPathItem* item);
	void ploygonMousePressEvent(QMouseEvent* event);
	
	void ploygonMouseReleaseEvent(QMouseEvent* event);
	void setSelectedItem(QGraphicsEllipseItem* item);
	void setSelectedItem(QGraphicsPathItem* item);
	QMap<QGraphicsPathItem*, QString>& exportPathItem();
	QMap<QGraphicsEllipseItem*, QString>& exportCircleItem();

	//void circleKeyPressEvent(QKeyEvent* event);

	void setCircleDrawState(bool state) { this->is_circle_draw = state; }

	void getPolygon(QGraphicsPathItem* cur_ploygon, const QPoint& point);
	void getCircle(QGraphicsEllipseItem* buf_circle, const QPoint& point);
	void getLocalPolygon(const QVector<QPointF>& vector, QGraphicsPathItem* path_item);
	QGraphicsPathItem* getCurPolgyon() const;
signals:
	void sendCircleNumberMap(const QMap<QGraphicsEllipseItem*, QString>& is);
	void sendShapeNumberMap(QMap<QGraphicsEllipseItem*, QString>& is, QMap<QGraphicsPathItem*, QString>& map);
	void sendSelectedShape(const QMap<QGraphicsEllipseItem*, QString>& circle_number_map,
	                       const QMap<QGraphicsPathItem*, QString>& polygon_number_map, QGraphicsItem* selectedItem);
	void sendRemoveCommand(QGraphicsPathItem* graphics_path_item);
	void sendNewPolygonToLocalGraphicsView(QGraphicsPathItem*& buf_item);
private:
	
	QGraphicsPixmapItem *pixmapItem{};
	QList<QGraphicsEllipseItem*> circle_items;
	QMap<QGraphicsEllipseItem*, QString> circle_number_map;
	QGraphicsEllipseItem* cur_circle;
	QGraphicsEllipseItem* selected_circle;
	QPen circle_pen;
	QBrush circle_brush;
	bool is_circle_selected;
	QPen blackDotPen;
	QPen blackPen;

	QPen redDotPen;
	QPen redPen;
	int mouse_button_type = -1;

	QPointF old_top_left;
	QPointF old_point;

	bool is_circle_draw = false;
	QPainterPath cur_paint_path;
	QGraphicsPathItem* cur_ploygon;
	QGraphicsPathItem* selected_ploygon;
	int point_count = 0;
	QPointF start_point;
	bool is_ploygon_selected;
	QList<QGraphicsPathItem*> ploygon_items;
	QMap<QGraphicsPathItem*, QString> ploygon_number_map;
	int clicked_polygon_type;

	//Debug 20190726
	bool is_control_key_push = false;
	double factor = 1;
	//Debug 20190727
	double width_factor = 1;
	double height_factor = 1;


	QMap<QGraphicsPathItem*, QGraphicsPathItem*> local_path_items;
	QGraphicsPathItem* buf_item;

public:
	QGraphicsScene* graphicsScene;
};
