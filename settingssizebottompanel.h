#pragma once

#include <QLabel>
#include <QApplication>
#include <QPushButton>
#include <QGroupBox>
#include <QWidget>
#include <QFont>
#include <QLayout>
#include <QString>

class SettingsSizeBottomPanel :
        public QWidget
{
    Q_OBJECT
public:
    SettingsSizeBottomPanel(QString text = "clear");
private:
    QGroupBox* m_boxLayout;
    QLabel* m_text;
    QGridLayout* m_gridLayout;
};
