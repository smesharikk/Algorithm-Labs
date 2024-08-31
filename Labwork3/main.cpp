#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>

// Node- структура, которая будет моделировать узлы
struct Node {
    int info;       // храним числовую полезную информацию
    Node* left;     // структура самоссылающая,будем ссылаться на левые и правые поддеревья
    Node* right;
};


// New - процедура создания узла 
// 
// вершина каждый раз будет листом , поэтому у новых вершин нет левого и правого поддеревья
//чтобы вершины не теряли возвращаем адрес по которому эту вершину создавали

Node* New(int data) {
    Node* V;
    V = (Node*)malloc(sizeof(Node));
    V->info = data;
    V->left = V->right = nullptr;
    return V;  // Возвращаем указатель
}


//Add - Добавление узла

//добавляем элемент data , в какое дерево добавляем?в дерево которое которое содержится по адресу v.
//Сначала дерево был пустым и после добавления мы должны его не терять, поэтому функция будет
//возращать адрес. Адрем нам нужен если моздаем дерево с 0. Вот это возвращаемое значение будет выдавать нам родителей

Node* Add(Node* v, int data) {

    // условие выхода из рекурсии, когда мы добавили все и пора выходить 

    // как только мы дошли до листа, нет потомков, создаем новый элемент 
    if (v == nullptr) {  // Добавление нового
        return New(data);  // Возвращаем указатель на новый элемент
    }

    // Поиск места для включения узла в дерево

    // у нас есть массив , берем очередное число и начинаем выяснять куда нам двигаться налево ии напр аво
    //
    if ((v->info) < data) //если значение в элементе который сейчас у нас текующий больше чем наш входящий параметр data 
    {
        v->right = Add(v->right, data); // тогда мы идем направо
        //когда мы реально добавим? только в том случае, когда текущая вершина v не будет содержать потомков
        // и вместо вызова функции будет подставлена возращаемое значение 
        //вызов надо рассматривать слева направо, а возврат справа на лево , когда значение записалось, возвращаем v 
    }
    else {
        v->left = Add(v->left, data);// пойдем налево 
    }
    return v;

}

// Count - Подсчёт количества узлов дерева
int Count(Node* v, int a) {
    int count = 0;
    for (int i = 0; i < a; i++) {
        count++;
    }
    return count;  // Возвращаем количество узлов дерева
}

// Pre_order - Прямой обход дерева в глубину (корень-лево-право)
    void Pre_order(Node* tree) {
    if (tree != nullptr) {  // Лист - окончание рекурсии (идём, пока не встретится пустой узел)
        printf("%d ", tree->info);  // Вывод информации о вершине
        Pre_order(tree->left);  // Рекурсивный обход левого поддерева
        Pre_order(tree->right);  // Рекурсивный обход правого поддерева
    }
}

// In_order - Поперечный обход дерева в глубину (лево-корень-право)
void In_order(Node* tree) {
    if (tree != nullptr) {  // Лист - окончание рекурсии (идём, пока не встретится пустой узел)
        In_order(tree->left);  // Рекурсивный обход левого поддерева
        printf("%d ", tree->info);  // Вывод информации о вершине
        In_order(tree->right);  // Рекурсивный обход правого поддерева
    }
} 

// Post_order - Обратный обход дерева в глубину (лево-право-корень)
void Post_order(Node* tree) {
    if (tree != nullptr) {  // Лист - окончание рекурсии (идём, пока не встретится пустой узел)
        Post_order(tree->left);  // Рекурсивный обход левого поддерева
        Post_order(tree->right);  // Рекурсивный обход правого поддерева
        printf("%d ", tree->info);  // Вывод информации о вершине
    }
}

// Height - Найти высоту дерева
int Height(Node* tree) {
    if (tree == nullptr) {
        return -1;  // Окончание рекурсии
    }
    int left_tree = Height(tree->left);
    int right_tree = Height(tree->right);

    if (left_tree > right_tree) {
        return (left_tree + 1);
    }
    else {
        return (right_tree + 1);
    }
}

// Amount - найти количество листьев дерева
int Amount(Node* tree) {
    int count = 0;

    if (tree == nullptr) {
        count = 0;
    }
    else if (tree->left == nullptr && tree->right == nullptr) {
        count = 1;
    }
    else {
        count = Amount(tree->left) + Amount(tree->right);
    }
    return count;
}


// prlevel - Печать уровня
void prlevel(Node* tree, int level) {
    if (tree == nullptr) {
        return;
    }
    else if (level == 0) {
        printf("%d ", tree->info);
    }
    else {
        prlevel(tree->right, level - 1);
        prlevel(tree->left, level - 1);
        // prlevel(r->right, level-1);
    }
}

// Breadth - ширина дерева
void Breadth(Node* tree) {
    int h = Height(tree);
    for (int i = 0; i <= h; i++) {
        prlevel(tree, i);
    }
}


// Print - Печать дерева
void Print(Node* v) {
    static int level = 0;  // Для счёта уровня

    if (!v) return;  // Лист – окончание рекурсии

    level++;

    Print(v->right); // Обход правого поддерева
    printf("(Level %d) %d \n", level, v->info); // Вывод информации о вершине
    Print(v->left);  // Обход левого поддерева

    level--;
}

// DeleteTree - Удаление бинарного дерева
void DeleteTree(Node** v) {
    if (*v) {
        DeleteTree(&((*v)->left));
        DeleteTree(&((*v)->right));
        free(*v);
    }
}

int main() {
    char string[256];  // Строка, в которую мы считаем данные из файла (максимальной длины 128)
    FILE* file_ptr;  // Указатель на файл, который будем считывать
    Node* V = nullptr;


    file_ptr = fopen("C:/Users/MSI/Desktop/text_for_lab3.txt.txt", "r");

    if (file_ptr != NULL) {  // Если удалось открыть файл
        printf("File was successfully opened\n");
        printf("Read from file: ");
        fgets(string, 256, file_ptr);  // Считывание строки
        fprintf(stdout, "%s\n", string);  // Печать считанной строки

        int i = 0;  // Счётчик для прохождения по считанной строке
        int num = 0;  // Переменная для подсчёта числа
        int mass[256];  // Массив, в который мы будем записывать считанные числа
        int count = 0;  // Переменная, созданная для того, чтобы могли поочерёдно вставлять в массив считанные числа
        //добавляем в массив mass
        while (string[i] != '\0') {
            if (string[i + 1] == ' ') {
                num = num * 10 + (string[i] - '0');
                mass[count] = num;
                // printf("%d ", num);
                count++;
                num = 0;
            }
            else if (string[i] != ' ') {
                num = num * 10 + (string[i] - '0');
                // printf("%d ", num);
                mass[count] = num;
            }
            i++;
        }

        // Вывод считанной строки чисел по одному числу (считываем эти данные из массива)
        for (int i = 0; i <= count; i++) {
            // printf("%d ", mass[i]);
            V = Add(V, mass[i]);
        }
    }
    else {
        printf("File was not opened\n");
        return 1;
    }

    Print(V);
    printf("\nCount=%d, H=%d", Amount(V), Height(V));

    printf("\nPre_order: ");
    Pre_order(V);

    printf("\nIn_order: ");
    In_order(V);

    printf("\nPost_order: ");
    Post_order(V);

    printf("\nBreadth: ");
    Breadth(V);

    fclose(file_ptr);

    return 0;

}