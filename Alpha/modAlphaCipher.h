/**
* @file modAlphaCipher.h
* @author Прохоров А.С.
* @version 1.0
* @brief Описание класса modAlphaCipher
* @date 17.11.2023
* @copyright ИБСТ ПГУ
*/

#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
using namespace std;

/**
 * @class modAlphaCipher
 * @brief Класс, реализующий шифрование методом "Гронсвельда"
 */
class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //!< Алфавит для текста, использующийся в программе
    std::map<char, int> alphaNum; //!< Ассоциативный массив "номер по символу"
    std::vector<int> key; //!< Атрибут для ключа

    /**
     * @brief Преобразование строки в вектор чисел
     * @details Формирует вектор чисел по индексам букв алфавита
     * @param s Строка текста типа "wstring"
     * @return std::vector<int> Вектор, хранящий индексы букв алфавита
     */
    std::vector<int> convert(const std::wstring& s);

    /**
     * @brief Преобразование вектора чисел в строку
     * @details Формирует строку текста по индексам алфавита "numAlpha"
     * @param v Вектор чисел
     * @return std::wstring Строка текста типа "wstring"
     */
    std::wstring convert(const std::vector<int>& v);

    /**
     * @brief Проверка ключа
     * @details Проверяет ключ на пустоту и наличие недопустимых символов
     * @param s Ключ типа "wstring"
     * @throw cipher_error Если ключ пуст или содержит недопустимые символы
     * @return std::wstring Валидный ключ
     */
    std::wstring getValidKey(const std::wstring& s);

    /**
     * @brief Проверка текста
     * @details Проверяет текст на пустоту и наличие недопустимых символов
     * @param s Текст типа "wstring"
     * @throw cipher_error Если текст пуст или содержит недопустимые символы
     * @return std::wstring Валидный текст
     */
    std::wstring getValidText(const std::wstring& s);

public:
    /**
     * @brief Конструктор для ключа
     * @details Инициализирует алфавит, ассоциативный массив "номер по символу" и ключ
     * @param skey Ключ для шифрования типа "wstring"
     */
    modAlphaCipher(const std::wstring& skey);

    /**
     * @brief Зашифрование
     * @details Шифрует текст с использованием ключа и возвращает зашифрованный текст
     * @param open_text Текст для зашифрования типа "wstring"
     * @throw cipher_error Если текст пуст или содержит недопустимые символы
     * @return std::wstring Зашифрованный текст
     */
    std::wstring encrypt(const std::wstring& open_text);

    /**
     * @brief Расшифрование
     * @details Расшифровывает зашифрованный текст с использованием ключа и возвращает исходный текст
     * @param cipher_text Зашифрованный текст для расшифрования типа "wstring"
     * @throw cipher_error Если текст пуст или содержит недопустимые символы
     * @return std::wstring Расшифрованный текст
     */
    std::wstring decrypt(const std::wstring& cipher_text);
};

/**
 * @class cipher_error
 * @brief Исключение для ошибок в классе modAlphaCipher
 */
class cipher_error : public std::invalid_argument
{
public:
    explicit cipher_error(const std::string& what_arg):
        std::invalid_argument(what_arg) {}

    explicit cipher_error(const char* what_arg):
        std::invalid_argument(what_arg) {}
};
