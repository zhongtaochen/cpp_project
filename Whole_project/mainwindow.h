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

#include <QMainWindow>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QSyntaxHighlighter>
#include <QPalette>
#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QListWidget>  //这里可能改动了！！！


class QAction;
class QMenu;
class QPlainTextEdit;
class QLineEdit;
class QTreeWidget;
class QSessionManager;
class FindDialog;



class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	QStringList fileNames;//改动了！！！！！
	void loadFile(const QString& fileName);

public slots:
	void search(const QString& str);
	void clear();

signals://改动了！！！！！
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
	void run();
	void debug();
	void documentWasModified();
	void changeBreakpoints(int row, int col);
	void removeFromList(int k);//改动了！！！！！
	void setTextSegment();
	void setAutos();
	void to_next_breakpoint();

	/**
	 * Method: step
	 * Usage: step();
	 * ------------------------------
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
	Linker linker;
	ExecutableFile exe_file;
	Debugger debugger;
	Loader loader;
	Simulator simulator;
};


#endif
