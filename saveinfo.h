#ifndef SAVEINFO_H
#define SAVEINFO_H

#include <QDialog>

#include "mainwindow.h"
#include <string>

namespace Ui {
class saveInfo;
}

class saveInfo : public QDialog
{
    Q_OBJECT

public:
    explicit saveInfo(QList<PaperCerberus::bookItem>* list,QWidget *parent = nullptr);
    ~saveInfo();
    void save();
private:
    Ui::saveInfo *ui;
    QList<PaperCerberus::bookItem>* list;
};

#endif // SAVEINFO_H
