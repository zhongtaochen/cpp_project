#include <QtWidgets>
#include <QtDebug>
#include <QDebug>
#include <QProcess>
#include "mainwindow.h"
#include "finddialog.h"
#include <sstream>
#include <iostream>



MainWindow::MainWindow()
	: textEdit(new CodeEditor), fileList(new DirectoryViewer), Autos(new QTableWidget), TextSegment(new QTableWidget)
{
	QSplitter* mainSplitter = new QSplitter(Qt::Horizontal);
	mainSplitter->addWidget(fileList);
	mainSplitter->addWidget(textEdit);
	mainSplitter->addWidget(Autos);
    mainSplitter->addWidget(TextSegment);

	Autos->setColumnCount(2);
	Autos->setWindowTitle("Variables & values");
	QStringList header1;
    header1 << "Registers" << "Values";
	Autos->setHorizontalHeaderLabels(header1);
	Autos->setEditTriggers(QAbstractItemView::NoEditTriggers);
	Autos->horizontalHeader()->setStretchLastSection(true);

    TextSegment->setColumnCount(1);
    TextSegment->setWindowTitle("breakpoint & asm_lines");
    QStringList header2;
    header2 << "address        asm_lines";
    TextSegment->setHorizontalHeaderLabels(header2);
    TextSegment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    TextSegment->horizontalHeader()->setStretchLastSection(true);


	mainSplitter->setStretchFactor(1, 1);

	setCentralWidget(mainSplitter);
	createActions();
	createStatusBar();
	readSettings();

	findDialog = 0;

	highlighter = new Highlighter(textEdit->document());
	connect(textEdit->document(), &QTextDocument::contentsChanged,
		this, &MainWindow::documentWasModified);

#ifndef QT_NO_SESSIONMANAGER
	QGuiApplication::setFallbackSessionManagementEnabled(false);
	connect(qApp, &QGuiApplication::commitDataRequest,
		this, &MainWindow::commitData);
#endif

	setCurrentFile(QString());
	setUnifiedTitleAndToolBarOnMac(true);

	QStringList fileNames;
    connect(fileList,SIGNAL(removeFrom(int)),this,SLOT(removeFromList(int)));

    connect(fileList,SIGNAL(changeToFile(int)),this,SLOT(changeTo(int)));
}


void MainWindow::closeEvent(QCloseEvent* event)
{
	if (maybeSave()) {
		writeSettings();
		event->accept();
	}
	else {
		event->ignore();
	}
}

void MainWindow::newFile()
{
	if (maybeSave()) {
		textEdit->clear();
		setCurrentFile(QString());
	}
}

void MainWindow::open()
{   //ask whether to save the current file or not
    if (maybeSave()) {
        //get the filenames of chosen files,keep them in a QtringList:addFileNames.
        QStringList addFileNames = QFileDialog::getOpenFileNames(this);
        //for each filename in addFileNames
        for (int i=0;i<addFileNames.size();i++){
            //if it is not in fileNamse,add it into fileNames.
            if (!fileNames.contains(addFileNames.at(i))){
                fileNames.push_back(addFileNames.at(i));
            }
            //if it is in fileNames,remove it from addFileNames.
            else{
                if (addFileNames.size()==1){
                    addFileNames.clear();
                }else{
                    addFileNames.removeAt(i);
                }
            }
        }
        //if there are filenames in addFileNames,present the first of them in the codeEditor
        //emit the signal to update the file list
        if (!addFileNames.isEmpty()){
            QString fileName=addFileNames.at(0);
            loadFile(fileName);
        emit tryUpdate(addFileNames);
        }
    }
}


void MainWindow::removeFromList(int k){
    //remove the file from fileNames
    if (fileNames.size()>1){
        fileNames.removeAt(k);
    }else{
        fileNames.clear();
    }
    //if there are files left in fileNames, present the first of them
    if (!fileNames.isEmpty()){
        QString fileName=fileNames.at(0);
        loadFile(fileName);
    //if there is no file left in fileNames,clear the codeEditor
    }else{
        textEdit->clear();
    }
}

void MainWindow::changeTo(int currentFile)
{
    if (QString::compare(curFile,fileNames.at(currentFile),Qt::CaseInsensitive)!=0){
        QString fileName=fileNames.at(currentFile);
        loadFile(fileName);
    }
}

bool MainWindow::save()
{
	if (curFile.isEmpty()) {
		return saveAs();
	}
	else {
		return saveFile(curFile);
	}
}

bool MainWindow::saveAs()
{
	QFileDialog dialog(this);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	if (dialog.exec() != QDialog::Accepted)
		return false;
	return saveFile(dialog.selectedFiles().first());
}

