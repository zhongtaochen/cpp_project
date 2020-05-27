// #include <QtGui>
#include <QDialog>
#include <QLabel>       //class QLabel;
#include <QLineEdit>    //class QLineEdit;
#include <QPushButton>  //class QPushButton;
#include <QHBoxLayout>   //in the finddialog.cpp
#include <QVBoxLayout>   //in the finddialog.cpp
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel (tr("Find &what:"));
    lineEdit = new QLineEdit;
    label -> setBuddy(lineEdit);
    findButton = new QPushButton(tr("&Find"));
    findButton -> setDefault(true);
    findButton -> setEnabled(false);
    closeButton = new QPushButton(tr("close"));
    connect (lineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableFindButton(const QString &)));
    connect (findButton, SIGNAL(clicked()),
             this, SLOT(findClicked()));
    connect (closeButton, SIGNAL(clicked()),
             this, SLOT(closeClicked()));

    QHBoxLayout *leftLayout = new QHBoxLayout;
    leftLayout -> addWidget(label);
    leftLayout -> addWidget(lineEdit);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout -> addWidget(findButton);
    rightLayout -> addWidget(closeButton);
    rightLayout -> addStretch();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout -> addLayout(leftLayout);
    mainLayout -> addLayout(rightLayout);
    setLayout(mainLayout);
    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());
}

void FindDialog::findClicked()
{
    QString text = lineEdit -> text();
    search(text);
}

void FindDialog::closeClicked()
{
    clear();
    lineEdit->clear();
    close();
}

void FindDialog::enableFindButton(const QString &text)
{
    findButton -> setEnabled(!text.isEmpty());
}


