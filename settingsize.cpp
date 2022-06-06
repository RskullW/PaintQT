#include "settingsize.h"

SettingSize::SettingSize(): isSelect(false)
{
    sizeText = new QLabel;
    textEnter = new QLineEdit();
    buttonTrue = new QPushButton();
    buttonFalse = new QPushButton();
    mainLayout = new QGridLayout;

    textEnter->setValidator( new QIntValidator(0, 10, this) );
    sizeText->setText(tr("Enter size text"));

    buttonTrue->setText("Select");
    buttonFalse->setText("Exit");

    mainLayout->addWidget(sizeText, 0, 0);
    mainLayout->addWidget(textEnter, 0, 1);
    mainLayout->addWidget(buttonTrue, 1, 0);
    mainLayout->addWidget(buttonFalse, 1, 1);

    setLayout(mainLayout);

    connect(buttonFalse, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonTrue, SIGNAL(clicked()), this, SLOT(Selected()));
    connect(buttonTrue, SIGNAL(clicked()), this, SLOT(close()));

}

void SettingSize::Selected() {
    *size = textEnter->text().toInt();

    if (*size <= 0) {
        *size = 1;
    }

    close();
}

void SettingSize::keyPressEvent(QKeyEvent* event) {
    int key = event->key();

    if (key==Qt::Key_Return) {
        Selected();
        close();
    }
}
