#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    typedTimer = new QTimer(this); //init
    //ui->testTextBox->set
    ui->charPerMinute->setText("0.0 znaków/min");
    ui->wordsPerMinute->setText("0.0 słów/min");
    QFile plik(":/res/res/Instrukcja.txt");
    show_text(plik);
    mistakeCounter=0;
    mistakes_string = "Błędy: ";
    mistakes_string +=  QString::number(mistakeCounter);
    ui->mistakesCounter->setText(mistakes_string);
    // połącznie sygnału zmiany tekstu wpisywanego z metodą obsługi błędu -> funkcja error()
    connect( ui->typedTextBox, SIGNAL(textChanged()), this, SLOT(error()));
    // połączenie sygnału zakończenia interwału timera z metodą update
    connect(typedTimer,SIGNAL(timeout()),this,SLOT(update()));

    typedTimer->setInterval(1000); //timer odpalajacy sie co 1 sec - odświeżenie statystyk

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: open_file(){

    typedTimer->stop(); //zatrzymaj timer i odświeżanie statystyk
    QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki txt (*.txt)"));
    QFile plik(fileName);

    show_text(plik);





}

void MainWindow::update() //interwał odświeżania statystyk
{
    tempLength = typedText.length(); //ilosc znakow w tekscie
    tempTime = elapsedTime.elapsed()/60000.0; //czas ktory uplynal od rozpoczecia pisania
    speedChar_string = QString::number(tempLength/tempTime,'f',1); //zamiana na string w formacie 0.0
    speedChar_string += " znaków/min";
    ui->charPerMinute->setText(speedChar_string); //do labela


    typedWords = QString::number(numberOfTypedWords/tempTime,'f',1); //zamiana na string w formacie 0.0
    typedWords += " słów/min";
    ui->wordsPerMinute->setText(typedWords);
}

void MainWindow::on_typedTextBox_textChanged() //metoda wywolywana przy kazdej edycji tekstu (wpisanie znaku, skasowanie)
{
    typedText = ui->typedTextBox->toPlainText(); //przesyl tekstu z TextBoxa do QString

    numberOfTypedWords = typedText.count(QRegExp("\\s\\S")) + 1; //wykrycie białego znaku a zaraz po nim znaku - czyli spacja

    if(typedText.length() == 1) //pierwszy znak - rozpoczecie odliczania czasu
    {
        typedTimer->start(); //interwał odświeżania statystyk
        elapsedTime.restart(); //liczymy czas pisania od nowa
    }




}



void MainWindow::show_text(QFile &file){

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;			 // jeżeli nie udało się otworzyć pliku: przerwij wczytywanie pliku

    // czyścimy wcześniej zapełnioną zmienną tekstową
    shownText.clear();
    ui->typedTextBox->clear(); //czyścimy też to co wcześniej wpisaliśmy

    // klasa zapewniająca nam interfejs do odczytu/zapisu tekstu
    QTextStream stream(&file);

    // czytamy wszystkie dane
    shownText = stream.readAll();

    // umieszczamy je wewnątrz text boxa
    ui->testTextBox->setText(shownText);

    file.close();

}

void MainWindow::changeShownText() //funkcja do zmiany tekstu na inny
{
    ui->typedTextBox->clear();
    typedTimer->stop();
}

void MainWindow::on_textList_activated(const QString &arg1)
{

    mistakeCounter=0;
    if(arg1=="Instrukcja"){
           QFile plik(":/res/res/Instrukcja.txt");
           show_text(plik);
           mistakeCounter=0;
       }

    if(arg1=="Tekst 1"){
        QFile plik(":/res/res/Tekst 1.txt");
        show_text(plik);
        changeShownText();
        mistakeCounter=0;
    }
    if(arg1=="Tekst 2"){
        QFile plik(":/res/res/Tekst 2.txt");
        show_text(plik);
        changeShownText();
        mistakeCounter=0;
    }
    if(arg1=="Tekst 3"){
        QFile plik(":/res/res/Tekst 3.txt");
        show_text(plik);
        changeShownText();
        mistakeCounter=0;
    }
    if(arg1=="Tekst 4"){
        QFile plik(":/res/res/Tekst 4.txt");
        show_text(plik);
        changeShownText();
        mistakeCounter=0;
    }
    if(arg1=="Tekst 5"){
        QFile plik(":/res/res/Tekst 5.txt");
        show_text(plik);
        changeShownText();
        mistakeCounter=0;
    }
    if(arg1=="Inny..."){
        open_file();
        mistakeCounter=0;
    }

}

void MainWindow::error(){

 //typedText.right(1).toInt()!=8
 QString temp;
 temp = shownText;
 int  STL = shownText.length();
 int TTL = typedText.length();
 temp.chop(STL-TTL);
 if(temp!=typedText && QKeyEvent::key() != Qt::Key_Backspace)
 {

        ui->typedTextBox->setTextColor(Qt::red);
        ++mistakeCounter;
    }
 mistakes_string = "Błędy: ";
 mistakes_string +=  QString::number(mistakeCounter);
 ui->mistakesCounter->setText(mistakes_string);
}

