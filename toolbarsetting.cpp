#include "toolbarsetting.h"
#include "string"

ToolBarSetting::ToolBarSetting(QSize size):
    toolbar(new QToolBar()) {
    toolbar->setIconSize(size);
}

void ToolBarSetting::AddMenu(QString index, QString text, QAction* action) {
    m_mapMenu[index] = new QMenu(text);

    if (action != nullptr) {
        m_mapMenu[index]->addAction(action);
        m_mapAction[index] = action;
    }

}

void ToolBarSetting::AddSecondMenu(QString mainIndex, QString index, QAction* action) {
    if (action == nullptr) {
        action = new QAction("Empty");
    }
    m_mapMenu[mainIndex]->addAction(action);
    m_mapAction[index] = action;
}


void ToolBarSetting::AddBar(QString path, QString index, QString text) {
    QAction* action = new QAction(tr(text.toStdString().c_str()));

    m_mapAction[index] = action;

    action->setIcon(QIcon(path.toStdString().c_str()));

    if (toolbar!=nullptr) {
        toolbar->addAction(m_mapAction[index]);
    }
}

QAction* ToolBarSetting::GetAction(QString index) {
    if (m_mapAction[index] != NULL) {
        return m_mapAction[index];
    }

    else {
        throw QString("QAction* not avialiable");
    }
}

QMenu* ToolBarSetting::GetMenu(QString index) {
    if (m_mapMenu[index] != nullptr) {
        return m_mapMenu[index];
    }

    else {
        throw QString("QMenu* not avialiable");
    }
}
