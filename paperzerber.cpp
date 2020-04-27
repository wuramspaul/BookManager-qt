#include "paperzerber.h"
#include "./ui_paperzerber.h"

#include <QFileDialog>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QBitArray>
#include <QJsonDocument>
#include <QDebug>

PaperZerber::PaperZerber(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PaperZerber)
{
    ui->setupUi(this);
    // Инициализация виджетов
    ui->searchWidget->hide();
    //ui->discriptionWidget->hide();
    json = new QJsonDocument;
}

PaperZerber::~PaperZerber()
{
    delete ui;
}


void PaperZerber::on_OpenArchveAction_triggered()
{
    QString path = QFileDialog::getOpenFileName
            (this,tr("Open Json File"),QString(),tr("JSON (*.json)"));
    QFileInfo fJsonInfo(path);
    QDir::setCurrent(fJsonInfo.path());
    QFile jsonFile(path);
    if (!jsonFile.open(QIODevice::ReadOnly)) return;
    QByteArray saveData = jsonFile.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData));

    qDebug() << jsonDocument.toJson(QJsonDocument::Compact);

    *json = jsonDocument;
}

void PaperZerber::on_ExitAction_triggered()
{
    PaperZerber::close();
}

void PaperZerber::on_SaveArhive_triggered()
{
    QString path = QFileDialog::getSaveFileName
            (this,tr("Save Json File"),QString(),tr("JSON (*.json)"));

    QFileInfo fileInfo(path);
    QDir::setCurrent(fileInfo.path());
    QFile jsonFile(path);
    if (!jsonFile.open(QIODevice::WriteOnly)) return;

    jsonFile.write(json->toJson(QJsonDocument::Compact));
    jsonFile.close();
}

void PaperZerber::on_AdvanceSearch_triggered()
{
    static bool isOn = false;
    if(isOn) {
        ui->searchWidget->setVisible(false);
        isOn = false;
    } else {
        ui->searchWidget->setVisible(true);
        isOn = true;
    }
}
