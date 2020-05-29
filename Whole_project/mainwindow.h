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
	MainWindow();
    QStringList fileNames;
	void loadFile(const QString& fileName);

public slots:
	void search(const QString& str);
	void clear();

signals:
	void tryUpdate(QStringList fileNames);

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void find();
	void about();
    void removeFromList(int k);
    void changeTo(int currentFile);
    /**
     * @brief Run the .asm file
     */
	void run();
    /**
     * @brief Initialize the debugger and set text segment.
     */
	void debug();
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
	void commitData(QSessionManager&);
#endif

private:
	void createActions();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	bool maybeSave();
	bool saveFile(const QString& fileName);
	void setCurrentFile(const QString& fileName);
	QString strippedName(const QString& fullFileName);

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
