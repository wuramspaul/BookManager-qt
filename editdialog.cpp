#include "editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(PaperCerberus::bookItem&item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog),
    i(item)
{
    PaperCerberus::printbook(i);
    ui->setupUi(this);
    ui->nameEdit->setText(i.name);
    ui->autorEdit->setText(i.autor);
    ui->dicsriptionEdit->setText(i.discriptionText);
    ui->backcolor->setText(i.backraudcolar.name());
    ui->fontcolor->setText(i.frontcolor.name());

    templabel = i.label;
    for(auto i : i.label)
        ui->listLabel->addItem(i);
}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::on_pushButton_3_clicked()
{
    i.name = ui->nameEdit->text();
    i.autor = ui->autorEdit->text();
    i.discriptionText = ui->dicsriptionEdit->text();
    i.frontcolor.setNamedColor(ui->fontcolor->text());
    i.backraudcolar.setNamedColor(ui->backcolor->text());

    i.label = templabel;

    editDialog::close();
}

void editDialog::on_pushButton_clicked()
{
    for(auto i : templabel)
        if(ui->labeledt->text() == i)
            return;

    qDebug() << "Add label: " + ui->labeledt->text();

    templabel.append(ui->labeledt->text());

    ui->listLabel->addItem(ui->labeledt->text());
}

void editDialog::on_pushButton_4_clicked()
{
    for(auto i : templabel)
        if(ui->labeledt->text() == i)
        {
            qDebug() << "Delet label: " + ui->labeledt->text();
            templabel.removeOne(i);
            ui->listLabel->clear();

            for(auto item : templabel)
                ui->listLabel->addItem(item);

            return;
        }
}

void editDialog::on_pushButton_2_clicked()
{
    editDialog::close();
}
