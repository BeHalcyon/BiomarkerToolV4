#pragma once

#include <QGraphicsItem>

class PictureItem : public QGraphicsItem
{
	Q_OBJECT

public:
	PictureItem(QWidget *parent);
	~PictureItem();
};
