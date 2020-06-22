#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "papercerberus.h"

class BookModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    BookModel(QList<PaperCerberus::bookItem>*);
private:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
private:

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QList<PaperCerberus::bookItem>* booklist;
};

#endif // BOOKMODEL_H
