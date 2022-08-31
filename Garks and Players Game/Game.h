
#ifndef GAME_H
#define GAME_H

class Mesa;  // This is needed to let the compiler know that Mesa is a
             // type name, since it's mentioned in the Game declaration.


class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

    // Mutators
    void play();

private:
    Mesa* m_mesa;
};

#endif // !GAME_H