#include <iostream>

#include <time.h>
#include <windows.h>
#include <vector>

#include "CardDeck.h"

using namespace std;

CardDeck::CardDeck()
{
    Deck.resize(CountOfRang * CountOfSuit);
    for (short int i = 0; i < CountOfRang; i++)
    {
        for (short int j = 0; j < CountOfSuit; j++)
        {
            Deck[i * CountOfSuit + j].SetRang(i);
            Deck[i * CountOfSuit + j].SetSuit(j);
            Deck[i * CountOfSuit + j].SetStatus(true);
        }
    }
    CurrentPoint = { 0,0 };
}

CardDeck::CardDeck(COORD CoordOfGame)
{
    Deck.resize(CountOfRang * CountOfSuit);
    for (short int i = 0; i < CountOfRang; i++)
    {
        for (short int j = 0; j < CountOfSuit; j++)
        {
            Deck[i * CountOfSuit + j].SetRang(i);
            Deck[i * CountOfSuit + j].SetSuit(j);
            Deck[i * CountOfSuit + j].SetStatus(true);
        }
    }
    CurrentPoint = CoordOfGame;
}

CardDeck::CardDeck(const CardDeck& obj)
{
    Deck = obj.Deck;
}

CardDeck::~CardDeck()
{

}

void CardDeck::ShaffleDeck() // Перемешать колоду
{
    srand((unsigned)time(NULL));
    for (short int i = 0; i < 52; i++)
    {
        swap(Deck[i], Deck[rand() % 52]);
    }
}

void CardDeck::PrintDeck()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, CurrentPoint);
    short int CardinLine = 8;
    for (short int i = 0; i < CountOfSuit * CountOfRang; i++)
    {
        Deck[i].SetCoord({ CurrentPoint.X + (i % CardinLine) * 9, CurrentPoint.Y + (i / CardinLine) * 5 });
        Deck[i].PrintCard();
    }
}

Card& CardDeck::operator[](size_t ind)
{
    return Deck[ind];
}