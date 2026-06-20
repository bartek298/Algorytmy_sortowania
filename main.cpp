#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


/*Bartosz Starkowski 287665*/
template <typename T>
void merge_sort_1(T arr[], T temp[], int lewy, int srodek, int prawy) {
    int i = lewy, j = srodek + 1, k = lewy;

    while (i <= srodek && j <= prawy) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= srodek) temp[k++] = arr[i++];
    while (j <= prawy) temp[k++] = arr[j++];

    for (i = lewy; i <= prawy; i++) arr[i] = temp[i];
}


// template <typename T>
// void merge_sort_2(T arr[], int lewy, int prawy) {
//     if(lewy<prawy) {
//         int srodek=lewy+(prawy-lewy)/2;
//
//         merge_sort_2(arr,lewy,srodek);
//         merge_sort_2(arr,srodek+1,prawy);
//
//         merge_sort_1(arr,lewy,srodek,prawy);
//     }
// }
template <typename T>
void merge_sort_2(T arr[], T temp[], int lewy, int prawy) {
    if(lewy < prawy) {
        int srodek = lewy + (prawy - lewy) / 2;
        merge_sort_2(arr, temp, lewy, srodek);
        merge_sort_2(arr, temp, srodek + 1, prawy);
        merge_sort_1(arr, temp, lewy, srodek, prawy);
    }
}


template <typename T>
void quick_sort (T arr[],int lewy, int prawy) {
    if(lewy<prawy) {
        int srodek=lewy+(prawy-lewy)/2;
        if(arr[srodek]<arr[lewy]) std::swap(arr[srodek], arr[lewy]);
        if(arr[prawy]<arr[lewy]) std::swap(arr[prawy],arr[lewy]);
        if(arr[prawy]<arr[srodek]) std::swap(arr[prawy],arr[srodek]);
        T pivot = arr[srodek];
        int i=lewy,j=prawy;

        while(i<=j) {
            while(arr[i]<pivot)
                i++;
            while(arr[j]>pivot)
                j--;
            if(i<=j) {
                std::swap(arr[i],arr[j]);
                i++;
                j--;
            }
        }
        if(lewy<j)
            quick_sort(arr,lewy,j);
        if(i<prawy)
            quick_sort(arr,i,prawy);

    }


}

template <typename T>
void intertion_sort(T arr[],int lewy, int prawy) {
    for(int i=lewy+1;i<=prawy;i++) {
        T key=arr[i];
        int j=i-1;
        while(j>=lewy && arr[j] >key) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}


template <typename T>
void heap_sort_1(T arr[],int n, int i, int x) {
    int najwiekszy=i;
    int lewy=2*i+1;
    int prawy=2*i+2;
    if(lewy<n && arr[x+lewy]>arr[x+najwiekszy])
        najwiekszy=lewy;
    if(prawy<n && arr[x+prawy]>arr[x+najwiekszy])
        najwiekszy=prawy;
    if(najwiekszy !=i) {
        std::swap(arr[x+i], arr[x+najwiekszy]);
        heap_sort_1(arr,n,najwiekszy,x);
    }
}
template <typename T>
void heap_sort_2(T arr[], int n,int x) {
    for(int i=n/2-1;i>=0;i--)
        heap_sort_1(arr,n,i,x);
    for(int i=n-1;i>0;i--) {
        std::swap(arr[x],arr[x+i]);
        heap_sort_1(arr,i,0,x);
    }
}

template <typename T>
void introsort(T arr[],int lewy, int prawy, int limit_glebokosci) {
    int size= prawy -lewy +1;

    if (size<18) {
        intertion_sort(arr,lewy,prawy);
        return;
    }
    if(limit_glebokosci==0) {
        heap_sort_2(arr,size,lewy);
        return;
    }
    int srodek=lewy+(prawy-lewy)/2;
    T pivot = arr[srodek];
    int i=lewy,j=prawy;
    while(i<=j) {
        while(arr[i]<pivot)
            i++;
        while(arr[j]>pivot)
            j--;
        if(i<=j) {
            std::swap(arr[i],arr[j]);
            i++;
            j--;
        }
    }
    if(lewy<j)
        introsort(arr,lewy,j,limit_glebokosci-1);
    if(i<prawy) introsort(arr,i,prawy,limit_glebokosci-1);
}
template <typename T>
void introsort2(T arr[], int n) {
    int limit_glebokosci= 2 * log(n);
    introsort(arr,0,n-1,limit_glebokosci);
}

template <typename T>
void copyArray(T source[], T dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = source[i];
}

template <typename T>
void generateData(T arr[], int n, double sortedPercent, bool reverse = false) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000000;

    if (reverse) {
        std::sort(arr, arr + n);
        std::reverse(arr, arr + n);
    } else if (sortedPercent > 0) {
        int limit = static_cast<int>(n * sortedPercent);
        std::sort(arr, arr + limit);
    }
}

