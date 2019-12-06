#pragma once

#include <QGraphicsView>
#include <QKeyEvent>
#include <CaptureLabel.h>
#include "CaptureGraphicsItem.h"
#include <QGraphicsRectItem>
#include "GraphicsRectItem.h"
#include <QGraphicsPixmapItem>

class LocalGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	LocalGraphicsView( QWidget *parent = nullptr);
	~LocalGraphicsView();
	void updateImage(QPoint startPoint, QPixmap& pixmap);
	void setRectLoadedState(bool state);
	void setRectSelectedState(GraphicsRectItem* rect_item);

	void setTiffSize(int tiffWidth, int tiffHeight, int sceneWidth, int sceneHeight);
	void setStartPoint(const QPointF& start_point);
	bool inBoundingBox(QPoint startPos);
	QRect getRect(const QPointF &beginPoint, const QPointF& endPoint);
	QPen& getPen(int penIndex) {
		if (penIndex == 1)
			return this->redPen;
		else if (penIndex == 2)
			return this->greenPen;
		else if (penIndex == 3) 
			return this->bluePen;
		else if (penIndex == 4) 
			return this->yellowPen;
		else
			return this->blackPen;
	}
	QPen& getOldDotPen(GraphicsRectItem* item) {
		QPen oldPen = item->pen();
		if (oldPen.color() == Qt::red)
			return this->redDotPen;
		else if (oldPen.color() == Qt::green)
			return this->greenDotPen;
		else if (oldPen.color() == Qt::blue)
			return this->blueDotPen;
		else if (oldPen.color() == Qt::yellow)
			return this->yellowDotPen;
		else
			return this->blackDotPen;
	}
	QPen& getOldPen(GraphicsRectItem* item) {
		QPen oldPen = item->pen();
		if (oldPen.color() == Qt::red)
			return this->redPen;
		else if (oldPen.color() == Qt::green)
			return this->greenPen;
		else if (oldPen.color() == Qt::blue)
			return this->bluePen;
		else if (oldPen.color() == Qt::yellow)
			return this->yellowPen;
		else
			return this->blackPen;
	}

	void setNavigationWindowSize(int windowWidth, int windowHeight, float sclarFactor) {
		this->navigationWindowWidth = windowWidth;
		this->navigationWindowHeight = windowHeight;
		this->navigationScalarFactor = sclarFactor;
		//init
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < (int)(tiffWidth/sceneWidth)+1; i++) {

				QVector<int> zoomOutBuffer, zoomInBuffer;
				for (int j = 0; j < (int)(tiffHeight / sceneHeight) + 1; j++) {
					zoomOutBuffer.push_back(0);
					//2倍size
					zoomInBuffer.push_back(0);
					zoomInBuffer.push_back(0);
				}
				zoomOutMakerNumber[k].push_back(zoomOutBuffer);
				zoomInMakerNumber[k].push_back(zoomInBuffer);
				zoomInMakerNumber[k].push_back(zoomInBuffer);
			}
		}
	}
