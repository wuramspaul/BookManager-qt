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
        QColor bookColor;
        QColor backraudcolar;
        QColor frontcolor;
        QString sha256;

        QList<QString> label;
        bookItem();
    };

    QList<bookItem>* booklist;

public:
    PaperCerberus();
    void newBookItemWidget(QWidget*);
    static void printBooks(QList<bookItem>*);
    static void printbook(bookItem item);


};

#endif // PAPERCERBERUS_H
