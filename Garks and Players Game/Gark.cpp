#include"Gark.h"
#include"Mesa.h"            // Mesa.h is #included before globals.h because it is also #included in the Mesa.h file. This prevents globals.h from being included twice
#include"globals.h"

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Gark implementation
///////////////////////////////////////////////////////////////////////////

Gark::Gark(Mesa* mp, int r, int c)
    : m_mesa(mp), m_row(r), m_col(c), m_health(INITIAL_GARK_HEALTH)
{
    if (mp == nullptr)
    {
        cout << "***** A gark must be created in some Mesa!" << endl;
        exit(1);
    }
    if (r < 1 || r > mp->rows() || c < 1 || c > mp->cols())
    {
        cout << "***** Gark created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
}

int Gark::row() const
{
    return m_row;
}

int Gark::col() const
{
    return m_col;
}

void Gark::move()
{
    // Attempt to move in a random direction; if it can't move, don't move
    int dir = randInt(0, NUMDIRS - 1);  // dir is now UP, DOWN, LEFT, or RIGHT
    m_mesa->determineNewPosition(m_row, m_col, dir);
}

bool Gark::getAttacked(int dir)  // return true if dies
{
    m_health--;
    if (m_health == 0)
        return true;
    if (!m_mesa->determineNewPosition(m_row, m_col, dir)) // determineNewPosition already accounts for pushing gark off the edge
    {
        m_health = 0;
        return true;
    }
    return false;
}
