#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtZlib/zlib.h>
#include "./include/JlCompress.h"

#include "papercerberus.h"
#include "bookmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(PaperCerberus* ,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addFile_triggered();

    void on_showSearchPanel_triggered();

    void on_pushButton_2_clicked();

    void on_booksWidgets_clicked(const QModelIndex &index);

    void on_closeDiscription_clicked();

    void on_exit_triggered();

    void on_booksWidgets_doubleClicked(const QModelIndex &index);

    void on_save_triggered();

    void on_open_triggered();

    void on_add_triggered();

private:
    Ui::MainWindow *ui;
    PaperCerberus* pc;
    BookModel* model;


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H
