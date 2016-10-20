
#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QtWidgets>
#include <QHeaderView>
#include <QApplication>
#ifndef F_NO_DEBUG
#include <QDebug>
#endif

class MyHeaderModel : public QAbstractItemModel
{
public:
    MyHeaderModel(QObject *parent = 0) : QAbstractItemModel(parent) {}
    int columnCount(const QModelIndex &parent = QModelIndex()) const { return 2; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const { return QVariant(); }
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const { return QModelIndex(); }
    QModelIndex parent(const QModelIndex &index) const { return QModelIndex(); }
    int rowCount(const QModelIndex &parent = QModelIndex()) const { return 0; }
};

class MyHeader : public QHeaderView
{
    Q_OBJECT
public:
    MyHeader(QHeaderView *header, QWidget *parent = 0) :
    	QHeaderView(Qt::Horizontal, header), mainHeader(header)
    {
        setModel(new MyHeaderModel(this));
        // This example uses hardcoded groups, you can extend
        // this yourself to save the groups
        // Group 1 is 0-2 and Group 2 is 3-4
        resizeSection(0, getSectionSizes(0, 2));
        resizeSection(1, getSectionSizes(3, 4));
        connect(this, SIGNAL(sectionResized(int,int,int)), this, SLOT(updateSizes()));
        connect(((QTableWidget *)(mainHeader->parentWidget()))->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateOffset()));
        setGeometry(0, 0, header->width(), header->height());
        updateOffset();
        mainHeader->installEventFilter(this);
    }
    ~MyHeader() {}

public slots:
    void updateSizes()
    {
        setOffset(mainHeader->offset());

#ifndef F_NO_DEBUG
        qDebug() << tr("%1, %2, %3").arg(mainHeader->sectionSize(2)).arg(sectionSize(0)).arg(getSectionSizes(0, 2));
#endif
        mainHeader->resizeSection(2, (sectionSize(0) - getSectionSizes(0, 1)));
        mainHeader->resizeSection(4, (sectionSize(1) - mainHeader->sectionSize(3) ));
        //mainHeader->resizeSection(2, mainHeader->sectionSize(2) + (sectionSize(0) - getSectionSizes(0, 2)));
        //mainHeader->resizeSection(4, mainHeader->sectionSize(4) + (sectionSize(1) - getSectionSizes(3, 4)));
    }
    void updateOffset()
    {
        setOffset(mainHeader->offset());
    }
protected:
    bool eventFilter(QObject *o, QEvent *e)
    {
        if (o == mainHeader) {
            if (e->type() == QEvent::Resize) {
                setOffset(mainHeader->offset());
                setGeometry(0, 0, mainHeader->width(), mainHeader->height());
            }
            return false;
        }
        return QHeaderView::eventFilter(o, e);
    }
private:
    int getSectionSizes(int first, int second)
    {
        int size = 0;
        for (int a=first;a<=second;++a)
            size += mainHeader->sectionSize(a);
        return size;
    }
    QHeaderView *mainHeader;

};

#include "example3.moc"
int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QWidget w;
    QVBoxLayout *vbox = new QVBoxLayout;
    QTableWidget *tw = new QTableWidget(5, 5);
    MyHeader *h = new MyHeader(tw->horizontalHeader());
    vbox->addWidget(tw);
    w.setLayout(vbox);
    w.show();
    return a.exec();
}
