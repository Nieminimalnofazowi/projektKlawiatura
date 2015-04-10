# projektKlawiatura
-TIMESTAMPY DONE (przechowywane od pierwszego znaku)


-Zapis danych do .xls (aktualnie do .txt - przemyslec to)



-Obróbka tych danych później (np skrypt w matlabie wyliczający te średnie, które teraz bez sensu mamy w programie w labelach)


-Wybrać kodowanie Unicode - multiplatformowość + polskie znaki


-Błędy nie na czerwono tylko blokada + naliczanie błędu (jakiś flesz, czy coś, że popełniono błąd) - usuwa to problem z backspace


-Użytkownicy z listy + dodawanie nowych. Implementacja zależna od nas? (pierwszy szkic klasy DONE

-KROTSZE TEXTY DONE

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
UPDATE 10.04.2015
Przypominam, katalog "users" w katalogu wykonwaczym
Pomyśleć o tych błędach i liczniku 
W konstruktorze MainWindow masz dodanie tego katalogu users, foreach ogarnia listę elementów z .txt, a combo dostaje je bez 4 ostatnich znaków, czyli właśnie .txt -> sam userID
Jednocześnie on_UserListCombo_activated daje nam string z aktualnie wybranym userem np Jan Nowak i ustawia jako plik do zapisu Jan Nowak.txt
on_pushButton_clicked() dodaje usera 
MIŁEJ ZABWY! 
