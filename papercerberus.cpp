#include "papercerberus.h"
#include "newitemdialog.h"

PaperCerberus::PaperCerberus()
{
    booklist = new QList<bookItem>;
}

void PaperCerberus::newBookItemWidget(QWidget* w)
{
    NewItemDialog* nid = new NewItemDialog(w,booklist);
    nid->exec();
}

void PaperCerberus::printBooks(QList<PaperCerberus::bookItem>* books)
{
    qDebug() << "BEGIN PRINT" << Qt::endl << Qt::endl;
    for(bookItem b : *books)
        PaperCerberus::printbook(b);
}

void PaperCerberus::printbook(PaperCerberus::bookItem item)
{
    qDebug()
            << "______________________________________________" << Qt::endl
            << "book name: " + item.name << Qt::endl
            << "book autor: " + item.autor << Qt::endl
            << "book diskr: " + item.discriptionText << Qt::endl
            << "book color: " + item.bookColor.name() << Qt::endl
            << "front color: " + item.frontcolor.name() << Qt::endl
            << "back color: " + item.backraudcolar.name() << Qt::endl
            << "label: ";
    for(auto i : item.label)
        qDebug() << '\t' << i;

    qDebug() << "______________________________________________";
}

PaperCerberus::bookItem::bookItem()
{
//    static QImage img = QImage("C:/Users/wuram/Desktop/123.png");
    static int k = 0;
    this->name = "noname" + QString::number(k++);
    this->path = "nopath";
    this->sha256 = "nosha512";
    this->autor = "niautor";
//    this->bookImage = img;
    this->discriptionText = "nodiscription";
    this->bookColor = QColor(qrand() % 255,qrand() % 255,qrand() % 255);
    this->frontcolor.setNamedColor("#1a1410");
    this->backraudcolar.setNamedColor("#ffffff");
    label = {};
}
