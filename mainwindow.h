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
#include <QDate>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open_file();	 // otwieranie pliku gdy wybrano "Inny.."
    void show_text(QFile &file);     // wyświetla wybrany text w oknie shownText + sprząta po tym co już napisano
    bool eventFilter(QObject *object, QEvent *e); //filter eventow (nie liczenie bckspc)
    void keyReleaseEvent(QKeyEvent *event); //obsluguje wszystko co wydarza sie po puszczeniu klawisza
    void mousePressEvent(QMouseEvent *event); //wymagana do ustawienia focusa
private slots:

    void on_textList_activated(const QString &arg1); //rozwiniecie listy tekstow do przepisania
    void on_saveButton_clicked(); //przycisk zapisz wyniki testu



    void on_UserListCombo_activated(const QString &arg1); //rozwiniecie listy userow

    void on_pushButton_clicked(); //wcisniecie przycisku Dodaj (usera)


    void on_resetButton_clicked(); //wcisniecie przycisku reset

private:
    Ui::MainWindow *ui; //wskaznik do elementow ui
    QTime elapsedTime; //czas od rozpoczecia przepisywania
    QString shownText; //tekst do przepisania
    QString typedText; //tekst przepisywany
    QString mistakes_string; //string dot. bledow (label)
    QVector<int> deltsVector; //vector tzw "delt" czyli milisekund od pierwszego znaku

    QVector<QString> charsVector; //vector wcisnietych klawiszy

    int mistakeCounter; //licznik pomylek
    int bladZnak;
    QVector<int> bladZnakVector;
    int currentUser; //aktualny numer usera w combo
    int currentText; //aktualny numer tekstu w combo

    bool backspace_flag; // ustawiana gdy wciśnięty backspace
    bool mistake_flag; //ustawiana gdy pomylka
    bool shift_flag; //przechwytywanie shifta
    bool enter_flag; //przechwytywanie entera

    QString redColour;
    QString blackColour;

    QString NewUserName; //nowy user
    QVector<user*> UserList; //vector wskaznikow na obiekty klasy user
    QString activeUserString; //aktualny user (do wyswietlania na labelu)
    QString userComboArg; //argument z userComboList
    QString textArg;
    QFile* statsFile; //aktualny plik do zapisu timestampow

    QTextCursor tmpCursor; //kursor uzywany do kolorowania tekstu

    QString date; //data czas jako string do nazwy pliku
    QDateTime day; //data czas obsluga
    int tempCounter; //liczenie znakow w obsludze bledow

};



#endif // MAINWINDOW_H
