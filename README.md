
# TestPlatform
Desktopowa aplikacja do wykonywania przez uczniów testów.


## Instalacja w środowisku Visual Studio
Projekt najpewniej uruchomić w środowisku Visual Studio. Skrypty budujące rozwiązanie
korzystają ze zmiennych używanych w Visualu.

Do instalacji repozytorium potrzebne są
* Cmake (pobrany przykładowo za pomocą visual installera)
* Kompilator C++ 17 lub nowszy  (pobrany przykładowo za pomocą visual installera)
* biblioteka Boost https://www.boost.org/
* biblioteka OpenSSL pobieramy
https://slproweb.com/products/Win32OpenSSL.html
* MySQL connector https://dev.mysql.com/downloads/connector/cpp/
pobieramy spakowane pliki zip x64 (Pobieranie Debug Binaries można pominąć, 
budować program będzie można tylko w wersji release lub dist)


Projekt należy zklonować przykładowo możemy do zrobić poleceniem:
```
git clone --recursive https://github.com/Skicken/TestPlatform.git
```
Aby prawidłowo załączyć biblioteki Boost, OpenSSl, MySQL connector
należy ustawić ścieżki bezwzględne do pobranych, wypakowanych (w przypadku Boosta zbudowanych) folderów.
Ustawiamy zatem zmienne środowiskowe:

* ```MYSQL_ROOT```
* ```BOOST_ROOT```
* ```OPENSSL_ROOT```
* ```MYSQL_DEBUG_ROOT``` (opcjonalnie)

lub w sklonowanym projekcie w plikach w folderze "premake/scripts"
* ```mysql_premake5.lua```
* ```mailio_premake5.lua```

ustawiamy odpowiednio zmienne

Następnie uruchamiamy skrypt ```premake.bat``` który skompiluje wszystkie potrzebne biblioteki proces może trwać od kilku do kilkunastu minut.
Należy pamiętać że w przypadku biblioteki mailio należy wejść do jej folderu
otworzyć jej rozwiązanie i zbudować w RELEASE!

Po uruchomieniu należy zbudować całe rozwiązanie. 


## Struktura Projektu
Rozwiązanie TestPlatform posiada 5 projektów:

* ExternalConnection - własna biblioteka służący do nawiązywania połączeń z bazą danych
oraz obsługującą wysyłanie maili ("backend" mimo wszystko jest wykonywany na kliencie).
* ExternalConnectionUnitTests - testy jednostkowe do ExternalConnection. Testy można wykonywać tylko w release mode!
* Projekty raylib,spdlog i mailio są bibliotekami zewnętrznymi
* TestPlatform "frontend" aplikacji.


## API konsoli

Aby wypisać jakiś tekst na konsoli (w celu debugowania lub informowania o błędach)
korzystamy z następujących zdefiniowanych makr

* `ERROR(format,argumenty...)`
* `INFO(format,argumenty...)`
* `TRACE(format,argumenty...)`
* `WARN(format,argumenty...)`
* `FATAL(format,argumenty...)`

Format jest argumentem ciągu znaków który określa sposób wyświetlania kolejno podawanych argumentów.
Argument oznaczamy jako ```{}``` a kolejność wyświetlania jest decydowana przez kolejność podawania argumentów w makrze.



Przykładowe wykorzystanie makr
```c++
int nr_błędu = 1;
char znak_błędu = 'c';
ERROR("komunikat o bledzie {} {}", nr_błędu,znak_błędu)
```
Wyświetlone zostanie 

```
komunikat o bledzie 1 c
```

Na końcu makra nie potrzebne jest dodawanie średnika

## Baza Danych

Baza danych do pobrania https://tinyurl.com/yd255mte