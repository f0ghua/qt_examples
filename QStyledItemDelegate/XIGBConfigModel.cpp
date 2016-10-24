#include "XIGBConfigModel.h"
#include "XIGBMsgDelegate.h"
#include "XIGBSignalDelegate.h"

#include <QDebug>

XIGBConfigMsgModel::XIGBConfigMsgModel(QObject* parent) :
	QAbstractTableModel(parent)
{
	TryParameters param;
	param.msgEnable = false;
	param.msgFrameType = "Data";
	for (int i = 0; i < 20; i++) {
		m_params.append(param);
	}
	fillHeaderModel(m_horizontalHeaderModel);
}

void XIGBConfigMsgModel::fillHeaderModel(QStandardItemModel &headerModel)
{
	QStandardItem *rootItem, *cell;
	QList<QStandardItem *> l;

	rootItem = new QStandardItem(tr("Message Name"));
	headerModel.setItem(0, 0, rootItem);

	rootItem = new QStandardItem(tr("Message Parameters"));
	l.clear();
	cell = new QStandardItem(tr("Identifier"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Frame Type"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Channel"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("DLC"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	headerModel.setItem(0, 1, rootItem);

	rootItem = new QStandardItem(tr("Triggering"));
	l.clear();
	cell = new QStandardItem(tr("Enable"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Cycle Time"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	headerModel.setItem(0, 2, rootItem);

	rootItem = new QStandardItem(tr("Data Field"));
	for (int i = 0; i < 8; i++) {
		l.clear();
		cell = new QStandardItem(tr("%1").arg(i));
		l.push_back(cell);
		rootItem->appendColumn(l);
	}
	headerModel.setItem(0, 3, rootItem);

}

int XIGBConfigMsgModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 20;
}

int XIGBConfigMsgModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 15;
}

QVariant XIGBConfigMsgModel::data(const QModelIndex& index, int role) const
{
	if(role == HierarchicalHeaderView::HorizontalHeaderDataRole) {
		QVariant v;
		v.setValue((QObject*)&m_horizontalHeaderModel);
		return v;
	}
	if(role == HierarchicalHeaderView::VerticalHeaderDataRole) {
		QVariant v;
		v.setValue((QObject*)&m_verticalHeaderModel);
		return v;
	}

	if (!index.isValid())
		return QVariant();

	int row = index.row();
	int col = index.column();

	switch (role) {
		case Qt::TextColorRole:
			return QColor(Qt::white);
		case Qt::TextAlignmentRole:
			return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
		case Qt::DisplayRole:
		{
			switch (col) {
				case XIGBMsgDelegate::COL_FRAMETYPE:
				{
					return m_params.at(row).msgFrameType;
				}
				default:
				{
					//return QString("index(%1, %2)").arg(index.row()).arg(index.column());
				}
			}
			break;
		}
		case Qt::CheckStateRole:
		{
			if (col == XIGBMsgDelegate::COL_ENABLE) {
				if (m_params.count() > row)
					return m_params.at(row).msgEnable ? Qt::Checked : Qt::Unchecked;
			}
		}

	}

	return QVariant();
}

Qt::ItemFlags XIGBConfigMsgModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return QAbstractItemModel::flags(index);

    switch (index.column()) {
    	/*
    	case XIGBMsgDelegate::COL_NAME:
    	{
    		return Qt::NoItemFlags;
    	}
    	*/
    	case XIGBMsgDelegate::COL_ENABLE:
    	{
    		return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    	}
    	default:
    	{
    		return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    		//return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    	}
    }
}

bool XIGBConfigMsgModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int row = index.row();
    int col = index.column();

    switch (role){
    	//case Qt::DisplayRole:
    	case Qt::EditRole:
    	{
    		switch (col) {
    			case XIGBMsgDelegate::COL_FRAMETYPE:
    			{
#ifndef F_NO_DEBUG
					qDebug() << tr("set param %1 msgType = %2").arg(row).arg(value.toString());
#endif
    				m_params[row].msgFrameType = value.toString();
    				return true;
    			}
    			default:
    			{
    				break;
    			}
    		}
    	}
    	case Qt::CheckStateRole:
    	{
    		if (col == XIGBMsgDelegate::COL_ENABLE){
            	m_params[row].msgEnable = (value.toInt() == Qt::Checked);
            	emit dataChanged(index, index);
            	return true;
    		}
    	}
    }

    return false;
}

// ----------------------------------------------------------------------------


XIGBConfigSignalModel::XIGBConfigSignalModel(QObject* parent) :
	QAbstractTableModel(parent)
{
	TryParameters param;
	param.msgEnable = false;
	param.msgFrameType = "Data";
	for (int i = 0; i < 20; i++) {
		m_params.append(param);
	}
	fillHeaderModel(m_horizontalHeaderModel);
}

void XIGBConfigSignalModel::fillHeaderModel(QStandardItemModel &headerModel)
{
	QStandardItem *rootItem, *cell;
	QList<QStandardItem *> l;

	rootItem = new QStandardItem(tr("Signal Name"));
	headerModel.setItem(0, 0, rootItem);

	rootItem = new QStandardItem(tr("Signal Parameters"));
	l.clear();
	cell = new QStandardItem(tr("Raw Value"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Phy Value"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Unit"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	headerModel.setItem(0, 1, rootItem);

	rootItem = new QStandardItem(tr("Adjusting"));
	l.clear();
	cell = new QStandardItem(tr("Dec"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Phy Step"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Inc"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	headerModel.setItem(0, 2, rootItem);

	rootItem = new QStandardItem(tr("Wave Form Generation"));
	l.clear();
	cell = new QStandardItem(tr("Enable"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Type"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	l.clear();
	cell = new QStandardItem(tr("Define"));
	l.push_back(cell);
	rootItem->appendColumn(l);
	headerModel.setItem(0, 3, rootItem);

}

int XIGBConfigSignalModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 8;
}

int XIGBConfigSignalModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 10;
}

QVariant XIGBConfigSignalModel::data(const QModelIndex& index, int role) const
{
	if(role == HierarchicalHeaderView::HorizontalHeaderDataRole) {
		QVariant v;
		v.setValue((QObject*)&m_horizontalHeaderModel);
		return v;
	}
	if(role == HierarchicalHeaderView::VerticalHeaderDataRole) {
		QVariant v;
		v.setValue((QObject*)&m_verticalHeaderModel);
		return v;
	}

	if (!index.isValid())
		return QVariant();

	int row = index.row();
	int col = index.column();

	switch (role) {
		case Qt::TextColorRole:
			return QColor(Qt::white);
		case Qt::TextAlignmentRole:
			return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
		case Qt::DisplayRole:
		{
			switch (col) {
				/*
				case XIGBSignalDelegate::COL_WFTYPE:
				{
					return m_params.at(row).msgFrameType;
				}
				*/
				/*
				case XIGBSignalDelegate::COL_ENABLE:
				{
					if (m_params.count() > row) {
						if (m_params.at(row).msgEnable) {
							return QString(" ");
						} else {
							return QString();
						}
					}

						//return (bool)m_params.at(row).msgEnable ? Qt::Checked : Qt::Unchecked;
					break;
				}
				*/

				default:
				{
					if ((col == XIGBSignalDelegate::COL_NAME) && (row == 0))
						return QString("index(%1, %2)").arg(index.row()).arg(index.column());
				}
			}
			break;
		}
		case Qt::UserRole+2:
		{
#ifndef F_NO_DEBUG
			qDebug() << tr("read UserRole = %1").arg(m_params.at(row).msgEnable);
#endif
			switch (col) {
				case XIGBSignalDelegate::COL_ENABLE:
				{
					// This value should not be returned in DisplayRole because that
					// will make text show in the item.
					if (m_params.count() > row) {
#ifndef F_NO_DEBUG
						qDebug() << tr("read msgEnable = %1").arg(m_params.at(row).msgEnable);
#endif
						return m_params.at(row).msgEnable ? true : false;
					}
				}
				break;
			}
		}
#if 0
		case Qt::CheckStateRole:
		{
			if (col == XIGBSignalDelegate::COL_ENABLE) {
				//return Qt::Unchecked;

				if (m_params.count() > row)
					return m_params.at(row).msgEnable ? Qt::Checked : Qt::Unchecked;

			}
		}
#endif
	}

	return QVariant();
}

Qt::ItemFlags XIGBConfigSignalModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return QAbstractItemModel::flags(index);

	Qt::ItemFlags flag = QAbstractItemModel::flags(index);
	// get first column data, if it's empty, then the row is not editable
	QString s = index.sibling(index.row(), 0).data().toString();
	flag = ((s.isEmpty()) ? (flag & (~Qt::ItemIsEditable)) : (flag | Qt::ItemIsEditable));

    switch (index.column()) {
    	case XIGBSignalDelegate::COL_NAME:
    	case XIGBSignalDelegate::COL_DEFINE:
    	{
    		flag &= (~Qt::ItemIsEditable);
    	}
    	case XIGBSignalDelegate::COL_ENABLE:
    	{
    		//flag |= Qt::ItemIsUserCheckable;
    		flag &= (~Qt::ItemIsEditable);
    		break;
    	}
    	default:
    	{
    		break;
    		//return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    		//return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    		//return Qt::NoItemFlags;
    	}
    }

    return flag;
}

bool XIGBConfigSignalModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int row = index.row();
    int col = index.column();

    switch (role){
    	//case Qt::DisplayRole:
    	case Qt::EditRole:
    	{
    		switch (col) {
    			case XIGBSignalDelegate::COL_WFTYPE:
    			{
#ifndef F_NO_DEBUG
					qDebug() << tr("set param %1 msgType = %2").arg(row).arg(value.toString());
#endif
    				m_params[row].msgFrameType = value.toString();
    				return true;
    			}
    			case XIGBSignalDelegate::COL_ENABLE:
    			{
#ifndef F_NO_DEBUG
					qDebug() << tr("set param %1 msgEnable = %2").arg(row).arg(value.toBool());
#endif
    				m_params[row].msgEnable = value.toBool();
#ifndef F_NO_DEBUG
					qDebug() << tr("write msgEnable = %1").arg(m_params[row].msgEnable);
#endif
    				return true;
    			}
    			default:
    			{
    				break;
    			}
    		}
    	}
#if 0
    	case Qt::CheckStateRole:
    	{
    		if (col == XIGBSignalDelegate::COL_ENABLE){
            	m_params[row].msgEnable = (value.toInt() == Qt::Checked);
            	emit dataChanged(index, index);
            	return true;
    		}
    	}
#endif
    }

    return false;
}

