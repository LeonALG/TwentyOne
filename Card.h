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
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //�������� ���������� ������ �� �������
    SetConsoleTextAttribute(hStdOut, (WORD)((backgroundColor << 4) | insideColor));
    std::wcout << inside;
}

class Card: public Point
{
private:
    // ����� ����� - 1 �����, 2 - �����, 3 - �����, 4 - ����
    short unsigned int suit;
    // �������� �����
    short unsigned int rang;
    // ������ ����� (����������� ��� ���)
    bool status;

public:
    //����������� �� ���������
    Card();

    //����������� � �����������
    Card(short unsigned int suit, short unsigned int rang, bool status);

    //����������� �����������
    Card(const Card& obj);

    //����������
    ~Card();

    //������ ������� �����
    bool CheckStatus();

    //������ ����� �����
    short unsigned int CheckSuit();

    //������ ����� �����
    short unsigned int CheckRang();

    //��������� ����� �����
    void SetSuit(short int suit);

    //��������� ����� �����
    void SetRang(short int rang);

    //��������� ������� ����� (����������� ��� ���)
    void SetStatus(bool status);

    //��������������� �����
    void FlipCard();

    //��������� �����
    void PrintCard() const;
};