#include "Board.h"
#include "Game.h"
#include"globals.h"
#include"utility.h"
#include <iostream>
#include <string>

using namespace std;

class BoardImpl
{
public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
private:
    char m_board[MAXROWS][MAXCOLS];
    const Game& m_game;
};

BoardImpl::BoardImpl(const Game& g) // may want to change the initialization of m_board
    : m_game(g)
{
    for (int r = 0; r < MAXROWS; r++)
    {
        for (int c = 0; c < MAXCOLS; c++)
        {
            m_board[r][c] = '.';
        }
    }
}

void BoardImpl::clear()
{
    for (int r = 0; r < m_game.rows(); r++)
    {
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (m_board[r][c] != '.')
            {
                m_board[r][c] = '.';
            }
        }
    }
}

void BoardImpl::block()
{
    int numberblocked = 0;
    int mustblock = (m_game.rows() * m_game.cols()) / 2;
    // Block cells with 50% probability

    while (numberblocked != mustblock)
    {
        for (int r = 0; r < m_game.rows(); r++)
        {
            for (int c = 0; c < m_game.cols(); c++)
            {
                if (numberblocked == mustblock)
                {
                    return;
                }

                if ((randInt(2) == 0) && (m_board[r][c] == '.'))
                {
                    m_board[r][c] = '#';
                    numberblocked++;
                }
            }
        }
    }
}

void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.rows(); r++)
    {
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (m_board[r][c] == '#')
            {
                m_board[r][c] = '.';
            }
        }
    }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    if ((shipId >= m_game.nShips()) || (m_game.isValid(topOrLeft) == false))    // 1. The shipId is invalid
    {
        return(false);
    }
    Ship newShip(m_game.shipLength(shipId), m_game.shipSymbol(shipId), m_game.shipName(shipId), shipId);

    for (int r = 0; r < m_game.rows(); r++) // 5. The ship with that ship ID has previously been placed on this Board and not yet been unplaced since its most recent placement.
    {
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (m_board[r][c] == newShip.getsymbol())
            {
                return(false);
            }
        }
    }
    
    if (dir == VERTICAL)    // topOrLeft is the top of ship
    {
        if ((m_game.rows() - topOrLeft.r) < newShip.getlength()) // 2. The ship would be partly or fully outside the board.
        {
            return(false);
        }

        for (int i = 0; i < newShip.getlength(); i++)   // 3. The ship would overlap an already-placed ship. // 4 .The ship would overlap one or more positions that were blocked by a previous call to the block function.
        {
            if (m_board[(topOrLeft.r + i)][topOrLeft.c] != '.')
            {
                return(false);
            }
        }

        for (int i = 0; i < newShip.getlength(); i++)
        {
            m_board[(topOrLeft.r + i)][topOrLeft.c] = newShip.getsymbol();
        }
        

        return(true);
    }

    if (dir == HORIZONTAL)  // topOrLeft is the left of ship
    {
        if ((m_game.cols() - topOrLeft.c) < newShip.getlength())    // 2. The ship would be partly or fully outside the board.
        {
            return(false);
        }

        for (int i = 0; i < newShip.getlength(); i++)    // 3. The ship would overlap an already-placed ship. // 4 .The ship would overlap one or more positions that were blocked by a previous call to the block function.
        {
            if (m_board[topOrLeft.r][(topOrLeft.c + i)] != '.')
            {
                return(false);
            }
        }

        for (int i = 0; i < newShip.getlength(); i++)
        {
            m_board[topOrLeft.r][(topOrLeft.c + i)] = newShip.getsymbol();
        }

        return(true);
    }  

    return(false);
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    if ((shipId >= m_game.nShips()) || (m_game.isValid(topOrLeft) == false))    // 1. The shipId is invalid
    {
        return(false);
    }
    Ship newShip(m_game.shipLength(shipId), m_game.shipSymbol(shipId), m_game.shipName(shipId), shipId);
    if (dir == VERTICAL)    // topOrLeft is the top of ship
    {
        if ((m_game.rows() - topOrLeft.r) < newShip.getlength()) // 2. The ship would be partly or fully outside the board.
        {
            return(false);
        }

        for (int i = 0; i < newShip.getlength(); i++)  //2. The board does not contain the entire ship at the indicated locations.
        {
            if (m_board[(topOrLeft.r + i)][topOrLeft.c] != newShip.getsymbol())
            {
                return(false);
            }
        }

        for (int i = 0; i < newShip.getlength(); i++)
        {
            m_board[(topOrLeft.r + i)][topOrLeft.c] = '.';
        }

        return(true);
    }

    if (dir == HORIZONTAL)  // topOrLeft is the left of ship
    {
        if ((m_game.cols() - topOrLeft.c) < newShip.getlength())    // 2. The ship would be partly or fully outside the board.
        {
            return(false);
        }

        for (int i = 0; i < newShip.getlength(); i++)    //2. The board does not contain the entire ship at the indicated locations.
        {
            if (m_board[topOrLeft.r][(topOrLeft.c + i)] != newShip.getsymbol())
            {
                return(false);
            }
        }

        for (int i = 0; i < newShip.getlength(); i++)
        {
            m_board[topOrLeft.r][(topOrLeft.c + i)] = '.';
        }

        return(true);
    }

    return(false);
}

