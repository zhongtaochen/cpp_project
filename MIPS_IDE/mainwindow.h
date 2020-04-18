/**
*@file mainwindow.h
* @brief
* @details  Create a GUI for our IDE
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

class QAction;
class QMenu;
class QPlainTextEdit;
class QStatusBar;
class QSessionManager;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

/**
 * Constructor:MainWindow
 * Usage: MainWindow mainWin;
 * ---------------------------
 * @brief Void initializer for class MainWindow.
 */
    MainWindow(QWidget *parent = nullptr);

/**
 * Destructor:~MainWindow
 * Usage: ~MainWindow mainWin;
 * ---------------------------
 * @brief Destruct a class MainWindow.
 */
    ~MainWindow();

/**
 * Method: loadFile
 * Usage: loadFile(fileName);
 * ------------------------------
 * @brief Load the file with the given filename,used in open().
 */
    void loadFile(const QString &fileName);

signals:
/**
 * Method: debugger
 * Usage: debugger()
 * ------------------------------
 * @brief Send the signal to invoke the debugger function
 */
    void debugger();

protected:
/**
 * Method: closeEvent
 * Usage: assm.output(file_path);
 * ------------------------------
 * @brief Output binary machine code in text file format.
 */
    void closeEvent(QCloseEvent *event) override;

private slots:

    // Menu Bar


    void newFile();


    void find();


    void replace();


    void open();


    bool save();


    bool saveAs();


    void documentWasModified();


    void debug();


    void run();


    void stop();


    void compile();


    void about();

#ifndef QT_NO_SESSIONMANAGER


    void commitData(QSessionManager &);
#endif


private:
    Ui::MainWindow *ui;

    void createActions();


    void createStatusBar();


    void readSettings();


    void writeSettings();


    bool maybeSave();


    bool saveFile(const QString &fileName);


    void setCurrentFile(const QString &fileName);


    QString strippedName(const QString &fullFileName);

    QPlainTextEdit *textEdit;
    QString curFile;
//    Highlighter *highlighter;
    QPlainTextEdit *assemblyText;
//    Assembler *assembler;

};
#endif // MAINWINDOW_H
