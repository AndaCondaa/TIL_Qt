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
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);
#if 1
    QTextEdit* textEdit = new QTextEdit(this);
    mdiArea->addSubWindow(textEdit);
#else
    newFile();
#endif

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
    QAction* clear= makeAction("","&Clear", tr("Ctrl+d"),
                             "UNDO!", this, SLOT(editText()));
    QAction* undo = makeAction("","&Undo", tr("Ctrl+z"),
                              "UNDO!", this, SLOT(editText()));
    QAction* redo = makeAction("","&Redo", QKeySequence::Redo,
                               "REDO!", this, SLOT(editText()));
    QAction* copy = makeAction("","&Copy", QKeySequence::Copy,
                               "카피!", this, SLOT(editText()));
    QAction* cut = makeAction("","&Cut", QKeySequence::Cut,
                               "껐뜨!", this, SLOT(editText()));
    QAction* paste = makeAction("","&Paste", QKeySequence::Paste,
                               "붙여넣자!", this, SLOT(editText()));
    QAction* zoomIn = makeAction("","&zoomIn", QKeySequence::ZoomIn,
                               "커져라!", this, SLOT(editText()));
    QAction* zoomOut = makeAction("","&zoomOut", QKeySequence::ZoomOut,
                               "작아져라!", this, SLOT(editText()));

//Edit 메뉴
    QMenu* edit = menubar->addMenu("&Edit");
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


//QDockWidget
    QLabel* label = new QLabel("Dock Widget",this);
    QDockWidget* dock = new QDockWidget("Dock Widgettttt",this);
    //붙일 수 있는 곳 선택 (왼쪽, 오른쪽)
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //add(초기 위치 설정
    addDockWidget(Qt::LeftDockWidgetArea,dock);
    dock->setWidget(label);     //여러 개의 위젯 붙이려면, 사용자 정의 위젯을 만들어서 한번에 올리기

    formatToolbar->addAction(dock->toggleViewAction());
}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile()
{
    qDebug("Make New File");
    QTextEdit* textedit = new QTextEdit;
    mdiArea->addSubWindow(textedit);
    textedit->show();
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

template <typename T, typename Functor>
QAction* QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
    {
        icon = ":/images/" + icon;      //리소스 시스템 경로 설정
         act->setIcon(QIcon(icon));
    }
    QKeySequence keySequence(shortCut);
    act->setShortcut(keySequence);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}

template <typename T>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              T shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    icon = ":/images/" + icon;
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

void QtEditor::alignText()
{
    QAction *action = qobject_cast<QAction*>(sender());
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    QTextEdit* textEdit = dynamic_cast<QTextEdit*>(subWindow->widget());
    if(action->text().contains("center",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignCenter);
    else if (action->text().contains("left",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignLeft);
    else if (action->text().contains("right",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignRight);
    else if (action->text().contains("justify",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignJustify);
}

void QtEditor::editText()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    QTextEdit* textEdit = dynamic_cast<QTextEdit*>(subWindow->widget());

    QAction *action = qobject_cast<QAction*>(sender());

    if(action->text().contains("clear",Qt::CaseInsensitive))
        textEdit->clear();
    else if (action->text().contains("undo",Qt::CaseInsensitive))
        textEdit->undo();
    else if (action->text().contains("redo",Qt::CaseInsensitive))
        textEdit->redo();
    else if (action->text().contains("copy",Qt::CaseInsensitive))
        textEdit->copy();
    else if (action->text().contains("cut",Qt::CaseInsensitive))
        textEdit->cut();
    else if (action->text().contains("paste",Qt::CaseInsensitive))
        textEdit->paste();
    else if (action->text().contains("zoomIn",Qt::CaseInsensitive))
        textEdit->zoomIn();
    else if (action->text().contains("zoomOut",Qt::CaseInsensitive))
        textEdit->zoomOut();
}
