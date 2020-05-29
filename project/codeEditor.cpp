/**
 * @file codeEditor.cpp
 * @brief <code>codeEditor</code> class implementation.
 */
#include <QtWidgets>
#include "codeEditor.h"

#define LINE_NUMBER_AREA_BASE_WIDTH 15
#define LINE_NUMBER_AREA_NUM_POS -7

/**
 * @brief <code>codeEditor</code> class.
 */

class LineNumberArea : public QWidget
{

public:
	LineNumberArea(CodeEditor* editor) : QWidget(editor)
	{
		codeEditor = editor;
	}

	QSize sizeHint() const Q_DECL_OVERRIDE
	{
		return QSize(codeEditor->lineNumberAreaWidth(), 0);
	}

protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE
	{
		codeEditor->lineNumberAreaPaintEvent(event);
	}

private:
	CodeEditor* codeEditor;
};



CodeEditor::CodeEditor(QWidget* parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));
	connect(this, SIGNAL(updateRequest(QRect, int)), this, SLOT(updateLineNumberArea(QRect, int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
	updateLineNumberAreaWidth();
	zoomIn(1);
}

int CodeEditor::lineNumberAreaWidth()
{
	int digits = 1;
    int max = qMax(0, blockCount());
	while (max >= 10)
    {
		max /= 10;
		++digits;
	}

	int space = LINE_NUMBER_AREA_BASE_WIDTH + fontMetrics().horizontalAdvance(QLatin1Char('0')) * digits;
	return space;
}

void CodeEditor::updateLineNumberAreaWidth()
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect& rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth();
}

void CodeEditor::resizeEvent(QResizeEvent* e)
{
	QPlainTextEdit::resizeEvent(e);
	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection selection;
		QColor lineColor = QColor(Qt::darkGray).lighter(160);

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);

		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}
	setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(lineNumberArea);


	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int)blockBoundingRect(block).height();


	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(LINE_NUMBER_AREA_NUM_POS, top, lineNumberArea->width(), fontMetrics().height(),
				Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}
}

