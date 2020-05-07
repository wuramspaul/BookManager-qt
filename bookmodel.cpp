#include "bookmodel.h"
#include <QBrush>
#include <QImage>
#include <QtPrintSupport/QPrinter>
#include <QDir>
#include <QColor>
#include <QRandomGenerator>

BookModel::BookModel(QList<PaperCerberus::bookItem>* bl) : booklist(bl)
{

}

int BookModel::rowCount(const QModelIndex &parent) const
{
    return booklist->size();
}

int BookModel::columnCount(const QModelIndex &parent) const
{
    // 0 - image, 1 - name, 2 - autor
    return 3;
}

QVariant BookModel::data(const QModelIndex &index, int role) const
{
    PaperCerberus::bookItem book = booklist->at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:
            return QVariant();
        case 1:
            return QVariant(book.name);
        case 2:
            return QVariant(book.autor);
        default:
            return QVariant();
        }
        break;
    case Qt::BackgroundRole:

        switch (index.column()) {
        case 0:
            return QBrush(book.bookColor);
        default:
            return QVariant();
        }
        break;
//    case Qt::SizeHintRole:
//        switch (index.column()) {
//        case 0:
//            return QSize(64,64);
//        default:
//            return QVariant();
//        }
        break;
    case Qt::ToolTipRole:
        switch (index.column()) {
        case 0:
            return book.sha256;
        default:
            return QVariant();
        }
        break;
    }

    return QVariant();
}

QVariant BookModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
    if (orientation == Qt::Horizontal) {
      switch (section)
      {
      case 0:
        return tr("H");
      case 1:
        return tr("Имя");
      case 2:
        return tr("Автор");
      default:
        return QString("");
      }
    }
  }
  return QVariant();
}
