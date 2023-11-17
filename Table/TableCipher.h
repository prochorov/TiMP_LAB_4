/**
* @file TableCipher.h
* @author Прохоров А.С.
* @version 1.0
* @brief Объявление класса Cipher для шифрования на основе таблицы
* @date 17.11.2023
*/

#ifndef TABLECIPHER_H
#define TABLECIPHER_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>

/**
 * @class Cipher
 * @brief Класс, реализующий шифрование на основе таблицы
 */
class Cipher {
private:
    int key; //!< Ключ для шифрования на основе таблицы

    /**
     * @brief Проверяет и возвращает валидный открытый текст
     * @param s Входной открытый текст
     * @return std::string Валидный открытый текст
     * @throw cipher_error Если открытый текст пуст или содержит недопустимые символы
     */
    std::string getValidOpenText(const std::string& s);

    /**
     * @brief Проверяет и возвращает валидный зашифрованный текст
     * @param s Входной зашифрованный текст
     * @return std::string Валидный зашифрованный текст
     * @throw cipher_error Если зашифрованный текст пуст или содержит недопустимые символы
     */
    std::string getValidCipherText(const std::string& s);

    /**
     * @brief Проверяет и возвращает валидный ключ
     * @param key Входной ключ
     * @param s Исходная строка ключа (для сообщений об ошибках)
     * @return int Валидный ключ
     * @throw cipher_error Если ключ отрицательный или не является числом
     */
    int getValidKey(const int key, const std::string& s);

public:
    //! Удаленный конструктор по умолчанию
    Cipher() = delete;

    /**
     * @brief Параметризованный конструктор для инициализации ключа
     * @param skey Ключ в виде строки
     */
    Cipher(const std::string& skey);

    /**
     * @brief Шифрует открытый текст на основе таблицы
     * @param open_text Входной открытый текст
     * @throw cipher_error Если открытый текст пуст или содержит недопустимые символы
     * @return std::string Зашифрованный текст
     */
    std::string encrypt(const std::string& open_text);

    /**
     * @brief Дешифрует зашифрованный текст на основе таблицы
     * @param cipher_text Входной зашифрованный текст
     * @throw cipher_error Если зашифрованный текст пуст или содержит недопустимые символы
     * @return std::string Расшифрованный текст
     */
    std::string decrypt(const std::string& cipher_text);
};

/**
 * @class cipher_error
 * @brief Пользовательское исключение для ошибок, связанных с шифром
 */
class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}

    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};

#endif
