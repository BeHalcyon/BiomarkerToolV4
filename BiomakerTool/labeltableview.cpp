#include "labeltableview.h"
#include <QHeaderView>

LabelTableView::LabelTableView(QWidget *parent):QTableView (parent)
{
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
