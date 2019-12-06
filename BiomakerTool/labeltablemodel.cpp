#include "labeltablemodel.h"

#include <algorithm>
#include <QDebug>
#include <iostream>

Qt::CheckState LabelTableModel::stateTransfer(Qt::CheckState state0,Qt::CheckState state1)
{
	if (state0 == Qt::Unchecked && state1 == Qt::Checked)
		return Qt::PartiallyChecked;
	if (state0 == Qt::PartiallyChecked && state1 == Qt::Unchecked)
		return Qt::Checked;
	if (state0 == Qt::Checked && state1 == Qt::Checked)
		return Qt::Unchecked;
	if (state0 == Qt::Unchecked && state1 == Qt::Unchecked)
		return Qt::PartiallyChecked;
	if (state0 == Qt::PartiallyChecked && state1 == Qt::Checked)
		return Qt::Checked;
	else if (state0 == Qt::Checked && state1 == Qt::Unchecked)
		return Qt::Unchecked;
}

LabelTableModel::LabelTableModel(QObject *parent) :QAbstractTableModel(parent), userAddCheckStateRole(false)
{

}

int LabelTableModel::rowCount(const QModelIndex & index) const
{
	Q_ASSERT_X(!index.isValid(), "LabelTableModel::setData", "Invalid index");
	return modelData.count();
}

int LabelTableModel::columnCount(const QModelIndex & index) const
{
	Q_ASSERT_X(!index.isValid(), "LabelTableModel::setData", "Invalid index");
	return 1;
}

QVariant LabelTableModel::data(const QModelIndex & index, int role) const
{

	const auto c = index.column();
	const auto r = index.row();

	if (r >= modelData.size())
		qDebug() << "row index is out of range";

	if(c == 0)
	{
		if (role == Qt::DisplayRole)
			return modelData[r].name;
		if (role == Qt::CheckStateRole)
			return modelData[r].checkState;
		if (role == Qt::UserRole)
			return modelData[r].id;
	}else
	{
		qDebug() << "column index is out of range";
	}
	return QVariant{};
}

bool LabelTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	const auto c = index.column();
	const auto r = index.row();
	bool success = false;

	if (r >= modelData.size())
	{
		qDebug() << "row index is out of range";
		return success;
	}

	if(c == 0)
	{
		if (role == Qt::CheckStateRole)
		{
			if (userAddCheckStateRole == false)
				//modelData[r].checkState = stateTransfer(modelData[r].checkState, (Qt::CheckState)value.toInt());
				modelData[r].checkState = value.toInt() == 0 ? Qt::PartiallyChecked : Qt::Checked;
			else
				modelData[r].checkState = (Qt::CheckState)value.toInt();
			success = true;
		}else if(role == Qt::DisplayRole)
		{
			modelData[r].name = value.toString();
			success = true;
		} else if (role == Qt::UserRole)
		{
			modelData[r].id = value.toInt();
			success = true;
		}
		emit modelsignal_SendCheckedState(index, modelData[r].checkState);

	}else
	{
		qDebug() << "column index is out of range";
	}
	emit dataChanged(index, index);
	return success;
}

QModelIndex LabelTableModel::index(int row, int column, const QModelIndex& parent) const
{
	Q_ASSERT_X(!parent.isValid(), "LabelTableModel::setData", "Invalid index");
	if (modelData.empty())
	{
		qDebug() << createIndex(row, column, nullptr);
		return createIndex(row, column, nullptr);
	}
		
	return createIndex(row, column,reinterpret_cast<void*>(const_cast<InternalTableItem*>(&modelData[row])));
}

Qt::ItemFlags LabelTableModel::flags(const QModelIndex& index) const
{
	const auto c = index.column();
	const auto r = index.row();
	if (c == 0)
		return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable;
	return QAbstractTableModel::flags(index);
}

bool LabelTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
	Q_ASSERT_X(!parent.isValid(), "LabelTableModel::setData", "Invalid index");
	beginInsertRows(parent, row, row + count);
	for(int i = 0 ; i<count;i++)
	{
		modelData.insert(row + i, InternalTableItem{ Qt::Unchecked,QString{},QVector<QVariant>{} });
	}
	endInsertRows();
	return true;
}

bool LabelTableModel::insertColumns(int columns, int count, const QModelIndex &parent)
{
	Q_ASSERT_X(!parent.isValid(), "LabelTableModel::setData", "Invalid index");
	beginInsertColumns(parent, columns, columns + count);
	for(auto & item:modelData)
	{
		item.data.insert(columns, count, QVariant{});
	}
	endInsertColumns();
	return true;
}

bool LabelTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
	Q_ASSERT_X(!parent.isValid(), "LabelTableModel::setData", "Invalid index");

	const auto beginIndex = std::min(row, modelData.size());
	const auto endIndex = std::min(row + count, modelData.size());

	if (beginIndex >= endIndex)
		return false;

	auto begin = modelData.begin(), end = modelData.begin();
	std::advance(begin, beginIndex);
	std::advance(end, endIndex);
	beginRemoveRows(parent, row, row + count);
	modelData.erase(begin, end);
	endRemoveRows();

	return true;
}

bool LabelTableModel::removeColumns(int columns, int count, const QModelIndex &parent)
{
	Q_ASSERT_X(!parent.isValid(), "LabelTableModel::setData", "Invalid index");
	bool success = false;

	beginRemoveColumns(parent, columns, columns + count);

	for (auto & item : modelData)
	{
		const auto beginIndex = std::min(columns, item.data.size());
		const auto endIndex = std::min(columns + count, item.data.size());

		if (beginIndex >= endIndex)
			continue;

		success = true;
		auto begin = modelData.begin(), end = modelData.begin();
		std::advance(begin, columns);
		std::advance(end, columns + count);
		modelData.erase(begin, end);
	}

	endRemoveColumns();
	return success;
}

QVariant LabelTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			if (section == 0)
				return "Name";
		}
		if (orientation == Qt::Vertical)
		{
			return QString::number(section);
		}
	}else
	{
		return QAbstractTableModel::headerData(section, orientation, role);
	}


	return QVariant{};
}

void LabelTableModel::addData(const QVector<TableItem>& items)
{
	//Debug 20190416
	//removeRows(0, rowCount(QModelIndex()));
	std::cout << "The size of table model is : " << rowCount(QModelIndex()) << std::endl;
	insertRows(0, items.size(), QModelIndex());
	userAddCheckStateRole = true;
	for(int i = 0 ;i<items.size();i++)
	{
		const auto idx = index(i, 0);
		//if (idx>=items.size())
		setData(idx, items[i].name, Qt::DisplayRole);
		setData(idx, items[i].state, Qt::CheckStateRole);
		setData(idx, items[i].id, Qt::UserRole);
	}
	userAddCheckStateRole = false;
}

void LabelTableModel::setUserAddCheckStateRole(bool state)
{
	userAddCheckStateRole = state;
}