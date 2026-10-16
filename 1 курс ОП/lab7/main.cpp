#include <stdio.h>
#include <locale.h>
#include <math.h>

int main() {
    // Устанавливаем локаль для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");
    
    //ЗАДАНИЕ II.1
    printf("ЗАДАНИЕ 1. ВЫЧИСЛЕНИЕ ЗНАЧЕНИЙ ФУНКЦИИ\n");
    
    double start_x;
    printf("Введите начальную точку интервала (0, 4]: ");
    scanf("%lf", &start_x);
    
    // Проверка корректности ввода
    if (start_x <= 0 || start_x > 4) {
        printf("Ошибка! Начальная точка должна быть в интервале (0, 4]\n");
        printf("Установлено значение по умолчанию: 0.1\n");
        start_x = 0.1;
    }
    
    double end_x = 4.0;
    double step = (end_x - start_x) / 9; // 10 точек = 9 промежутков
    
    printf("\nРезультаты вычислений функции y = ln(x) * sqrt(x):\n");
    printf("     x      |         y\n");
    
    for (int i = 0; i < 10; i++) {
        double x = start_x + i * step;
        if (x > 4) x = 4; // Корректировка для последней точки
        
        double y = log(x) * sqrt(x);
        printf("   %6.4f    |   %10.6f\n", x, y);
    }
    printf("\n\n");
    
    //ЗАДАНИЕ II.2
    printf("ЗАДАНИЕ 2. ЧИСЛА ФИБОНАЧЧИ\n");
    
    int MAX;
    printf("Введите максимальное значение суммы (MAX): ");
    scanf("%d", &MAX);
    
    int first = 1, second = 1, next;
    int sum = first + second; // Начинаем с суммы первых двух чисел
    int N = 2; // Количество использованных чисел
    
    // Проверка для малых значений MAX
    if (MAX < 2) {
        sum = first;
        N = 1;
    }
    
    // Вычисление суммы чисел Фибоначчи
    while (sum <= MAX) {
        next = first + second;
        if (sum + next > MAX) {
            break;
        }
        sum += next;
        first = second;
        second = next;
        N++;
    }
    
    printf("\nРезультаты:\n");
    printf("  Количество чисел (N): %d\n", N);
    printf("  Сумма чисел (S): %d\n", sum);
    printf("  Максимальная сумма (MAX): %d\n\n", MAX);
    
    // Дополнительный вывод последовательности
    printf("Последовательность Фибоначчи:\n");
    first = 1; second = 1;
    printf("  F1 = 1\n  F2 = 1\n  Сумма = 2\n");
    int temp_sum = 2;
    
    for (int i = 3; i <= N; i++) {
        next = first + second;
        temp_sum += next;
        printf("  F%d = %d, Промежуточная сумма = %d\n", i, next, temp_sum);
        first = second;
        second = next;
    }
    printf("\n\n");
    
    //ЗАДАНИЕ II.3
    printf("ЗАДАНИЕ 3. КРЕДИТНЫЕ ПЛАТЕЖИ\n");
 
    double credit_sum, rate;
    int months;
    
    printf("Введите сумму кредита: ");
    scanf("%lf", &credit_sum);
    printf("Введите срок кредита (в месяцах): ");
    scanf("%d", &months);
    printf("Введите процентную ставку (годовых): ");
    scanf("%lf", &rate);
    
    // Расчет ежемесячного платежа по основному долгу
    double main_payment = credit_sum / months;
    
    // Месячная процентная ставка
    double month_rate = rate / 100 / 12;
    
    printf("\n");
    printf("                   ТАБЛИЦА ЕЖЕМЕСЯЧНЫХ ПЛАТЕЖЕЙ\n");
    printf("| Месяц | Остаток долга | Осн. платеж | Проценты | Общий платеж |\n");
   
    double remaining_debt = credit_sum;
    double total_interest = 0;
    double total_payment = 0;
    
    for (int month = 1; month <= months; month++) {
        double interest = remaining_debt * month_rate;
        double monthly_payment = main_payment + interest;
        
        // Для последнего месяца корректируем остаток
        if (month == months) {
            main_payment = remaining_debt;
            monthly_payment = main_payment + interest;
        }
        
        printf("|  %3d   |  %10.2f   |   %7.2f   |  %7.2f |   %8.2f   |\n",
               month, remaining_debt, main_payment, interest, monthly_payment);
        
        remaining_debt -= main_payment;
        total_interest += interest;
        total_payment += monthly_payment;
        
        // Предотвращаем отрицательный остаток из-за погрешности вычислений
        if (remaining_debt < 0.01) {
            remaining_debt = 0;
        }
    }

    printf("\nИТОГОВАЯ ИНФОРМАЦИЯ:\n");
    printf("  Сумма кредита: %.2f\n", credit_sum);
    printf("  Срок кредита: %d месяцев\n", months);
    printf("  Процентная ставка: %.2f%% годовых\n", rate);
    printf("  Общая сумма процентов: %.2f\n", total_interest);
    printf("  Общая сумма выплат: %.2f\n", total_payment);
    printf("  Переплата: %.2f\n", total_interest);
    
    printf("         РАБОТА ПРОГРАММЫ ЗАВЕРШЕНА\n");
    
    return 0;
}
