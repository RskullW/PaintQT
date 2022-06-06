#include "mainwindow.h"
#include <QMenuBar>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QToolBar>
#include <QFont>
#include <QRgb>
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QtMath>
#include <QPalette>
#include <QtSvg/QSvgGenerator>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isCreateNewList(false), isDraw(false), isEraser(false),
      isSave(false), isClose(false), isReturn(false), widthPen(1),
      m_borderBottom(geometry().height()-47), m_borderTo(47)
{
    m_background = new QPainter();
    m_mapPen["background"] = new QPen();
    m_mapPen["draw"] = new QPen(Qt::black, Qt::SolidLine);

    m_brush = new QBrush();
    m_point = new QPoint();
    m_selectSize = new SettingSize();

    this->setMouseTracking(true);

    SetGeometryWindow();

    CreateToolBar();
    ToolBarClick();

    setAttribute(Qt::WA_StaticContents);
}

MainWindow::~MainWindow()
{

}

void MainWindow::CreateToolBar() {
    toolbar = new ToolBarSetting();

    toolbar->AddMenu("File", "File");
    toolbar->AddSecondMenu("File", "createnew", new QAction(tr("Create new (CTRL+N)...")));
    toolbar->AddSecondMenu("File", "saveas", new QAction(tr("Save as (CTRL+S)...")));

    toolbar->AddMenu("Settings", "Settings");
    toolbar->AddSecondMenu("Settings", "changesize", new QAction(tr("Change size pen...")));
    toolbar->AddSecondMenu("Settings", "selectcolor", new QAction(tr("Select color pen...")));

    toolbar->AddMenu("Info", "Info");
    toolbar->AddSecondMenu("Info", "resume", new QAction(tr("Link to resume")));
    toolbar->AddSecondMenu("Info", "github", new QAction(tr("Link to GitHub")));
    toolbar->AddSecondMenu("Info", "youtube", new QAction(tr("Link to youtube channel")));


    toolbar->AddBar(":/resources/img/new-document.png", "new-document", "Create new (CTRL+N)...");
    toolbar->AddBar(":/resources/img/save.png", "save", "Save as png (CTRL+S)...");
    toolbar->AddBar(":/resources/img/enter-color.png", "enter-color", "Color...");
    toolbar->AddBar(":/resources/img/eraser.png", "eraser", "Eraser...");
    toolbar->AddBar(":/resources/img/input.png", "size", "Select size pen...");

    this->menuBar()->addMenu(toolbar->GetMenu("File"));
    this->menuBar()->addMenu(toolbar->GetMenu("Settings"));
    this->menuBar()->addMenu(toolbar->GetMenu("Info"));

    this->addToolBar(toolbar->GetToolbar());

}

void MainWindow::SetGeometryWindow() {
    this->setWindowState(Qt::WindowMaximized);
    this->setMinimumSize(QSize(600, 480));
}

template <typename T> void MainWindow::Log(T text) {
    qDebug() << text;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    StartBackground();
    DrawMouse();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();

    if (key==Qt::Key_Control) {
        isSave = isCreateNewList = isClose = isReturn = true;
        return;
    }

    if (key==Qt::Key_S && isSave) {
        SavePNG();
        isSave = false;
        return;
    }

    else if (key==Qt::Key_N && isCreateNewList) {
        NewPNG();
        isCreateNewList = false;
        return;
    }

    else if (key==Qt::Key_W && isClose) {
        SavePNG();
        close();
    }

    else if (key == Qt::Key_Z && isReturn) {
        ReturnChange();
    }

    isCreateNewList = isSave = isClose = isReturn = false;

}

