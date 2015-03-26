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
    QFile plik(":/res/res/Instrukcja.txt");
    show_text(plik);

    // połącznie sygnału zmiany tekstu wpisywanego z metodą obsługi błędu -> funkcja error()
    connect( ui->typedTextBox, SIGNAL(textChanged()), this, SLOT(error()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: open_file(){

    QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki txt (*.txt)"));

    QFile plik(fileName);

    show_text(plik);





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



void MainWindow::show_text(QFile &file){

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;			 // jeżeli nie udało się otworzyć pliku: przerwij wczytywanie pliku

    // czyścimy wcześniej zapełnioną zmienną tekstową
    shownText.clear();


    // klasa zapewniająca nam interfejs do odczytu/zapisu tekstu
    QTextStream stream(&file);

    // czytamy wszystkie dane
    shownText = stream.readAll();

    // umieszczamy je wewnątrz text boxa
    ui->testTextBox->setText(shownText);

    file.close();

}

void MainWindow::on_textList_activated(const QString &arg1)
{
    if(arg1=="Tekst 1"){
        QFile plik(":/res/res/Tekst 1.txt");
        show_text(plik);
    }
    if(arg1=="Tekst 2"){
        QFile plik(":/res/res/Tekst 2.txt");
        show_text(plik);
    }
    if(arg1=="Tekst 3"){
        QFile plik(":/res/res/Tekst 3.txt");
        show_text(plik);
    }
    if(arg1=="Tekst 4"){
        QFile plik(":/res/res/Tekst 4.txt");
        show_text(plik);
    }
    if(arg1=="Tekst 5"){
        QFile plik(":/res/res/Tekst 5.txt");
        show_text(plik);
    }
    if(arg1=="Inny..."){
        open_file();
    }
}

//jakoś działa -> pokazuje to pomocnicze okno
void MainWindow::error(){
 QString temp;
 temp = shownText;
 int  STL = shownText.length();
 int TTL = typedText.length();
 temp.chop(STL-TTL);
 if(temp==typedText)
    ui->tekstProba->setText("OK");
 else
     ui->tekstProba->setText("Not OK");


}

