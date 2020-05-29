#include "treeView.h"
#include <QDirModel>
#include <qdir.h>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QPushButton>

DirectoryViewer::DirectoryViewer(QWidget* parent)
    : QDialog(parent)
{
    listwidget = new QListWidget;
    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton* removeButton = buttonBox->addButton(tr("&Remove"),
        QDialogButtonBox::ActionRole);

    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    connect(listwidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(update()));

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listwidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Directory Viewer"));

}

void DirectoryViewer::updateList(QStringList addFileNames) {
    if (addFileNames.size()) {
        for (int i = 0; i < addFileNames.size(); i++) {
            new QListWidgetItem(addFileNames.at(i), listwidget);
        }
    }
}

void DirectoryViewer::remove()
{
    //Get the pointer to the QlistWidgetItem on current row
    QListWidgetItem* item = listwidget->takeItem(listwidget->currentRow());
    emit removeFrom(listwidget->currentRow());
    delete item;        //Release the QlistWidgetItem the pointer pointed to

}

void DirectoryViewer::update()
{
    int currentFile = listwidget->currentRow();
    emit changeToFile(currentFile);
}

