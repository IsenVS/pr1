#include <iostream>

using namespace std;

long modexp(long a, int x, int p) {
    long result = 1;
    a = a % p;
    while (x > 0) {
        if (x % 2 == 1) {
            result = (result * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }
    return result;
}

int main() {
    int a, b, c;
    cout << "Введите этажи нужного числа: ";
    cin >> a >> b >> c;

    int one = modexp(a, b, 10);
    int two = modexp(one, c, 10);
    cout << "Последняя цифра: " << two << endl;
    return 0;
}