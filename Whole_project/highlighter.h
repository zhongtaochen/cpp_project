/**
 * @file highlighter.h
 * @brief <code>Highlighter</code> class.
 * @details This file exports <code>Highlighter</code> class, which provide
 * syntax coloring and a better overall experience for users.
 */

#ifndef HIGHTLIGHTER_H
#define HIGHTLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

/**
 * @brief  Provides syntax coloring including the keywords, numbers, and comments.
 */

class QTextDocument;

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    /**
     * @brief Initializer for <code>Highlighter</code> class
     */
    Highlighter(QTextDocument *parent = 0);

protected:
    /**
     * @brief highlightBlock: set the syntax format for the coding block
     */
    void highlightBlock(const QString &text) override;

private:
    /**
     * @brief The strcutre of Highlighting rule
     */
    struct HighlightingRule {
        QRegExp pattern;
        QTextCharFormat format;
    };

    /**
     * @brief the  rules of syntax coloring
     */
    QVector<HighlightingRule> highlightingRules;


    /**
     * @brief Reg expression for start comment
     */
    QRegExp commentStartExpression;

    /**
     * @brief Reg expression for end comment
     */
    QRegExp commentEndExpression;

    /**
     * @brief The format of keywords
     */
    QTextCharFormat keywordFormat;

    /**
     * @brief The format of reg
     */
    QTextCharFormat regFormat;

    /**
     * @brief The format of single-line comment
     */
    QTextCharFormat singleLineCommentFormat;

    /**
     * @brief The format of multiple-line comment
     */
    QTextCharFormat multiLineCommentFormat;

    /**
     * @brief The format of quotation
     */
    QTextCharFormat quotationFormat;

    /**
     * @brief The format of function
     */
    QTextCharFormat functionFormat;

    /**
     * @brief The format of imediaate number
     */
    QTextCharFormat immediateNumberFormat;
};

#endif // HIGHTLIGHTER_H
