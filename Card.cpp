#include <iostream>
#include <windows.h>

#include "Card.h"

using namespace std;

const wchar_t* CardSuit[4]{ (wchar_t*)L"\x2665\ ", (wchar_t*)L"\x2666\ ", (wchar_t*)L"\x2663\ ", (wchar_t*)L"\x2660\ " };
const char* CardRang[13]{ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

//����������� �� ���������
Card::Card()
{
    suit = 0;
    rang = 0;
    status = false;
};

//����������� � �����������
Card::Card(short unsigned int suit, short unsigned int rang, bool status)
{
    this->suit = suit;
    this->rang = rang;
    this->status = status;
};

//����������� �����������
Card::Card(const Card& obj)
{
    suit = obj.suit;
    rang = obj.rang;
    status = obj.status;
}

//����������
Card::~Card()
{

};

//������ ������� �����
bool Card::CheckStatus()
{
    return status;
};

//������ ����� �����
short unsigned int Card::CheckSuit()
{
    return suit;
};

//������ ����� �����
short unsigned int Card::CheckRang()
{
    return rang;
};

//��������� ����� �����
void Card::SetSuit(short int suit)
{
    if (this->suit != suit)
        this->suit = suit;
};

//��������� ����� �����
void Card::SetRang(short int rang)
{
    if (this->rang != rang)
        this->rang = rang;
};

//��������� ������� ����� (����������� ��� ���)
void Card::SetStatus(bool status)
{
    if (this->status != status)
        this->status = status;
};

//��������������� �����
void Card::FlipCard()
{
    status = !status;
}

//��������� �����
void Card::PrintCard() const
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y });
    if (status == true)
    {
        wcout << "+-----+";
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 1 });;
        if (rang == 8)
            wcout << "|" << CardRang[rang] << "   |";
        else
            wcout << "| " << CardRang[rang] << "   |";
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 2 });

        if ((suit == 0) || (suit == 1)) {
            wcout << "|  "; PrintColorSuit(CardSuit[suit], Red); PrintColorSuit((wchar_t*)L" |", White);
        }
        else
            wcout << "|  " << CardSuit[suit] << " |";

        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 3 });
        if (rang == 8)
            wcout << "|   " << CardRang[rang] << "|";
        else
            wcout << "|   " << CardRang[rang] << " |";
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 4 });
        wcout << "+-----+";
    }
    else
    {
        wcout << "+--+--+";
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 1 });
        wcout << "|--|--|";
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 2 });
        wcout << "+-----+";
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 3 });
        wcout << "|--|--|";
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 4 });
        wcout << "+--+--+";
    }
    SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 5 });
};