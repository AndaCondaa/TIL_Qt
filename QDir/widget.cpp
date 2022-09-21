#include "widget.h"
#include <QDir>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QTextEdit>
#include <QMessageBox>
#include <QProcess>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    directory = new QDir(".");
    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    QPushButton* makeDir = new QPushButton("Make Directory", this);
    QPushButton* removeDir = new QPushButton("Remove Directory", this);
    QPushButton* renameDir = new QPushButton("Rename Directory", this);
    QPushButton* copy = new QPushButton("COPY", this);
    outputEdit = new QTextEdit(this);
    outputEdit->setReadOnly(true);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(makeDir);
    layout->addWidget(removeDir);
    layout->addWidget(renameDir);
    layout->addWidget(copy);
    layout->addWidget(outputEdit);


    connect(dirListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            SLOT(selectItem(QListWidgetItem*)));
    connect(dirListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            SLOT(changeDir()));
    connect(makeDir, SIGNAL(clicked()), SLOT(makeDir()));
    connect(removeDir, SIGNAL(clicked()), SLOT(removeDir()));
    connect(renameDir, SIGNAL(clicked()), SLOT(renameDir()));
    connect(copy, SIGNAL(clicked()), SLOT(copy()));

    refreshDir();
}


Widget::~Widget()
{
}

void Widget::refreshDir()
{
    dirListWidget->clear();
    for(int index = 0; index < directory->entryList().count(); index++){
        dirListWidget->addItem(directory->entryList().at(index));
    }
}

void Widget::selectItem(QListWidgetItem* item)
{
    filenameLineEdit->setText(item->text());
}

void Widget::changeDir()
{
    QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());
    QFileInfo checkDir(filename);
    if(checkDir.isDir()){
        directory->cd(filename);
        refreshDir();
    } else if(checkDir.isFile()){
        QFileInfo fileInfo(filename);
        if(checkDir.isExecutable()){
            QProcess cmd;
            QStringList arguments;
            cmd.start(filename, arguments);
            outputEdit->clear();
            if(!cmd.waitForStarted())
                return;
            QByteArray result = cmd.readAllStandardOutput();
            outputEdit->append(result);
            if(!cmd.waitForFinished())
                return;
            result = cmd.readAllStandardOutput();
            outputEdit->append(result);
        } else if(fileInfo.isReadable()){
            QFile file(filename);
            file.open(QIODevice::ReadOnly);
            QByteArray msg = file.readAll();
            file.close();
            QTextEdit* textedit = new QTextEdit(0);
            textedit->setWindowTitle(filename);
            textedit->setPlainText(msg);
            textedit->setReadOnly(true);
            textedit->show();
        } else{
            QMessageBox::warning(this, "Error", "Can't Read this file",
                                 QMessageBox::Ok);
        }
    }
}

void Widget::makeDir()
{
    if(filenameLineEdit->text().length()){
        directory->mkdir(filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

void Widget::removeDir()
{
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
         QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());
         QFileInfo checkDir(filename);
         if(checkDir.isDir()){
             directory->rmdir(filename);
         } else if(checkDir.isFile()){
             QFile::remove(filename);
         }
     }
     directory->refresh();
     refreshDir();
}

void Widget::renameDir()
{
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        directory->rename(dirListWidget->currentItem()->text(),
                          filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

void Widget::copy()
{
    QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());
    QFileInfo checkDir(filename);
    if(checkDir.isDir()){
        QMessageBox::warning(this, "Error", "Can't copy Directory",
                             QMessageBox::Ok);
    } else if(checkDir.isFile()){
        QFile::copy(filename, filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}
