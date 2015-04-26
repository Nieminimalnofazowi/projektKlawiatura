#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    statsFile(NULL) //init statsFile
{
    ui->setupUi(this);


    QFile plik(":/res/res/Instrukcja.txt");
    show_text(plik); //pokaz instrukcje



    mistakeCounter=0;
    mistakes_string = "Błędy: ";
    mistakes_string +=  QString::number(mistakeCounter);
    ui->mistakesCounter->setText(mistakes_string); //ustaw pierwotny text na label

    ui->typedTextBox->installEventFilter(this); //antybackspace
    mistake_flag=0;
    activeUserString= "Bieżący użytkownik to: \n";
    ui->activeUser->setText(activeUserString );

    redColour = "<font color=\"Red\">";
    blackColour = "<font color=\"Black\">";
    tmpCursor = ui->typedTextBox->textCursor();
    tmpCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 4);

    // na razie tutaj dodam vector userów
    //QVector<user*>* UserList = new QVector<user*>();

    QDir directory("users/"); //tworzenie dir users/
    if(!directory.exists())
    {
//        TODO
//        QDir::mkdir("users/");
    }
    //uzupelnienie listy userow na podstawie katalogu users
    foreach(QString userName, directory.entryList(QStringList("*.txt")))
    {
        ui->UserListCombo->addItem(userName.left(userName.length() - 4));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
 * Otwieranie wlasnego pliku do przepisania
 */
void MainWindow::open_file(){

    QString fileName = QFileDialog::getOpenFileName(this,tr("Otwórz..."), "/home/", tr("Pliki txt (*.txt)"));
    QFile plik(fileName);
    mistakeCounter=0;
    show_text(plik);
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
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (ui->typedTextBox->hasFocus())
    {
        typedText = ui->typedTextBox->toPlainText(); //przesyl tekstu z TextBoxa do QString
        if(typedText.length() == 1) //pierwszy znak - rozpoczecie odliczania czasu
        {
            elapsedTime.restart(); //liczymy czas pisania
            deltsVector.append(elapsedTime.elapsed());
            charsVector.append(event->text());
        }
        if(elapsedTime.elapsed()) //gdy timer ruszyl (nie zapisze zer na poczatku)
        {
            deltsVector.append(elapsedTime.elapsed());
            charsVector.append(event->text());
        }   

        int TTL = typedText.length();
        //temp.chop(STL-TTL);

        if(shownText.left(TTL)==typedText ) mistake_flag=0;
        if(typedText.isEmpty()) mistake_flag=0;
        if(shownText.left(TTL)!=typedText && backspace_flag!=0)
        {

               ++mistakeCounter;
                typedText.insert(typedText.length()-1,redColour);

                ui->typedTextBox->setText(typedText);
                ui->typedTextBox->setTextCursor(tmpCursor);
                /*typedText.insert(typedText.length(),blackColour);
                ui->typedTextBox->setText(typedText);
                ui->typedTextBox->setTextCursor(tmpCursor);*/
               mistake_flag=1;


        }
        else if(shownText.left(TTL)==typedText) mistake_flag=0;
        mistakes_string = "Błędy: ";
        mistakes_string +=  QString::number(mistakeCounter);
        ui->mistakesCounter->setText(mistakes_string);


    }
}
/*
 * Gdy cos zmieniono w textboxie
 */

void MainWindow::on_typedTextBox_textChanged()
{
    //typedText = ui->typedTextBox->toPlainText(); //przesyl tekstu z TextBoxa do QString

    //numberOfTypedWords = typedText.count(QRegExp("\\s\\S")) + 1; //wykrycie białego znaku a zaraz po nim znaku - czyli spacja

   // if(typedText.length() == 1) //pierwszy znak - rozpoczecie odliczania czasu
  //  {
  //      typedTimer->start(); //interwał odświeżania statystyk
  //      elapsedTime.restart(); //liczymy czas pisania od nowa
  //  }

    //QString temp;
    //temp = shownText;



}


/*
 * Wyświetlenie tekstu z resources/wlasnego zrodla do shownTextbox
 * czyli boxa do przepisywania.
 * Tutaj tez wykonuje sie CLEAR tego co dokonano do tej pory
 */
void MainWindow::show_text(QFile &file)
{


    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;			 // jeżeli nie udało się otworzyć pliku: przerwij wczytywanie pliku

    // czyścimy wcześniej zapełnioną zmienną tekstową
    shownText.clear();
    ui->typedTextBox->clear(); //czyścimy też to co wcześniej wpisaliśmy
    mistakeCounter = 0; //zerujemy ilość popełnionych błędów
    deltsVector.clear(); //zerujemy i zwalniamy pamiec z dotychczasowych timestampow
    charsVector.clear(); //zerujemy i zwalniamy pamiec z dotychczasowych znakow
    elapsedTime.restart(); //restart milisekund
    mistake_flag=0; //flaga na 0
    // klasa zapewniająca nam interfejs do odczytu/zapisu tekstu
    QTextStream stream(&file);

    // czytamy wszystkie dane
    shownText = stream.readAll();

    // umieszczamy je wewnątrz text boxa
    ui->testTextBox->setText(shownText);

    file.close();

}
/*
 * Rozwiniecie listy dostepnych tekstow
 */
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

/*
 * Klikniecie przycisku Zapisz - zapisujemy do aktualnego pliku wynik testu (timestampy)
 */
void MainWindow::on_saveButton_clicked()
{
    if(statsFile == NULL) //gdy nie wybrano usera!
    {
        QMessageBox::information(this,"Błąd!","Wybierz użytkownika!");
        return;
    }
    QTextStream out(statsFile);

    for (int i=0 ; i<deltsVector.size() ; i++)
    {
        out << deltsVector[i] << " ";
        out << charsVector[i];
        out << "\n";
    }
    out << mistakeCounter;
    if(!(statsFile->error())) //gdy brak errorow
        QMessageBox::information(this,"Zapis","Zapis zakończony powodzeniem!");
}

bool MainWindow::eventFilter(QObject *, QEvent *e){

    if(e->type() == QEvent::KeyPress )
    {
        QKeyEvent * ke = static_cast<QKeyEvent * >(e);
        if(ke->key()==Qt::Key_Backspace)
        {

            backspace_flag =0;
            return 0;
        }
        else if(ke->key()!= Qt::Key_Backspace && mistake_flag==1 && backspace_flag==1) // już lepiej -> został problem z dwoma pierwszymi znakami źle
        {
            return 1;
        }
        else
        {
            backspace_flag=1;
            return 0;
        }


    }
}


/*
 * Rozwinieto liste userow
 */
void MainWindow::on_UserListCombo_activated(const QString &arg1)
{
      ui->activeUser->setText(activeUserString + arg1); //zmiana tekstu w labelu
      if(this->statsFile != NULL) //gdy otwarty to zamknij
      {
          if(this->statsFile->isOpen())
          {
              this->statsFile->close();
          }
      }

      this->statsFile = new QFile(QString("users/%0.txt").arg(arg1)); //ustaw wskaznik na nowy plik
      if(!this->statsFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) //otworz w trybie append
          return;

}
/*
 * Kliknieto przycisk dodaj usera
 */
void MainWindow::on_pushButton_clicked()
{

    //z LineEdit do stringa
    NewUserName = ui->UserName->toPlainText();

    if(!NewUserName.isEmpty()){ //gdy cos wpisano

        UserList.append(new user(NewUserName)); //dodanie usera
        QFile userFile(QString("users/%0.txt").arg(NewUserName)); //oraz jego pliku do /users
        if(!userFile.open(QIODevice::WriteOnly | QIODevice::Text)) //otwarcie i zamkniecie aby go utworzyc pustego
        {

        }
        userFile.close();
        ui->UserListCombo->addItem(NewUserName); //dodanie nowego usera do combolisty
        ui->UserListCombo->update(); //update combo
        QMessageBox::information(this,"Wiadomość","Dodano użytkownika: " + NewUserName);
        ui->UserName->clear(); //clear LineEdit
    }



}
/*
 * Czysty reset tego co wpisano
 */
void MainWindow::on_resetButton_clicked()
{
    ui->typedTextBox->clear(); //czyścimy też to co wcześniej wpisaliśmy
    mistakeCounter = 0; //zerujemy ilość popełnionych błędów
    mistakes_string = "Błędy: ";
    mistakes_string +=  QString::number(mistakeCounter);
    ui->mistakesCounter->setText(mistakes_string);
    deltsVector.clear(); //zerujemy i zwalniamy pamiec z dotychczasowych timestampow
    charsVector.clear(); //zerujemy i zwalniamy pamiec z dotychczaasowych znakow
    elapsedTime.restart(); //restart milisekund
    mistake_flag=0; //flaga na 0
}
