#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTime>
#include <QTextStream>


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
    void show_text(QFile &file);     // wyświetla wybrany text w oknie shownText
private slots:

    void on_typedTextBox_textChanged();
    void on_textList_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QTime elapsedTime; //czas od rozpoczecia przepisywania
    QString shownText; //tekst do przepisania
    QString typedText; //tekst przepisywany
    QString speedChar_string; //np "400 znaków/min"
    int counter; //chwilowo
};



#endif // MAINWINDOW_H
