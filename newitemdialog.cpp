#include <QCryptographicHash>

#include "newitemdialog.h"
#include "ui_newitemdialog.h"

NewItemDialog::NewItemDialog(QWidget *parent, QList<PaperCerberus::bookItem>* l) :
    QDialog(parent),
    ui(new Ui::NewItemDialog)
{
    ui->setupUi(this);
    if(l == nullptr) qDebug() << "ERROR LIST not init";
    list = l;
    NewItemDialog::on_openButton_clicked();
}

NewItemDialog::~NewItemDialog()
{
    delete ui;
}

void NewItemDialog::on_openButton_clicked()
{
    QDir::setCurrent("C:/Users/wuram/Desktop/BOOKS");
    QString pdfPath = QFileDialog::getOpenFileName
            (this,tr("Open PDF file"),QString(),tr("PDF (*.pdf)"));

    QFileInfo* fi = new QFileInfo(QFile(pdfPath));


    ui->pathEdit->setText(pdfPath);
    ui->additionWitgets->setEnabled(true);
    ui->nameEdit->setText(fi->baseName());
    ui->addButton->setEnabled(true);
}

void NewItemDialog::on_closeButton_clicked()
{
    close();
}

void NewItemDialog::on_addButton_clicked()
{
    PaperCerberus::bookItem book;
    book.path = ui->pathEdit->text();
    book.name = ui->nameEdit->text();
    book.autor = ui->autorEdit->text();
    book.discriptionText = ui->dicsriptionEdit->text();
    QFile* file = new QFile(book.path);
    file->open(QIODevice::ReadOnly | QIODevice::ReadWrite);
    book.sha256 = QString(QCryptographicHash::hash(file->readAll(),QCryptographicHash::Sha256).toHex());

//    qDebug() << book.sha256;
//    qDebug() << '#' + book.sha256.right(6);
    book.bookColor.setNamedColor('#' + book.sha256.right(6));

    list->push_front(book);
    NewItemDialog::close();
}
