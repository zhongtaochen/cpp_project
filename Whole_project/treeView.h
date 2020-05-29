/**
 * @file treeView.h
 * @brief <code>DirectoryViewer</code> class.
 * @details This file exports <code>DirectoryViewer</code> class, which provides
 * a presentation of the paths of all opened files,i.e.,a list of file paths.
 */

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QDialog>
#include <QListWidget>

class QDialogButtonBox;
class QDirModel;

/**
 * @brief Create a fileList by using a QListWidget.
 *        The fileList present the path of all the files opened.
 *        It will <code>update</code> when users <code>open</code> new files or <code>remove</code> opened files.
 *        Subclass of <code>QDialog</code>.
 */
class DirectoryViewer : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Initializer of <code>DirectoryViewer</code> class.
     */
    DirectoryViewer(QWidget* parent = nullptr);
    QListWidget* listwidget;

private slots:
    /**
     * @brief Remove the item which currently selected by cursor from QlistWidget
     */
    void remove();
    /**
     * @brief Update the contents in codeEditor to the file currently selected by cursor.
     */
    void update();

signals:
    /**
     * @brief A signal to remove the file from the QStringList:fileNames and update the contents in codeEditor.
     *        Emits when user clicked remove botton.
     */
    void removeFrom(int k);
    /**
     * @brief A signal to update the contents in codeEditor to the file currently selected by cursor.
     *        Emits when user double clicked a filename in the fileList.
     */
    void changeToFile(int currentFile);

public slots:
    /**
     * @brief Update the fileList.
     */
    void updateList(QStringList fileNames);

private:
    QDialogButtonBox* buttonBox;
};

#endif // TREEVIEW_H
