
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#define A_SIZE 20
#define G_SIZE 10
#define MAX_W 10

// Max deger icin sonsuz sayi
#define INF INT_MAX

void generate(int a[], int size);
void function1(int a[], int size);
int function2(int a[], int size);
void function3(int g[][G_SIZE], int d[][G_SIZE], int size);
void print1(int a[], int size);
void print2(int g[][G_SIZE], int size);
void print3(int g[][G_SIZE], int size, int t);

int main()
{
    int a[A_SIZE];
    int g[G_SIZE][G_SIZE] = {
        {0, 10, 3, 0, 0, 5, 0, 17, 0, 22},
        {10, 0, 5, 0, 2, 0, 13, 0, 0, 0},
        {3, 5, 0, 2, 0, 4, 0, 21, 0, 11},
        {0, 0, 2, 0, 7, 0, 6, 0, 0, 0},
        {0, 2, 0, 7, 0, 6, 0, 0, 19, 0},
        {5, 0, 4, 0, 6, 0, 9, 3, 0, 0},
        {0, 13, 0, 6, 0, 9, 0, 4, 0, 0},
        {17, 0, 21, 0, 0, 3, 4, 0, 8, 0},
        {0, 0, 0, 0, 19, 0, 0, 8, 0, 5},
        {22, 0, 11, 0, 0, 0, 0, 0, 5, 0}};
    int d[G_SIZE][G_SIZE];
    int t;

    // Rastgele sayi uretici icin seed
    srand(time(NULL));

    // Calisma suresinin hesaplanmasi
    clock_t start, end;
    double time;

    start = clock();

    generate(a, A_SIZE);
    printf("A:\n");
    print1(a, A_SIZE);

    function1(a, A_SIZE);
    printf("\nFunction1 Sonuc:\n");
    print1(a, A_SIZE);

    t = function2(a, A_SIZE);
    printf("\nFunction2 Sonuc: %d\n", t);

    printf("\nG:\n");
    print2(g, G_SIZE);

    function3(g, d, G_SIZE);
    printf("\nFunction3 Sonuc:\n");
    print2(d, G_SIZE);

    printf("\n%d icin sonuc:\n", t);
    print3(d, G_SIZE, t);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCalisma Suresi: %f sn\n", time);

    return 0;
}
/*
void function1(int a[], int size) {
    for (int i = 0; i < size - 1; i++) {//(n -1 kere tekrar eder)
        for (int j = 0; j < size - 1 - i; j++) {//n -1 kere tekrar eder
            if (a[j] > a[j + 1]) {//1
                int tmp = a[j];//1
                a[j] = a[j + 1];//1
                a[j + 1] = tmp;//1
            }
        }
    }
}
sonuç: (n-1) * (n-1) = n^2 -2n + 1
yaklaşık olarak: O(n) = n^2 sonucunu elde ederiz.
bubble sort algoritması kullanılmıştır, bunun yerine merge sort algoritması önerilir.

*/

