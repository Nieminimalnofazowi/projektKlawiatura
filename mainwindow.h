#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTime>
#include <QTimer>
#include <QTextStream>
#include <QRegExp>
#include <QColor>
#include <QTextCursor>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <user.h>
#include <QComboBox>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open_file();	 // otwieranie pliku
    void show_text(QFile &file);     // wyświetla wybrany text w oknie shownText + sprząta po tym co już napisano
private slots:
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void on_typedTextBox_textChanged(bool isBackspace);
    void on_textList_activated(const QString &arg1);
    void error();
    void update();
    void on_saveButton_clicked();

    bool eventFilter(QObject *watched, QEvent *e);
    void on_comboBox_activated(const QString &arg1);

    void on_UserListCombo_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_UserName_textChanged();

private:
    Ui::MainWindow *ui;
    QTime elapsedTime; //czas od rozpoczecia przepisywania
    QString shownText; //tekst do przepisania
    QString typedText; //tekst przepisywany
    QString speedChar_string; //np "400 znaków/min"
    QString mistakes_string;
    QString typedWords; //np "300 słów/min"
    QString statPercentage; //np "Poprawność: 90.0%"
    QVector<int> deltsVector;
    QTimer *typedTimer;
    bool wordCheck;
    float numberOfTypedWords;
    float tempTime;
    float tempLength;
    int mistakeCounter;
    int *key;
    bool backspace_flag; // ustawiana gdy wciśnięty backspace
    bool mistake_flag;


    QString NewUserName;
    QVector<user*> UserList;
    void updateComboBox(QComboBox *comboToUpdate, const QVector<user*> & list );
    QString activeUserString;
signals:
    void wrongCharacterTyped();
    void correctCharacterTyped();
};



#endif // MAINWINDOW_H
