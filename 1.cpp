#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

// Функция для проверки, является ли число простым
bool isPrime(int n) {
    if (n <= 1) return false; 
    if (n <= 3) return true; 
    if (n % 2 == 0 || n % 3 == 0) return false; 
    for (int i = 5; i * i <= n; i += 6) 
        if (n % i == 0 || n % (i + 2) == 0) 
            return false;
    return true;
}

// Функция для нахождения НОД (наибольший общий делитель) двух чисел
int gcd(int a, int b) {
    while (b != 0) {
        int t = b; 
        b = a % b; 
        a = t; 
    }
    return a; 
}

// Функция Эйлера для нахождения количества целых чисел, взаимно простых с n
int eulerPhi(int n) {
    int result = n; 
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) { // Если i является делителем n
            while (n % i == 0) // Удаляем все множители i из n
                n /= i;
            result -= result / i; // Уменьшаем результат на его долю, соответствующую i
        }
    }
    if (n > 1) result -= result / n; // Если остался какой-то множитель, уменьшаем на его долю
    return result;
}

// Функция для быстрого возведения числа в степень по модулю
long modexp(long base, long exponent, long modulus) {
    long result = 1;
    base = base % modulus; 

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent /= 2;
        base = (base * base) % modulus;
    }
    return result;
}

// Функция для вычисления остатков двумя способами
pair<int, int> remainder(int& basis, int& power, int& modP) {
    pair<int, int> ost = { 1, 1 };

    ost.first = modexp(basis, power, modP); // Первый остаток

    int logByNumber = log2(power); // Логарифм степени по основанию 2
    vector<int> binary; // Двоичное представление степени
    int power2 = power;
    while (power2 > 0) {
        binary.push_back(power2 % 2); // Записываем двоичные разряды
        power2 /= 2;
    }

    int resultForPrime = 1;
    for (int i = 0; i <= logByNumber; i++) {
        if (binary[i] == 1) { // Если соответствующий бит равен 1
            int oneDegree = pow(2, i); // Степень двойки, соответствующая позиции бита
            resultForPrime *= modexp(basis, oneDegree, modP); // Возводим в степень и умножаем
        }
    }
    ost.second = resultForPrime % modP; // Второй остаток

    return ost; // Возвращаем пару остатков
}

int main() {
    int base, exp, mod;
    cout << "Введите основание, степень и модуль: ";
    cin >> base >> exp >> mod; 

    bool flag = false; 

    // Проверяем условия теоремы Ферма
    if ((base % mod != 0) && isPrime(mod)) {
        cout << "Согласно теореме Ферма получим: " << base << "^" << exp << " mod " << mod << " = 1" << endl;
        pair<int, int> ost = remainder(base, exp, mod); // Рассчитываем остаток от деления
        cout << "Проверим, используя логарифм: " << ost.second << endl;
        flag = true; // проверка теоремы успешна
    }

    // Проверяем условия теоремы Эйлера
    if (gcd(base, mod) == 1 && exp == eulerPhi(mod)) {
        flag = true; // Отмечаем, что условия теоремы Эйлера выполнены
        cout << "Согласно теореме Эйлера получим: " << base << "^" << exp << " mod " << mod << " = 1" << endl;
        pair<int, int> ost = remainder(base, exp, mod); // Рассчитываем остаток от деления
        cout << "Проверим, используя логарифм: " << ost.second << endl;
    }

    // Если ни одна теорема не применима, используем общие свойства степеней по модулю
    if (!flag) {
        exp = eulerPhi(mod); // Корректируем степень согласно функции Эйлера
        int result = modexp(base, exp, mod); // Вычисляем результат по модулю
        pair<int, int> ost = remainder(base, exp, mod); // Получаем остатки от деления
        cout << "Результат, используя свойства сравнений = " << ost.first << " и результат, используя логарифм = " << ost.second << endl;
    }

    int base2 = 0, exp2 = 0;
    cout << "Введите основание второго числа, которое будете сравнивать по модулю: ";
    cin >> base2; 
    cout << "Введите степень числа второго числа, которое будете сравнивать по модулю: ";
    cin >> exp2; 

    // Сравниваем результаты возведения в степень по модулю для двух чисел
    if (modexp(base, exp, mod) > modexp(base2, exp2, mod)) {
        cout << base << "^" << exp << " mod " << mod << " > " << base2 << "^" << exp2 << " mod " << mod << endl;
    } else {
        cout << base << "^" << exp << " mod " << mod << " < " << base2 << "^" << exp2 << " mod " << mod << endl;
    }
    return 0;
}
