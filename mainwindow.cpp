#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter=0; //do usuniecia gdy zmienie na dodatkowy timer!
    ui->charPerMinute->setText("0.0 znaków/min");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki txt (*.txt)"));


}

void MainWindow::on_typedTextBox_textChanged() //metoda wywolywana przy kazdej edycji tekstu (wpisanie znaku, skasowanie)
{
    counter++; //nieelegancko - do poprawy
    typedText = ui->typedTextBox->toPlainText(); //przesyl tekstu z TextBoxa do QString
    if(typedText.length() == 1) //pierwszy znak - rozpoczecie odliczania czasu
    {
        elapsedTime.start();
        /* możliwy bug - ktos popelnia blad na pierwszym znaku, cofa sie BACKSPACE, pisze 1 znak od nowa - timer startuje
         * od nowa*/
    }
    if(!(counter%5)) //dokonaj update znakow/minute co 5 znakow (docelowo bedzie odswiezanie co interwal liczony innym timerem)
    {
        float tempLength = typedText.length(); //ilosc znakow w tekscie
        float tempTime = elapsedTime.elapsed()/60000.0; //czas ktory uplynal od rozpoczecia pisania
        speedChar_string = QString::number(tempLength/tempTime,'f',1); //zamiana na string w formacie 0.0
        speedChar_string = speedChar_string + " znaków/min";
        ui->charPerMinute->setText(speedChar_string); //do labela
    }
}
