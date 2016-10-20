/*
Copyright (c) 2009, Krasnoshchekov Petr
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY Krasnoshchekov Petr ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Krasnoshchekov Petr BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QtGui>
#include <QStandardItemModel>
#include <QTableView>
#include <QApplication>

#include "ProxyModelWithHeaderModels.h"

void BuildDataModel(QStandardItemModel& model)
{
	QString cellText("cell(%1, %2)");
    for(int i=0; i<9; ++i)
	{
		QList<QStandardItem*> l;
        for(int j=0; j<9; ++j)
		{
			QStandardItem* cell=new QStandardItem(cellText.arg(i).arg(j));
			l.push_back(cell);
		}
		model.appendRow(l);
	}
}

void BuildHeaderModel(QStandardItemModel& headerModel)
{
    //START ADDING HEADERS(Can also be done in a separate function)
    QStandardItem *Header1 = new QStandardItem(QObject::tr("Header1"));
    QStandardItem *Header2 = new QStandardItem(QObject::tr("Header2"));
    QStandardItem *Header3 = new QStandardItem(QObject::tr("Header3"));
    QStandardItem *Header4 = new QStandardItem(QObject::tr("Header4"));
    QStandardItem *Header5 = new QStandardItem(QObject::tr("Header5"));
    QStandardItem *Header6 = new QStandardItem(QObject::tr("Header6"));
    QStandardItem *Header7 = new QStandardItem(QObject::tr("Header7"));
    QStandardItem *Header8 = new QStandardItem(QObject::tr("Header8"));

    QList<QStandardItem *> l;
    l.push_back( new QStandardItem("Sub Header1"));
    Header3->appendColumn(l);

    l.clear();
    l.push_back(new QStandardItem("Sub Header2"));
    Header3->appendColumn(l);

    l.clear();
    l.push_back(new QStandardItem("Sub Header3"));
    Header6->appendColumn(l);

    l.clear();
    l.push_back(new QStandardItem("Sub Header4"));
    Header6->appendColumn(l);

    //Add all the table header items to to table header model.
    headerModel.setItem(0, 0, Header1);
    headerModel.setItem(0, 1, Header2);
    headerModel.setItem(0, 2, Header3);
    headerModel.setItem(0, 3, Header4);
    headerModel.setItem(0, 4, Header5);
    headerModel.setItem(0, 5, Header6);
    headerModel.setItem(0, 6, Header7);
    headerModel.setItem(0, 7, Header8);
    //END ADDING HEADERS

//	QStandardItem* rootItem = new QStandardItem("root");
//	QList<QStandardItem*> l;

//	QStandardItem* rotatedTextCell=new QStandardItem("Rotated text");
//	rotatedTextCell->setData(1, Qt::UserRole);
//	l.push_back(rotatedTextCell);
//	rootItem->appendColumn(l);

//	l.clear();

//	QStandardItem* cell=new QStandardItem("level 2");
//	l.push_back(cell);
//	rootItem->appendColumn(l);
	
//	l.clear();

//	l.push_back(new QStandardItem("level 3"));
//	cell->appendColumn(l);
	
//	l.clear();

//	l.push_back(new QStandardItem("level 3"));
//	cell->appendColumn(l);

//	l.clear();

//	l.push_back(new QStandardItem("level 2"));
//	rootItem->appendColumn(l);

}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QStandardItemModel headerModel;
    BuildHeaderModel(headerModel);

	QStandardItemModel dataModel;
    BuildDataModel(dataModel);

    ProxyModelWithHeaderModels proxyModel;

    proxyModel.setSourceModel(&dataModel);
    proxyModel.setHorizontalHeaderModel(&headerModel);
    proxyModel.setVerticalHeaderModel(&headerModel);

    QTableView tableView;
    tableView.setModel(&proxyModel);

    //Create the headerview and set the column span.
    HierarchicalHeaderView *headerView = new HierarchicalHeaderView(Qt::Horizontal, &tableView);
    tableView.setHorizontalHeader(headerView);

    tableView.show();

//	QTableView tv;
//	HierarchicalHeaderView* hv=new HierarchicalHeaderView(Qt::Horizontal, &tv);
//	tv.setHorizontalHeader(hv);
//	hv=new HierarchicalHeaderView(Qt::Vertical, &tv);
//	tv.setVerticalHeader(hv);
//	tv.setModel(&model);
//	tv.resizeColumnsToContents();
//	tv.resizeRowsToContents();
//	tv.show();
	return app.exec();
}
