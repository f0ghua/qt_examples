#include "XIGBMsgDelegate.h"

#include <QtWidgets>
#include <QRegExp>

static const QStringList g_itemCbFrameType = QStringList() << "Data" << "Remote";

XIGBMsgDelegate::XIGBMsgDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

QWidget *XIGBMsgDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
	Q_UNUSED(option);

	QWidget *editor = 0;

	switch (index.column()) {
		case COL_NAME:
		{
			editor = new QLineEdit(parent);
			break;
		}
		case COL_ID:
		{
			editor = new QLineEdit(parent);
			break;
		}
		case COL_FRAMETYPE:
		{
			QComboBox *cb = new QComboBox(parent);
			foreach (const QString &s, g_itemCbFrameType) {
				cb->addItem(s);
			}
			editor = cb;
			break;
		}
		case COL_CYCLETIME:
		{
			QSpinBox *sb = new QSpinBox(parent);
			//sb->setMinimum(0);
			sb->setRange(0, 100000);
			sb->setSingleStep(100);
			editor = sb;
			break;
		}
		case COL_DATABYTE0:
		{
			editor = new QLineEdit(parent);
			QRegExp regExp("^[0-9a-fA-F]{2}$");
			static_cast<QLineEdit*>(editor)->setValidator(new QRegExpValidator(regExp, parent));
			break;
		}
		default:
		{
			return QStyledItemDelegate::createEditor(parent, option, index);
		}
	}

	editor->installEventFilter(const_cast<XIGBMsgDelegate *>(this));

    return editor;
}

void XIGBMsgDelegate::setEditorData(QWidget *editor,
	const QModelIndex &index) const
{
	QVariant value = index.model()->data(index, Qt::DisplayRole);

	switch (index.column()) {
		case COL_NAME:
		{
			QLineEdit *le = static_cast<QLineEdit*>(editor);
			le->setText(value.toString());
			break;
		}
		case COL_ID:
		{
			QLineEdit *le = static_cast<QLineEdit*>(editor);
			le->setText(value.toString());
			break;
		}
		case COL_FRAMETYPE:
		{
			QComboBox *cb = static_cast<QComboBox *>(editor);
			int index = cb->findText(value.toString());
			if (index == -1) index = 0;
			cb->setCurrentIndex(index);
			break;
		}
		case COL_CYCLETIME:
		{
			QSpinBox *sb = static_cast<QSpinBox *>(editor);
			sb->setValue(value.toInt());
			break;
		}
		default:
		{
			QStyledItemDelegate::setEditorData(editor, index);
			break;
		}
	}
}

void XIGBMsgDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	QVariant value;

	switch (index.column()) {
		case COL_NAME:
		{
			value = static_cast<QLineEdit*>(editor)->text();
			break;
		}
		case COL_ID:
		{
			value = static_cast<QLineEdit*>(editor)->text();
			break;
		}
		case COL_FRAMETYPE:
		{
			value = static_cast<QComboBox*>(editor)->currentText();

			break;
		}
		case COL_CYCLETIME:
		{
			value = static_cast<QSpinBox*>(editor)->value();
			break;
		}
		default:
		{
			return QStyledItemDelegate::setModelData(editor, model, index);
		}
	}

	model->setData(index, value);
}


void XIGBMsgDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
