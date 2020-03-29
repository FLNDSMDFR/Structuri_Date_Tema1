#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int n, maxim, el_max, v[1000000], w[1000000];

void random_alloc(){
    int i;
    srand(time(NULL));
    for(i = 0; i < n; i++){
        v[i] = rand() % el_max;
        w[i] = v[i];
        if(maxim < v[i]) maxim = v[i];
    }
}

int check(int r_tests){
    int y_n;
    cout << "Run all " << r_tests << " remaining tests on the same algorithm?   [1]Yes / [2]No \n";
    cin >> y_n;
    if(y_n == 1) return true;
    else{
        if(y_n == 2) return false;
        else{
            cout << "Invalid entry, please try again \n";
            return check(r_tests);
        }
    }
}

void test(int x){
    int i;
    bool fail = false;
    for(i = 0; i < n - 1; i++){
        if(v[i] > v[i + 1]) fail = true;
        v[i] = 0;
    }
    v[i + 1] = 0;
    if(fail){
        cout << "The algorithm failed to sort the numbers \n";
    }
    else cout << "Sorting process successful \n";
    auto start = high_resolution_clock::now();
    sort(w, w+n);
    auto finish = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(finish - start);
    cout << "process for sort() function ended in " << duration.count() << " 탎 \n";
}

void bubble_sort(){
    int i, j;
    bool swapped;
    for(i = 0; i < n - 1; i++){
        swapped = false;
        for(j = 0; j < n - i - 1; j++){
            if(v[j] > v[j + 1]){
                swap(v[j], v[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
}

void count_sort(){
    int i, counter[el_max] = {0}, result[n];
    for(i = 0; i < n; i++){
        counter[v[i]]++;
    }
    for(i = 1; i < el_max; i++){
        counter[i] += counter[i - 1];
    }
    for(i = n - 1; i >= 0; i--){
        result[counter[v[i]] - 1] = v[i];
        counter[v[i]]--;
    }
    for(i = 0; i < n; i++){
        v[i] = result[i];
    }
}

void single_digit_csort(int exp){
    int result[n];
    int i, counter[10] = {0};
    for(i = 0; i < n; i++){
        counter[(v[i] / exp) % 10]++;
    }
    for(i = 1; i < 10; i++){
        counter[i] += counter[i - 1];
    }
    for(i = n - 1; i >= 0; i--){
        result[counter[(v[i] / exp) % 10] - 1] = v[i];
        counter[(v[i] / exp) % 10]--;
    }
    for(i = 0; i < n; i++){
        v[i] = result[i];
    }
}

void radix_sort(){
    int exp;
    for(exp = 1; maxim / exp > 0; exp *= 10)
        single_digit_csort(exp);
}

void merge_(int l, int m, int r){
    int il, ir, i, nl, nr;
    nl = m - l + 1;
    nr = r - m;
    int L[nl], R[nr];
    for(il = 0; il < nl; il++){
        L[il] = v[l + il];
    }
    for(ir = 0; ir < nr; ir++)
        R[ir] = v[m + ir + 1];
    il = 0;
    ir = 0;
    i = l;
    while(il < nl && ir < nr){
        if(L[il] <= R[ir]){
            v[i] = L[il];
            il++;
        }
        else{
            v[i] = R[ir];
            ir++;
        }
        i++;
    }
    while(il < nl){
        v[i] = L[il];
        il++;
        i++;
    }
    while(ir < nr){
        v[i] = R[ir];
        ir++;
        i++;
    }
}

void merge_sort(int l, int r){
    if(l < r){
        int m = l + ((r - l) / 2);
        merge_sort(l, m);
        merge_sort(m + 1, r);
        merge_(l, m, r);
    }
}

int part(int l, int r){
    int p = v[r];
    int j, i = l - 1;
    for(j = l; j <= r - 1; j++){
        if(v[j] <= p){
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[j]);
    return (i + 1);
}

int random(int l, int r){
    srand(time(NULL));
    int i = l + rand() % (r - l);
    swap(v[i], v[r]);
    return part(l, r);
}

void quick_sort(int l, int r){
    if(l < r){
        int p = random(l, r);
        quick_sort(l, p - 1);
        quick_sort(p + 1, r);
    }
}

int main()
{
    ifstream fin("input.txt");
    int nr_teste, c_1 = 0;
    bool c_2 = false, missed = false;
    fin >> nr_teste;
    for(int i = 0; i < nr_teste; i++){
        if(missed == false){
            fin >> n >> el_max;
            random_alloc();
        }
        else{
            i--; missed == false;
        }
        if(c_2 == false){
            cout << "What algorithm would you like to test? \n";
            cout << " [1] BubbleSort \n [2] CountSort \n [3] RadixSort \n";
            cout << " [4] MergeSort \n [5] QuickSort \n";
            cin >> c_1;
            c_2 = check(nr_teste - i);
        }
        if(c_1 == 1){
            auto start = high_resolution_clock::now();
            bubble_sort();
            auto finish = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(finish - start);
            cout << "process ended in " << duration.count() << " 탎 \n";
        }
        else{
            if(c_1 == 2){
                auto start = high_resolution_clock::now();
                count_sort();
                auto finish = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(finish - start);
                cout << "process ended in " << duration.count() << " 탎 \n";
            }
            else{
                if(c_1 == 3){
                auto start = high_resolution_clock::now();
                radix_sort();
                auto finish = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(finish - start);
                cout << "process ended in " << duration.count() << " 탎 \n";
                }
                else{
                    if(c_1 == 4){
                        auto start = high_resolution_clock::now();
                        merge_sort(0, n - 1);
                        auto finish = high_resolution_clock::now();
                        auto duration = duration_cast<microseconds>(finish - start);
                        cout << "process ended in " << duration.count() << " 탎 \n";
                    }
                    else{
                        if(c_1 == 5){
                            auto start = high_resolution_clock::now();
                            quick_sort(0, n);
                            auto finish = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(finish - start);
                            cout << "process ended in " << duration.count() << " 탎 \n";
                        }
                        else{
                            cout << "Invalid entry, please try again \n";
                            missed = true;
                        }
                    }
                }
            }
        }
        if(missed == false) test(i);
    }

    fin.close();
    return 0;
}
