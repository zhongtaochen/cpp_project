#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog: public QDialog
{
    Q_OBJECT
public:
    FindDialog(QWidget *parent = 0);

signals:
    void search(const QString &str);
    void clear();

private slots:
    void findClicked();
    void closeClicked();
    void enableFindButton (const QString &text);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif // FINDDIALOG_H
