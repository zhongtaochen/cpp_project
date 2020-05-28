#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QDialog>
#include <QListWidget>

class QDialogButtonBox;
class QDirModel;

class DirectoryViewer : public QDialog
{
    Q_OBJECT

public:
    DirectoryViewer(QWidget *parent = nullptr);
    QListWidget *listwidget;

private slots:
    void remove();
    void update();

signals:
    void removeFrom(int k);
    void changeToFile(int currentFile);

public slots:
    void updateList(QStringList fileNames);

private:
    QDialogButtonBox *buttonBox;
};

#endif // TREEVIEW_H
