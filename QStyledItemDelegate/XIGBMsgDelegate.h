#ifndef XIGBLOCKDELEGATE_H
#define XIGBLOCKDELEGATE_H

#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QtWidgets>

class XIGBMsgDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
	enum Columns {
		COL_NAME 		= 0x00,
		COL_ID			= 0x01,
		COL_FRAMETYPE 	= 0x02,
		COL_CHANNEL 	= 0x03,
		COL_DLC 		= 0x04,
		COL_ENABLE 		= 0x05,
		COL_CYCLETIME 	= 0x06,
		COL_DATABYTE0	= 0x07,
		COL_DATABYTE1	= 0x08,
		COL_DATABYTE2	= 0x09,
		COL_DATABYTE3	= 0x10,
		COL_DATABYTE4	= 0x11,
		COL_DATABYTE5	= 0x12,
		COL_DATABYTE6	= 0x13,
		COL_DATABYTE7	= 0x14
	};

    XIGBMsgDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // XIGBLOCKDELEGATE_H