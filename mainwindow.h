#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTime>

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
private slots:


    void on_openFileButton_clicked();

    void on_typedTextBox_textChanged();

private:
    Ui::MainWindow *ui;
    QTime elapsedTime; //czas od rozpoczecia przepisywania
    QString shownText; //tekst do przepisania
    QString typedText; //tekst przepisywany
    QString speedChar_string; //np "400 znaków/min"
    int counter; //chwilowo
};



#endif // MAINWINDOW_H
