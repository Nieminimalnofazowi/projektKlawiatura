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
/*!
 * \brief Klasa MainWindow obsługująca główne okno aplikacji
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /*!
     * \brief Otwieranie pliku gdy wybrano "Inny.."
     */
    void open_file();	 // otwieranie pliku gdy wybrano "Inny.."
    /*!
     * \brief Wyświetla wybrany text w oknie shownText oraz sprząta po tym co już napisano
     * \param Wybrany tekst - plik z resources
     */
    void show_text(QFile &file);     // wyświetla wybrany text w oknie shownText + sprząta po tym co już napisano
private slots:
    /*!
     * \brief Obsługuje wszystko co dzieje się po puszczeniu klawisza
     * \param QT Event - przekształcany na puszczany klawisz
     */
    void keyReleaseEvent(QKeyEvent *event); //obsluguje wszystko co wydarza sie po puszczeniu klawisza
    /*!
     * \brief Ustawienie focus'a
     * \param QT Event
     */
    void mousePressEvent(QMouseEvent *event); //wymagana do ustawienia focusa
    /*!
     * \brief Wybór elementu z listy tekstów do przepisania
     * \param Wybrany tekst
     */
    void on_textList_activated(const QString &arg1); //rozwiniecie listy tekstow do przepisania
    /*!
     * \brief Obsługuje wciśnięcie przycisku "Zapisz"
     */
    void on_saveButton_clicked(); //przycisk zapisz wyniki testu
    /*!
     * \brief Filtr eventów
     * \param Przesyłany QT Object
     * \param QT Event - przekształcany na wciśnięty klawisz
     * \return Zwracany bool decyduje czy przekazać event obiektowi klasy MainWindow
     */
    bool eventFilter(QObject *object, QEvent *e); //filter eventow (nie liczenie bckspc)
    /*!
     * \brief Wybranie elementu z listy użytkowników
     * \param Wybrany użytkownik
     */
    void on_UserListCombo_activated(const QString &arg1); //rozwiniecie listy userow
    /*!
     * \brief Obsługuje wciśnięcie przycisku "Dodaj" (użytkownika)
     */
    void on_pushButton_clicked(); //wcisniecie przycisku Dodaj (usera)

    /*!
     * \brief Obsługuje wciśnięcie przycisku "Reset" (napisanego do tej pory tekstu)
     */
    void on_resetButton_clicked(); //wcisniecie przycisku reset

private:
    Ui::MainWindow *ui; //wskaznik do elementow ui
    /*!
     * \brief Czas od rozpoczecia przepisywania
     */
    QTime elapsedTime; //czas od rozpoczecia przepisywania
    /*!
     * \brief Tekst do przepisania
     */
    QString shownText; //tekst do przepisania
    /*!
     * \brief Tekst przepisany
     */
    QString typedText; //tekst przepisywany
    /*!
     * \brief Label dotyczący błędów
     */
    QString mistakes_string; //string dot. bledow (label)
    /*!
     * \brief Vector tzw "delt" czyli milisekund od pierwszego znaku
     */
    QVector<int> deltsVector; //vector tzw "delt" czyli milisekund od pierwszego znaku
    /*!
     * \brief Vector wciśniętych klawiszy
     */
    QVector<QString> charsVector; //vector wcisnietych klawiszy
    /*!
     * \brief Licznik pomyłek
     */
    int mistakeCounter; //licznik pomylek
    /*!
     * \brief Aktualny numer usera w Combo
     */
    int currentUser; //aktualny numer usera w combo
    /*!
     * \brief Aktualny numer tekstu w combo
     */
    int currentText; //aktualny numer tekstu w combo
    /*!
     * \brief Ustawiana gdy wciśnięty backspace
     */
    bool backspace_flag; // ustawiana gdy wciśnięty backspace
    /*!
     * \brief Ustawiana gdy pomyłka
     */
    bool mistake_flag; //ustawiana gdy pomylka
    /*!
     * \brief Przechwytywanie shifta
     */
    bool shift_flag; //przechwytywanie shifta
    /*!
     * \brief Przechwytywanie entera
     */
    bool enter_flag; //przechwytywanie entera

    QString redColour;
    QString blackColour;
    /*!
     * \brief Nowy użytkownik
     */
    QString NewUserName; //nowy user
    /*!
     * \brief Vector wskaznikow na obiekty klasy user
     */
    QVector<user*> UserList; //vector wskaznikow na obiekty klasy user
    /*!
     * \brief Aktualny użytkownik - do wyświetlania na Labelu
     */
    QString activeUserString; //aktualny user (do wyswietlania na labelu)
    /*!
     * \brief Argument z userComboList
     */
    QString userComboArg; //argument z userComboList
    /*!
     * \brief Aktualny plik do zapisu timestampow
     */
    QFile* statsFile; //aktualny plik do zapisu timestampow
    /*!
     * \brief Kursor uzywany do kolorowania tekstu
     */
    QTextCursor tmpCursor; //kursor uzywany do kolorowania tekstu
    /*!
     * \brief Data i czas jako string do nazwy pliku
     */
    QString date; //data czas jako string do nazwy pliku
    /*!
     * \brief Data i czas obsługa
     */
    QDateTime day; //data czas obsluga
    /*!
     * \brief Liczenie znakow w obsludze bledow
     */
    int tempCounter; //liczenie znakow w obsludze bledow

};



#endif // MAINWINDOW_H
