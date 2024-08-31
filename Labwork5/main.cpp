#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print(int* mass, int razmer) {
    for (int j = 0; j < razmer + 1; j++) {
        printf("%d ", mass[j]);
    }
}

void readfile(FILE* file, char* str) {
    if (file == NULL) {
        printf("File opening error!\n");
        exit(0);
    }
    if (file != NULL) {
        fgets(str, 128, file);
    }
}

void Elevate(int* mass, int i) { // РїРѕРґРЅСЏС‚РёРµ РёР»Рё РІСЃРїР»С‹С‚РёРµ
    if (i == 0) {
        return;
    }
    int parent = (i - 1) / 2;
    while ((mass[i] > mass[parent])) { //  && 1 || (mass[i] < mass[parent]) && 0
        int x = mass[i];
        mass[i] = mass[parent];
        mass[parent] = x;
        if (parent == 0) break;
        i = parent;
        parent = (i - 1) / 2;
    }
}

void MakeHeap(int* mass, int i, int num) { // СЃРѕР·РґР°РЅРёРµ РљСѓС‡Рё
    mass[i] = num;
    if (i == 0) {
        return;
    }
    Elevate(mass, i); // РїРѕРґРЅСЏС‚РёРµ РёР»Рё РІСЃРїР»С‹С‚РёРµ
}

int MAXget(int* mass, int n) {
    int count = -1;
    int max = -1;
    for (int i = 0; i < n + 1; i++) {
        if (max < mass[i]) {
            max = mass[i];
            count++;
        }
    }
    mass[count] = mass[n];
    mass[n] = 0;
    for (int i = 0; i <= n; i++) {
        Elevate(mass, i);
    }
    return max;
}

int main() {
    char str[128];
    int z[128];
    int a = 0;
    int i = 0;
    int count = 0;
    FILE* file = fopen("C:/Users/MSI/Desktop/test_for_5_lab.txt.txt", "r");
    readfile(file, str);
    while (str[i] != '\0') {
        if (str[i + 1] == ' ') {
            a = a * 10 + (str[i] - '0');
            z[count] = a;
            count = count + 1;
            a = 0;
        }
        else if (str[i] != ' ') {
            a = a * 10 + (str[i] - '0');
            z[count] = a;
        }
        i++;
    }
    printf("\n");
    printf("From file: "); print(z, count); printf("\n");
    int* zvc = (int*)malloc((count) * sizeof(int));
    printf("Make Heap:\n");
    for (int i = 0; i <= count; i++) {
        MakeHeap(zvc, i, z[i]);
        for (int j = 0; j <= i; j++) {
            printf("%d ", zvc[j]);
        }
        printf("n = %d\n", i + 1);
    }
    printf("_____________________________________________________________________\n\n");
    printf("Heap:\n"); print(zvc, count); printf("n = %d\n", count + 1);
    
    int bvc = MAXget(zvc, count);
    count = count - 1;
    printf("Max element: %d\n", bvc);
    printf("After find max element: "); print(zvc, count);
    printf("\n\n");

    free(zvc);
}