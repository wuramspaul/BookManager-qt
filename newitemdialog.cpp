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
    QDir::setCurrent("C:");
    QString pdfPath = QFileDialog::getOpenFileName
            (this,tr("Open PDF file"),QString(),tr("PDF (*.pdf)"));

    QFileInfo* fi = new QFileInfo(QFile(pdfPath));


    ui->pathEdit->setText(pdfPath.replace("/","\\"));
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

//    qDebug()  book.path;

    book.name = ui->nameEdit->text();
    book.autor = ui->autorEdit->text();
    book.discriptionText = ui->dicsriptionEdit->text();
    QFile* file = new QFile(book.path);
    file->open(QIODevice::ReadOnly | QIODevice::ReadWrite);
    book.sha256 = QString(QCryptographicHash::hash(file->readAll(),QCryptographicHash::Sha256).toHex());


    book.bookColor.setNamedColor('#' + book.sha256.right(6));
    book.frontcolor.setNamedColor('#' + ui->frontcolor->text());
    book.backraudcolar.setNamedColor('#' + ui->backcolor->text());

    for(auto i : templabel)
        book.label.append(i);

    qDebug()
            << "book name: " + book.name << Qt::endl
            << "book autor: " + book.autor << Qt::endl
            << "book diskr: " + book.discriptionText << Qt::endl
            << "book color: " + book.bookColor.name() << Qt::endl
            << "front color: " + book.frontcolor.name() << Qt::endl
            << "back color: " + book.backraudcolar.name() << Qt::endl
            << "label: ";

    for(auto i : book.label)
        qDebug() << '\t' << i;


    list->push_front(book);
    NewItemDialog::close();
}

void NewItemDialog::on_pushButton_clicked()
{
    for(auto i : templabel)
        if(ui->newlabel->text() == i)
            return;

    qDebug() << "Add label: " + ui->newlabel->text();

    templabel.append(ui->newlabel->text());

    ui->laballist->addItem(ui->newlabel->text());
}

void NewItemDialog::on_deletelabel_clicked()
{
    for(auto i : templabel)
        if(ui->newlabel->text() == i)
        {
            qDebug() << "Delet label: " + ui->newlabel->text();
            templabel.removeOne(i);
            ui->laballist->clear();

            for(auto item : templabel)
                ui->laballist->addItem(item);

            return;
        }
}
