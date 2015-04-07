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
    void on_typedTextBox_textChanged();
    void on_textList_activated(const QString &arg1);
    void error();
    void update();
    void on_saveButton_clicked();

    bool eventFilter(QObject *watched, QEvent *e);
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

};



#endif // MAINWINDOW_H
