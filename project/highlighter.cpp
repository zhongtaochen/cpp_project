/**
 * @file highlighter.cpp
 * @brief <code>highlighter</code> class implementation.
 */
#include "highlighter.h"

Highlighter::Highlighter(QTextDocument* parent)
	: QSyntaxHighlighter(parent)
{
	HighlightingRule rule;
    // set the color and front
	keywordFormat.setForeground(Qt::darkMagenta);
	keywordFormat.setFontWeight(QFont::Bold);

	QStringList keywordPatterns;
    keywordPatterns << "\\badd\\b" << "\\baddu\\b" << "\\baddi\\b" << "\\baddiu\\b"
                    << "\\band\\b" << "\\bandi\\b" << "\\bbeq\\b" << "\\bbgez\\b"
                    << "\\bbgezal\\b" << "\\bbgtz\\b" << "\\bblez\\b" << "\\bbltz\\b"
                    << "\\bbltzal\\b" << "\\bbne\\b" << "\\bdiv\\b" << "\\bdivu\\b"
                    << "\\bj\\b" << "\\bjal\\b" << "\\bjalr\\b" << "\\bjr\\b"
                    << "\\blb\\b" << "\\blbu\\b" << "\\blh\\b" << "\\blhu\\b"
                    << "\\blw\\b" << "\\bmfhi\\b" << "\\bmflo\\b" << "\\bmthi\\b"
                    << "\\bmtlo\\b" << "\\bmult\\b" << "\\bmultu\\b" << "\\bnor\\b"
                    << "\\bor\\b" << "\\bori\\b" << "\\bsb\\b" << "\\bsh\\b"
                    << "\\bsll\\b" << "\\bsllv\\b" << "\\bslt\\b" << "\\bslti\\b"
                    << "\\bsltiu\\b" << "\\bsltu\\b" << "\\bsub\\b" << "\\bsubu\\b"
                    << "\\bsra\\b" << "\\bsrav\\b" << "\\bsrl\\b" << "\\bsrlv\\b"
                    << "\\bsw\\b" << "\\bteq\\b" << "\\bteqi\\b" << "\\btge\\b"
                    << "\\btgei\\b" << "\\btgeiu\\b" << "\\btgeu\\b" << "\\btlt\\b"
                    << "\\btlti\\b" << "\\btltu\\b" << "\\btltiu\\b" << "\\btne\\b"
                    << "\\btnei\\b" << "\\bxor\\b" << "\\bxori\\b"
                    << "\\babs\\b" << "\\bb\\b" << "\\bbal\\b" << "\\bbeqz\\b"
                    << "\\bbge\\b" << "\\bbgt\\b" << "\\bbgtu\\b" << "\\bble\\b"
                    << "\\bblt\\b" << "\\bbne\\b" << "\\bclear\\b" << "\\bdiv\\b"
                    << "\\bla\\b" << "\\bli\\b" << "\\bmove\\b" << "\\bmul\\b"
                    << "\\bmulou\\b" << "\\bnot\\b" << "\\bnop\\b" << "\\brem\\b"
                    << "\\bremu\\b" << "\\blui\\b" << "\\bsyscall\\b";


	foreach(const QString & pattern, keywordPatterns) {
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);
	}

	immediateNumberFormat.setFontWeight(QFont::Bold);
	immediateNumberFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("\\b[0-9]+\\b");
	rule.format = immediateNumberFormat;
	highlightingRules.append(rule);

	regFormat.setFontWeight(QFont::Bold);
	regFormat.setForeground(Qt::darkMagenta);
	rule.pattern = QRegExp("\\B\\$[0-9]{1,2}\\b");
	rule.format = regFormat;
	highlightingRules.append(rule);

	singleLineCommentFormat.setForeground(Qt::lightGray);
	rule.pattern = QRegExp("#[^\n]*");
	rule.format = singleLineCommentFormat;
	highlightingRules.append(rule);


	commentStartExpression = QRegExp("/\\*");
	commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString& text)
{
	foreach(const HighlightingRule & rule, highlightingRules) {
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}
	setCurrentBlockState(0);

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = commentStartExpression.indexIn(text);

	while (startIndex >= 0) {
		int endIndex = commentEndExpression.indexIn(text, startIndex);
		int commentLength;
		if (endIndex == -1) {
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		}
		else {
			commentLength = endIndex - startIndex
				+ commentEndExpression.matchedLength();
		}
		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
	}
}
