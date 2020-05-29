/**
 * @file codeEditor.h
 * @brief <code>codeEditor</code> class.
 * @details This file exports <code>codeEditor</code> class, which is the structure
 * of the code Editor part: it has the line number on the left and can highlight the
 * line where the mouse puts.
 */

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>

/**
 * @brief Add a area on the left which shows the number of line
 */
class LineNumberArea;

/**
 * @brief Provide the structure of the the code Editor part.
 */
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    /**
     * @brief Initializer for <code>codeEditor</code> class.
     */
    CodeEditor(QWidget *parent = 0);

    /**
     * @brief Draw the line-number area
     */
    void lineNumberAreaPaintEvent(QPaintEvent *event);

    /**
     * @brief Calculate the width of line-Number Area
     * @return the width of line number Area
     */
    int lineNumberAreaWidth();

protected:
    /**
     * @brief Override the resizeEvent method of QPlainTextEdit
     */
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:

    /**
     * @brief Highlight the current line where the mouse is put
     */
    void highlightCurrentLine();

    /**
     * @brief Update the width of line-number
     */
    void updateLineNumberAreaWidth();

    /**
     * @brief Update the line number area
     */
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};


#endif // CODEEDITOR_H
