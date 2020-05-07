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
    qDebug() << "BEGIN PRINT" << endl << endl;
    for(bookItem b : *books)
    {
        qDebug() << "NAME" << b.name  << endl
                 << "PATH" << b.path  << endl
                 << "AUTR" << b.autor << endl
                 << "DISC" << b.discriptionText << endl
                 << endl;

    }
}

PaperCerberus::bookItem::bookItem()
{
    static QImage img = QImage("C:/Users/wuram/Desktop/123.png");
    static int k = 0;
    this->name = "noname" + QString::number(k++);
    this->path = "nopath";
    this->sha256 = "nosha512";
    this->autor = "niautor";
    this->bookImage = img;
    this->discriptionText = "nodiscription";
    this->bookColor = QColor(qrand() % 255,qrand() % 255,qrand() % 255);
}
