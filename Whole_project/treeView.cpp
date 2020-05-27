#include "treeView.h"
#include <QDirModel>
#include <qdir.h>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QPushButton>

DirectoryViewer::DirectoryViewer(QWidget *parent)
    : QDialog(parent)
{
    listwidget = new QListWidget;
    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *removeButton = buttonBox->addButton(tr("&Remove"),
            QDialogButtonBox::ActionRole);
    buttonBox->addButton(tr("&Quit"), QDialogButtonBox::AcceptRole);

    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listwidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Directory Viewer"));

}

void DirectoryViewer::updateList(QStringList addFileNames){
    if (addFileNames.size()){
        for (int i=0;i<addFileNames.size();i++){
            new QListWidgetItem(addFileNames.at(i),listwidget);
        }
    }
}

void DirectoryViewer::remove()
{
    //获取列表项的指针
    QListWidgetItem *item=listwidget->takeItem(listwidget->currentRow());
    emit removeFrom(listwidget->currentRow());
    delete item;        //释放指针所指向的列表项

}

