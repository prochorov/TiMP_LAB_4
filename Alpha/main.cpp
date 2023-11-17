#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"
#include <string>
#include <locale>
#include <codecvt>

SUITE(KeyTest)
{
    TEST(ValidKey) {
        std::wstring expected = L"КУБКУ";
        std::wstring actual = modAlphaCipher(L"КУБ").encrypt(L"ААААА");
        CHECK(expected == actual);
    }

    TEST(LongKey) {
        std::wstring expected = L"КУБАЧ";
        std::wstring actual = modAlphaCipher(L"КУБАЧУК").encrypt(L"ААААА");
        CHECK(expected == actual);
    }

    TEST(LowCaseKey) {
        std::wstring expected = L"КУБКУ";
        std::wstring actual = modAlphaCipher(L"куб").encrypt(L"ААААА");
        CHECK(expected == actual);
    }

    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher(L"ку7"), cipher_error);
    }

    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher(L"ку!б"), cipher_error);
    }
    
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp(L"Б В"), cipher_error);
    }
    
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(L""), cipher_error);
    }
    
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp(L"AAAAA"), cipher_error);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher(L"Б");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        std::wstring expected = L"ГПРСПТ";
        std::wstring actual = modAlphaCipher(L"Б").encrypt(L"ВОПРОС");
        CHECK(expected == actual);
    }

    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        std::wstring expected = L"ГПРСПТ";
        std::wstring actual = modAlphaCipher(L"Б").encrypt(L"вопрос");
        CHECK(expected == actual);
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        std::wstring expected = L"ГПРСПТ";
        std::wstring actual = modAlphaCipher(L"Б").encrypt(L"ВО П РОС!");
        CHECK(expected == actual);
    }

    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        std::wstring expected = L"ГПРСТ";
        std::wstring actual = modAlphaCipher(L"Б").encrypt(L"ВОПР0С");
        CHECK(expected == actual);
    }

    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(L""), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt(L"2345"), cipher_error);
    }

    TEST(MaxShiftKey) {
        std::wstring expected = L"БНОПНР";
        std::wstring actual = modAlphaCipher(L"Я").encrypt(L"ВОПРОС");
        CHECK(expected == actual);
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        std::wstring expected = L"БНОПНР";
        std::wstring actual = p->decrypt(L"ВОПРОС");
        CHECK(expected == actual);
    }

    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt(L"ВоПрОс"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt(L"Воп Рос"), cipher_error);
    }

    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(L""), cipher_error);
    }

    TEST(MaxShiftKey) {
        std::wstring expected = L"ГПРСПТ";
        std::wstring actual = modAlphaCipher(L"Я").decrypt(L"ВОПРОС");
        CHECK(expected == actual);
    }
    
    TEST_FIXTURE(KeyB_fixture, DigitsSrting) {
        CHECK_THROW(p->decrypt(L"В0ПР0С"), cipher_error);
    }
    
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt(L"ВО!П,РОС"), cipher_error);
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
