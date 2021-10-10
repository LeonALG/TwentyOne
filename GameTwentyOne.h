#pragma once
#include "Point.h"
#include "CardDeck.h"

class GameTwentyOne: public Point
{
private:
    const short int DistBetweenPlayers = 11;

    ////Координаты стола
    //COORD CurrentCoord;

    //Количество рангов карт
    short int CountOfRang{ 13 };
    //Количество мастей
    short int CountOfSuit{ 4 };

    //Массив индексов взятых из колоды карт
    std::vector <int> PickedCards;
    //Количество взятых карт из колоды
    short int CountPickedCards;

    //Количество взятых карт игроком
    short int PickedPlayer;
    //Количество взятых карт компьютером
    short int PickedComputer;

    //Рука игрока
    std::vector<Card> PlayerHand;

    //Рука компьютера
    std::vector<Card> ComputerHand;

    CardDeck Deck;
private:
    //Добавление в руку карты одному из игроков
    std::vector<Card> PlayerOrComputerAddHand(std::vector<Card> obj, short int& CountObj, short int TypeOfPlayer);
    //Подсчёт счёта одного из игроков
    short int PlayerOrComputerScore(std::vector<Card> obj, const short int CountObj) const;
public:
	GameTwentyOne();
    GameTwentyOne(const GameTwentyOne& obj);
	GameTwentyOne(int x, int y);
	virtual ~GameTwentyOne();

    //Метод взятия карты из колоды в руку одного из игроков
    bool GetCard(Card& Example);
    //Подготовка к началу игры
    void PreparationStartGame();
    //Проверка очков одного из игроков
    short int CheckedScore(short int NumberOfPlayer) const;
    //Добавление карты одному из игроков
    bool AddHand(short int NumberOfPlayer);
    //Открытие скрытой карты компьютера
    void OpenComputerCards();
    //Очистка сообщений нажатия клавиш
    void ClearUnderScore();

    void LoadGame();
    void SaveGame();

	bool Game();
};