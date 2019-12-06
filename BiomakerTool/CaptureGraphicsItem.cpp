#include "CaptureGraphicsItem.h"

CaptureGraphicsItem::CaptureGraphicsItem(int sceneWidth, int sceneHeight, QPoint startPoint, QObject* object)
	:QObject(object)
{
	this->sceneWidth = sceneWidth;
	this->sceneHeight = sceneHeight;
	this->startPoint = startPoint;
	boundingBox = QRectF(0, 0, sceneWidth, sceneHeight);
	isMousePressed = false;
	isRectSeleted = false;
	seletedRectIndex = -1;
	setAcceptedMouseButtons(Qt::RightButton);
	setFlag(QGraphicsItem::ItemIsSelectable);
}

CaptureGraphicsItem::~CaptureGraphicsItem()
{

}
void CaptureGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	QColor shadowColor = QColor(0, 0, 0, 100);
	painter->setPen(QPen(Qt::red, 0.8, Qt::SolidLine, Qt::FlatCap));
	for (int i = 0; i < captureRects.size(); i++)
	{
		if (i == seletedRectIndex&&isRectSeleted) {
			painter->setPen(QPen(Qt::red, 0.9, Qt::DotLine, Qt::FlatCap));
		}
		else {
			painter->setPen(QPen(Qt::red, 0.8, Qt::SolidLine, Qt::FlatCap));
		}
		QRect curRect = captureRects[i];
		curRect.moveTopLeft(QPoint(curRect.topLeft()) - startPoint);
		painter->drawRect(curRect);
	}
	if (!(qAbs(curBeginPoint.x() - curEndPoint.x()) <= 5 || qAbs(curBeginPoint.y() - curEndPoint.y()) <= 5) &&
		!(curBeginPoint.x() <= 1 && curBeginPoint.y() <= 1) && !(curEndPoint.x() <= 1 && curEndPoint.y() <= 1)) {
		QRect curRect = getRect(curBeginPoint, curEndPoint);
		//captureRects.push_back(curRect);
		painter->drawRect(curRect);
	}
}

void CaptureGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {

	//whether the rects are seleted
	if (event->button() == Qt::RightButton) {
		if (isRectSeleted&&!selectedRect.contains(event->pos().toPoint() + startPoint)) {
			isRectSeleted = false;
			update();
		}
		//Ѱ�Ҹõ��Ƿ���ָ���������ڣ���������¼״̬
		for (int i = 0; i < captureRects.size(); i++)
		{
			if (captureRects[i].contains(event->pos().toPoint() + startPoint)) {
				seletedRectIndex = i;
				selectedRect = captureRects[i];
				isRectSeleted = true;
				break;
			}
		}
		if (isRectSeleted) {
			isMousePressed = false;
			curBeginMovePoint = event->pos();
			update();
			//return;
		}
		else {
			//�õ㲻��ָ�������ڣ�˵��û�е��ѡ�񣬸�����£���¼ѡ���
			//������о�����ѡ��״̬����ȥ����״̬
			if (isRectSeleted) {
				isRectSeleted = false;
			}
			isMousePressed = true;
			curBeginPoint = event->pos();
			update();
		}
	}
	//QGraphicsItem::mousePressEvent(event);
}

void CaptureGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
	//�������
	//1.������������ڣ����ƶ���������
	if (isRectSeleted) {
		curEndMovePoint = event->pos();
		if (!(curEndMovePoint.x() <= 1 && curEndMovePoint.y() <= 1) && selectedRect.contains(curBeginMovePoint.toPoint() + startPoint)) {
			QRect curRec = captureRects[seletedRectIndex];
			curRec.moveTopLeft(selectedRect.topLeft() + (curEndMovePoint - curBeginMovePoint).toPoint());
			captureRects[seletedRectIndex] = curRec;
			update();
		}

	}
	//2.����㲻�������ڣ������µľ�������
	else if (isMousePressed) {
		curEndPoint = event->pos();
		update();
	}

}
void CaptureGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	//�������
	//1.�����ѡ�������ڣ�����Ҫ�仯
	if (isRectSeleted) {

	}
	else if (isMousePressed) {
		if (!(qAbs(curBeginPoint.x() - curEndPoint.x()) <= 5 || qAbs(curBeginPoint.y() - curEndPoint.y()) <= 5) &&
			!(curBeginPoint.x() <= 1 && curBeginPoint.y() <= 1) && !(curEndPoint.x() <= 1 && curEndPoint.y() <= 1)) {
			QRect curRect = getRect(curBeginPoint, curEndPoint);
			curRect.moveTopLeft(QPoint(curRect.topLeft()) + startPoint);
			captureRects.push_back(curRect);
			isMousePressed = false;
		}
	}
	QGraphicsItem::mouseReleaseEvent(event);
}
QRect CaptureGraphicsItem::getRect(const QPointF &beginPoint, const QPointF& endPoint)
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
void CaptureGraphicsItem::setStartPoint(QPoint startPoint){
	this->startPoint = startPoint;
}
QRectF CaptureGraphicsItem::boundingRect() const
{
	return this->boundingBox;
}
void CaptureGraphicsItem::keyPressEvent(QKeyEvent *event) {
	
	if (event->key() == Qt::Key_Delete) {

		if (isRectSeleted) {
			QRect& buffer = captureRects[seletedRectIndex];
			//captureRects.rem);
			update();
		}


	}
}