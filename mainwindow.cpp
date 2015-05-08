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

    //zatwierdzam nowego usera enterem
    connect(ui->addUser,SIGNAL(returnPressed()),ui->pushButton,SIGNAL(clicked()));

    mistakeCounter=0;
    mistakes_string = "Błędy: ";
    mistakes_string +=  QString::number(mistakeCounter);
    ui->mistakesCounter->setText(mistakes_string); //ustaw pierwotny text na label

    ui->typedTextBox->installEventFilter(this); //antybackspace
    mistake_flag=0;
    backspace_flag=1;
    enter_flag=1;
    shift_flag=1;
    activeUserString= "Bieżący użytkownik to: \n";
    ui->activeUser->setText(activeUserString );

    redColour = "<font color=\"Red\">";
    blackColour = "<font color=\"Black\">";
    tmpCursor = ui->typedTextBox->textCursor();
    tmpCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 4);
    ui->typedTextBox->setEnabled(0);
    ui->saveButton->setEnabled(0);
    tempCounter=0;

    /*QDir directory("users/"); //tworzenie dir users/ (windows??)
    if(!directory.exists())
    {

    }*/
    QDir directory("users"); //tworzenie dir users/ (linux??)

    if (!directory.exists()) {
       directory.mkpath(".");
    }
    //uzupelnienie listy userow na podstawie folderów w katalogu users
    foreach(QString userName, directory.entryList(QStringList()))
    {
        if(userName=="." || userName=="..")
            continue;
        ui->UserListCombo->addItem(userName);
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
    if(!enter_flag)
    {
        typedText=ui->typedTextBox->toPlainText();

        if((shownText.length()-1==typedText.length()) && mistake_flag==0)
            on_saveButton_clicked();
        else
        {
            on_resetButton_clicked();
        }
    }
    else if (ui->typedTextBox->hasFocus())
    {
        typedText = ui->typedTextBox->toPlainText(); //przesyl tekstu z TextBoxa do QString
        if(typedText.length()==0)
            elapsedTime.restart();
        if(typedText.length() == 1 ) //pierwszy znak - rozpoczecie odliczania czasu
        {
            elapsedTime.restart(); //liczymy czas pisania
            deltsVector.append(elapsedTime.elapsed());
            charsVector.append(event->text());
        }


        int TTL = typedText.length(); //TypedTextLength

        if(shownText.left(TTL)==typedText ) mistake_flag=0;
        if(typedText.isEmpty()) mistake_flag=0;
        if(shownText.left(TTL)!=typedText && backspace_flag!=0)
        {

               ++mistakeCounter;
                mistake_flag=1;
                typedText.insert(typedText.left(tempCounter).length() ,redColour);

                ui->typedTextBox->setText(typedText);
                //po pokolorowaniu ustaw z powrotem kursor w miejsce pisania
                ui->typedTextBox->setTextCursor(tmpCursor);

        }
        else if(shownText.left(TTL)==typedText)
        {

                mistake_flag=0;
                tempCounter=typedText.length();


        }
        mistakes_string = "Błędy: ";
        mistakes_string +=  QString::number(mistakeCounter);
        ui->mistakesCounter->setText(mistakes_string);

        if(elapsedTime.elapsed()) //gdy timer ruszyl
        {
            if(backspace_flag!=0 && mistake_flag==0 && shift_flag!=0)
            {
                deltsVector.append(elapsedTime.elapsed());
                charsVector.append(event->text());
            }
        }
    }
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

    // reset wszystkiego
    on_resetButton_clicked();
    shownText.clear();
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
    if(ui->textList->currentIndex()==0){
        QFile plik(":/res/res/Instrukcja.txt");
        show_text(plik);
        ui->typedTextBox->setEnabled(0);
        ui->saveButton->setEnabled(0);
    }

    if(arg1=="Tekst 1"){
        QFile plik(":/res/res/Tekst 1.txt");
        show_text(plik);
        ui->typedTextBox->setEnabled(1);
        ui->saveButton->setEnabled(1);
        currentText = ui->textList->currentIndex();
    }
    if(arg1=="Tekst 2"){
        QFile plik(":/res/res/Tekst 2.txt");
        show_text(plik);
        ui->typedTextBox->setEnabled(1);
        ui->saveButton->setEnabled(1);
        currentText = ui->textList->currentIndex();
    }
    if(arg1=="Tekst 3"){
        QFile plik(":/res/res/Tekst 3.txt");
        show_text(plik);
        ui->typedTextBox->setEnabled(1);
        ui->saveButton->setEnabled(1);
        currentText = ui->textList->currentIndex();
    }
    if(arg1=="Tekst 4"){
        QFile plik(":/res/res/Tekst 4.txt");
        show_text(plik);
        ui->typedTextBox->setEnabled(1);
        ui->saveButton->setEnabled(1);
        currentText = ui->textList->currentIndex();
    }
    if(arg1=="Tekst 5"){
        QFile plik(":/res/res/Tekst 5.txt");
        show_text(plik);
        ui->typedTextBox->setEnabled(1);
        ui->saveButton->setEnabled(1);
        currentText = ui->textList->currentIndex();
    }
    if(arg1=="Inny..."){
        open_file();
        ui->typedTextBox->setEnabled(1);
        ui->saveButton->setEnabled(1);
        currentText = ui->textList->currentIndex();
    }
}




