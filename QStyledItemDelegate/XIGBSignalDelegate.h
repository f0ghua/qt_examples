#ifndef XIGBSIGNALDELEGATE_H
#define XIGBSIGNALDELEGATE_H

#include <QtWidgets>

class XIGBSignalDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    enum Columns {
        COL_NAME        = 0x00,
        COL_RAWVALUE    = 0x01,
        COL_PHYVALUE    = 0x02,
        COL_UNIT        = 0x03,
        COL_DEC         = 0x04,
        COL_PHYSTEP     = 0x05,
        COL_INC         = 0x06,
        COL_ENABLE      = 0x07,
        COL_WFTYPE      = 0x08,
        COL_DEFINE      = 0x09,
    };

    XIGBSignalDelegate(QObject *parent = 0) {}
};

class XIGBSignalDelegate_RawValue : public QStyledItemDelegate
{
    Q_OBJECT

public:
    XIGBSignalDelegate_RawValue(QObject *parent = 0) : QStyledItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setMinimum(1);
        editor->setMaximum(100);
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        int value = index.model()->data(index, Qt::EditRole).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
        spinBox->setValue(value);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const
    {
        QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
        spinBox->interpretText();
        int value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};

class XIGBSignalDelegate_Define : public QStyledItemDelegate
{
    Q_OBJECT

public:
    XIGBSignalDelegate_Define(QObject *parent = 0);
    ~XIGBSignalDelegate_Define();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

Q_SIGNALS:
	sig_buttonClicked(const QModelIndex &index);

private:
	QMap<QModelIndex, QStyleOptionButton *> m_pBtns;
};

#if 1
class QCheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    QCheckBoxDelegate(QObject *parent = 0);
protected:
    void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const;
    bool editorEvent(QEvent *event,
    	QAbstractItemModel *model,
        const QStyleOptionViewItem &option,
        const QModelIndex &index);
private:
    QPen         pen;
    QTableView*  view;
};
#endif



#endif // XIGBSIGNALDELEGATE_H
