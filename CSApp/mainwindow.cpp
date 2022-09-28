#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientmanagerform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ClientManagerForm *clientForm = new ClientManagerForm(this);
    ui->tabWidget->addTab(clientForm,"&Client Form");
}

MainWindow::~MainWindow()
{
    delete ui;
}

