#include <iostream>
#include <cmath>
using namespace std;

// ========== СПОСОБ 1: В ЛОБ С МАТРИЦЕЙ ==========
int count1 = 0;

// Проверка, безопасно ли ставить ферзя в позицию (row, col)
bool isSafe(int** board, int row, int col, int K) {
    // проверка горизонтали (влево)
    for (int j = 0; j < col; j++) 
        if (board[row][j]) return false;
    
    // проверка вертикали (вверх)
    for (int i = 0; i < row; i++) 
        if (board[i][col]) return false;
    
    // проверка диагонали вверх-влево
    for (int i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--) 
        if (board[i][j]) return false;
    
    // проверка диагонали вверх-вправо
    for (int i = row-1, j = col+1; i >= 0 && j < K; i--, j++) 
        if (board[i][j]) return false;
    
    return true;
}

// Рекурсивная функция для расстановки ферзей
void solve1(int** board, int* queens, int row, int K) {
    if (row == K) { // все ферзи расставлены
        count1++; //увеличиваем счетчик
        for (int i = 0; i < K; i++) 
            cout << queens[i] + 1 << " "; //выводим номера столбцов
        cout << endl;
        return;
    }
    
    // пробуем поставить ферзя в каждый столбец текущей строки
    for (int col = 0; col < K; col++) { //перерираем все столбцы
        if (isSafe(board, row, col, K)) {
            board[row][col] = 1; // ставим ферзя 
            queens[row] = col;    // запоминаем позицию
            solve1(board, queens, row + 1, K); //переход к след строке
            board[row][col] = 0; // убираем ферзя (backtracking)
        }
    }
}

// Основная функция для первого метода
void method1(int K) {
    // создаем доску KxK
    int** board = new int*[K];
    int* queens = new int[K];
    
    for (int i = 0; i < K; i++) {
        board[i] = new int[K]; //для каждой строки выделяем массив
        for (int j = 0; j < K; j++) 
            board[i][j] = 0; //заполняем нулями
    }
    
    count1 = 0;
    cout << "\n=== МЕТОД 1: ПРЯМОЙ ПЕРЕБОР С МАТРИЦЕЙ ===\n";
    solve1(board, queens, 0, K); //запускаем поиск первой строки
    cout << "Всего решений: " << count1 << endl;
    
    // очистка памяти
    for (int i = 0; i < K; i++) delete[] board[i];
    delete[] board;
    delete[] queens;
}

// ========== СПОСОБ 2: АЛГОРИТМ ИЗ ЛЕКЦИИ ==========
int count2 = 0;

// Проверка для оптимизированного метода
bool isSafe2(int queens[], int row, int col) {
    for (int i = 0; i < row; i++) { //проверка предыдущих строк
        if (queens[i] == col || abs(queens[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

// Рекурсивная функция для оптимизированного метода
void solve2(int queens[], int row, int K) {
    if (row == K) { //если все ферзи расставлены
        count2++; //увеличиваем счетчик
        for (int i = 0; i < K; i++) 
            cout << queens[i] + 1 << " "; //выводим номера столбцов
        cout << endl;
        return;
    }
    
    for (int col = 0; col < K; col++) {
        if (isSafe2(queens, row, col)) {
            queens[row] = col;
            solve2(queens, row + 1, K);
        }
    }
}

// Основная функция для второго метода
void method2(int K) {
    int* queens = new int[K];
    count2 = 0;
    cout << "\n=== МЕТОД 2: ОПТИМИЗИРОВАННЫЙ (ИЗ ЛЕКЦИИ) ===\n";
    solve2(queens, 0, K);
    cout << "Всего решений: " << count2 << endl;
    delete[] queens;
}

// ========== ТЕСТЫ ==========
void runTests() {
    cout << "\n=== ТЕСТИРОВАНИЕ ===\n";
    int tests[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int expected[] = {1, 0, 0, 2, 10, 4, 40, 92};
    
    for (int i = 0; i < 8; i++) {
        int K = tests[i];
        int* q = new int[K];
        count2 = 0;
        solve2(q, 0, K);
        cout << "K=" << K << ": " << count2 << " решений ";
        if (count2 == expected[i]) cout << "✓\n";
        else cout << "✗ (ожидалось " << expected[i] << ")\n";
        delete[] q;
    }
}

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========
int main() {
    int K;
    cout << "ЗАДАЧА О РАССТАНОВКЕ K ФЕРЗЕЙ\n";
    cout << "Введите K (1-8) или 0 для тестов: ";
    cin >> K;
    
    if (K == 0) {
        runTests();
    } else {
        method1(K);
        method2(K);
        
        cout << "\n=== АНАЛИЗ МЕТОДОВ ===\n";
        cout << "МЕТОД 1 (с матрицей):\n";
        cout << "  + Наглядно, легко понять\n";
        cout << "  + Проверяет все направления\n";
        cout << "  - Требует O(K²) памяти\n";
        cout << "  - Медленная проверка\n\n";
        
        cout << "МЕТОД 2 (из лекции):\n";
        cout << "  + Быстрая проверка O(1)\n";
        cout << "  + Требует O(K) памяти\n";
        cout << "  + Эффективный перебор\n";
        cout << "  - Менее наглядно\n";
    }
    
    return 0;
}