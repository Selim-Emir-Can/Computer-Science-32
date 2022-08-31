#include"Player.h"
#include"Mesa.h"
#include"Game.h"
#include"globals.h"

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nGarks)
{
    if (nGarks < 0)
    {
        cout << "***** Cannot create Game with negative number of garks!" << endl;
        exit(1);
    }
    if (nGarks > MAXGARKS)
    {
        cout << "***** Trying to create Game with " << nGarks
            << " garks; only " << MAXGARKS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1 && cols == 1 && nGarks > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the garks!" << endl;
        exit(1);
    }

    // Create mesa
    m_mesa = new Mesa(rows, cols);

    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_mesa->addPlayer(rPlayer, cPlayer);

    // Populate with garks
    while (nGarks > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a gark where the player is
        if (r == rPlayer && c == cPlayer)
            continue;
        m_mesa->addGark(r, c);
        nGarks--;
    }
}

Game::~Game()
{
    delete m_mesa;
}

void Game::play()
{
    m_mesa->display();
    Player* player = m_mesa->player();
    if (player == nullptr)
        return;
    while (!player->isDead() && m_mesa->garkCount() > 0)                // u corresponds to row - 1 , col
    {                                                                   // d corresponds to row + 1 , col
        cout << endl;                                                   // l corresponds to row , col - 1
        cout << "Move (u/d/l/r/h/q or nothing): ";                      // r corresponds to row , col + 1
        string action;
        getline(cin, action);
        if (action.size() == 0)  // player stands
            player->stand();
        else
        {
            switch (action[0])
            {
            default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
            case 'q':
                return;
            case 'u':
            case 'd':
            case 'l':
            case 'r':
                player->moveOrAttack(decodeDirection(action[0]));
                break;
            case 'h':       // added by me
                string s;
                m_mesa->history().display();
                cout << "Press enter to continue.";
                getline(cin, s);
                m_mesa->display();
                continue;
            }
        }
        m_mesa->moveGarks();
        m_mesa->display();
    }
}

