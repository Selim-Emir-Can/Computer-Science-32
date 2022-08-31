
#ifndef PLAYER_H
#define PLAYER_H

class Mesa;  // This is needed to let the compiler know that Mesa is a
             // type name, since it's mentioned in the Player declaration.


class Player
{
public:
    // Constructor
    Player(Mesa* mp, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

    // Mutators
    void   stand();
    void   moveOrAttack(int dir);
    void   setDead();

private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

#endif // !PLAYER_H