/**
 * @file mainwindow.h
 * @brief <code>Mainwindow</code> class.
 * @details This file exports <code>Mainwindow</code> class, which displays the GUI and support open,
 * save and remove files and debug and run MIPS Program.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "highlighter.h"
#include "codeEditor.h"
#include "treeView.h"
#include "assembler.h"
#include "assembler.h"
#include "linker.h"
#include "debugger.h"
#include "loader.h"
#include "simulator.h"
#include "utils.h"
#include "finddialog.h"

#include <QMainWindow>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QSyntaxHighlighter>
#include <QPalette>
#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidget>



class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    /**
     * @brief Initialize a new MainWindow.
     */
    MainWindow();
    /**
     * @brief A QStringList to keep the file names of all opened file.
     */
    QStringList fileNames;
    /**
     * @brief Present a file with specified fileName in codeEditor.
     */
    void loadFile(const QString& fileName);

public slots:
    /**
     * @brief Find and highlight the str in codeEditor if str is found successfully.
     *        Show an error message if str isn't found.
     */
    void search(const QString& str);
    /**
     * @brief Undo the highlights in search func.
     */
    void clear();

signals:
    /**
     * @brief A signal that emits to update the fileList when opening file.
     */
    void tryUpdate(QStringList addFileNames);

protected:
    /**
     * @brief Ask user whether to save changes or not before closing an event.
     */
    void closeEvent(QCloseEvent* event) override;

private slots:
    /**
     * @brief Create a new file.
     */
    void newFile();
    /**
     * @brief Open an existing file.
     */
    void open();
    /**
     * @brief Save the change to current file.
     */
    bool save();
    /**
     * @brief Save the current file as a name inputed by user.
     */
    bool saveAs();
    /**
     * @brief Ask user to input a string.
     *        Find and highlight the string in the current file.(by calling search func)
     */
    void find();
    /**
     * @brief Show the application's About box.
     */
    void about();
    /**
     * @brief Remove the file whose index is k from the QStringList:fileNames.
     *        If there are any files left, present the first file in fileNames in codeEditor.
     *        Otherwise, clear the codeEditor.
     */
    void removeFromList(int k);
    /**
     * @brief Change contents presented in codeEditor to what user double clicked in fileList
     */
    void changeTo(int currentFile);
    /**
     * @brief Run the .asm file.
     */
    void run();
    /**
     * @brief Initialize the debugger and set text segment.
     */
    void debug();
    /**
     * @brief Set whether the file in codeEditor is modified.
     */
    void documentWasModified();
    /**
     * @brief Set or remove breakpoints at (row, col).
     */
    void changeBreakpoints(int row, int col);
    /**
     * @brief Fill the TextSegment with machinecodes and mips instructions.
     */
    void setTextSegment();
    /**
     * @brief Show values of registers in the interface.
     */
    void setAutos();
    /**
     * @brief Run the codes to the next break point.
     */
    void to_next_breakpoint();
    /**
     * @brief step to the next line of execution.
     */
    void step();
#ifndef QT_NO_SESSIONMANAGER
    /**
     * @brief Save all the data,i.e., all the files opened and with operating permission to.
     */
    void commitData(QSessionManager&);
#endif

private:
    /**
     * @brief 1.Create and set up the actions
     *        2.Create the menu and populate them with the actions.
     *        3.Create the toolbars and populate them with the actions.
     */
    void createActions();
    /**
     * @brief Create the StatusBar.
     */
    void createStatusBar();
    /**
     * @brief
     */
    void readSettings();
    /**
     * @brief
     */
    void writeSettings();
    /**
     * @brief Ask user whether to save the change to file in codeEditor.
     *        If yes, save the file(by calling save func).
     */
    bool maybeSave();
    /**
     * @brief Store current contents in codeEditor to the file.
     */
    bool saveFile(const QString& fileName);
    /**
     * @brief Set path of current file as the Qstring:fileName.
     *        Called when trying to loadFile or saveFile.
     */
    void setCurrentFile(const QString& fileName);

	CodeEditor* textEdit;
	QString curFile;
	Highlighter* highlighter;
	DirectoryViewer* fileList;
	FindDialog* findDialog;
	bool isFirstTime;
	QTableWidget* Autos;
	QTableWidget* TextSegment;
	QStringList Registers = { "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0",
							   "$t1",   "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1",
						   "$s2",   "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0",
						   "$k1",   "$gp", "$sp", "$fp", "$ra", "Hi", "Lo"
	};
	std::vector<int> breakpoints;
	int curr_row = 0;
	std::vector<ObjectFile> obj_file_list;
    //Linker linker;
	ExecutableFile exe_file;
	Debugger debugger;
	Loader loader;
	Simulator simulator;
};


#endif
