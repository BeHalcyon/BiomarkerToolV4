#ifndef LABELLISTMODEL_H
#define LABELLISTMODEL_H

#include <QAbstractTableModel>
#include <QGraphicsItem>


struct TableItem
{
	int id;
	QGraphicsItem* rect_item;
	QString name;
	Qt::CheckState state;
	TableItem(int id = 0, QGraphicsItem* rect_item = nullptr,
		const QString & name = QString{}, Qt::CheckState state = Qt::Unchecked) 
	:id(id), rect_item(rect_item), name(name), state(state) {}
};

struct InternalTableItem
{
	Qt::CheckState checkState;
	QString name;
	QVector<QVariant> data;
	int id;
	InternalTableItem(Qt::CheckState check, const QString & name, const QVector<QVariant> & data) :checkState(check), name(name), data(data),id(id) {}
};

class LabelTableModel:public QAbstractTableModel
{
	Q_OBJECT
	QList<InternalTableItem> modelData;
	Qt::CheckState stateTransfer(Qt::CheckState state0,Qt::CheckState state1);
	bool userAddCheckStateRole;

Q_SIGNALS:
	void modelsignal_SendCheckedState(const QModelIndex& index, Qt::CheckState check_state);

public:
	enum {CustomAddRole = Qt::UserRole + 123};

    LabelTableModel(QObject * parent);
    int rowCount(const QModelIndex & index)const override;
    int columnCount(const QModelIndex & index)const override;
    QVariant data(const QModelIndex & index,int role)const override;
	
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool insertRows(int row,int count, const QModelIndex & parent = QModelIndex()) override;
    bool insertColumns(int columns,int count, const QModelIndex & parent = QModelIndex()) override;
    bool removeRows(int row,int count, const QModelIndex & parent = QModelIndex())override;
    bool removeColumns(int columns,int count, const QModelIndex & parent = QModelIndex())override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	void addData(const QVector<TableItem> & items);
	void setUserAddCheckStateRole(bool state);
};

#endif // LABELLISTMODEL_H
