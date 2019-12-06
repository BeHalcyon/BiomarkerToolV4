#include "CaptureLabel.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

CaptureLabel::CaptureLabel(QWidget *parent)
	: QLabel(parent)
{
	isMousePressed = false;
	setStyleSheet("border:1px solid gray");
}

CaptureLabel::~CaptureLabel()
{
}



void CaptureLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		isMousePressed = true;
		curBeginPoint = event->pos();
	}
	return QWidget::mousePressEvent(event);
}

void CaptureLabel::mouseMoveEvent(QMouseEvent *event)
{
	if (isMousePressed)
	{
		curEndPoint = event->pos();
		update();
	}
	return QWidget::mouseMoveEvent(event);
}

void CaptureLabel::mouseReleaseEvent(QMouseEvent *event)
{
	curEndPoint = event->pos();
	isMousePressed = false;
	captureRects.push_back(getRect(curBeginPoint, curEndPoint));
	return QWidget::mouseReleaseEvent(event);

}

void CaptureLabel::keyPressEvent(QKeyEvent *event)
{

}

void CaptureLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);
	QPainter painter(this);

	QColor shadowColor = QColor(0, 0, 0, 100);
	painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));

	for (int i = 0; i < captureRects.size(); i++)
	{
		painter.drawRect(captureRects[i]);
	}

	if (isMousePressed)
	{
		QRect curRect = getRect(curBeginPoint, curEndPoint);
		painter.drawRect(curRect);
	}
}

QRect CaptureLabel::getRect(const QPoint &beginPoint, const QPoint& endPoint)
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

QVector<QRect>& CaptureLabel::getCaptureRects()
{
	return captureRects;
}

void CaptureLabel::clearCaptureRects()
{
	captureRects.clear();
	update();
}