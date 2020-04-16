#include "bookmanager.h"
#include "./ui_bookmanager.h"

BookManager::BookManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BookManager)
{
    ui->setupUi(this);
}

BookManager::~BookManager()
{
    delete ui;
}

