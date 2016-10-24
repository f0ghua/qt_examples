#include "XIGBSignalDelegate.h"
#include <QDebug>

XIGBSignalDelegate_Define::XIGBSignalDelegate_Define(QObject *parent) :
	QStyledItemDelegate(parent)
{
}

XIGBSignalDelegate_Define::~XIGBSignalDelegate_Define()
{
    foreach (QStyleOptionButton *pBtn, m_pBtns.values()) {
        if (NULL != pBtn) {
            delete pBtn;
            pBtn = NULL;
        }
    }
    m_pBtns.clear();
}

void XIGBSignalDelegate_Define::paint(QPainter *painter,
	const QStyleOptionViewItem &option, const QModelIndex &index) const
{
#ifndef F_NO_DEBUG
	qDebug() << tr("paint: cell(%1,%2)").arg(index.row()).arg(index.column());
#endif
	QStyledItemDelegate::paint(painter, option, index);

	// only show checkbox when first column has data
	QString s = index.sibling(index.row(), 0).data().toString();
	if (s.isEmpty()) return;

    QStyleOptionButton *pBtn = m_pBtns.value(index);
    if (NULL == pBtn) {
        pBtn = new QStyleOptionButton();
        pBtn->state |= QStyle::State_Enabled;
        (const_cast<XIGBSignalDelegate_Define *>(this))->m_pBtns.insert(index, pBtn);
    }

    QRect r = option.rect;//getting the rect of the cell
#if 0
    int x,y,w,h;
    x = r.left() + r.width()*2/3;
    y = r.top();
    w = r.width()*1/3;
    h = r.height();
    pBtn->rect = QRect(x,y,w,h);
#endif

#if 0
    int dx1 = r.width()*2/3; int dy1 = 1;
    int dx2 = -1; int dy2 = -1;
    pBtn->rect = option.rect.adjusted(dx1, dy1, dx2, dy2); //设置按钮的大小
#endif

  	//pBtn->icon= QIcon(QString::fromUtf8(":images/btn_23x23.png"));
  	//pBtn->iconSize = QSize(23,23);

    int btnW = 20, btnY = 20;
    int dx2 = -2, dy2 = -(r.height()-20)/2;
    int dx1 = r.width() + dx2 - btnW;
    int dy1 = (r.height()-20)/2;
    pBtn->rect = option.rect.adjusted(dx1, dy1, dx2, dy2);

    pBtn->text = "...";
    pBtn->state |= QStyle::State_Enabled;
    pBtn->state |= QStyle::State_Raised;
    //pBtn->state |= QStyle::State_Sunken;

#if 0
    painter->save();
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.light());
    }
    painter->restore();
#endif

    QApplication::style()->drawControl(QStyle::CE_PushButton, pBtn, painter);
    //QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, pBtn, painter);
}

