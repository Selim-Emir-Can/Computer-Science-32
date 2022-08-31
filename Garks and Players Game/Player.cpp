#include"Player.h"
#include"Mesa.h"        // we need access to the implementation of both classes

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>

using namespace std;



///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Mesa* mp, int r, int c)
    : m_mesa(mp), m_row(r), m_col(c), m_age(0), m_dead(false)
{
    if (mp == nullptr)
    {
        cout << "***** The player must be created in some Mesa!" << endl;
        exit(1);
    }
    if (r < 1 || r > mp->rows() || c < 1 || c > mp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::moveOrAttack(int dir)      // Changed the original function implementation
{                                       // Function now uses tells m_mesa 's m_history to record when a gark is attacked but not killed 
    int tempgarkcount = 0; // New code

    m_age++;
    int r = m_row;
    int c = m_col;
    if (m_mesa->determineNewPosition(r, c, dir))
    {
        if (m_mesa->numGarksAt(r, c) > 0)
        {
            tempgarkcount = m_mesa->garkCount();  // New code
            
            m_mesa->attackGarkAt(r, c, dir);

            if (tempgarkcount == m_mesa->garkCount()) // All of the if statement is new code
            {
                // u corresponds to row - 1 , col
            // d corresponds to row + 1 , col
            // l corresponds to row , col - 1
            // r corresponds to row , col + 1 
                switch (dir)
                {
                case(LEFT):
                    m_mesa->history().record(m_mesa->player()->row(), (m_mesa->player()->col() - 1));
                    break;
                case(RIGHT):
                    m_mesa->history().record(m_mesa->player()->row(), (m_mesa->player()->col() + 1));
                    break;
                case(DOWN):
                    m_mesa->history().record((m_mesa->player()->row() + 1), m_mesa->player()->col());
                    break;
                case(UP):
                    m_mesa->history().record((m_mesa->player()->row() - 1), m_mesa->player()->col());
                    break;
                default:
                    break;
                } // relies on the fact that player stays stationary after attack
            }
            tempgarkcount = 0;
        }
        else
        {
            m_row = r;
            m_col = c;
        }
    }
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}