void merge(int a[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftArray[leftSize];
    int rightArray[rightSize];

    for (int i = 0; i < leftSize; i++)
    { // n/2
        leftArray[i] = a[left + i];
    }

    for (int j = 0; j < rightSize; j++)
    { // n/2
        rightArray[j] = a[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize)
    { // n
        if (leftArray[i] <= rightArray[j])
        {
            a[k] = leftArray[i];
            i++;
        }
        else
        {
            a[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < leftSize)
    { // n/2
        a[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < rightSize)
    { // n/2
        a[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int a[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}

void function1(int a[], int size)
{
    mergeSort(a, 0, size - 1);
}
/*
sonuç: t(n) = 2[2 * t*(n/2^2) + n/2] + n
n = n/2^2 ise
O(n) = nlog(n) şeklindedir, merge sort'un worst case halidir.
*/

/*
int function2(int a[], int size) {
    int t = 0, current_sum = 0, count=0;//1
    for (int i = 0; i < size; i++) {//n
        if (current_sum + a[i] > 0) {//1 * n
            current_sum = current_sum + a[i]; // 1 * n
        }
        else { // 1 * n
            current_sum = 0; // 1 * n
        }
        if (current_sum > t) {// 1 * n
            t = current_sum;// 1 * n
            count++; // 1 * n
        }
    }
    return t/count; //1
}


bu fonksiyonda tek for döngüsü vardır ve önerilecek fonksiyonda da
bir for döngüsü bulunmaktadır dolayısıyla biraz küçük hesaplar yapmalıyız

t(n) = 1  + n + n + n + n + n + n + 1
    = 7n + 2
O(n) = n değerini buluruz.

*/

int function2(int arr[], int size)
{
    int sum = 0; // 1
    for (int i = 0; i < size; i++)
    {                  // n
        sum += arr[i]; // n * 1
    }
    return sum / size; // 1
}
/*
sonuc: t(n) = 1 + n + n + 1
    t(n) = 2n + 1

O(n) = n şeklinde bulunur.
*/

/*

void function3(int g[][G_SIZE], int d[][G_SIZE], int size) {
    for (int i = 0; i < size; i++) {//n
        for (int j = 0; j < size; j++) {// n * n
            if (i == j) { // 1 * n * n
                d[i][j] = 0; // 1 * n * n
            }
            else if (g[i][j] != 0) {// 1 * n * n
                d[i][j] = g[i][j];// 1 * n * n
            }
            else {// 1 * n * n
                d[i][j] = INF;// 1 * n * n
            }
        }
    }

    for (int k = 0; k < size; k++) {// n
        for (int i = 0; i < size; i++) { // n * n
            for (int j = 0; j < size; j++) { // n * n * n
                if (d[i][k] != INF && d[k][j] != INF &&// 1 * n * n
                    d[i][k] + d[k][j] < d[i][j]) {// 1 * n * n
                    d[i][j] = d[i][k] + d[k][j];// 1 * n * n
                }
            }
        }
    }
}
algoritmanın ismi Floyd-Warshall algoritmasıdır.
sonuç: T(n) = n^3 + 2n^2 + 18n + 9
O(n) = n^3 şeklindedir.
*/

void function3(int g[][G_SIZE], int d[][G_SIZE], int size)
{
    bool visited[G_SIZE] = {false}; // 1
    for (int i = 0; i < size; i++) 
    { // n
        for (int j = 0; j < size; j++)
        { // n * n
            if (i == j) // n * n * 1
            {
                d[i][j] = 0;// n * n * 1
            }
            else if (g[i][j] != 0)// n * n * 1
            {
                d[i][j] = g[i][j];// n * n * 1
            }
            else// n * n * 1
            {
                d[i][j] = INF;// n * n * 1
            }
        }
    }
    for (int k = 0; k < size; k++)
    {// n
        int minDist = INF; // n * 1
        int minIndex = -1; // n * 1

        for (int i = 0; i < size; i++) // n * n
        {
            if (!visited[i] && d[i][k] < minDist)// n * n * 1
            {
                minDist = d[i][k];// n * n * 1
                minIndex = i;// n * n * 1
            }
        }

        if (minIndex == -1)// n
        {

            break; // n
        }

        visited[minIndex] = true;// n
        for (int j = 0; j < size; j++) // n * n 
        {
            if (!visited[j] && d[minIndex][k] != INF && g[k][j] != 0 &&
                d[minIndex][k] + g[k][j] < d[minIndex][j])
            {// n * n * 1
                d[minIndex][j] = d[minIndex][k] + g[k][j];// n * n * 1
            }
        }
    }
}
/*
sonuç: t(n) = 1 + n + n^2 + 11 n^2 + 11 + n + n + n
    O(n) = n^2 şeklindedir.


*/


/*
Çalışma süresi arasındaki gözlemlerim:
    kodun eski halinde çalışma süresi 0.000417 sn iken yeni hali 0.000209 sn'dir.
*/