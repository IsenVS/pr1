#include <iostream>
#include <cmath>
#include <string>
using namespace std;
// Проврка на простоту
bool isPrime(int p) {
    if (p <= 1) return false;
    if (p <= 3) return true;
    if (p % 2 == 0 || p % 3 == 0) return false;
    for (int i = 5; i * i <= p; i += 6) {
        if (p % i == 0 || p % (i + 2) == 0) return false;
    }
    return true;
}

// Функция для вычисления a^b mod p
int power(int a, int b, int p) {
    int result = 1;
    a = a % p;
    while (b > 0) {
        if (b & 1) {    // if (b % 2 == 1)
            result = (result * a) % p;
        }
        b /= 2;
        a = (a * a) % p;
    }
    return result;
}

// Функция для генерации общего секретного ключа на основе обмена публичными ключами
int generateSecretKey(int publicKey, int secretKey, int p) {
    return power(publicKey, secretKey, p);
}

string encryptMessage(const string& message, int key) {
    string encryptedMessage = message;
    for (char& c : encryptedMessage) {
        c = c + key; // Простой сдвиг символа на значение ключа
    }
    return encryptedMessage;
}

string decryptMessage(const string& encryptedMessage, int key) {
    string decryptedMessage = encryptedMessage;
    for (char& c : decryptedMessage) {
        c = c - key; // Обратный сдвиг символа на значение ключа
    }
    return decryptedMessage;
}

int main() {
    int p, g, secretKeyAlice, secretKeyBob;
    cout << "Введите простой модуль" << endl; cin >> p;
    if (!isPrime(p)){
        cout << "Модуль должен быть простым" << endl;
        return -1;
    }
    cout << "Введите основание" << endl;      cin >> g;

    cout << "Введите Секретный ключ Алисы" << endl; 
    cin >> secretKeyAlice;

    cout << "Введите Секретный ключ Боба" << endl; 
    cin >> secretKeyBob;

    // Вычисление публичных ключей для Alice и Bob
    int publicKeyAlice = power(g, secretKeyAlice, p);
    int publicKeyBob = power(g, secretKeyBob, p);

    // Генерация общего секретного ключа на основе обмена публичными ключами
    int secretKeySharedAlice = generateSecretKey(publicKeyBob, secretKeyAlice, p);
    int secretKeySharedBob = generateSecretKey(publicKeyAlice, secretKeyBob, p);

    string message;
    cin.ignore(); // очистка входного буфера
    cout << "Ваше сообщение: ";
    getline(cin, message);

    // Шифрование сообщения
    string encryptedMessage = encryptMessage(message, secretKeySharedAlice);
    cout << "Зашифрованное сообщение: " << encryptedMessage << endl;

    // Дешифрование сообщения
    string decryptedMessage = decryptMessage(encryptedMessage, secretKeySharedBob);
    cout << "Дешифрованное сообщение: " << decryptedMessage << endl;

    return 0;
}
