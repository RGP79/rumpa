# rumpa
Projekt współtworzony przez Michała Odziemkowskiego i Kamila Chodorowskiego na rzecz zajęć z podstaw programowania

Jest to wstępna wersja projektu, jednka napotkaliśmy na kilka problemów. Najtrudniejszym do rozwiązania jest fakt że przy próbie uruchomienia w makefile test-gra-whole-valgout
program zawsze wywala sie po obrocie w prawo.
Natomiast przy użyciu make test-gra-whole program już działa i dochodzi do końca.
Oczywiście nie jest to nasz bot ;D

Dodatkowo mamy pewien problem z przetestowaniem dopisywania dynamicznie mapy w lewo i do dołu, przez to że czołg zawsze pojawia się w punkcie 1,1.
Ciężko nam nawet powiedzieć czy aktualna funckja sprosta takiemu dopisywaniu.

W pliku logic.c znajduje sie bot aczkolwiek nie jest on także w pełni jeszcze skończony. Podczas testowania napotkałem 2 miejsca w których program się wywala i co najzabawniejsze
nie następuje to za każdym razem. Jak bot dojdzie do punktu 1,9 w kierunku N program pokazuje błąd free(): invalid pointer lub corrupted size vs. prev_size. identycznie sytuacja następuje
w puncie 6,9 w kierunku N. Jak bot wraca do tego punktu bo zaraz bedzie musial zawrócić problem już nie następuje.
Aktualizacja: Po głębszej analizie błedy pokazują się przy dowolnej współrzędnej x oraz KONKRETNIE współrzędnej y = 9! (natrafiłem na te błędy przy 4,9 w kierunku N)
Bardzo często pomaga ponowne uruchomienie programu i błędy już nie wyskakują.
Bota na razie można testować make test-bot
