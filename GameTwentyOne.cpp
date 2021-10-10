#include <iostream>

#include <fstream>
#include <sstream>
#include <conio.h>

#include <fcntl.h>
#include <io.h>

#include <string>

#include <windows.h>
#include <vector>
#include "GameTwentyOne.h"

using namespace std;

GameTwentyOne::GameTwentyOne()
{
    CurrentPoint.X = 0;
    CurrentPoint.Y = 0;
}

GameTwentyOne::GameTwentyOne(int x, int y)
{
    CurrentPoint.X = x;
    CurrentPoint.Y = y;
}

GameTwentyOne::GameTwentyOne(const GameTwentyOne& obj)
{
    CountOfRang = obj.CountOfRang;
    CountOfSuit = obj.CountOfSuit;

    CountPickedCards = obj.CountPickedCards;
    PickedCards = obj.PickedCards;

    PickedPlayer = obj.PickedPlayer;
    PlayerHand = obj.PlayerHand;

    PickedComputer = obj.PickedComputer;
    ComputerHand = obj.ComputerHand;

    Deck = obj.Deck;
}

GameTwentyOne::~GameTwentyOne() {};

vector<Card> GameTwentyOne::PlayerOrComputerAddHand(vector<Card> obj, short int& CountObj, short int TypeOfPlayer)
{
    if (CountPickedCards == CountOfRang * CountOfSuit)
        return obj;

    CountObj++;
    obj.resize(CountObj);
    this->GetCard(obj[CountObj - 1]);
    for (short int i = 0; i < CountObj; i++)
    {
        obj[i].SetCoord({ CurrentPoint.X + i * 9, CurrentPoint.Y + TypeOfPlayer * DistBetweenPlayers });
        obj[i].PrintCard();
    }
    return obj;
}

short int GameTwentyOne::PlayerOrComputerScore(vector<Card> obj, const short int CountObj) const
{
    short int SumScore{ 0 };
    short int SumAce{ 0 };
    for (short int i = 0; i < CountObj; i++)
    {
        if (obj[i].CheckRang() < 9)
            SumScore += obj[i].CheckRang() + 2;
        else if ((obj[i].CheckRang() >= 9) && (obj[i].CheckRang() < 12))
        {
            SumScore += 10;
        }
        else if (obj[i].CheckRang() == 12)
        {
            SumAce++;
        }
    }
    if (SumAce > 0)
        for (short int i = 0; i < SumAce; i++)
        {
            if ((SumScore + 11) <= (21 - (SumAce - 1)))
                SumScore += 11;
            else SumScore += 1;
        }
    return SumScore;
}

void GameTwentyOne::LoadGame()
{
    short int counterDeck = 0;

    ifstream file("game1.txt");
    string Line;

    short int VariationWrite = 0;
    PickedComputer = 0;
    PickedPlayer = 0;
    CountPickedCards = 0;

    short int Rang{ 0 };
    short int Suit{ 0 };

    while (getline(file, Line))
    {
        std::istringstream line_variation(Line);
        if (Line == "+")
        {
            VariationWrite = 1;
            continue;
        }
        else if (Line == "-")
        {
            VariationWrite = 2;
            continue;
        }
        else if (Line == "=")
        {
            VariationWrite = 3;
            continue;
        }
        if (VariationWrite != 1)
            line_variation >> Rang >> Suit;
        else line_variation >> Rang;

        if (VariationWrite == 0)
        {
            counterDeck++;
            Deck[counterDeck - 1].SetRang(Rang);
            Deck[counterDeck - 1].SetSuit(Suit);
            Deck[counterDeck - 1].SetStatus(true);
        }
        else if (VariationWrite == 1)
        {
            CountPickedCards++;
            PickedCards.resize(CountPickedCards);
            PickedCards[CountPickedCards - 1] = Rang;
        }
        else if (VariationWrite == 2)
        {
            PickedPlayer++;
            PlayerHand.resize(PickedPlayer);
            PlayerHand[PickedPlayer - 1].SetRang(Rang);
            PlayerHand[PickedPlayer - 1].SetSuit(Suit);
            PlayerHand[PickedPlayer - 1].SetStatus(true);
        }
        else if (VariationWrite == 3)
        {
            PickedComputer++;
            ComputerHand.resize(PickedComputer);
            ComputerHand[PickedComputer - 1].SetRang(Rang);
            ComputerHand[PickedComputer - 1].SetSuit(Suit);
            ComputerHand[PickedComputer - 1].SetStatus(true);
        }
    }
    ComputerHand[1].SetStatus(false);
    file.close();
    for (short int i = 0; i < PickedPlayer; i++)
    {
        PlayerHand[i].SetCoord({ CurrentPoint.X + i * 9, CurrentPoint.Y });
        PlayerHand[i].PrintCard();
    }
    for (short int i = 0; i < PickedComputer; i++)
    {
        ComputerHand[i].SetCoord({ CurrentPoint.X + i * 9, CurrentPoint.Y + DistBetweenPlayers });
        ComputerHand[i].PrintCard();
    }
}

