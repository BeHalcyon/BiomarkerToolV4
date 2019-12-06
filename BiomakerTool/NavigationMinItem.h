#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
class NavigationMinItem : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	NavigationMinItem();
	NavigationMinItem(QRectF boundingBox, QPointF startPoint, int sliderRecWidth, int sliderRecHeight);
	void setFactor(float factor) {
		this->factor = factor;
	}
	public slots:
	void setShowNavigationMinWindow(QPoint);
signals:
	void sendCenterPoint(QPointF center);
protected:
	QRectF boundingRect() const
	{
		//qreal penWidth = 1;
		return this->boundingBox;
		//qreal penWidth = 1;
		//return QRectF(- penWidth / 2, penWidth / 2,
		//	20 + penWidth, 20 + penWidth);
	}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget)
	{
		qDebug() << currentBox;
		painter->drawRect(currentBox);
		
		//painter->drawRoundedRect(0, 0, 20, 20, 5, 5);
	}
	void mousePressEvent(QGraphicsSceneMouseEvent *event) {

		QPointF curPoint = event->pos();
	
		if (event->buttons()&Qt::LeftButton) {
		//if (currentBox.contains(curPoint)) {
			oldPoint = curPoint;
			//setCursor(Qt::PointingHandCursor);
		}
		
		if (boundingBox.contains(QRectF(curPoint + offset, QSize(sliderRecWidth, sliderRecHeight))))
			startPoint = curPoint + offset;
		currentBox = QRectF(startPoint, QSize(sliderRecWidth, sliderRecHeight));
		emit sendCenterPoint(currentBox.topLeft());
		update();
		//QGraphicsItem::mousePressEvent(event);
	}

	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
		//qDebug() << m_lastMousePos;
		//if (event->button() == Qt::LeftButton) {
			m_lastMousePos = event->pos();
			QPointF moveOffset = m_lastMousePos - oldPoint;
			//moveOffset.setX(-moveOffset.x());
			if (boundingBox.contains(QRectF(startPoint, QSize(sliderRecWidth, sliderRecHeight)))) {
				startPoint += moveOffset;
			}
			else {
				QPointF moveX = QPointF(moveOffset.x(), 0);
				QPointF moveY = QPointF(0, moveOffset.y());

				if (boundingBox.contains(QRectF(startPoint + moveX, QSize(sliderRecWidth, sliderRecHeight)))) {
					startPoint += moveX;
				}
				else if (boundingBox.contains(QRectF(startPoint + moveY, QSize(sliderRecWidth, sliderRecHeight)))) {
					startPoint += moveY;
				}
			}

			//qDebug() << m_lastMousePos;
			oldPoint = m_lastMousePos;
			currentBox = QRectF(startPoint, QSize(sliderRecWidth, sliderRecHeight));
			emit sendCenterPoint(currentBox.topLeft());
			update();
		//}
		//QGraphicsItem::mouseMoveEvent(event);
	}
public:
	~NavigationMinItem();


private:
	QRectF boundingBox;
	QRectF currentBox;
	QPointF startPoint;
	int sliderRecWidth;
	int sliderRecHeight;
	QPointF oldPoint;
	QPointF m_lastMousePos;
	QPointF offset;
	float factor;
};