bool MainWindow::eventFilter(QObject *object, QEvent *e){

    if(object==ui->typedTextBox && e->type() == QEvent::KeyPress )
    {
        QKeyEvent * ke = static_cast<QKeyEvent * >(e);
        if(ke->key()==Qt::Key_Backspace)
        {

            backspace_flag =0;
        }
        else
        {
            backspace_flag=1;
        }
        if(ke->key()==Qt::Key_Shift)
        {
            shift_flag=0;
            return true;
        }
        else
        {
            shift_flag=1;

        }
        if(ke->key()==Qt::Key_Return || ke->key()==Qt::Key_Enter)
        {
            enter_flag=0;
            return true;
        }
        else
        {
            enter_flag=1;
            //return false;
        }

    }
  return QMainWindow::eventFilter(object,e);
}

/*
 * Klikniecie przycisku Zapisz - zapisujemy do aktualnego pliku wynik testu (timestampy)
 */
void MainWindow::on_saveButton_clicked()
{
    if(ui->UserListCombo->currentIndex()==0)
    {
        QMessageBox::information(this,"Błąd!","Wybierz użytkownika!");
        return;
    }

    if(this->statsFile != NULL) //gdy otwarty to zamknij
    {
        if(this->statsFile->isOpen())
        {
            this->statsFile->close();
        }
    }
    date = day.currentDateTime().toString();
    date.replace(":",".");
    QString fileName = QString("users/"+userComboArg+"/"+"%0.txt").arg(date);
    this->statsFile = new QFile(fileName);
    if(!this->statsFile->open(QIODevice::ReadWrite | QIODevice::Text)) //otworz
        return;

    QTextStream out(statsFile);


    for (int i=0 ; i<deltsVector.size() ; i++)
    {
        if(charsVector[i]=="")
            continue;
        out << deltsVector[i] << "\t";
        out << charsVector[i];
        out << "\n";
    }
    out << mistakeCounter;

    if(!(statsFile->error())) //gdy brak errorow
        QMessageBox::information(this,"Zapis","Zapis zakończony powodzeniem!");
    ui->UserListCombo->setCurrentIndex(currentUser);
    ui->textList->setCurrentIndex(currentText);
    ui->typedTextBox->setEnabled(1);
    ui->saveButton->setEnabled(1);
    on_resetButton_clicked();

}
/*
 * Rozwinieto liste userow
 */
void MainWindow::on_UserListCombo_activated(const QString &arg1)
{
      ui->activeUser->setText(activeUserString + arg1); //zmiana tekstu w labelu
      currentUser = ui->UserListCombo->currentIndex();
      userComboArg = arg1;
}
/*
 * Kliknieto przycisk dodaj usera
 */
void MainWindow::on_pushButton_clicked()
{

    //z LineEdit do stringa
    NewUserName = ui->addUser->text();

    if(!NewUserName.isEmpty())
    { //gdy cos wpisano

        QDir().mkdir("users/"+NewUserName+"/"); // tworzenie folderu z userem zamiast pliku

        UserList.append(new user(NewUserName)); //dodanie usera

        ui->UserListCombo->addItem(NewUserName); //dodanie nowego usera do combolisty
        ui->UserListCombo->update(); //update combo
        QMessageBox::information(this,"Wiadomość","Dodano użytkownika: " + NewUserName);
        ui->addUser->clear(); //clear LineEdit
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
