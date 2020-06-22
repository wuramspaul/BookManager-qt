#include "saveinfo.h"
#include "ui_saveinfo.h"

saveInfo::saveInfo(QList<PaperCerberus::bookItem>* l,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveInfo)
{
    list = l;
    show();
    ui->setupUi(this);
    save();
    setHidden(true);
}

saveInfo::~saveInfo()
{
    delete ui;
}

void saveInfo::save()
{
    ui->label->setText("");
    QString jsonPath = "index.json";
    QDir::setCurrent("C:");
    QString arhPath = QFileDialog::getSaveFileName
            (this,tr("Save arhive File"),QString(),tr("ZIP (*.zip)"));

    QFile jsonFile(jsonPath);
    jsonFile.open(QIODevice::WriteOnly | QIODevice::ReadWrite);

    QJsonArray jarr;
    QJsonObject jobj;

    unsigned procent = (100 - 10) / list->count();

    for(PaperCerberus::bookItem o: *list)
    {

        ui->label->setText(o.path);
        jobj["name"]  = o.name;
        jobj["autor"] = o.autor;
        jobj["discriptionText"] = o.discriptionText;
        jobj["path"] = "arhive";
        jobj["bookColor"] = o.bookColor.name();
        jobj["backraudcolar"] = o.backraudcolar.name();
        jobj["frontcolor"] = o.frontcolor.name();
        jobj["sha256"] = o.sha256;

        QJsonArray labelarr;
        for(auto i : o.label)
            labelarr.push_back(QJsonValue::fromVariant(QVariant(i)));

        jobj["label"] = labelarr;

        jarr.push_back(jobj);

        qDebug() << o.path;

        QString pathToFile = o.path;
        QString end_pathToFile = QDir::currentPath() + "\\temp\\" + o.sha256 + ".pdf";

        QDir spath(QDir::currentPath());
        spath.mkdir("temp");

        QFile::copy(pathToFile, end_pathToFile);

        ZipFile::AddFile(arhPath.toStdString(), end_pathToFile.toStdString() , "book/" + o.sha256.toStdString() + ".pdf");

        ui->progressBar->setValue(ui->progressBar->value() + procent);
    }


    jsonFile.resize(0);
    jsonFile.write(QJsonDocument(jarr).toJson(QJsonDocument::Indented));
    jsonFile.close();
    ui->label->setText("Сохранение метафайла");
    ZipFile::AddFile(arhPath.toStdString(), jsonPath.toStdString());

    ui->progressBar->setValue(100);
    ui->label->setText("Готово");
}