void GameTwentyOne::SaveGame()
{
    try
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        std::ofstream file;
        file.open("game1.txt", std::ofstream::out | std::ofstream::trunc);
        if (!file)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 8 });
            wcout << "file could not be open for writing!" << endl;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 9 });
            wcout << "Possibly read-only file! " << endl;
        }
        else
        {
            for (short int i = 0; i < CountOfRang * CountOfSuit; i++)
            {
                file << to_string(Deck[i].CheckRang()) << " " << to_string(Deck[i].CheckSuit()) << endl;
            }
            file << "+" << endl;
            for (short int i = 0; i < CountPickedCards; i++)
            {
                file << to_string(PickedCards[i]) << endl;
            }

            file << "-" << endl;
            for (short int i = 0; i < PickedPlayer; i++)
            {
                file << to_string(PlayerHand[i].CheckRang()) << " " << to_string(PlayerHand[i].CheckSuit()) << endl;
            }

            file << "=" << endl;
            for (short int i = 0; i < PickedComputer; i++)
            {
                file << to_string(ComputerHand[i].CheckRang()) << " " << to_string(ComputerHand[i].CheckSuit()) << endl;
            }
            file.close();
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 8 });
            wcout << "Game is saved in 'game1.txt'            ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 9 });
            wcout << "                           ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 9 });
        }
    }
    catch (...)
    {
        cerr << "There was an error: " << endl;
    }
}

bool GameTwentyOne::GetCard(Card& Example) //Взять карту из колоды
{
    if (CountPickedCards == (CountOfRang * CountOfSuit))
        return false;

    bool Find_Flag{ false };
    while (true)
    {
        if (CountPickedCards == 0)
        {
            PickedCards.resize(1);
            CountPickedCards++;
            PickedCards[CountPickedCards - 1] = CountPickedCards;
            Example = Deck[CountPickedCards - 1];
            return true;
        }
        else
        {
            Find_Flag = false;
            if (Find_Flag == true)
                continue;
            CountPickedCards++;
            PickedCards.resize(CountPickedCards);
            PickedCards[CountPickedCards - 1] = CountPickedCards;
            Example = Deck[CountPickedCards - 1];
            return true;
        }
    }
    return false;
}

void GameTwentyOne::PreparationStartGame()
{
    CountPickedCards = 0;

    PickedPlayer = 0;
    PickedComputer = 0;

    PlayerHand.resize(2);
    ComputerHand.resize(2);
    for (short int i = 0; i < 2; i++)
    {
        GetCard(PlayerHand[PickedPlayer]);
        GetCard(ComputerHand[PickedComputer]);
        PickedPlayer++;
        PickedComputer++;
        if (i == 1)
            ComputerHand[i].FlipCard();
        PlayerHand[i].SetCoord({ CurrentPoint.X + i * 9, CurrentPoint.Y });
        PlayerHand[i].PrintCard();
        ComputerHand[i].SetCoord({ CurrentPoint.X + i * 9, CurrentPoint.Y + DistBetweenPlayers });
        ComputerHand[i].PrintCard();
    }
}

short int GameTwentyOne::CheckedScore(short int NumberOfPlayer) const
{
    short int Tmp_Result{ 0 };
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (NumberOfPlayer == 0)
    {
        Tmp_Result = PlayerOrComputerScore(PlayerHand, PickedPlayer);
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 5 });
        wcout << "You're score: " << Tmp_Result << endl;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 6 });
        wcout << "Press 'y' to get another card" << endl;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 7 });
        wcout << "Press 'n' to finish the set of cards";
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 8 });
    }
    else if (NumberOfPlayer == 1)
    {
        Tmp_Result = PlayerOrComputerScore(ComputerHand, PickedComputer);
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + DistBetweenPlayers + 5 });
        wcout << "Opponent score: " << Tmp_Result;
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + DistBetweenPlayers + 6 });
    }

    return Tmp_Result;
}