void MainWindow::ReturnChange() {
    if (m_coordinatePicture.size()>0) {
        int k = 2*widthPen;
        while (m_coordinatePicture.size()>0 && k--) {
            m_coordinatePicture.pop_back();
            update();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();

    if (key == Qt::Key_Control) {
        isCreateNewList = isSave = isClose = isReturn = false;
    }

}

void MainWindow::StartBackground() {
        int height = qAbs(geometry().height()-0), width = qAbs(geometry().width()-0);

        m_background->begin(this);

        m_mapPen["background"]->setColor(Qt::black);
        m_mapPen["background"]->setStyle(Qt::SolidLine);
        m_mapPen["background"]->setWidth(3);

        m_brush->setColor(Qt::white);
        m_brush->setStyle(Qt::SolidPattern);

        m_background->setPen(*m_mapPen["background"]);
        m_background->setBrush(*m_brush);

        QPolygon m_winPol;

        m_winPol << QPoint(toolbar->x(), 47) << QPoint(width-2, 47);
        m_winPol << QPoint(width-2, height-47) << QPoint(toolbar->x(),height-47);

        m_background->drawPolygon(m_winPol);
        m_background->end();
}

void MainWindow::SavePNG() {
    QString fileName = QFileDialog::getSaveFileName(this, "save as", "/home/", "All File (*.*) ;; JPG File (*.jpg) ;; PNG File (*.png) ;; SVG file (*.svg)");
    QSvgGenerator generator;
    QPainter painter;
    QPolygon m_winPol;

    generator.setFileName(fileName);
    generator.setSize(QSize(geometry().width()-2, geometry().height()-47));
    generator.setViewBox(QRect(toolbar->x(), 47, geometry().width()-2, geometry().height()-47));

    painter.begin(&generator);
    m_mapPen["background"]->setColor(Qt::black);
    m_mapPen["background"]->setStyle(Qt::SolidLine);
    m_mapPen["background"]->setWidth(3);

    m_brush->setColor(Qt::white);
    m_brush->setStyle(Qt::SolidPattern);

    painter.setPen(*m_mapPen["background"]);
    painter.setBrush(*m_brush);

    m_winPol << QPoint(toolbar->x(), 47) << QPoint(geometry().width()-2, 47);
    m_winPol << QPoint(geometry().width()-2, geometry().height()-47) << QPoint(toolbar->x(),geometry().height()-47);

    painter.drawPolygon(m_winPol);

    m_borderBottom = geometry().height()-47;
    m_borderTo = 47;

    for (int i = 1; i < m_coordinatePicture.size(); ++i) {

        if(m_coordinatePicture[i-1].fl==1 || (m_coordinatePicture[i-1].pos.y()<=m_borderTo) || (m_coordinatePicture[i-1].pos.y()>=m_borderBottom)) {
             continue;
         }

         painter.setPen(QPen(m_coordinatePicture[i-1].color, m_coordinatePicture[i-1].width));

         painter.drawLine(m_coordinatePicture[i-1].pos.x(), m_coordinatePicture[i-1].pos.y(), m_coordinatePicture[i].pos.x(), m_coordinatePicture[i].pos.y());
    }

    painter.end();

}

void MainWindow::NewPNG() {
    m_coordinatePicture.clear();
    this->update();
}

void MainWindow::Eraser() {
    m_mapPen["draw"]->setColor(Qt::white);
    isEraser = true;
}

void MainWindow::ChangeSize() {
    m_selectSize->show();
    m_selectSize->passSize(&widthPen);
}

void MainWindow::ToolBarClick() {
    connect(toolbar->GetAction("save"), SIGNAL(triggered()), this, SLOT(SavePNG()));
    connect(toolbar->GetAction("new-document"), SIGNAL(triggered()), this, SLOT(NewPNG()));
    connect(toolbar->GetAction("enter-color"), SIGNAL(triggered()), this, SLOT(SelectColor()));
    connect(toolbar->GetAction("eraser"), SIGNAL(triggered()), this, SLOT(Eraser()));
    connect(toolbar->GetAction("size"), SIGNAL(triggered()), this, SLOT(ChangeSize()));

    connect(toolbar->GetAction("createnew"), SIGNAL(triggered()), this, SLOT(NewPNG()));
    connect(toolbar->GetAction("changesize"), SIGNAL(triggered()), this, SLOT(ChangeSize()));
    connect(toolbar->GetAction("saveas"), SIGNAL(triggered()), this, SLOT(SavePNG()));
    connect(toolbar->GetAction("selectcolor"), SIGNAL(triggered()), this, SLOT(SelectColor()));

    connect(toolbar->GetAction("resume"), SIGNAL(triggered()), this, SLOT(ToResume()));
    connect(toolbar->GetAction("youtube"), SIGNAL(triggered()), this, SLOT(ToYoutube()));
    connect(toolbar->GetAction("github"), SIGNAL(triggered()), this, SLOT(ToGithub()));

}

void MainWindow::SelectColor() {
    QColor color = QColorDialog::getColor(Qt::black, this, "Choose color");
    m_mapPen["draw"]->setColor(color);
    isEraser = false;
}

void MainWindow::DrawMouse() {

    QPainter painter(this);

    m_borderBottom = geometry().height()-47;
    m_borderTo = 47;

    for (int i = 1; i < m_coordinatePicture.size(); ++i) {

        if(m_coordinatePicture[i-1].fl==1 || (m_coordinatePicture[i-1].pos.y()<=m_borderTo) || (m_coordinatePicture[i-1].pos.y()>=m_borderBottom)) {
             continue;
         }

         painter.setPen(QPen(m_coordinatePicture[i-1].color, m_coordinatePicture[i-1].width));

         painter.drawLine(m_coordinatePicture[i-1].pos.x(), m_coordinatePicture[i-1].pos.y(), m_coordinatePicture[i].pos.x(), m_coordinatePicture[i].pos.y());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    m_borderBottom = geometry().height()-47;
    m_borderTo = 47;

    if (isDraw == false || (event->pos().y()<=m_borderTo) || (event->pos().y()>=m_borderBottom)) {
        return;
    }

    *m_point = event->pos();

    m_mapPen["draw"]->setWidth(widthPen);

    CoordPicture coord;
    coord.color = m_mapPen["draw"]->color();
    coord.width = m_mapPen["draw"]->width();
    coord.pos = *m_point;
    coord.fl = 0;
    m_coordinatePicture.append(coord);

    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        isDraw = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        isDraw = 0;

        if(m_coordinatePicture.size()>0) {
            m_coordinatePicture[m_coordinatePicture.size()-1].fl=1;
        }
    }
}
