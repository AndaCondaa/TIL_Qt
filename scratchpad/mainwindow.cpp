#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scratchpad.h"
#include <QToolBar>
#include <QAction>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scratchPad = new ScratchPad(ui->tabWidget);
    ui->tabWidget->addTab(m_scratchPad, tr("Scratch Pad"));
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

    resize(1024, 800);

//툴바 생성
    QToolBar* toolBar = addToolBar(tr("&tool"));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QAction* Color = new QAction("&Color", this);
    toolBar->addAction(Color);
    QSpinBox* sizeSpin = new QSpinBox(this);
    toolBar->addWidget(sizeSpin);

    connect(Color, SIGNAL(triggered(bool)), m_scratchPad, SLOT(setPaintColor()));
    connect(sizeSpin, SIGNAL(valueChanged(int)), m_scratchPad, SLOT(setPaintSize(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}