bool GameTwentyOne::AddHand(short int NumberOfPlayer)
{
    if (NumberOfPlayer == 0)
    {
        PlayerHand = PlayerOrComputerAddHand(PlayerHand, PickedPlayer, NumberOfPlayer);
    }
    else if (NumberOfPlayer == 1)
    {
        ComputerHand = PlayerOrComputerAddHand(ComputerHand, PickedComputer, NumberOfPlayer);
    }
    return true;
}

void GameTwentyOne::OpenComputerCards()
{
    ComputerHand[1].FlipCard();
    for (short int i = 0; i < PickedComputer; i++)
    {
        ComputerHand[i].SetCoord({ CurrentPoint.X + i * 9, CurrentPoint.Y + DistBetweenPlayers });
        ComputerHand[i].PrintCard();
    }
}

void GameTwentyOne::ClearUnderScore()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 6 });
    wcout << "Your turn is over...            ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 7 });
    wcout << "                                    ";
}

bool GameTwentyOne::Game() 
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);

    const short int Player_Id = 0;
    const short int Computer_Id = 1;
    while (true)
    {
        system("cls");
        string filepath{ "game1.txt" };
        std::ifstream fin(filepath.c_str());
        //Deck.SetCoord({ CurrentPoint.X, CurrentPoint.Y + 30 });
        //Deck.PrintDeck();
        if (fin.is_open())
        {
            wcout << "File with save detected. Load game? (y - yes, n - no): ";
            Deck.SetCoord({ CurrentPoint.X, CurrentPoint.Y + 1 });

            char ChooseLoad;
            do
            {
                ChooseLoad = _getch();
                if (ChooseLoad == 'y')
                {
                    wcout << "Game loaded from 'game1.txt'...";
                    LoadGame();
                }
                else if (ChooseLoad == 'n')
                {
                    Deck.ShaffleDeck();
                    PreparationStartGame();
                }
            } while ((ChooseLoad != 'y') && (ChooseLoad != 'n'));
        }
        else
        {
            Deck.ShaffleDeck();
            PreparationStartGame();
        }
        fin.close();


        //DeckGame.PrintDeck({0,18});

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

        short int SumPlayer = CheckedScore(Player_Id);

        bool Game_Result{ false };

        while (SumPlayer < 21)
        {
            char ChooseChar = _getch();
            SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 18 });
            if (ChooseChar == 'y')
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 8 });
                wcout << "                                      " << endl;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 9 });
                wcout << "                                      " << endl;
                if (AddHand(Player_Id) == false)
                {
                    wcout << "Cards is out..." << endl;
                    break;
                }
                else
                {
                    SumPlayer = CheckedScore(Player_Id);
                    if (SumPlayer == 21)
                    {
                        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 17 });
                        break;
                    }
                    else if (SumPlayer > 21)
                    {
                        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 17 });
                        wcout << "Your loser!" << endl;
                        Game_Result = true;
                        break;
                    }
                }
            }
            else if (ChooseChar == 'n')
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 8 });
                wcout << "                                      " << endl;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { CurrentPoint.X, CurrentPoint.Y + 9 });
                wcout << "                                      " << endl;
                break;
            }
            else if (ChooseChar == 's')
            {
                SaveGame();
            }
        }

        ClearUnderScore();
        OpenComputerCards();
        short int SumComputer = CheckedScore(Computer_Id);
        if (Game_Result == false)
        {
            while ((SumComputer <= SumPlayer) && (SumComputer < 17))
            {
                AddHand(Computer_Id);
                SumComputer = CheckedScore(Computer_Id);
            }
            SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 17 });
            if ((SumComputer < SumPlayer) || (SumComputer > 21))
                wcout << "Your winner!" << endl;
            else if (SumComputer > SumPlayer)
                wcout << "Your loser!" << endl;
            else
                wcout << "Tie!" << endl;
        }
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 18 });
        wcout << "Game is over. Press 'y' to Retry, 'n' to exit.";
        SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 19 });
        char RestartOrExit{ ' ' };
        while (((RestartOrExit = _getch()) != 'y') || (RestartOrExit != 'n'))
        {
            if (RestartOrExit == 'n')
            {
                SetConsoleCursorPosition(handle, { CurrentPoint.X, CurrentPoint.Y + 19 });
                wcout << "GoodLuck!" << endl;
                return 0;
            }
            else if (RestartOrExit == 'y')
                break;
        }
    }
};