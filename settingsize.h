#pragma once
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QIntValidator>
#include <QPushButton>
#include <QKeyEvent>

class SettingSize: public QWidget
{
    Q_OBJECT
public:
    SettingSize();
    int PassSize();

    void keyPressEvent(QKeyEvent* event) override;
    void passSize(int *width) {size = width;}
private slots:
    void Selected();
private:
    QString stringSize;
    QLabel* sizeText;
    QLineEdit* textEnter;
    QPushButton* buttonTrue, *buttonFalse;
    QGridLayout* mainLayout;

    bool isSelect;
    int* size;
};
