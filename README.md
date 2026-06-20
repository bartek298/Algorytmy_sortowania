# Badanie Wydajności Algorytmów Sortowania

Projekt realizuje implementację oraz testy porównawcze wydajności trzech zaawansowanych algorytmów sortowania w języku C++. Celem projektu jest analiza czasu wykonywania operacji w zależności od rozmiaru tablicy oraz stopnia jej wstępnego posortowania.

## 🚀 Zaimplementowane Algorytmy
* **Merge Sort (Sortowanie przez scalanie)** – algorytm o stałej złożoności $O(n \log n)$.
* **Quick Sort (Sortowanie szybkie)** – z implementacją wyboru pivota metodą *Median-of-Three* (mediana z trzech elementów) w celu uniknięcia pesymistycznej złożoności.
* **Introsort (Sortowanie introspektywne)** – hybrydowy algorytm łączący zalety Quick Sort, Heap Sort (sortowania przez kopcowanie) oraz Insertion Sort (sortowania przez wstawianie), będący standardem m.in. w bibliotece STL (`std::sort`).

## 📊 Metodologia Badań

Aplikacja automatycznie przeprowadza serię testów wydajnościowych:
1.  **Rozmiary danych ($n$):** 10 000, 50 000, 100 000, 500 000, 1 000 000 elementów.
2.  **Warianty ułożenia danych:**
    * Losowe ($0\%$)
    * Częściowo posortowane ($25\%$, $50\%$, $75\%$, $95\%$, $99\%$, $99.7\%$)
    * Posortowane odwrotnie
3.  **Uśrednianie wyników:** Każdy pomiar powtarzany jest **100 razy** w celu eliminacji błędów losowych (wyniki są uśredniane).

## 📁 Plik Wynikowy (CSV)

Po zakończeniu działania programu w głównym katalogu generowany jest plik `wyniki_sortowania.csv`. 
Dane te można łatwo zaimportować do programu Excel, Origin lub skryptu w Pythonie (Pandas/Matplotlib) w celu wygenerowania wykresów porównawczych.

🛠️ Jak uruchomić projekt
Wymagania
Kompilator wspierający standard C++11 lub nowszy (np. GCC, Clang, MSVC)

Środowisko CLion lub narzędzie CMake
Uruchomienie w CLion
Otwórz folder projektu w CLion jako projekt CMake.

Zbuduj projekt (Build -> Build Project).

Uruchom program. W konsoli pojawi się faza weryfikacji algorytmów ([OK]), a następnie statusy zakończenia pomiarów dla poszczególnych rozmiarów danych.

