#include "Card.h"
#include "Point.h"

class CardDeck: public Point 
{
private:
    //���������� ������ ����
    short int CountOfRang{ 13 };
    //���������� ������
    short int CountOfSuit{ 4 };
    //������
    std::vector<Card> Deck;

public:
    //����������� �� ���������
    CardDeck();

    //����������� � ���������� - ������������ ������ "�����"
    CardDeck(COORD CoordOfGame);

    //����������� �����������
    CardDeck(const CardDeck& obj);

    //���������� ������
    virtual ~CardDeck();

    ////������� ��������� ����
    //void SetCoord(COORD CoordOfGame);

    ////������ ��������� ����
    //COORD GetCoord();

    //������� ����
    void ShaffleDeck(); // ���������� ������

    //��������� ������
    void PrintDeck();

    Card& operator[](size_t ind);
};