void BoardImpl::display(bool shotsOnly) const
{
    /*
    First line: The function must print two spaces followed by the digits for each
column, starting at 0, followed by a newline. You may assume there will be no
more than 10 columns.
2. Remaining lines: The function must print a digit specifying the row number,
starting at 0, followed by a space, followed by the contents of the current row,
followed by a newline. You may assume there will be no more than 10 rows. In
each of the positions of the row, use the following characters to represent the
playing field:
    */

    std::cout << "  "; // two spaces
    for (int i = 0; i < m_game.cols(); i++)
    {
        std::cout << i;
    }
    std::cout << std::endl;
    if (shotsOnly == true)
    {
        for (int r = 0; r < m_game.rows(); r++)
        {
            std::cout << r << " ";
            for (int c = 0; c < m_game.cols(); c++)
            {
                if ((m_board[r][c] != 'o') && (m_board[r][c] != '.') && (m_board[r][c] != 'X'))
                {
                    std::cout << '.';
                }
                else
                {
                    std::cout << m_board[r][c];
                }
            }
            std::cout << std::endl;
        }
    }
    else
    {
        for (int r = 0; r < m_game.rows(); r++)
        {
            std::cout << r << " ";
            for (int c = 0; c < m_game.cols(); c++)
            {
                std::cout << m_board[r][c];
            }
            std::cout << std::endl;
        }
    }
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    if (m_game.isValid(p) == false)
    {
        shipId = -1;
        return(false);
    }

    if ((m_board[p.r][p.c] == 'X') || (m_board[p.r][p.c] == 'o'))
    {
        shipId = -1;
        return(false);
    }

    if (m_board[p.r][p.c] == '.')
    {
        shotHit = false;
        m_board[p.r][p.c] = 'o';
    }
    else // we have a ship
    {
        shotHit = true;
        char symbol = m_board[p.r][p.c];
        m_board[p.r][p.c] = 'X';
        for (int i = 0; i < m_game.nShips(); i++)
        {
            if (m_game.shipSymbol(i) == symbol)
            {
                shipId = i;
                break;
            }
        }

        for (int r = 0; r < m_game.rows(); r++)
        {
            for (int c = 0; c < m_game.cols(); c++)
            {
                if (m_board[r][c] == symbol)
                {
                    shipDestroyed = false;
                    return(true);
                }
            }
        }
        shipDestroyed = true;
    }

    return(true);
}

bool BoardImpl::allShipsDestroyed() const
{
    for (int r = 0; r < m_game.rows(); r++)
    {
        for (int c = 0; c < m_game.cols(); c++)
        {
            if ((m_board[r][c] != 'X') && (m_board[r][c] != '.') && (m_board[r][c] != 'o'))
            {
                return(false);
            }
        }
    }

    return(true);
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
