#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(PaperCerberus* papercerbirus, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Создание объекта класса и модели
    pc = papercerbirus;

    //Настойка горизонтальных заговолков
    ui->booksWidgets->horizontalHeader()->setStretchLastSection(true);
    ui->booksWidgets->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    ui->booksWidgets->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);


    //Настойка вериткальных заговолков
    ui->booksWidgets->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //Инициализациия виджетов
    ui->searchWidget->setHidden(true);
    ui->discriptionWidget->setHidden(true);
    ui->discriptionImage->setHidden(true);

    updateBookWidget();

    path = QDir::currentPath();
    qDebug() << "current path" << path.replace("/","\\");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addFile_triggered()
{

    pc->newBookItemWidget(this);

    updateBookWidget();
}


void MainWindow::on_showSearchPanel_triggered()
{
    if(ui->searchWidget->isHidden())
        ui->searchWidget->setHidden(false);
    else
        ui->searchWidget->setHidden(true);

    updateBookWidget();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->searchWidget->setHidden(true);
}

void MainWindow::on_booksWidgets_clicked(const QModelIndex &index)
{
    correctitem = index.row();
    for(auto i : *(pc->booklist))
        if(
        ui->booksWidgets->model()->data(ui->booksWidgets->model()->index(correctitem,1)).toString()
            == i.name)
        {
            ci = i;
            qDebug() << "Valid item: " + ci.name;
        }
}

void MainWindow::on_closeDiscription_clicked()
{
    ui->discriptionWidget->setHidden(true);

}

void MainWindow::on_exit_triggered()
{
    close();
}

//void MainWindow::resizeEvent(QResizeEvent *event)
//{
//    updateBookWidget();
//}

void MainWindow::on_booksWidgets_doubleClicked(const QModelIndex &index)
{
    if (ui->discriptionWidget->isHidden())
        ui->discriptionWidget->setHidden(false);
    else
        ui->discriptionWidget->setHidden(true);

    correctitem = index.row();
    for(auto i : *(pc->booklist))
        if(
        ui->booksWidgets->model()->data(ui->booksWidgets->model()->index(correctitem,1)).toString()
            == i.name)
        {
            ci = i;
            qDebug() << "Valid item: " + ci.name;
        }

    updateBookWidget();

    ui->discriptionLabel->setText(model->booklist->at(index.row()).discriptionText);
}


void MainWindow::on_save_triggered()
{    
    auto si = new saveInfo(pc->booklist,this);
    si->exec();
}

void MainWindow::on_open_triggered()
{
    QDir::setCurrent("C:");
    QString zippath = QFileDialog::getOpenFileName
            (this,tr("Open arhive file"),QString(),tr("zip (*.zip)"));
    if(zippath == "") return;
    QString jsonpath =  path + "index.json";
    ZipFile::ExtractFile(zippath.toStdString(), "index.json", jsonpath.toStdString());

    QFile jarh(jsonpath);
    jarh.open(QIODevice::ReadWrite);
    QJsonArray jarr = QJsonDocument::fromJson(jarh.readAll()).array();

    QDir pathdir(path);
    pathdir.mkdir("book");

    pc->booklist->clear();

    for(QJsonValue v: jarr)
    {
        QJsonObject o = v.toObject();

        PaperCerberus::bookItem bi;
        bi.name = o["name"].toString();
        bi.autor = o["autor"].toString();
        bi.discriptionText = o["discriptionText"].toString();

        bi.bookColor.setNamedColor(o["bookColor"].toString());
        bi.backraudcolar.setNamedColor(o["backraudcolar"].toString());
        bi.frontcolor.setNamedColor(o["frontcolor"].toString());

        bi.sha256 = o["sha256"].toString();

        for(auto i : o["label"].toArray())
            bi.label.push_back(i.toString());

        ZipFile::ExtractFile(zippath.toStdString(),
                             "book/" + bi.sha256.toStdString() + ".pdf",
                             path.toStdString() + "\\book\\" + bi.sha256.toStdString() + ".pdf"
                             );

        bi.path = path + "\\book\\" + bi.sha256 + ".pdf";


        bi.bookColor = "#" + bi.sha256.right(6);
        pc->booklist->push_front(bi);
    }

    updateBookWidget();

}

void MainWindow::on_openBook_clicked()
{
    qDebug() << ci.path;
    QString pathToFile = ci.path;
    QString pathToProgramm = "explorer";
    QString cmd = pathToProgramm + " " + pathToFile;
    QProcess* proc = new QProcess;
    //proc.execute(pathToFile + pathToProgramm);
    qDebug() << "Command execludable: " + cmd;
    proc->start(cmd);
}

void MainWindow::on_pushButton_4_clicked()
{
    PaperCerberus::bookItem bi = pc->booklist->at(correctitem);
    editDialog ed(bi,this);
    ed.exec();
    PaperCerberus::printbook(bi);

    pc->booklist->operator[](correctitem) = bi;

    ui->discriptionLabel->setText(bi.discriptionText);
    updateBookWidget();
}

void MainWindow::updateBookWidget()
{
    model = new BookModel(pc->booklist);
    if(!searchlabel.isEmpty())
        searh2(searchlabel);
    ui->booksWidgets->setModel(model);
    ui->booksWidgets->setColumnWidth(0,ui->booksWidgets->width() * 0.05);
    ui->booksWidgets->setColumnWidth(1,ui->booksWidgets->width() * 0.6);
    ui->booksWidgets->setColumnWidth(2,ui->booksWidgets->width() * 0.3  - 10);
}

void MainWindow::searh2(QList<QString> labellist)
{

    auto *List1 = pc->booklist;
    auto *List2 = new QList<PaperCerberus::bookItem>;

    for(auto item : *List1)
    {
        bool find = true;
        for(auto l : labellist)
        {
            bool find2 = false;
            for(auto li: item.label)
                if(l == li) find2 = true;
            find = find && find2;
        }
        if(find)
        {
            qDebug() << '\t' << "find file: " + item.name;
            List2->push_back(item);
        }
    }

    //PaperCerberus::printBooks(List2);
    model = new BookModel(List2);
    ui->booksWidgets->setModel(model);
}

void MainWindow::on_pushButton_clicked()
{
    for(auto i : searchlabel)
        if(ui->labeledit->text() == i)
            return;

    qDebug() << "Add label: " + ui->labeledit->text();

    searchlabel.append(ui->labeledit->text());

    ui->labellist->addItem(ui->labeledit->text());

    updateBookWidget();
}

void MainWindow::on_pushButton_5_clicked()
{
    for(auto i : searchlabel)
        if(ui->labeledit->text() == i)
        {
            qDebug() << "Delet label: " + ui->labeledit->text();
            searchlabel.removeOne(i);
            ui->labellist->clear();

            for(auto item : searchlabel)
                ui->labellist->addItem(item);

            searh2(searchlabel);

        }
        updateBookWidget();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->labellist->clear();
    ui->labeledit->clear();
    searchlabel.clear();
    updateBookWidget();
}
