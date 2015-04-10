#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    typedTimer = new QTimer(this); //init

    ui->charPerMinute->setText("0.0 znaków/min");
    ui->wordsPerMinute->setText("0.0 słów/min");
    ui->correctPercentage->setText("Poprawność: x %");

    QFile plik(":/res/res/Instrukcja.txt");
    show_text(plik);

    mistakeCounter=0;
    mistakes_string = "Błędy: ";
    mistakes_string +=  QString::number(mistakeCounter);
    ui->mistakesCounter->setText(mistakes_string);

    // połącznie sygnału zmiany tekstu wpisywanego z metodą obsługi błędu -> funkcja error()
   // connect( ui->typedTextBox, SIGNAL(textChanged()), this, SLOT(error()));
    // połączenie sygnału zakończenia interwału timera z metodą update
    connect(typedTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(ui->typedTextBox, SIGNAL(textChanged(isBackspace)), this, SLOT(on_typedTextBox_textChanged(isBackspace)));

    typedTimer->setInterval(1000); //timer odpalajacy sie co 1 sec - odświeżenie statystyk

//    ui->typedTextBox->installEventFilter(this);
    mistake_flag=0;
    activeUserString= "Bieżący użytkownik to: \n";
    ui->activeUser->setText(activeUserString );

    // na razie tutaj dodam vector userów

    QVector<user*>* UserList = new QVector<user*>();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: open_file(){

    typedTimer->stop(); //zatrzymaj timer i odświeżanie statystyk
    QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki txt (*.txt)"));
    QFile plik(fileName);
    mistakeCounter=0;
    show_text(plik);
}

void MainWindow::update() //interwał odświeżania statystyk
{
    //znaki na minute
    tempLength = typedText.length(); //ilosc znakow w tekscie
    tempTime = elapsedTime.elapsed()/60000.0; //czas ktory uplynal od rozpoczecia pisania
    speedChar_string = QString::number(tempLength/tempTime,'f',1); //zamiana na string w formacie 0.0
    speedChar_string += " znaków/min";
    ui->charPerMinute->setText(speedChar_string); //do labela

    //słowa na minute
    typedWords = QString::number(numberOfTypedWords/tempTime,'f',1); //zamiana na string w formacie 0.0
    typedWords += " słów/min";
    ui->wordsPerMinute->setText(typedWords);

    //poprawność
    float currentPercentage = 100*(tempLength-mistakeCounter)/tempLength;
    statPercentage = QString::number(currentPercentage,'f',1);
    statPercentage = "Poprawność: " + statPercentage + " %";
    ui->correctPercentage->setText(statPercentage);
}

/*
 * Metoda ktorej celem jest ustawienie focus na klawiature. Pozwala
 * na "przeniesienie" scope'a keyReleaseEvent z klasy QWidget na MainWindow
 * source: stackoverflow :))
 */
void MainWindow::mousePressEvent(QMouseEvent *)
{
    setFocusPolicy(Qt::ClickFocus);
}

/*
 * Uruchamiana po puszczeniu klawisza. zapelnia wektor z elementami
 * typu integer timestampami
 */
void MainWindow::keyReleaseEvent(QKeyEvent *)
{
//    if (ui->typedTextBox->isActiveWindow())
//    {
//        typedText = ui->typedTextBox->toPlainText(); //przesyl tekstu z TextBoxa do QString
//        if(typedText.length() == 1) //pierwszy znak - rozpoczecie odliczania czasu
//        {
//            //typedTimer->start(); //interwał odświeżania statystyk
//            elapsedTime.start(); //liczymy czas pisania
//        }
//        deltsVector.append(elapsedTime.elapsed());
//        //poniższy kod sluzy sprawdzeniu zawartosci vectora
//        int temp = deltsVector[deltsVector.size()-1];
//        QString TString = QString::number(temp,10);
//        ui->correctPercentage->setText(TString);
//        //wyglada na to ze dziala!
//    }
}

/*
 * Czy bedzie jeszcze potrzebna?? zwijam poki co
 */
void MainWindow::on_typedTextBox_textChanged(bool isBackspace)
{
    //typedText = ui->typedTextBox->toPlainText(); //przesyl tekstu z TextBoxa do QString

    //numberOfTypedWords = typedText.count(QRegExp("\\s\\S")) + 1; //wykrycie białego znaku a zaraz po nim znaku - czyli spacja

    /*if(typedText.length() == 1) //pierwszy znak - rozpoczecie odliczania czasu
    {
        typedTimer->start(); //interwał odświeżania statystyk
        elapsedTime.restart(); //liczymy czas pisania od nowa
    }*/

    //QString temp;
    //temp = shownText;
    QString typedText = ui->typedTextBox->toPlainText();
    int STL = shownText.length();
    int TTL = typedText.length();
    //temp.chop(STL-TTL);

//    qDebug() << 'blad';
    if(shownText.left(TTL)==typedText ) mistake_flag=0;
    if(typedText.isEmpty()) mistake_flag=0;
    if(shownText.left(TTL)!=typedText && !isBackspace)
    {
           ++mistakeCounter;

           mistake_flag=1;
        emit wrongCharacterTyped();

    }
    else if(shownText.left(TTL)==typedText){
        mistake_flag=0;
        emit correctCharacterTyped();
    }

    mistakes_string = "Błędy: ";
    mistakes_string +=  QString::number(mistakeCounter);
    ui->mistakesCounter->setText(mistakes_string);



}



void MainWindow::show_text(QFile &file)
{


    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;			 // jeżeli nie udało się otworzyć pliku: przerwij wczytywanie pliku

    // czyścimy wcześniej zapełnioną zmienną tekstową
    typedTimer->stop();
    shownText.clear();
    ui->typedTextBox->clear(); //czyścimy też to co wcześniej wpisaliśmy
    mistakeCounter = 0; //zerujemy ilość popełnionych błędów
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

    mistakeCounter=0;
    if(arg1=="Instrukcja"){
           QFile plik(":/res/res/Instrukcja.txt");
           show_text(plik);
       }

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

void MainWindow::error(){

 QString temp;
 temp = shownText;
 int  STL = shownText.length();
 int TTL = typedText.length();
 temp.chop(STL-TTL);

 if(temp==typedText ) mistake_flag=0;
 if(typedText.isEmpty()) mistake_flag=0;
 if(temp!=typedText && backspace_flag!=0)
 {

        ++mistakeCounter;

        mistake_flag=1;


 }
 else if(temp==typedText) mistake_flag=0;
 mistakes_string = "Błędy: ";
 mistakes_string +=  QString::number(mistakeCounter);
 ui->mistakesCounter->setText(mistakes_string);
}


void MainWindow::on_saveButton_clicked()
{
    //plik tworzy mi sie tylko jak dodam C:\\
    //samo Results.txt albo /res/res/Results nie działa!!
    //Windows bug?
    QFile plikWynikowy("C:\\Results.txt");
    if(!plikWynikowy.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&plikWynikowy);
    for (int i=0 ; i<deltsVector.size() ; i++)
    {
        out << deltsVector[i] << " ";
    }
    plikWynikowy.close();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *e){

//    if(e->type() == QEvent::KeyPress )
//    {
//        QKeyEvent * ke = static_cast<QKeyEvent * >(e);
//        if(ke->key()==Qt::Key_Backspace)
//        {

//            backspace_flag =0;
//            return 0;
//        }
//        else if(ke->key()!= Qt::Key_Backspace && mistake_flag==1 && backspace_flag==1) // już lepiej -> został problem z dwoma pierwszymi znakami źle
//        {
//            return 1;
//        }
//        else
//        {
//            backspace_flag=1;
//            return 0;
//        }


//    }

}



void MainWindow::on_UserListCombo_activated(const QString &arg1)
{
      ui->activeUser->setText(activeUserString + arg1);
}

void MainWindow::on_pushButton_clicked()
{


    NewUserName = ui->UserName->toPlainText();

    if(!NewUserName.isEmpty()){

        UserList.append(new user(NewUserName));

    }
    // lamersko, może cały wektor mu dać?
    ui->UserListCombo->addItem(NewUserName);
    ui->UserListCombo->update();
    QMessageBox::information(this,"Wiadomość","Dodano użytkownika: " + NewUserName);
    ui->UserName->clear();
    //for(int i=0; i<=UserList.size();i++)
    //ui->testwindow->setText(UserList[i]->userID );

    ui->testwindow->setText(UserList[0]->userID);

}



void MainWindow::updateComboBox(QComboBox *comboToUpdate, const QVector<user*> & list )
{
    /*QString currentText = comboToUpdate->currentText();
    comboToUpdate->clear();
    comboToUpdate->insertItems(list);
    comboToUpdate->setCurrentIndex(comboToUpdate->findText(currentText));*/
}