template <typename T>
bool isSorted(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}
int main() {
    srand(time(NULL));
    int rozmiary[] = {10000, 50000, 100000, 500000, 1000000};
    double warianty[] = {0.0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997};

    ofstream file("wyniki_sortowania.csv");
    file << "Algorytm;Rozmiar;Wariant;Czas_ms\n";
    cout << "Weryfikacja poprawnosci algorytmow" << endl;
    int testSize = 1000;
    int* testTab = new int[testSize];
    int* tempM = new int[testSize];

    string algos[] = {"MergeSort", "QuickSort", "Introsort"};

    for (string a : algos) {
        generateData(testTab, testSize, 0, false);

        if (a == "MergeSort") merge_sort_2(testTab, tempM, 0, testSize - 1);
        else if (a == "QuickSort") quick_sort(testTab, 0, testSize - 1);
        else introsort2(testTab, testSize);

        if (isSorted(testTab, testSize)) {
            cout << "[OK] " << a << " sortuje poprawnie." << endl;
        } else {
            cout << "[BLAD] " << a << " NIE SORTUJE POPRAWNIE!" << endl;
        }
    }
    delete[] testTab;
    delete[] tempM;
    cout << "---------------------------------------" << endl;

    for (int n : rozmiary) {
        int* tabPierwotna = new int[n];
        int* tabDoSortowania = new int[n];
        int* tempMerge = new int[n];
        string algorytmy[] = {"MergeSort", "QuickSort", "Introsort"};

        for (string alg : algorytmy) {
            for (double p : warianty) {
                double totalTime = 0;
                for (int proba = 0; proba < 100; proba++) {
                    generateData(tabPierwotna, n, p, false);
                    copyArray(tabPierwotna, tabDoSortowania, n);

                    auto start = chrono::high_resolution_clock::now();

                    if (alg == "MergeSort") merge_sort_2(tabDoSortowania, tempMerge, 0, n - 1);
                    else if (alg == "QuickSort") quick_sort(tabDoSortowania, 0, n - 1);
                    else introsort2(tabDoSortowania, n);

                    auto end = chrono::high_resolution_clock::now();
                    totalTime += chrono::duration<double, milli>(end - start).count();
                }
                file << alg << ";" << n << ";" << p * 100 << "%;" << totalTime / 100.0 << "\n";
            }
            double totalTimeRev = 0;
            for (int proba = 0; proba < 100; proba++) {
                generateData(tabPierwotna, n, 0, true);
                copyArray(tabPierwotna, tabDoSortowania, n);
                auto start = chrono::high_resolution_clock::now();

                if (alg == "MergeSort") merge_sort_2(tabDoSortowania, tempMerge, 0, n - 1);
                else if (alg == "QuickSort") quick_sort(tabDoSortowania, 0, n - 1);
                else introsort2(tabDoSortowania, n);

                auto end = chrono::high_resolution_clock::now();
                totalTimeRev += chrono::duration<double, milli>(end - start).count();
            }
            file << alg << ";" << n << ";Odwrotnie_posortowane;" << totalTimeRev / 100.0 << "\n";
        }

        delete[] tabPierwotna;
        delete[] tabDoSortowania;
        delete[] tempMerge;
        cout << "Zakonczono pomiary dla rozmiaru: " << n << endl;
    }

    file.close();
    return 0;
}