void MainWindow::find()
{
	if (!findDialog) {
		findDialog = new FindDialog(this);
		connect(findDialog, SIGNAL(search(const QString&)),
			this, SLOT(search(const QString&)));
	}
	connect(findDialog, SIGNAL(clear()),
		this, SLOT(clear()));
	findDialog->show();
	findDialog->raise();
	findDialog->activateWindow();
}

void MainWindow::search(const QString& str)
{
	// 查找当前选中文本
	QString search_text = str;
	QTextDocument* document = textEdit->document();

	bool found = false;

	if (isFirstTime == false)
		document->undo();

	if (search_text.trimmed().isEmpty()) {
		QMessageBox::information(this, tr("Empty search field"), tr("The search field is empty.Please enter a word and click Find."));
	}
	else {
		QTextCursor highlight_cursor(document);
		QTextCursor cursor(document);

		cursor.beginEditBlock();

		while (!highlight_cursor.isNull() && !highlight_cursor.atEnd()) {
			highlight_cursor = document->find(search_text, highlight_cursor);//, QTextDocument::FindWholeWords
			if (!highlight_cursor.isNull()) {
				found = true;
				highlight_cursor.movePosition(QTextCursor::WordRight,
					QTextCursor::KeepAnchor);
				setAutoFillBackground(true);
				QTextCharFormat fmt = highlight_cursor.charFormat();
				fmt.setBackground(Qt::yellow);
				highlight_cursor.mergeCharFormat(fmt);
			}
		}
		cursor.endEditBlock();
		isFirstTime = false;
		if (found == false) {
			QMessageBox::information(this, tr("Word not found"), tr("Sorry,the word cannot be found."));
		}
	}
}

void MainWindow::clear()
{
	textEdit->undo();
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Application"),
		tr("The <b>Application</b> example demonstrates how to "
			"write modern GUI applications using Qt, with a menu bar, "
			"toolbars, and a status bar."));
}



void MainWindow::run()
{
    obj_file_list = {};
	if (fileNames.isEmpty()) {
		QMessageBox::about(this, tr("About Run"),
			tr("Please check if you have opened any file or you have saved the file"));
		return;
	}
	for (QString file_name : fileNames) {
		std::ifstream file = readFile(file_name.toStdString());
		Assembler assm;
		assm.assemble(file);
		obj_file_list.push_back(assm.getObjFile());
	}
    Linker linker;
	linker.link(obj_file_list);
	exe_file = linker.getExecutableFile();
	loader.load(&exe_file);
	simulator.simulate(loader.getMemorySimulator(), loader.getRegisterFilesSimulator());
	simulator.run();

}

void MainWindow::setTextSegment() {
	QStringList result = textseg_to_Qstring(debugger.getTextSection());
    TextSegment->setRowCount(result.size());;
    TextSegment->setColumnCount(1);
	for (int i = 0; i < result.size(); i++) {
		QString tmp = result.at(i);
		QTableWidgetItem* item0 = new QTableWidgetItem(tmp);
        item0->setCheckState(Qt::Unchecked);
        TextSegment->setItem(i, 0, item0);
    }
    TextSegment->viewport()->update();
}

void MainWindow::setAutos() {
    Autos->setColumnCount(2);
    Autos->setRowCount(Registers.size());
	for (int i = 0; i < Registers.size(); i++) {
		unsigned int address = debugger.getRegisterFilesSimulator()->readReg(i);
		std::stringstream sstrm;
		sstrm << std::dec << address;
		QTableWidgetItem* item1 = new QTableWidgetItem(Registers.at(i));
		QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(sstrm.str()));
        Autos->setItem(i, 0, item1);
        Autos->setItem(i, 1, item2);
	}
	Autos->viewport()->update();
}
void MainWindow::debug() {
    if(!obj_file_list.empty()){
        disconnect(TextSegment, SIGNAL(cellChanged(int, int)), this, SLOT(changeBreakpoints(int, int)));
    }
    if (fileNames.isEmpty()) {
        QMessageBox::about(this, tr("About Debug"),
            tr("Please check if you have opened any file or you have saved the file"));
        return;
    }
    obj_file_list.clear();
    breakpoints.clear();
    TextSegment->clearContents();
    Autos->clearContents();
    for (QString file_name : fileNames) {
        std::ifstream file = readFile(file_name.toStdString());
        Assembler assm;
        assm.assemble(file);
        obj_file_list.push_back(assm.getObjFile());
    }
    Linker linker;
    linker.link(obj_file_list);
    ExecutableFile exe_file = linker.getExecutableFile();
    debugger.debug(&exe_file);
    setTextSegment();
    QMessageBox::about(this, tr("About Debug"), tr("Now you need to set breakpoints(●'◡'●)"));
    connect(TextSegment, SIGNAL(cellChanged(int, int)), this, SLOT(changeBreakpoints(int, int)));
}

