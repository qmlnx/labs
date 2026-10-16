#include <iostream>
#include <fstream>
using namespace std;

const int MAXN = 100; // максимум вершин

int main() {
    int i, j, n = 0, m = 0;
    int v1[200], v2[200];        //массивы, рёбра (первые и вторые вершины)
    int M[MAXN + 1][MAXN + 1];   // матрица смежности
    int adj[MAXN + 1][MAXN + 1]; // список смежности
    int deg[MAXN + 1];           // степень вершины (сколько соседей)
    
    // ========== 1. ЧИТАЕМ РЁБРА ИЗ ФАЙЛА ==========
    ifstream in("edges.txt");
    while (in >> v1[m] >> v2[m]) {
        if (v1[m] == -1 && v2[m] == -1) break;
        // находим максимальный номер вершины
        if (v1[m] > n) n = v1[m];
        if (v2[m] > n) n = v2[m];
        m++;
    }
    in.close();
    
    // ========== 2. ОБНУЛЯЕМ МАССИВЫ ==========
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            M[i][j] = 0;
            adj[i][j] = 0;
        }
        deg[i] = 0;
    }
    
    // ========== 3. УПРАЖНЕНИЕ 1: МАТРИЦА СМЕЖНОСТИ ==========
    for (i = 0; i < m; i++) { //проходим по ребрам
        M[v1[i]][v2[i]] = 1;
        M[v2[i]][v1[i]] = 1; // неориентированный граф
    }
    
    ofstream outMat("matrix.txt"); //создаем файл 
    for (i = 1; i <= n; i++) { //по строкам
        for (j = 1; j <= n; j++) { //по столбцам
            outMat << M[i][j] << " ";
        }
        outMat << endl;
    }
    outMat.close();
    
    // ========== 4. УПРАЖНЕНИЕ 2: СПИСОК СМЕЖНОСТИ ==========
    for (i = 0; i < m; i++) {
        // добавляем v2 в список вершины v1
        adj[v1[i]][deg[v1[i]]] = v2[i];
        deg[v1[i]]++;
        // добавляем v1 в список вершины v2
        adj[v2[i]][deg[v2[i]]] = v1[i];
        deg[v2[i]]++;
    }
    
    ofstream outList("adjlist.txt"); //создаем файл 
    for (i = 1; i <= n; i++) { //для каждой вершины ее номер 
        outList << i << ": ";
        for (j = 0; j < deg[i]; j++) { //проход по всем соседним
            outList << adj[i][j] << " "; //выводим соседние через пробел
        }
        outList << endl;
    }
    outList.close();
    
    // ========== 5. УПРАЖНЕНИЕ 3: ВОССТАНАВЛИВАЕМ РЁБРА ==========
    int printed[MAXN + 1][MAXN + 1] = {0}; // чтобы не выводить ребро дважды
    
    ofstream outEdges("restored_edges.txt");
    for (i = 1; i <= n; i++) { //по всем вершинам
        for (j = 0; j < deg[i]; j++) { //по соседним вершинам
            int v = adj[i][j];
            // выводим только если i < v и ещё не выводили
            if (i < v && printed[i][v] == 0) { 
                outEdges << i << " " << v << endl;
                printed[i][v] = 1; //доп проверка чтоб не было повторов
            }
        }
    }
    outEdges.close();
    
    // ========== 6. ВЫВОДИМ СООБЩЕНИЕ ==========
    cout << "Готово!" << endl;
    cout << "matrix.txt  - матрица смежности" << endl;
    cout << "adjlist.txt - список смежности" << endl;
    cout << "restored_edges.txt - восстановленные рёбра" << endl;
    
    return 0;
}