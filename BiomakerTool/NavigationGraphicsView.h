#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "NavigationMinItem.h"
#include <QGraphicsRectItem>
#include <QImage>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QGraphicsLineItem>
class NavigationGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	NavigationGraphicsView(int width, int height, QWidget *parent);
	~NavigationGraphicsView();
	void setNavigationMinWindowSize(float minWindowWidth, float minWindowHeight);
	void setImage(QImage* image);
	void setFactor(float factor);

	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

	QRect getRect(const QPoint &beginPoint, const QPoint& endPoint);
	QColor getColor(int penType, int num){
		int scalar = 5;
		if (penType == 1) {
			return QColor(255, 0, 0, scalar * num);
		}
		else if (penType == 2) {
			return QColor(0, 255, 0, scalar * num);
		}
		else if (penType == 3) {
			return QColor(0, 0, 255, scalar * num);
		}
		else if (penType == 4) {
			return QColor(255, 255, 0, scalar * num);
		}
		else {
			return QColor(0, 0, 0, scalar * num);
		}
	}
signals:
	void sendCenterPoint(QPointF centerPoint);
	public slots:
	void setShowNavigationMinWindow(QPointF globalPoint);
	void setZoomInState(bool state);
	void getGraphicsItems(QList<QGraphicsItem*>& items) {
		this->graphicsItems = items;
	}
	void setMakerNumber(QVector<QVector<int>>* zoomOutMakerNumber, QVector<QVector<int>>* zoomInMakerNumber) {
		if (zoomOutMakerNumber) {
			this->zoomOutMakerNumber = zoomOutMakerNumber;
		}
		if (zoomInMakerNumber) {
			this->zoomInMakerNumber = zoomInMakerNumber;
		}
		if (this->zoomOutMakerNumber == nullptr) {
			return;
		}
		
		if (!isZoomIn) {

			for (int i = 0; i < this->zoomOutMakerNumber[penType - 1].size(); i++) {
				for (int j = 0; j < this->zoomOutMakerNumber[penType - 1][i].size(); j++) {
					int num = this->zoomOutMakerNumber[penType - 1][i][j];
					if (num < 0)
						num = 0;
					QPointF innerPoint(i*minWindowWidth + 0.10f, j*minWindowHeight + 0.10f);
					QList<QGraphicsItem*> items = navigationScene->items();
					for each (QGraphicsItem* item in items)
					{
						if (item->type() == QGraphicsRectItem::Type) {
							QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
							if (rectItem != navigationItem&&rectItem->rect().contains(innerPoint)) {
								
								rectItem->setBrush(QBrush(getColor(penType, num)));
								break;
							}
						}
					}
				}
			}
			update();
		}
		
	}

	void setPenType(int penType) {
		this->penType = penType;
		setMakerNumber(nullptr, nullptr);
		//this->navigationItem->setPen(pen[penType - 1]);
		update();
	}
protected:


private:
	QGraphicsScene* navigationScene;
	int width;
	int height;
	float minWindowWidth;
	float minWindowHeight;
	QPoint startPoint;
	QImage* image;
	QPointF oldPoint;
	QRectF boundingBox;
	QPointF offset;
	QPointF rectItemStartPoint;
	QPointF oldRecItemStartPoint;
	QRectF currentBox;
	bool isRectItemSelected;
	float factor;
	bool isZoomIn;

	int penType = 1;
	QVector<QVector<int>>* zoomOutMakerNumber;
	QVector<QVector<int>>* zoomInMakerNumber;
	QPen pen[5];

public:
	NavigationMinItem* navigationMinItem;
	QGraphicsRectItem* navigationItem;
	QList<QGraphicsItem*> graphicsItems;
};
