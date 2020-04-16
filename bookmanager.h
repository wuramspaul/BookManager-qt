#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class BookManager; }
QT_END_NAMESPACE

class BookManager : public QMainWindow
{
    Q_OBJECT

public:
    BookManager(QWidget *parent = nullptr);
    ~BookManager();

private:
    Ui::BookManager *ui;
};
#endif // BOOKMANAGER_H
