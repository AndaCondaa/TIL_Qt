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
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

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
    QAction* newAct = makeAction("new.png","&New",tr("Ctrl+N"), "Make new file", this, SLOT(newFile()));
    QAction* openAct = makeAction("open.png","&Open",tr("Ctrl+O"), "Open new file", this, SLOT(openFile()));
    QAction* saveAct = makeAction("save.png", "&Save", tr("Ctrl+S"), "Save this file", this, SLOT(saveFile()));
    QAction* saveAsAct = makeAction("", "&Save As", QKeySequence::SaveAs, "Save this file", this, SLOT(saveAsFile()));
    QAction* printAct = makeAction("", "&Print", tr("Ctrl+P"), "Print", this, SLOT(printFile()));
    QAction* quitAct = makeAction("quit.png","&Quit",tr("Ctrl+Q"), "Quit this program", qApp, SLOT(quit()));

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
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), textEdit, SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), textEdit, SLOT(setFontPointSize(qreal)));

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
//    QAction* clear= makeAction("","&Clear", tr("Ctrl+d"),
//                               "UNDO!", this, SLOT(clear()));
//    QAction* undo = makeAction("","&Undo", tr("Ctrl+z"),
//                               "UNDO!", this, SLOT(undo()));
//    QAction* redo = makeAction("","&Redo", QKeySequence::Redo,
//                               "REDO!", this, SLOT(redo()));
//    QAction* copy = makeAction("","&Copy", QKeySequence::Copy,
//                               "카피!", this, SLOT(copy()));
//    QAction* cut = makeAction("","&Cut", QKeySequence::Cut,
//                              "껐뜨!", this, SLOT(cut()));
//    QAction* paste = makeAction("","&Paste", QKeySequence::Paste,
//                                "붙여넣자!", this, SLOT(paste()));
//    QAction* zoomIn = makeAction("","&zoomIn", QKeySequence::ZoomIn,
//                                 "커져라!", this, SLOT(zoomIn()));
//    QAction* zoomOut = makeAction("","&zoomOut", QKeySequence::ZoomOut,
//                                  "작아져라!", this, SLOT(zoomOut()));
    QAction* clear = new QAction("&Clear", this);
    QAction* undo = new QAction("&Undo", this);
    QAction* redo = new QAction("&Redo", this);
    QAction* copy = new QAction("&Copy", this);
    QAction* cut = new QAction("&Cut", this);
    QAction* paste = new QAction("&Paste", this);
    QAction* zoomIn = new QAction("&zoomIn", this);
    QAction* zoomOut = new QAction("&zoomOut", this);

//Edit 메뉴 추가
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

//QList에 액션 추가
    actions.append(clear);
    actions.append(undo);
    actions.append(redo);
    actions.append(copy);
    actions.append(cut);
    actions.append(paste);
    actions.append(zoomIn);
    actions.append(zoomOut);

    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            SLOT(connectWindow(QMdiSubWindow*)));

//QMessageBox 클래스
    QMenu* help = menubar->addMenu("&Help");
    QAction* about = help->addAction("&About");
    QAction* aboutqt = help->addAction("&Aboutqqqqq");
    connect(about, SIGNAL(triggered()), this, SLOT(aboutBox()));
    connect(aboutqt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

//Window메뉴
    QMenu* window = menubar->addMenu("&Window");
    QAction* nextWindow = makeAction("", "&Next",
                                     "Ctrl+]", "다음 창!", mdiArea, SLOT(activateNextSubWindow()));
    QAction* prevWindow = makeAction("", "&Prev",
                                     "Ctrl+[", "이전 창!", mdiArea, SLOT(activatePreviousSubWindow()));
    QAction* cascadeWindow = makeAction("", "&Cascade",
                                     "", "정렬!", mdiArea, SLOT(cascadeSubWindows()));
    QAction* closeActWindow = makeAction("", "&CloseAct",
                                     "", "closeAct!", mdiArea, SLOT(closeActiveSubWindow()));
    QAction* closeAllWindow = makeAction("", "&CloseAll",
                                     "", "closeAll!", mdiArea, SLOT(closeAllSubWindows()));
    QAction* tileWindow = makeAction("", "&CloseAct",
                                     "", "closeAct!", mdiArea, SLOT(tileSubWindows()));
    window->addAction(nextWindow);
    window->addAction(prevWindow);
    window->addAction(cascadeWindow);
    window->addAction(closeActWindow);
    window->addAction(closeAllWindow);
    window->addAction(tileWindow);
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
    QString filename = QFileDialog::getOpenFileName(this, "Select file to open",
                                             ".","Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
}
void QtEditor::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save",
                                             ".","Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
}
void QtEditor::saveAsFile()
{
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save as",
                                             ".","Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
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
    QKeySequence keySequence(shortCut);
    act->setShortcut(keySequence);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

void QtEditor::alignText()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    QTextEdit* textEdit = dynamic_cast<QTextEdit*>(subWindow->widget());

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

/*
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
}*/

void QtEditor::connectWindow(QMdiSubWindow* actWin)
{
//    QTextEdit* newEdit = qobject_cast<QTextEdit*>(actWin->widget());
//    //기존 해제
//    if (prevEdit != nullptr)
//    {
//        Q_FOREACH(QAction* act, actions)
//            act->disconnect(prevEdit);
//    }
//    //새로 연결
//    const char *methods[7] = {
//        SLOT(undo( )), SLOT(redo( )), SLOT(copy( )), SLOT(cut( )),
//        SLOT(paste( )), SLOT(zoomIn( )), SLOT(zoomOut( ))
//    };
//    int cnt = 0;
//    Q_FOREACH(QAction *action, actions) {
//        connect(action, SIGNAL(triggered()), newEdit, methods[cnt++]);
//    }

//    prevEdit = newEdit;

    if(actWin == nullptr) {		// 모든 창이 닫혔을 때
        prevEdit = nullptr;     // prevTextEdit 변수에 저장한 창이 닫히므로 nullptr로 초기화
    } else {				// 창이 열려 있을 때
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(actWin->widget( ));
        /* 모든 QAction에 연결된 슬롯 해제 */
        if(prevEdit != nullptr) {
            Q_FOREACH(QAction *action, actions)
                action->disconnect(prevEdit);
        }
        prevEdit = textEdit;			/* 현재 객체를 다음 처리를 위해 저장 */

        // 슬롯들을 위한 배열
        const char *methods[7] = {
            SLOT(undo( )), SLOT(redo( )), SLOT(copy( )), SLOT(cut( )),
            SLOT(paste( )), SLOT(zoomIn( )), SLOT(zoomOut( ))
        };

        /* QAction에 현재 선택된 객체의 슬롯을 연결 */
        int cnt = 0;
        Q_FOREACH(QAction *action, actions) {
            connect(action, SIGNAL(triggered( )), textEdit, methods[cnt++]);
        }
    }
}

void QtEditor::aboutBox()
{
    QMessageBox::information(this, "Information",
                 "infomation contents", QMessageBox::Yes |
                 QMessageBox::No | QMessageBox::Cancel);
}

