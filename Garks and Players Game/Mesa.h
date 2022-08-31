#ifndef MESA_H
#define MESA_H
#include"History.h" // Needed because we include a member function that returns a type History by reference
#include"globals.h" // Needed because we need access to the values of the global constants being used

class Player;  // This is needed to let the compiler know that Player is a
             // type name, since it's mentioned in the Mesa declaration.
class Gark;  // This is needed to let the compiler know that Gark is a
             // type name, since it's mentioned in the Mesa declaration.

class Mesa
{
public:
    // Constructor/destructor
    Mesa(int nRows, int nCols);
    ~Mesa();

    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     garkCount() const;
    int     numGarksAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

    History& history(); // ADDED

    // Mutators
    bool   addGark(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackGarkAt(int r, int c, int dir);
    bool   moveGarks();

private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Gark* m_garks[MAXGARKS];
    int     m_nGarks;

    History m_history; //ADDED  need to include history because of this

};

#endif // !MESA_H