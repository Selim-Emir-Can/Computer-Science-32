// garks.cpp

#include"Gark.h"
#include"Player.h"
#include"Mesa.h"        // Mesa.h is #included before globals.h because it is also #included in the Mesa.h file. This prevents globals.h from being included twice
#include"globals.h"
#include"Game.h"

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}