#pragma once

#include <QApplication>
#include <QDebug>
#include <QWidget>
#include <QToolBar>
#include <QMenuBar>
#include <QSize>

#include <map>

class ToolBarSetting: public QWidget
{
    Q_OBJECT

public:
    ToolBarSetting(QSize size = QSize(24,24));

    void AddMenu(QString index, QString text, QAction* action = nullptr);
    void AddSecondMenu(QString mainIndex, QString index, QAction* action = nullptr);
    void AddBar(QString path, QString index, QString text);

    QAction* GetAction(QString index);
    QMenu* GetMenu(QString index);
    QToolBar* GetToolbar() {return toolbar;}
private:
    std::map<QString, QAction*> m_mapAction;
    std::map<QString, QMenu*> m_mapMenu;

    QToolBar* toolbar;
};

