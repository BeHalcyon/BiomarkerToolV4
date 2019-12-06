#pragma once

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include<QMouseEvent>
#include <QDebug>
#include <QKeyEvent>
class CaptureGraphicsItem : public QObject, public QGraphicsItem
{
	//Q_OBJECT

public:
	CaptureGraphicsItem(int sceneWidth,int sceneHeight, QPoint startPoint, QObject* object = nullptr);
	~CaptureGraphicsItem();
	void setStartPoint(QPoint startPoint);
	QRectF boundingRect() const;
protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget) Q_DECL_OVERRIDE;
	void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

	QRect getRect(const QPointF &beginPoint, const QPointF& endPoint);

	int sceneWidth;
	int sceneHeight;
	QPoint startPoint;
	QRectF boundingBox;
	bool isMousePressed;
	QPointF curBeginPoint;
	QPointF curEndPoint;
	QPointF curBeginMovePoint;
	QPointF curEndMovePoint;
	bool isRectSeleted;
	int seletedRectIndex;
	QRect selectedRect;
public:
	static QVector<QRect> captureRects;
	static int loadedNum;
};