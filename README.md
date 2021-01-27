# rumpa
Projekt współtworzony przez Michała Odziemkowskiego i Kamila Chodorowskiego na rzecz zajęć z podstaw programowania

1.	Instrukcja obsługi
Na początku gry dobrze jest wykonać funkcję resetującą (make test-reset), sprowadzi to postęp gry do stanu początkowego, synchronizując tym samym stan plików do stanu serwera. Możemy też wyświetlić techniczne informacje zwracane przez serwer (funkcja make test). W konsoli pojawią się informacje o statusie odpowiedzi, nazwie świata, obecnym położeniu na koordynatach x y, kierunek w którym jesteśmy zwróceni, typ pola na którym się znajdujemy, oraz ilość wykonanych przez nas ruchów.
Na tym etapie nic nie przeszkadza nam w rozpoczęciu gry. Mamy dwie opcje:
-Możemy zacząć grę samodzielnie. Tutaj nasza pula możliwości wygląda następująco: możemy obracać się w lewo (make test-rotL), w prawo (make test-rotR), posunąć się o 1 pole do przodu (make test-mov) lub odkryć 3 pola przed nami (pole tuż przed nami i 2 pola na ukos po lewej i po prawej) (make test-exp). Każda z tych komend dodaje 1 ruch do puli wykonanych kroków. Dodatkowo możemy łączyć wiele ruchów za jednym aktywowaniem programu np. „./main qwerty_22 M M E” wykonując w ten sposób 2 ruchy i eksploracją. Dostępne ruchy po „./main”:
M – ruch do przodu
E – eksploracja
Rright – obrót w prawo
Rleft – obrót w lewo
reset – resetuje świat
-Zacząć eksplorować mapę automatycznie za pomocą bota wykonując komendę 
„make test-bot” lub „./main qwerty_22 bot”
