#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "memoalbum.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_memoAlbum = new MemoAlbum(ui->tabWidget);
    ui->tabWidget->addTab(m_memoAlbum, tr("Memo Album"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

