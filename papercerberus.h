#ifndef PAPERCERBERUS_H
#define PAPERCERBERUS_H
#include <QJsonArray>
#include <QList>
#include <QString>
#include <QImage>
#include <QBitArray>
#include <QColor>

class PaperCerberus
{

public:
    struct bookItem{
        QString path;
        QString name;
        QString autor;
        QString discriptionText;
        QImage bookImage;
        QColor bookColor;
        QString sha256;
        bookItem();
    };

    QList<bookItem>* booklist;

public:
    PaperCerberus();
    void newBookItemWidget(QWidget*);
    static void printBooks(QList<bookItem>*);
};

#endif // PAPERCERBERUS_H