void MainWindow::to_next_breakpoint() {
	debugger.run();
	setAutos();
    if(!breakpoints.empty()){
        curr_row = *(breakpoints.begin());
        breakpoints.erase(breakpoints.begin());
        std::string message = "We are at the " + std::to_string(debugger.getNumOfBreakpoints() - breakpoints.size()) + "th break point" + "which is the" + std::to_string(curr_row + 1) + "th row";
        QMessageBox::about(this, tr("About to_next_breakpoint"), tr(message.c_str()));
    }
    else{
        QMessageBox::about(this, tr("About to_next_breakpoint"), tr("Now we reach the end of the program"));

    }
}

void MainWindow::step() {
	if (TextSegment->item(curr_row + 1, 0)->checkState() == Qt::Checked) {
		to_next_breakpoint();
	}
	else {
		curr_row += 1;
		debugger.step();
		std::string message = "We are at the " + std::to_string(curr_row + 1) + "th row";
        QMessageBox::about(this, tr("About to_next_line"), tr(message.c_str()));
	}
}

void MainWindow::changeBreakpoints(int row, int col) {

    QString addr = TextSegment->item(row, 0)->text();
    uint32_t address = stoi(addr.left(32).toStdString(), 0, 16);
	if (TextSegment->item(row, col)->checkState() == Qt::Checked) {
		debugger.addBreakpoint(address);
		breakpoints.push_back(row);
		std::sort(breakpoints.begin(), prev(breakpoints.end()));
	}
	else {
		debugger.removeBreakpoint(address);
        std::vector<int>::iterator iter = std::find(breakpoints.begin(), breakpoints.end(), row);
		breakpoints.erase(iter);
	}
}

void MainWindow::documentWasModified()
{
	setWindowModified(textEdit->document()->isModified());
}

void MainWindow::createActions()
{
    //fileMenu
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));	
	QToolBar* fileToolBar = addToolBar(tr("File"));
	const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
	QAction* newAct = new QAction(newIcon, tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
	fileMenu->addAction(newAct);
	fileToolBar->addAction(newAct);
	const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
	QAction* openAct = new QAction(openIcon, tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, &QAction::triggered, this, &MainWindow::open);
	connect(this, SIGNAL(tryUpdate(QStringList)), fileList, SLOT(updateList(QStringList)));
	fileMenu->addAction(openAct);
	fileToolBar->addAction(openAct);

	const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
	QAction* saveAct = new QAction(saveIcon, tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the document to disk"));
	connect(saveAct, &QAction::triggered, this, &MainWindow::save);
	fileMenu->addAction(saveAct);
	fileToolBar->addAction(saveAct);

	const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
	QAction* saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip(tr("Save the document under a new name"));

	fileMenu->addSeparator();

	const QIcon exitIcon = QIcon::fromTheme("application-exit");
	QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);

	exitAct->setStatusTip(tr("Exit the application"));

    // editMenu
	QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
	QToolBar* editToolBar = addToolBar(tr("Edit"));

#ifndef QT_NO_CLIPBOARD

	const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
	QAction* cutAct = new QAction(cutIcon, tr("&Cut"), this);
	cutAct->setShortcuts(QKeySequence::Cut);
	cutAct->setStatusTip(tr("Cut the current selection's contents to the "
		"clipboard"));
	connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut);
	editMenu->addAction(cutAct);
	editToolBar->addAction(cutAct);

	const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
	QAction* copyAct = new QAction(copyIcon, tr("&Copy"), this);
	copyAct->setShortcuts(QKeySequence::Copy);
	copyAct->setStatusTip(tr("Copy the current selection's contents to the "
		"clipboard"));
	connect(copyAct, &QAction::triggered, textEdit, &QPlainTextEdit::copy);
	editMenu->addAction(copyAct);
	editToolBar->addAction(copyAct);

	const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
	QAction* pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
	pasteAct->setShortcuts(QKeySequence::Paste);
	pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
		"selection"));
	connect(pasteAct, &QAction::triggered, textEdit, &QPlainTextEdit::paste);
	editMenu->addAction(pasteAct);
	editToolBar->addAction(pasteAct);

	const QIcon findIcon = QIcon::fromTheme("edit-find", QIcon(":/images/find.png"));
	QAction* findAct = new QAction(findIcon, tr("&Find"), this);
	findAct->setShortcuts(QKeySequence::Find);
	findAct->setStatusTip(tr("Find the matching content in the text "));
	connect(findAct, &QAction::triggered, this, &MainWindow::find);
	editMenu->addAction(findAct);
	editToolBar->addAction(findAct);

	menuBar()->addSeparator();