bool XIGBSignalDelegate_Define::editorEvent(QEvent *event,
	QAbstractItemModel *model,
	const QStyleOptionViewItem &option,
	const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
#ifndef F_NO_DEBUG
    	qDebug() << tr("editorEvent: cell(%1,%2) MouseButtonPress").arg(index.row()).arg(index.column());
#endif
        QMouseEvent *ev = static_cast<QMouseEvent*>(event);
        if (m_pBtns.contains(index)) {
            QStyleOptionButton *pBtn = m_pBtns.value(index);
            if (pBtn->rect.contains(ev->x(), ev->y())) {
#ifndef F_NO_DEBUG
            	qDebug() << "editorEvent: State_Sunken";
#endif
                pBtn->state |= QStyle::State_Sunken;
                //pBtn->state &= (~QStyle::State_Raised);
                return true;
            }
        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
#ifndef F_NO_DEBUG
    	qDebug() << tr("editorEvent: cell(%1,%2) MouseButtonRelease").arg(index.row()).arg(index.column());
#endif
        QMouseEvent * ev = static_cast<QMouseEvent*>(event);
        if (m_pBtns.contains(index)) {
            QStyleOptionButton * pBtn = m_pBtns.value(index);
            if (pBtn->rect.contains(ev->x(), ev->y())) {
#ifndef F_NO_DEBUG
            	qDebug() << "editorEvent: !State_Sunken";
#endif
                pBtn->state &= (~QStyle::State_Sunken);
                //pBtn->state |= QStyle::State_Raised;
                emit sig_buttonClicked(index);

                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
/*
    if( event->type() == QEvent::MouseButtonRelease )
    {
        QMouseEvent *e = (QMouseEvent *)event;
        int clickX = e->x();
        int clickY = e->y();

        QRect r = option.rect;//getting the rect of the cell
        int x,y,w,h;
        x = r.left() + r.width() - 30;//the X coordinate
        y = r.top();//the Y coordinate
        w = 30;//button width
        h = 30;//button height

        if( clickX > x && clickX < x + w )
            if( clickY > y && clickY < y + h )
            {
                QDialog *d = new QDialog();
                d->setGeometry(0,0,100,100);
                d->show();
            }
    }
*/
}

// ----------------------------------------------------------------------------

static QRect CheckBoxRect(const QStyleOptionViewItem &option)
{
	QStyleOptionButton cbOpt;
	QRect cbRect = QApplication::style()->subElementRect(
		QStyle::SE_CheckBoxIndicator,
		&cbOpt
		);
	QPoint cbPoint(
		option.rect.x() + option.rect.width() / 2 - cbRect.width() / 2,
		option.rect.y() + option.rect.height() / 2 - cbRect.height() / 2
		);
	return QRect(cbPoint, cbRect.size());
}

QCheckBoxDelegate::QCheckBoxDelegate(QObject *parent)
  : QStyledItemDelegate(parent)
{

}

void QCheckBoxDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
#if 0
	QModelIndex *idx = new QModelIndex();
	QVariant value = index.data(Qt::DisplayRole);
#ifndef F_NO_DEBUG
	qDebug() << "index.data = " << index.data(Qt::DisplayRole).toInt();
#endif
	// we don't like the text shown in item
	QTableView *tv = (QTableView *)option.widget;
	tv->model()->setData(index, QVariant());
#ifndef F_NO_DEBUG
	qDebug() << "index.data = " << index.data(Qt::DisplayRole).toInt();
#endif
	QStyledItemDelegate::paint(painter, option, index);
#endif
	QStyledItemDelegate::paint(painter, option, index);

	// only show checkbox when first column has data
	QString s = index.sibling(index.row(), 0).data().toString();
	if (s.isEmpty()) return;

#if 1
	bool checked = index.model()->data(index, Qt::UserRole+2).toBool();
#ifndef F_NO_DEBUG
	qDebug() << "paint checked = " << checked;
#endif
	//bool checked = index.model()->data(index, Qt::DisplayRole).toString().isEmpty()?false:true;
	QStyleOptionButton opt;
	opt.state |= QStyle::State_Enabled;
	if (checked) {
		opt.state |= QStyle::State_On;
	} else {
		opt.state |= QStyle::State_Off;
	}
	opt.rect = CheckBoxRect(option);

    const QWidget *widget = option.widget;
    QStyle *style = widget ? widget->style() : QApplication::style();
	style->drawControl(QStyle::CE_CheckBox, &opt, painter, widget);
#endif
}

// This is essentially copied from QStyledItemEditor, except that we
// have to determine our own "hot zone" for the mouse click.
bool QCheckBoxDelegate::editorEvent(QEvent *event,
	QAbstractItemModel *model,
	const QStyleOptionViewItem &option,
	const QModelIndex &index)
{
	if ((event->type() == QEvent::MouseButtonRelease) ||
		(event->type() == QEvent::MouseButtonDblClick)) {
		QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
		if (mouse_event->button() != Qt::LeftButton ||
			!CheckBoxRect(option).contains(mouse_event->pos())) {
			return false;
		}
		if (event->type() == QEvent::MouseButtonDblClick) {
			return true;
		}
	} else if (event->type() == QEvent::KeyPress) {
		if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
			static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select) {
			return false;
		}
	} else {
		return false;
	}

	bool checked = index.model()->data(index, Qt::UserRole+2).toBool();
#ifndef F_NO_DEBUG
	qDebug() << "checked = " << checked;
#endif
	return model->setData(index, !checked, Qt::EditRole);
}
