#ifndef NEWITEMDIALOG_H
#define NEWITEMDIALOG_H
#include <QDialog>
#include <QFileDialog>
#include "mainwindow.h"
#include "papercerberus.h"

namespace Ui {
class NewItemDialog;
}

class NewItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewItemDialog(QWidget *parent = nullptr, QList<PaperCerberus::bookItem>* l = nullptr);
    ~NewItemDialog();

private slots:

    void on_openButton_clicked();
    void on_closeButton_clicked();
    void on_addButton_clicked();

    void on_pushButton_clicked();

    void on_deletelabel_clicked();

private:
    Ui::NewItemDialog *ui;
    QList<PaperCerberus::bookItem>* list;
    QList<QString> templabel;
};

#endif // NEWITEMDIALOG_H