#endif

    //runMenu
	QMenu* runMenu = menuBar()->addMenu(tr("&Run"));
	QToolBar* runToolBar = addToolBar(tr("Run"));

	const QIcon runIcon = QIcon::fromTheme("run", QIcon(":/images/run.png"));
	QAction* runAct = new QAction(runIcon, tr("&Run"), this);
	runAct->setShortcut(tr("CTRL+R"));
	runAct->setStatusTip(tr("Run file"));
	connect(runAct, &QAction::triggered, this, &MainWindow::run);
	runMenu->addAction(runAct);
	runToolBar->addAction(runAct);

    //debugMenu
	QMenu* debugMenu = menuBar()->addMenu(tr("&Debug"));
	QToolBar* debugToolBar = addToolBar(tr("Debug"));

	const QIcon debugIcon = QIcon::fromTheme("debug", QIcon(":/images/debug.png"));
	QAction* debugAct = new QAction(debugIcon, tr("&Debug"), this);
	debugAct->setShortcut(tr("CTRL+Y"));
	debugAct->setStatusTip(tr("Debug file"));
	connect(debugAct, &QAction::triggered, this, &MainWindow::debug);
	debugMenu->addAction(debugAct);
	debugToolBar->addAction(debugAct);

	const QIcon stepIcon = QIcon::fromTheme("step", QIcon(":/images/step.png"));
	QAction* stepAct = new QAction(stepIcon, tr("&next line"), this);
	stepAct->setShortcut(tr("CTRL+I"));
	stepAct->setStatusTip(tr("Run the line"));
	connect(stepAct, &QAction::triggered, this, &MainWindow::step);
	debugMenu->addAction(stepAct);
	debugToolBar->addAction(stepAct);

	const QIcon nextBreakpointIcon = QIcon::fromTheme("nextBreakpoint", QIcon(":/images/nextBreakpoint.png"));
	QAction* nextBreakpointAct = new QAction(nextBreakpointIcon, tr("&next breakpoint"), this);
	nextBreakpointAct->setShortcut(tr("CTRL+O"));
	nextBreakpointAct->setStatusTip(tr("Run the line"));
	connect(nextBreakpointAct, &QAction::triggered, this, &MainWindow::to_next_breakpoint);
	debugMenu->addAction(nextBreakpointAct);
	debugToolBar->addAction(nextBreakpointAct);

	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	QAction* aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
	aboutAct->setStatusTip(tr("Show the application's About box"));

#ifndef QT_NO_CLIPBOARD

	cutAct->setEnabled(false);
	copyAct->setEnabled(false);
	connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
	connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);

#endif // !QT_NO_CLIPBOARD

}

void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
	if (geometry.isEmpty()) {
		const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
		resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
		move((availableGeometry.width() - width()) / 2,
			(availableGeometry.height() - height()) / 2);
	}
	else {
		restoreGeometry(geometry);
	}
}

void MainWindow::writeSettings()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	settings.setValue("geometry", saveGeometry());
}

bool MainWindow::maybeSave()
{
	if (!textEdit->document()->isModified())
		return true;
	const QMessageBox::StandardButton ret
		= QMessageBox::warning(this, tr("Application"),
			tr("The document has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	switch (ret) {
	case QMessageBox::Save:
		return save();
	case QMessageBox::Cancel:
		return false;
	default:
		break;
	}
	return true;
}

void MainWindow::loadFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot read file %1:\n%2.")
			.arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return;
	}

	QTextStream in(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot write file %1:\n%2.")
			.arg(QDir::toNativeSeparators(fileName),
				file.errorString()));
		return false;
	}

	QTextStream out(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}
//QString MainWindow::strippedName(const QString& fullFileName)
//{
//	return QFileInfo(fullFileName).fileName();
//}
#ifndef QT_NO_SESSIONMANAGER
void MainWindow::commitData(QSessionManager& manager)
{
	if (manager.allowsInteraction()) {
		if (!maybeSave())
			manager.cancel();
	}
	else {
		// Non-interactive: save without asking
		if (textEdit->document()->isModified())
			save();
	}
}

#endif



