#include "qteditor.h"
#include <QApplication>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QStatusBar>
#include <QLabel>

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
//텍스트 에디터 생성
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

//메뉴바 생성
    QMenuBar* menubar = new QMenuBar(this);
    setMenuBar(menubar);

//액션 생성 in fileMenu
    QAction* newAct = makeAction("new.png","&New",tr("Ctrl+N"),
                                 "Make new file", this, SLOT(newFile()));
    QAction* openAct = makeAction("open.png","&Open",tr("Ctrl+O"),
                                  "Open new file", this, SLOT(openFile()));
    QAction* saveAct = makeAction("save.png", "&Save", tr("Ctrl+S"),
                                  "Save this file", this, SLOT(saveFile()));
    QAction* saveAsAct = makeAction("", "&Save As", QKeySequence::SaveAs,
                                    "Save this file", this, SLOT(saveAsFile()));
    QAction* printAct = makeAction("", "&Print", tr("Ctrl+P"),
                                   "Print", this, SLOT(printFile()));
    QAction* quitAct = makeAction("quit.png","&Quit",tr("Ctrl+Q"),
                                  "Quit this program", qApp, SLOT(quit()));

//fileMenu 생성 및 액션추가
    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

//ToolBar 생성 및 액션추가
    QToolBar* fileToolBar = addToolBar("&ToolBar");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

//toolBarMenu 생성 (토글액션)
    QMenu* toolBarMenu = menubar->addMenu("&toolBarMenu");
    toolBarMenu->addAction(fileToolBar->toggleViewAction());

//ToolBar에 위젯 추가
    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)),
            textEdit, SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)),
            textEdit, SLOT(setFontPointSize(qreal)));

    addToolBarBreak();

    QToolBar* formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

//QStatusBar 클래스
    QStatusBar* statusbar = statusBar();
    QLabel* statusLabel = new QLabel("Qt Editor", statusbar);
    statusLabel->setObjectName("Status Label");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);

//Edit 액션 추가
    QAction* append= new QAction("&Append", this);
    connect(append, SIGNAL(triggered(bool)), textEdit, SLOT(append()));
    QAction* clear= new QAction("&Clear", this);
    connect(clear, SIGNAL(triggered(bool)), textEdit, SLOT(clear()));
    QAction* undo = makeAction("","&Undo", tr("Ctrl+z"),
                              "UNDO!", textEdit, SLOT(undo()));
    QAction* redo = makeAction("","&Redo", QKeySequence::Redo,
                               "REDO!", textEdit, SLOT(redo()));
    QAction* copy = makeAction("","&Copy", QKeySequence::Copy,
                               "카피!", textEdit, SLOT(copy()));
    QAction* cut = makeAction("","&Cut", QKeySequence::Cut,
                               "껐뜨!", textEdit, SLOT(cut()));
    QAction* paste = makeAction("","&Paste", QKeySequence::Paste,
                               "붙여넣자!", textEdit, SLOT(paste()));
    QAction* zoomIn = makeAction("","&zoomIn", QKeySequence::ZoomIn,
                               "커져라!", textEdit, SLOT(zoomIn()));
    QAction* zoomOut = makeAction("","&zoomOut", QKeySequence::ZoomOut,
                               "작아져라!", textEdit, SLOT(zoomOut()));

//Edit 메뉴
    QMenu* edit = menubar->addMenu("&Edit");
    edit->addAction(append);
    edit->addAction(clear);
    edit->addSeparator();
    edit->addAction(undo);
    edit->addAction(redo);
    edit->addSeparator();
    edit->addAction(copy);
    edit->addAction(cut);
    edit->addAction(paste);
    edit->addSeparator();
    edit->addAction(zoomIn);
    edit->addAction(zoomOut);

//서브메뉴 align
    QMenu* formatMenu = menubar->addMenu("&Format");
    QMenu* alignMenu = new QMenu("&Align",this);
    formatMenu->addMenu(alignMenu);
    QAction* center = new QAction("&Center", this);
    QAction* left = new QAction("&Left", this);
    QAction* right = new QAction("&Right", this);
    QAction* justify = new QAction("&Justify", this);
    alignMenu->addAction(center);
    alignMenu->addAction(left);
    alignMenu->addAction(right);
    alignMenu->addAction(justify);

    connect(center, SIGNAL(triggered()), SLOT(alignText()));
    connect(left, SIGNAL(triggered()), SLOT(alignText()));
    connect(right, SIGNAL(triggered()), SLOT(alignText()));
    connect(justify, SIGNAL(triggered()), SLOT(alignText()));

}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile()
{
    qDebug("Make New File");
}
void QtEditor::openFile()
{
    qDebug("Open New File");
}
void QtEditor::saveFile()
{
    qDebug("Save This File");
}
void QtEditor::saveAsFile()
{
    qDebug("Save As....");
}
void QtEditor::printFile()
{
    qDebug("Print");
}


template <typename T>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              T shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

template <typename T, typename Functor>
QAction* QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
         act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}

void QtEditor::alignText()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action->text().contains("center",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignCenter);
    else if (action->text().contains("left",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignLeft);
    else if (action->text().contains("right",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignRight);
    else if (action->text().contains("justify",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignJustify);
}

