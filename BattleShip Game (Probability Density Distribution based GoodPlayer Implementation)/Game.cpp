#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include "utility.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

bool getLineWithTwoIntegers(int& r, int& c);

class GameImpl
{
public:
    GameImpl(int nRows, int nCols);
    ~GameImpl();
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
private:
    void AskAttack(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
    int m_rows;
    int m_cols;
    Node<Ship>* m_head;
    int m_nShips;
};

GameImpl::~GameImpl()
{
    Node<Ship>* curr = m_head;
    while (curr != nullptr)
    {
        Node<Ship>* Next = curr->getLink();
        delete curr;
        curr = Next;
    }
    m_head = nullptr;
}

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols)
    : m_rows(nRows), m_cols(nCols), m_head(nullptr), m_nShips(0)
{}

int GameImpl::rows() const
{
    return(m_rows);
}

int GameImpl::cols() const
{
    return(m_cols);
}

bool GameImpl::isValid(Point p) const   // only checks if the point is on the board // other types of checks within the game must be implemented seperately
{
    return((p.r >= 0) && (p.r < rows()) && (p.c >= 0) && (p.c < cols()));
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name) //looks like the invalid inputs are handled by bool Game::addShip(int length, char symbol, string name)
{
    Ship newShip(length, symbol, name, m_nShips);
    if (m_head == nullptr)
    {
        m_head = new Node<Ship>(newShip, nullptr);
    }
    else
    {
        Node<Ship>* curr = m_head;
        while (curr->getLink() != nullptr)
        {
            curr = curr->getLink();
        }

        Node<Ship>* add = new Node<Ship>(newShip, nullptr);
        curr->setLink(add);
    }
    m_nShips++;
    return(true);
}

int GameImpl::nShips() const
{
    return(m_nShips);
}

int GameImpl::shipLength(int shipId) const
{
    if (m_head == nullptr)
    {
        return(-1);
    }
    else
    {
        Node<Ship>* curr = m_head;
        while (curr != nullptr)
        {
            Ship data = curr->getData();
            if (shipId == data.getshipId())
            {
                return(data.getlength());
            }
            curr = curr->getLink();
        }

        return(-1);
    }
}

char GameImpl::shipSymbol(int shipId) const
{
    if (m_head == nullptr)
    {
        return('?');
    }
    else
    {
        Node<Ship>* curr = m_head;
        while (curr != nullptr)
        {
            Ship data = curr->getData();
            if (shipId == data.getshipId())
            {
                return(data.getsymbol());
            }
            curr = curr->getLink();
        }

        return('?');
    }
}

string GameImpl::shipName(int shipId) const
{
    if (m_head == nullptr)
    {
        return("");
    }
    else
    {
        Node<Ship>* curr = m_head;
        while (curr != nullptr)
        {
            Ship data = curr->getData();
            if (shipId == data.getshipId())
            {
                return(data.getname());
            }
            curr = curr->getLink();
        }

        return("");
    }
}

void GameImpl::AskAttack(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{
    std::cout << p1->name() << "'s turn.  Board for " << p2->name() << ":\n";
    b2.display(p1->isHuman());
    Point point = p1->recommendAttack();
    bool shotHit = false, shipDestroyed = false;
    int shipId = 0;
    if (b2.attack(point, shotHit, shipDestroyed, shipId) == true)
    {
        if (shotHit == false)
        {
            std::cout << p1->name() << " attacked (" << point.r << "," << point.c << ") and missed, resulting in:\n";
        }
        else
        {
            if (shipDestroyed == true)
            {
                std::cout << p1->name() << " attacked (" << point.r << "," << point.c << ") and destroyed the " << shipName(shipId) << ", resulting in:\n";
            }
            else
            {
                std::cout << p1->name() << " attacked (" << point.r << "," << point.c << ") and hit something, resulting in:\n";
            }
        }
        b2.display(p1->isHuman());
    }
    else
    {
        std::cout << p1->name() << " wasted a shot at (" << point.r << "," << point.c << ").\n";
    }

    p1->recordAttackResult(point, isValid(point), shotHit, shipDestroyed, shipId);

    if (shouldPause == true)
    {
        waitForEnter();
    }
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)  // all the ships are added to the game before this function is called
{
    // if bool shouldPause == true , wait for enter after each turn
    if (p1->placeShips(b1) && p2->placeShips(b2))
    {
        while ((b1.allShipsDestroyed() == false) && (b2.allShipsDestroyed() == false))
        {
            AskAttack(p1, p2, b1, b2, shouldPause);
            if (b2.allShipsDestroyed() == true)
            {
                std::cout << p1->name() << " wins!\n";
                if (p2->isHuman())
                {
                    std::cout << "Here is where " << p2->name() << "'s ships were:\n";
                    b1.display(false);
                }
                return(p1);
            }
            AskAttack(p2, p1, b2, b1, shouldPause);
            if (b1.allShipsDestroyed() == true)
            {
                std::cout << p2->name() << " wins!\n";
                if (p1->isHuman())
                {
                    std::cout << "Here is where " << p2->name() << "'s ships were:\n";
                    b2.display(false);
                }
                return(p2);
            }
        }

        return(nullptr);
    }
    else
    {
        return(nullptr);
    }
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1 || nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1 || nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows() && length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
            << endl;
        return false;
    }
    if (!isascii(symbol) || !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
            << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X' || symbol == '.' || symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
            << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr || p2 == nullptr || nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

