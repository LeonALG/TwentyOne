#include "Card.h"
#include "Point.h"

class CardDeck: public Point 
{
private:
    //Количество рангов карт
    short int CountOfRang{ 13 };
    //Количество мастей
    short int CountOfSuit{ 4 };
    //Колода
    std::vector<Card> Deck;

public:
    //Конструктор по умолчанию
    CardDeck();

    //Конструктор с параметром - координатами начала "стола"
    CardDeck(COORD CoordOfGame);

    //Конструктор копирования
    CardDeck(const CardDeck& obj);

    //Деструктор класса
    virtual ~CardDeck();

    ////Задание координат игры
    //void SetCoord(COORD CoordOfGame);

    ////Взятие координат игры
    //COORD GetCoord();

    //Тасовка карт
    void ShaffleDeck(); // Перемешать колоду

    //Отрисовка колоды
    void PrintDeck();

    Card& operator[](size_t ind);
};