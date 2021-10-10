#pragma once
#include "Point.h"
#include "CardDeck.h"

class GameTwentyOne: public Point
{
private:
    const short int DistBetweenPlayers = 11;

    ////���������� �����
    //COORD CurrentCoord;

    //���������� ������ ����
    short int CountOfRang{ 13 };
    //���������� ������
    short int CountOfSuit{ 4 };

    //������ �������� ������ �� ������ ����
    std::vector <int> PickedCards;
    //���������� ������ ���� �� ������
    short int CountPickedCards;

    //���������� ������ ���� �������
    short int PickedPlayer;
    //���������� ������ ���� �����������
    short int PickedComputer;

    //���� ������
    std::vector<Card> PlayerHand;

    //���� ����������
    std::vector<Card> ComputerHand;

    CardDeck Deck;
private:
    //���������� � ���� ����� ������ �� �������
    std::vector<Card> PlayerOrComputerAddHand(std::vector<Card> obj, short int& CountObj, short int TypeOfPlayer);
    //������� ����� ������ �� �������
    short int PlayerOrComputerScore(std::vector<Card> obj, const short int CountObj) const;
public:
	GameTwentyOne();
    GameTwentyOne(const GameTwentyOne& obj);
	GameTwentyOne(int x, int y);
	virtual ~GameTwentyOne();

    //����� ������ ����� �� ������ � ���� ������ �� �������
    bool GetCard(Card& Example);
    //���������� � ������ ����
    void PreparationStartGame();
    //�������� ����� ������ �� �������
    short int CheckedScore(short int NumberOfPlayer) const;
    //���������� ����� ������ �� �������
    bool AddHand(short int NumberOfPlayer);
    //�������� ������� ����� ����������
    void OpenComputerCards();
    //������� ��������� ������� ������
    void ClearUnderScore();

    void LoadGame();
    void SaveGame();

	bool Game();
};