#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDialog(PaperCerberus::bookItem& item, QWidget *parent = nullptr);
    ~editDialog();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::editDialog *ui;
    PaperCerberus::bookItem& i;
    QList<QString> templabel;
};

#endif // EDITDIALOG_H
