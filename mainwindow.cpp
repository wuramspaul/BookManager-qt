#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newitemdialog.h"

MainWindow::MainWindow(PaperCerberus* papercerbirus, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Создание объекта класса и модели
    pc = papercerbirus;
    model = new BookModel(pc->booklist);
    ui->booksWidgets->setModel(model);

    //Настойка горизонтальных заговолков
    ui->booksWidgets->horizontalHeader()->setStretchLastSection(true);
    ui->booksWidgets->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    ui->booksWidgets->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui->booksWidgets->setColumnWidth(0,ui->booksWidgets->width() * 0.05);
    ui->booksWidgets->setColumnWidth(1,ui->booksWidgets->width() * 0.6);
    ui->booksWidgets->setColumnWidth(2,ui->booksWidgets->width() * 0.3  - 10);

    //Настойка вериткальных заговолков
    ui->booksWidgets->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //Инициализациия виджетов
    ui->searchWidget->setHidden(true);
    ui->discriptionWidget->setHidden(true);
    ui->discriptionImage->setHidden(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addFile_triggered()
{
    pc->newBookItemWidget(this);
    model = new BookModel(pc->booklist);
    ui->booksWidgets->setModel(model);

    ui->booksWidgets->setColumnWidth(0,ui->booksWidgets->width() * 0.05);
    ui->booksWidgets->setColumnWidth(1,ui->booksWidgets->width() * 0.6);
    ui->booksWidgets->setColumnWidth(2,ui->booksWidgets->width() * 0.3  - 10);
}


void MainWindow::on_showSearchPanel_triggered()
{
    if(ui->searchWidget->isHidden())
        ui->searchWidget->setHidden(false);
    else
        ui->searchWidget->setHidden(true);

    ui->booksWidgets->setColumnWidth(0,ui->booksWidgets->width() * 0.05);
    ui->booksWidgets->setColumnWidth(1,ui->booksWidgets->width() * 0.6);
    ui->booksWidgets->setColumnWidth(2,ui->booksWidgets->width() * 0.3  - 10);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->searchWidget->setHidden(true);
}

void MainWindow::on_booksWidgets_clicked(const QModelIndex &index)
{

}

void MainWindow::on_closeDiscription_clicked()
{
    ui->discriptionWidget->setHidden(true);

}

void MainWindow::on_exit_triggered()
{
    close();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->booksWidgets->setColumnWidth(0,ui->booksWidgets->width() * 0.05);
    ui->booksWidgets->setColumnWidth(1,ui->booksWidgets->width() * 0.6);
    ui->booksWidgets->setColumnWidth(2,ui->booksWidgets->width() * 0.3  - 10);
}

void MainWindow::on_booksWidgets_doubleClicked(const QModelIndex &index)
{
    if (ui->discriptionWidget->isHidden())
        ui->discriptionWidget->setHidden(false);
    else
        ui->discriptionWidget->setHidden(true);

    ui->booksWidgets->setColumnWidth(0,ui->booksWidgets->width() * 0.05);
    ui->booksWidgets->setColumnWidth(1,ui->booksWidgets->width() * 0.6);
    ui->booksWidgets->setColumnWidth(2,ui->booksWidgets->width() * 0.3  - 10);

    ui->discriptionLabel->setText(model->booklist->at(index.row()).discriptionText);
}


void MainWindow::on_save_triggered()
{

    QString jsonPath = QFileDialog::getSaveFileName
            (this,tr("Save Json File"),QString(),tr("JSON (*.json)"));
    QFile jsonFile(jsonPath);
    jsonFile.open(QIODevice::WriteOnly | QIODevice::ReadWrite);
    QJsonArray jarr;
    QJsonObject jobj;

    for(PaperCerberus::bookItem o: *(pc->booklist))
    {
        jobj["name"]  = o.name;
        jobj["autor"] = o.autor;
        jobj["sha256"] = o.sha256;

        jarr.push_back(jobj);
    }

    jsonFile.write(QJsonDocument(jarr).toJson(QJsonDocument::Indented));
    jsonFile.close();
}

void MainWindow::on_open_triggered()
{
    QDir::setCurrent("C:/Users/wuram/Desktop/testPapCer");
    QString path = QFileDialog::getOpenFileName
            (this,tr("Open arhive file"),QString(),tr("json (*.json)"));
    QFile jarh(path);
    jarh.open(QIODevice::ReadWrite);
    QJsonArray jarr = QJsonDocument::fromJson(jarh.readAll()).array();

    pc->booklist->clear();

    for(QJsonValue v: jarr)
    {
        QJsonObject o = v.toObject();
        qDebug() << o["name"].toString()
                 << o["autor"].toString();
        PaperCerberus::bookItem bi;
        bi.name = o["name"].toString();
        bi.autor = o["autor"].toString();
        bi.sha256 = o["sha256"].toString();
        bi.bookColor = "#" + bi.sha256.right(6);
        pc->booklist->push_front(bi);
    }

    model = new BookModel(pc->booklist);
    ui->booksWidgets->setModel(model);
    ui->booksWidgets->setColumnWidth(0,ui->booksWidgets->width() * 0.05);
    ui->booksWidgets->setColumnWidth(1,ui->booksWidgets->width() * 0.6);
    ui->booksWidgets->setColumnWidth(2,ui->booksWidgets->width() * 0.3  - 10);

}

void MainWindow::on_add_triggered()
{
    QString path = QFileDialog::getOpenFileName
            (this,tr("Open arhive file"),QString(),tr("zip (*.zip)"));
    QuaZip zip_s(path);
    zip_s.open(QuaZip::mdUnzip);

    QuaZipFile file_s(&zip_s);
    QString data;
    for(bool f=zip_s.goToFirstFile(); f; f=zip_s.goToNextFile())
    {   file_s.open(QIODevice::ReadOnly);
        {  data=file_s.readAll();
           qDebug()<<data;
        }
        file_s.close();
    }
    zip_s.close();
}