protected:

	
	// 上/下/左/右键向各个方向移动、加/减键进行缩放、空格/回车键旋转
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
	void keyReleaseEvent(QKeyEvent* event) override;
	// 平移
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void localPloygonMousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	// 放大/缩小
	void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
	public slots:
	void setZoomIn() {
		if (!isZoomIn) {
			isZoomIn = true;
			this->scale(2, 2);
			emit sendZoomInState(isZoomIn);
			update();
		}
	}
	void setZoomOut(){
		if (isZoomIn) {
			isZoomIn = false;
			this->scale(0.5, 0.5);
			emit sendZoomInState(isZoomIn);
			update();
		}
	}
	void setRedPen(){
		this->penIndex = 1; 
		emit sendPenType(penIndex);
		update();
	}
	void setGreenPen(){
		this->penIndex = 2; 
		emit sendPenType(penIndex);
		update();
	}
	void setBluePen(){
		this->penIndex = 3;
		emit sendPenType(penIndex);
		update();
	}
	void setYellowPen(){
		this->penIndex = 4; 
		emit sendPenType(penIndex);
		update();
	}
	void setBlackPen(){
		this->penIndex = 5; 
		emit sendPenType(penIndex);
		update();
	}
	public Q_SLOTS:
	void zoomIn();  // 放大
	void zoomOut();  // 缩小
	void zoom(float scaleFactor); // 缩放 - scaleFactor：缩放的比例因子
	void translate(QPointF delta);  // 平移
	void circleMouseMoveEvent(QMouseEvent* event);
	void circleMousePressEvent(QMouseEvent* event);
	
	void circleMouseReleaseEvent(QMouseEvent* event);
	void ploygonMouseMoveEvent(QMouseEvent* event);
	int getRectCountInPolygon(QPainterPath graphics_path);
	void updateMarkerNumber();
	void updataCircleMarkerNumber();
	void updatePolygonMarkerNumber();
	void ploygonMousePressEvent(QMouseEvent* event);
	
	void ploygonMouseReleaseEvent(QMouseEvent* event);

	void setCircleDrawState(bool state) { this->is_circle_draw = state; }
	
	void setRegionState(bool state) { this->is_region_painting_set = state; }

	void getRemovePolygon(QGraphicsPathItem* item);
	void setNewPolygon(QPainterPath painter_path, double factor);
	void setNewPolygon(QPainterPath painter_path, double width_factor, double height_factor);
	void setNewPolygonFromGlobalGraphicsView(QGraphicsPathItem*& item);

	Q_SIGNALS:
	void startPointChanged(QPointF);
	void sendZoomInState(bool);
	void sendRedLabelNumbers(int);
	void sendGreenLabelNumbers(int);
	void sendBlueLabelNumbers(int);
	void sendYellowLabelNumbers(int);
	void sendBlackLabelNumbers(int);
	//设置导航视图的透明颜色，发送该items
	void sendGraphicsItems(QList<QGraphicsItem*>&);
	void sendMakerNumber(QVector<QVector<int>>* zoomOutMakerNumber, QVector<QVector<int>>* zoomInMakerNumber);
	void sendPenType(int);
	void signal_SendCurrentRectItem(QGraphicsItem* item);
	void signal_SendCheckedState(GraphicsRectItem* item, int i);

	void sendShapeNumberMap(const QMap<QGraphicsEllipseItem*, int>& is, const QMap<QGraphicsPathItem*, int>& map);
	void sendSelectedShape(const QMap<QGraphicsEllipseItem*, int>& circle_number_map, const QMap<QGraphicsPathItem*, int>& polygon_number_map, QGraphicsItem* selectedItem);
	void sendPolygon(QGraphicsPathItem* cur_ploygon, const QPoint& point);
	void sendCircle(QGraphicsEllipseItem* cur_circle, const QPoint& point);
	void sendLocalPolygon(const QVector<QPointF>& vector, QGraphicsPathItem* path_item);
private:
	Qt::MouseButton m_translateButton;  // 平移按钮
	qreal m_translateSpeed;  // 平移速度
	qreal m_zoomDelta;  // 缩放的增量
	bool m_bMouseTranslate;  // 平移标识
	QPoint m_lastMousePos;  // 鼠标最后按下的位置
	qreal m_scale;  // 缩放值
	int tiffWidth;
	int tiffHeight;
	int sceneWidth;
	int sceneHeight;
	int xOffset = 20;
	int yOffset = 20;
	
	QPoint oldPoint;
	
	CaptureGraphicsItem* captureGraphicsItem;
	
	GraphicsRectItem* rectItem;
	QPointF rectTopLeft;
	QPoint oldStartPoint;
	QPixmap *oldPixmap;
	QGraphicsPixmapItem *pixmapItem;
	QPoint dragStartPoint;
	QPoint dragEndPoint;
	QPointF selectedRectTopLeft;
	QPoint oldBuf;
	bool isRectSeleted;
	GraphicsRectItem *selectedRectItem;
	QRect boundingBox;
	bool isZoomIn;
	QRect tiffRec;


	
	int penIndex;

	QPen redPen;
	QPen greenPen;
	QPen bluePen;
	QPen yellowPen;
	QPen blackPen;
	QPen redDotPen;
	QPen greenDotPen;
	QPen blueDotPen;
	QPen yellowDotPen;
	QPen blackDotPen;

	int navigationWindowWidth;
	int navigationWindowHeight;
	float navigationScalarFactor;
	bool is_rect_item_loaded_from_file = false;

	//Debug 20190725
	bool is_control_key_push = false;
	QMap<QGraphicsPathItem*, int> ploygon_number_map;
	QMap<QGraphicsEllipseItem*, int> circle_number_map;

	QPainterPath cur_paint_path;
	QGraphicsPathItem* cur_ploygon;
	QGraphicsPathItem* selected_ploygon;
	int point_count = 0;
	QPointF start_point;
	bool is_ploygon_selected;
	int clicked_polygon_type;


	bool is_circle_draw = false;
	QList<QGraphicsEllipseItem*> circle_items;
	QGraphicsEllipseItem* cur_circle;
	QGraphicsEllipseItem* selected_circle;
	QPen circle_pen;
	QBrush circle_brush;
	bool is_circle_selected;

	int mouse_button_type = -1;
	QPointF old_top_left;
	QPointF old_point;



	//Debug 20190726
	bool is_region_painting_set = false;
	QVector<QPointF> polygon_region;

public:
	QGraphicsScene* graphicsScene;
	QPoint startPoint;
	QVector<QVector<int>> zoomOutMakerNumber[5];
	QVector<QVector<int>> zoomInMakerNumber[5];

	int redLabelNumber = 0;
	int greenLabelNumber = 0;
	int blueLabelNumber = 0;
	int yellowLabelNumber = 0;
	int blackLabelNumber = 0;
};
