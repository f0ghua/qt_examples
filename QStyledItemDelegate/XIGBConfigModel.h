#ifndef XIGBCONFIGMODEL_H
#define XIGBCONFIGMODEL_H

#include <QStandardItemModel>
#include <QAbstractTableModel>

#include "XHierarchicalHeaderView.h"

struct TryParameters {
	quint32 msgId;
	QString msgFrameType;
	bool msgEnable;
};

class XIGBConfigMsgModel : public QAbstractTableModel
{
	Q_OBJECT

public:
    QList<TryParameters> m_params;

    XIGBConfigMsgModel(QObject* parent = 0);
   	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
   	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
   	Qt::ItemFlags flags(const QModelIndex &index) const;
   	bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QStandardItemModel m_horizontalHeaderModel;
    QStandardItemModel m_verticalHeaderModel;

	void fillHeaderModel(QStandardItemModel &headerModel);

};

class XIGBConfigSignalModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    QList<TryParameters> m_params;

    XIGBConfigSignalModel(QObject* parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QStandardItemModel m_horizontalHeaderModel;
    QStandardItemModel m_verticalHeaderModel;

    void fillHeaderModel(QStandardItemModel &headerModel);

};

#endif // XIGBCONFIGMODEL_H