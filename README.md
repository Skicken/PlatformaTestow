
# TestPlatform
Desktopowa aplikacja do wykonywania przez uczniów testów.


## Instalacja w środowisku Visual Studio
Do instalacji repozytorium potrzebne są
* Cmake
* Kompilator C++ 17 lub nowszy

Projekt należy zklonować przykładowo możemy do zrobić poleceniem:
```
git clone --recursive https://github.com/Skicken/TestPlatform.git
```

Następnie uruchamiamy skrypt który skompiluje wszystkie potrzebne biblioteki proces może trwać od kilku do kilkunastu minut.
```
premake.bat
``` 

W Visual Studio należy zbudować całe rozwiązanie dopiero potem można Kompilować.



## API konsoli

Aby wypisać jakiś tekst na konsoli (w celu debugowania lub informowania o błędach)
korzystamy z następujących zdefiniowanych makr

* `ERROR(format,argumenty...)`
* `INFO(format,argumenty...)`
* `TRACE(format,argumenty...)`
* `WARN(format,argumenty...)`
* `FATAL(format,argumenty...)`

Format jest argumentem ciągu znaków który określa sposób wyświetlania kolejno podawanych argumentów.
Argument oznaczamy jako **{}** a kolejność wyświetlania jest decydowana przez kolejność podawania argumentów w makrze.



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
