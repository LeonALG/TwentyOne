#pragma once
#include "Point.h"
enum ConsoleColor {
    Black = 0,
    DarkBlue = 1,
    DarkGreen = 2,
    DarkCyan = 3,
    DarkRed = 4,
    DarkPink = 5,
    Brown = 6,
    LightGray = 7,
    Gray = 8,
    Blue = 9,
    Green = 10,
    Cyan = 11,
    Red = 12,
    Pink = 13,
    Yellow = 14,
    White = 15
};

template < typename T >
void PrintColorSuit(T inside, int insideColor, int bracketColor = LightGray, int backgroundColor = Black) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //Получаем дескриптор вывода на консоль
    SetConsoleTextAttribute(hStdOut, (WORD)((backgroundColor << 4) | insideColor));
    std::wcout << inside;
}

class Card: public Point
{
private:
    // Масть карты - 1 черви, 2 - бубны, 3 - трефы, 4 - пики
    short unsigned int suit;
    // Значение карты
    short unsigned int rang;
    // Статус карты (перевернута или нет)
    bool status;

public:
    //Конструктор по умолчанию
    Card();

    //Конструктор с параметрами
    Card(short unsigned int suit, short unsigned int rang, bool status);

    //Конструктор копирования
    Card(const Card& obj);

    //Деструктор
    ~Card();

    //Взятие статуса карты
    bool CheckStatus();

    //Взятие масти карты
    short unsigned int CheckSuit();

    //Взятие ранга карты
    short unsigned int CheckRang();

    //Установка масти карты
    void SetSuit(short int suit);

    //Установка ранга карты
    void SetRang(short int rang);

    //Установка статуса карты (перевернута или нет)
    void SetStatus(bool status);

    //Переворачивание карты
    void FlipCard();

    //Отрисовка карты
    void PrintCard() const;
};