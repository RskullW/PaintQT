#pragma once
#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QGroupBox>
#include "toolbarsetting.h"
#include <QLabel>
#include <QKeyEvent>
#include <QDesktopServices>
#include "settingsize.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    struct CoordPicture {
        QPoint pos;
        QColor color;
        int width;
        int fl;
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void CreateToolBar();
    void SetGeometryWindow();
    void ToolBarClick();
    void StartBackground();
    void DrawMouse();

    template <typename T> void Log(T text);

protected:

     void paintEvent(QPaintEvent* event) override;
     void keyPressEvent(QKeyEvent* event) override;
     void keyReleaseEvent(QKeyEvent* event) override;
     void mouseMoveEvent(QMouseEvent* event) override;
     void mousePressEvent(QMouseEvent* event) override;
     void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
    void SavePNG();
    void NewPNG();
    void SelectColor();
    void Eraser();
    void ChangeSize();
    void ReturnChange();

private slots:
    void ToYoutube() {
        QDesktopServices::openUrl(QUrl(linkYoutube));
    }

    void ToGithub() {
        QDesktopServices::openUrl(QUrl(linkGit));
    }

    void ToResume() {
        QDesktopServices::openUrl(QUrl(linkResume));
    }
private:
    ToolBarSetting* toolbar;
    QMap<QString, QGroupBox*> m_mapGroupBox;
    QMap<QString, QLabel*> m_mapLabel;
    QImage* m_image;
    QPainter* m_background;
    QMap<QString, QPen*> m_mapPen;
    QBrush* m_brush;

    QVector<CoordPicture> m_coordinatePicture;
    QPoint* m_point;
    SettingSize* m_selectSize;
private:
    bool isCreateNewList;
    bool isSave;
    bool isDraw;
    bool isEraser;
    bool isReturn;
    bool isClose;

    int m_borderBottom, m_borderTo;
    int widthPen;
    QString linkGit = "https://github.com/RskullW", linkResume = "https://spb.hh.ru/resume/4bfb94cfff09d17afd0039ed1f4d4b7a376941", linkYoutube = "https://www.youtube.com/channel/UCAfd0llAInS11lB_O5Rfp5A";
};
