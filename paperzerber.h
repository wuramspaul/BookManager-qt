#ifndef PAPERZERBER_H
#define PAPERZERBER_H

#include <QMainWindow>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class PaperZerber; }
QT_END_NAMESPACE

class PaperZerber : public QMainWindow
{
    Q_OBJECT

public:
    PaperZerber(QWidget *parent = nullptr);
    ~PaperZerber();

private slots:
    void on_OpenArchveAction_triggered();

    void on_ExitAction_triggered();

    void on_SaveArhive_triggered();

    void on_AdvanceSearch_triggered();

private:
    Ui::PaperZerber *ui;
    QJsonDocument* json;
};
#endif // PAPERZERBER_H
