#pragma once

#include <QLabel>
#include <QPoint>
#include <QVector>
class CaptureLabel : public QLabel
{
	Q_OBJECT

public:
	CaptureLabel(QWidget *parent=nullptr);
	~CaptureLabel();

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void paintEvent(QPaintEvent *event);

	QRect getRect(const QPoint &beginPoint, const QPoint& endPoint);

	QVector<QRect>& getCaptureRects();
	void CaptureLabel::clearCaptureRects();

	bool isMousePressed;
	QPoint curBeginPoint;
	QPoint curEndPoint;
	QVector<QRect> captureRects;
};
