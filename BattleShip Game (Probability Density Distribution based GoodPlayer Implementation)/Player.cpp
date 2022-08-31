#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include"utility.h"
#include <iostream>
#include <string>

using namespace std;

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
        bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
    : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
    // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if (!b.placeShip(Point(k, 0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
    bool /* shotHit */, bool /* shipDestroyed */,
    int /* shipId */)
{
    // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
    // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class HumanPlayer : public Player
{
public:
    HumanPlayer(string nm, const Game& g);
    virtual bool isHuman() const;
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
private:
};

HumanPlayer::HumanPlayer(string nm, const Game& g)
    : Player(nm, g)
{}

bool HumanPlayer::isHuman() const
{
    return(true);
}

bool HumanPlayer::placeShips(Board& b)
{
    std::string direction = "";
    std::cout << name() << " must place " << game().nShips() << " ships.\n";
    for (int i = 0; i < game().nShips(); i++)
    {
        b.display(false);
        std::cout << "Enter h or v for direction of " << game().shipName(i) << " (length " << game().shipLength(i) << "): ";
        std::getline(std::cin, direction);
        while ((direction.size() == 0) || ((direction.at(0) != 'h') && (direction.at(0) != 'v')))
        {
            std::cout << "Direction must be h or v.\n";
            std::cout << "Enter h or v for direction of " << game().shipName(i) << " (length " << game().shipLength(i) << "): ";
            std::getline(std::cin, direction);
        }

        Direction dir;
        if (direction.at(0) == 'h')
        {
            dir = HORIZONTAL;
        }
        else // direction.at(0) == 'v'
        {
            dir = VERTICAL;
        }

        std::cout << "Enter row and column of leftmost cell (e.g., 3 5): ";
        int r = 0, c = 0;
        bool getLine = getLineWithTwoIntegers(r, c);
        Point point(r, c);
        while ((!getLine) || (b.placeShip(point, i, dir) == false)) // possible error might cause placeship to trigger twice if c++ doesn't short circuit
        {
            if (!getLine)
            {
                std::cout << "You must enter two integers.\n";
            }
            else // b.placeShip(point, i, dir) == false
            {
                std::cout << "The ship can not be placed there.\n";
            }

            std::cout << "Enter row and column of leftmost cell (e.g., 3 5): ";
            getLine = getLineWithTwoIntegers(r, c);
            point.r = r;
            point.c = c;
        }
        b.placeShip(point, i, dir); // possible error might cause placeship to trigger twice
    }
    return(true);
}

Point HumanPlayer::recommendAttack()
{
    int r = 0, c = 0;
    std::cout << "Enter the row and column to attack (e.g., 3 5): ";
    bool getLine = getLineWithTwoIntegers(r, c);
    Point point(r, c);
    while (!getLine)
    {
        std::cout << "You must enter two integers.\n";
        std::cout << "Enter the row and column to attack (e.g., 3 5): ";
        getLine = getLineWithTwoIntegers(r, c);
        point.r = r;
        point.c = c;
    }
    return(point);
}

void HumanPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{}

void HumanPlayer::recordAttackByOpponent(Point p)
{}

//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class MediocrePlayer : public Player
{
public:
    ~MediocrePlayer();
    MediocrePlayer(string nm, const Game& g);
    //std::string name() const { return m_name; }
    //const Game& game() const { return m_game; }
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    
private:
    bool recursivePlace(Board& b, int nShips, Point point, bool backtrack);
    bool recursivePlace(Board& b, int nShips, Point point, bool backtrack, int& depth);
    int Lvalid(Point point);
    int Rvalid(Point point);
    int Uvalid(Point point);
    int Dvalid(Point point);
    bool doneCross();
    int m_state;
    Node<Point>* m_head;
    Point m_lastCellAttacked;
    Point m_centerOfCross;
    int u_size;
    int d_size;
    int l_size;
    int r_size;
    Node<Point>* m_cross;
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
    : Player(nm, g), m_state(1), m_head(nullptr), m_lastCellAttacked(0, 0), m_centerOfCross(0,0), u_size(0), d_size(0), l_size(0), r_size(0), m_cross(nullptr)
{

}

MediocrePlayer::~MediocrePlayer()
{
    Node<Point>* curr = m_head;
    while (curr != nullptr)
    {
        Node<Point>* Next = curr->getLink();
        delete curr;
        curr = Next;
    }
    m_head = nullptr;

    Node<Point>* surr = m_cross;
    while (surr != nullptr)
    {
        Node<Point>* Next = surr->getLink();
        delete surr;
        surr = Next;
    }
    m_cross = nullptr;
}

int MediocrePlayer::Lvalid(Point point)
{
    int i = 0;
    point.c--;
    while ((i < 4) && (game().isValid(point)))
    {
        i++;
        point.c--;
    }

    return(i);
}

int MediocrePlayer::Rvalid(Point point)
{
    int i = 0;
    point.c++;
    while ((i < 4) && (game().isValid(point)))
    {
        point.c++;
        i++;
    }

    return(i);
}

int MediocrePlayer::Uvalid(Point point)
{
    int i = 0;
    point.r--;
    while ((i < 4) && (game().isValid(point)))
    {
        point.r--;
        i++;
    }

    return(i);
}

int MediocrePlayer::Dvalid(Point point)
{
    int i = 0;
    point.r++;
    while ((i < 4) && (game().isValid(point)))
    {
        i++;
        point.r++;
    }

    return(i);
}

bool MediocrePlayer::doneCross()
{
    Node<Point>* curr = m_cross;
    int i = 0;
    while (curr != nullptr)
    {
        i++;
        curr = curr->getLink();
    }
    if (i >= (u_size + d_size + l_size + r_size))   // I don't know if this makes my mediocre player not fit in with the spec
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

bool MediocrePlayer::recursivePlace(Board& b, int nShips, Point point, bool backtrack)
{
    if (nShips == game().nShips())
    {
        return(true);
    }

    if (backtrack == false)
    {
        if ((point.r == (game().rows() - 1)) && (point.c == (game().cols() - 1)))
        {
            if (nShips == 0)
            {
                return(false);
            }

            if ((nShips == (game().nShips() - 1)) && (b.placeShip(point, nShips, HORIZONTAL) == true))  // ship of length one at the last spot
            {
                return(true);
            }

            backtrack = true;
            recursivePlace(b, (nShips - 1), point, backtrack);
        }

        if (b.placeShip(point, nShips, VERTICAL) == true)   // ALWAYS PLACES VERTICALLY IF IT CAN
        {
            Point start(0, 0);
            return(recursivePlace(b, (nShips + 1), start, backtrack));
        }

        if (b.placeShip(point, nShips, HORIZONTAL) == true)
        {
            Point start(0, 0);
            return(recursivePlace(b, (nShips + 1), start, backtrack));
        }


        if (point.c == (game().cols() - 1))
        {
            point.r = point.r + 1;
            point.c = 0;
        }
        else
        {
            point.c = point.c + 1;
        }
        return(recursivePlace(b, nShips, point, backtrack));
    }
    else
    {
        if (b.unplaceShip(point, nShips, VERTICAL) == true)
        {
            if (b.placeShip(point, nShips, HORIZONTAL) == true)
            {
                nShips++;
                Point start(0, 0);
                backtrack = false;
                return(recursivePlace(b, nShips, start, backtrack));
            }

            if (point.r == (game().rows() - 1))
            {
                if (point.c == (game().cols() - 1))
                {
                    ;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }
            else
            {
                if (point.c == (game().cols() - 1))
                {
                    point.r = point.r + 1;
                    point.c = 0;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }

            backtrack = false;
            return(recursivePlace(b, nShips, point, backtrack));
        }

        if (b.unplaceShip(point, nShips, HORIZONTAL) == true)
        {
            if (point.r == (game().rows() - 1))
            {
                if (point.c == (game().cols() - 1))
                {
                    ;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }
            else
            {
                if (point.c == (game().cols() - 1))
                {
                    point.r = point.r + 1;
                    point.c = 0;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }

            backtrack = false;
            return(recursivePlace(b, nShips, point, backtrack));
        }

        if (point.c == 0)
        {
            if (point.r == 0)   // this case is not possible
            {
                return(false);
            }
            else
            {
                point.c = game().cols() - 1;
                point.r = point.r - 1;
            }
        }
        else
        {
            point.c = point.c - 1;
        }

        return(recursivePlace(b, nShips, point, backtrack));
    }
}

bool  MediocrePlayer::recursivePlace(Board& b, int nShips, Point point, bool backtrack, int& depth)
{
    depth++;
    if (depth == 200)
    {
        return(false);
    }
    if (nShips == game().nShips())
    {
        return(true);
    }

    if (backtrack == false)
    {
        if ((point.r == (game().rows() - 1)) && (point.c == (game().cols() - 1)))
        {
            if (nShips == 0)
            {
                return(false);
            }

            if ((nShips == (game().nShips() - 1)) && (b.placeShip(point, nShips, HORIZONTAL) == true))  // ship of length one at the last spot
            {
                return(true);
            }

            backtrack = true;
            recursivePlace(b, (nShips - 1), point, backtrack, depth);
        }

        if (b.placeShip(point, nShips, VERTICAL) == true)   // ALWAYS PLACES VERTICALLY IF IT CAN
        {
            Point start(0, 0);
            return(recursivePlace(b, (nShips + 1), start, backtrack, depth));
        }

        if (b.placeShip(point, nShips, HORIZONTAL) == true)
        {
            Point start(0, 0);
            return(recursivePlace(b, (nShips + 1), start, backtrack, depth));
        }


        if (point.c == (game().cols() - 1))
        {
            point.r = point.r + 1;
            point.c = 0;
        }
        else
        {
            point.c = point.c + 1;
        }
        return(recursivePlace(b, nShips, point, backtrack, depth));
    }
    else
    {
        if (b.unplaceShip(point, nShips, VERTICAL) == true)
        {
            if (b.placeShip(point, nShips, HORIZONTAL) == true)
            {
                nShips++;
                Point start(0, 0);
                backtrack = false;
                return(recursivePlace(b, nShips, start, backtrack, depth));
            }

            if (point.r == (game().rows() - 1))
            {
                if (point.c == (game().cols() - 1))
                {
                    ;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }
            else
            {
                if (point.c == (game().cols() - 1))
                {
                    point.r = point.r + 1;
                    point.c = 0;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }

            backtrack = false;
            return(recursivePlace(b, nShips, point, backtrack, depth));
        }

        if (b.unplaceShip(point, nShips, HORIZONTAL) == true)
        {
            if (point.r == (game().rows() - 1))
            {
                if (point.c == (game().cols() - 1))
                {
                    ;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }
            else
            {
                if (point.c == (game().cols() - 1))
                {
                    point.r = point.r + 1;
                    point.c = 0;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }

            backtrack = false;
            return(recursivePlace(b, nShips, point, backtrack, depth));
        }

        if (point.c == 0)
        {
            if (point.r == 0)   // this case is not possible
            {
                return(false);
            }
            else
            {
                point.c = game().cols() - 1;
                point.r = point.r - 1;
            }
        }
        else
        {
            point.c = point.c - 1;
        }

        return(recursivePlace(b, nShips, point, backtrack, depth));
    }
}

bool MediocrePlayer::placeShips(Board& b)
{
    int depth = 0;
    b.block();
    Point point(0, 0);
    bool backtrack = false;
    int i = 0;
    while ((recursivePlace(b, 0, point, backtrack, depth) == false) && (i < 50))
    {
        depth = 0;
        b.clear();
        b.block();
        i++;
    }
    b.unblock();
    if (i >= 50)
    {
        return(false);
    }
    else
    {
        return(true);
    }    
}

void MediocrePlayer::recordAttackByOpponent(Point p)
{}

Point MediocrePlayer::recommendAttack()
{
    //In state 1, recommendAttack returns a randomly chosen position on the board that has not been chosen before.
    if (m_state == 1)
    {
        if (m_head == nullptr)
        {
            Point point(game().randomPoint());
            m_head = new Node<Point>(point, nullptr);
            return(point);
        }
        else
        {
            Node<Point>* curr = m_head;
            Point point(0, 0);
            bool exit = false;
            bool success = false;
            while (!success)
            {
                curr = m_head;
                Point temp(game().randomPoint());
                point.r = temp.r;
                point.c = temp.c;
                while (curr != nullptr)
                {
                    if ((curr->getData().r == point.r) && (curr->getData().c == point.c))
                    {
                        exit = true;
                        break;
                    }
                    curr = curr->getLink();
                }

                if (curr == nullptr)
                {
                    success = true;
                }

                if (exit)
                {
                    exit = false;
                    success = false;    // just in case
                }
            }

            curr = m_head;
            while (curr->getLink() != nullptr)
            {
                curr = curr->getLink();
            }
            Node<Point>* add = new Node<Point>(point, nullptr);
            curr->setLink(add);
            return(point);
        }
    }
    else // (m_state == 2)
    {
        if (doneCross())
        {
            Node<Point>* surr = m_cross;
            while (surr != nullptr)
            {
                Node<Point>* Next = surr->getLink();
                delete surr;
                surr = Next;
            }
            m_cross = nullptr;
            m_state = 1;
            if (m_head == nullptr)
            {
                Point point(game().randomPoint());
                m_head = new Node<Point>(point, nullptr);
                return(point);
            }
            else
            {
                Node<Point>* curr = m_head;
                Point point(0, 0);
                bool exit = false;
                bool success = false;
                while (!success)
                {
                    curr = m_head;
                    Point temp(game().randomPoint());
                    point.r = temp.r;
                    point.c = temp.c;
                    while (curr != nullptr)
                    {
                        if ((curr->getData().r == point.r) && (curr->getData().c == point.c))
                        {
                            exit = true;
                            break;
                        }
                        curr = curr->getLink();
                    }

                    if (curr == nullptr)
                    {
                        success = true;
                    }

                    if (exit)
                    {
                        exit = false;
                        success = false;    // just in case
                    }
                }

                curr = m_head;
                while (curr->getLink() != nullptr)
                {
                    curr = curr->getLink();
                }
                Node<Point>* add = new Node<Point>(point, nullptr);
                curr->setLink(add);
                return(point);
            }
        }
        ////////////////////////////////////////////////////////////
        bool success = false;
        bool exited = false;
        int count = 0;
        while ((!success) && (count < 100))
        {
            count++;
            if ((randInt(2) == 0) && ((u_size > 0) || (d_size > 0)))  // vertical
            {
                if ((randInt(2) == 0) && (u_size > 0))   // up
                {
                    int i = randInt(u_size) + 1;
                    Point temp((m_centerOfCross.r - i), m_centerOfCross.c);
                    if (m_head == nullptr)
                    {
                        m_head = new Node<Point>(temp, nullptr);
                        if (m_cross == nullptr)
                        {
                            m_cross = new Node<Point>(temp, nullptr);
                        }
                        else
                        {
                            Node<Point>* surr = m_cross;
                            while (surr->getLink() != nullptr)
                            {
                                surr = surr->getLink();
                            }

                            Node<Point>* add = new Node<Point>(temp, nullptr);
                            surr->setLink(add);
                        }
                        success = true;
                        return(temp);
                    }
                    else
                    {
                        Node<Point>* curr = m_head;
                        while (curr->getLink() != nullptr)
                        {
                            if ((curr->getData().r == temp.r) && (curr->getData().c == temp.c))
                            {
                                if (m_cross == nullptr)
                                {
                                    m_cross = new Node<Point>(temp, nullptr);
                                }
                                else
                                {
                                    Node<Point>* surr = m_cross;
                                    while (surr->getLink() != nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            break;
                                        }
                                        surr = surr->getLink();
                                    }

                                    if (surr->getLink() == nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            Node<Point>* add = new Node<Point>(temp, nullptr);
                                            surr->setLink(add);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                exited = true;
                                break;
                            }
                            curr = curr->getLink();
                        }

                        if (curr->getLink() == nullptr)
                        {
                            if ((curr->getData().r == temp.r) && (curr->getData().c == temp.c))
                            {
                                if (m_cross == nullptr)
                                {
                                    m_cross = new Node<Point>(temp, nullptr);
                                }
                                else
                                {
                                    Node<Point>* surr = m_cross;
                                    while (surr->getLink() != nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            break;
                                        }
                                        surr = surr->getLink();
                                    }

                                    if (surr->getLink() == nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            Node<Point>* add = new Node<Point>(temp, nullptr);
                                            surr->setLink(add);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                exited = true;
                            }
                        }
                        else
                        {
                            ; // already set exited == true
                        }

                        if (exited == true)
                        {
                            exited = false;
                        }
                        else
                        {
                            Node<Point>* curr = m_head;
                            while (curr->getLink() != nullptr)
                            {
                                curr = curr->getLink();
                            }
                            Node<Point>* add = new Node<Point>(temp, nullptr);
                            curr->setLink(add);
                            if (m_cross == nullptr)
                            {
                                m_cross = new Node<Point>(temp, nullptr);
                            }
                            else
                            {
                                Node<Point>* surr = m_cross;
                                while (surr->getLink() != nullptr)
                                {
                                    surr = surr->getLink();
                                }

                                Node<Point>* add = new Node<Point>(temp, nullptr);
                                surr->setLink(add);
                            }
                            success = true;
                            return(temp);
                        }

                    }
                }
                else if (d_size > 0) // down
                {
                    int i = randInt(d_size) + 1;
                    Point temp((m_centerOfCross.r + i), m_centerOfCross.c);
                    if (m_head == nullptr)
                    {
                        m_head = new Node<Point>(temp, nullptr);
                        if (m_cross == nullptr)
                        {
                            m_cross = new Node<Point>(temp, nullptr);
                        }
                        else
                        {
                            Node<Point>* surr = m_cross;
                            while (surr->getLink() != nullptr)
                            {
                                surr = surr->getLink();
                            }

                            Node<Point>* add = new Node<Point>(temp, nullptr);
                            surr->setLink(add);
                        }
                        success = true;
                        return(temp);
                    }
                    else
                    {
                        Node<Point>* curr = m_head;
                        while (curr->getLink() != nullptr)
                        {
                            if ((curr->getData().r == temp.r) && (curr->getData().c == temp.c))
                            {
                                if (m_cross == nullptr)
                                {
                                    m_cross = new Node<Point>(temp, nullptr);
                                }
                                else
                                {
                                    Node<Point>* surr = m_cross;
                                    while (surr->getLink() != nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            break;
                                        }
                                        surr = surr->getLink();
                                    }

                                    if (surr->getLink() == nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            Node<Point>* add = new Node<Point>(temp, nullptr);
                                            surr->setLink(add);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                exited = true;
                                break;
                            }
                            curr = curr->getLink();
                        }

                        if (curr->getLink() == nullptr)
                        {
                            if ((curr->getData().r == temp.r) && (curr->getData().c == temp.c))
                            {
                                if (m_cross == nullptr)
                                {
                                    m_cross = new Node<Point>(temp, nullptr);
                                }
                                else
                                {
                                    Node<Point>* surr = m_cross;
                                    while (surr->getLink() != nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            break;
                                        }
                                        surr = surr->getLink();
                                    }

                                    if (surr->getLink() == nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            Node<Point>* add = new Node<Point>(temp, nullptr);
                                            surr->setLink(add);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                exited = true;
                            }
                        }
                        else
                        {
                            ; // already set exited == true
                        }

                        if (exited == true)
                        {
                            exited = false;
                        }
                        else
                        {
                            Node<Point>* curr = m_head;
                            while (curr->getLink() != nullptr)
                            {
                                curr = curr->getLink();
                            }
                            Node<Point>* add = new Node<Point>(temp, nullptr);
                            curr->setLink(add);
                            if (m_cross == nullptr)
                            {
                                m_cross = new Node<Point>(temp, nullptr);
                            }
                            else
                            {
                                Node<Point>* surr = m_cross;
                                while (surr->getLink() != nullptr)
                                {
                                    surr = surr->getLink();
                                }

                                Node<Point>* add = new Node<Point>(temp, nullptr);
                                surr->setLink(add);
                            }
                            success = true;
                            return(temp);
                        }

                    }
                }
            }
            else if ((l_size > 0) || (r_size > 0))
            {
                if ((randInt(2) == 0) && (l_size > 0))   // left
                {
                    int i = randInt(l_size) + 1;
                    Point temp(m_centerOfCross.r, (m_centerOfCross.c - i));
                    if (m_head == nullptr)
                    {
                        m_head = new Node<Point>(temp, nullptr);
                        if (m_cross == nullptr)
                        {
                            m_cross = new Node<Point>(temp, nullptr);
                        }
                        else
                        {
                            Node<Point>* surr = m_cross;
                            while (surr->getLink() != nullptr)
                            {
                                surr = surr->getLink();
                            }

                            Node<Point>* add = new Node<Point>(temp, nullptr);
                            surr->setLink(add);
                        }
                        success = true;
                        return(temp);
                    }
                    else
                    {
                        Node<Point>* curr = m_head;
                        while (curr->getLink() != nullptr)
                        {
                            if ((curr->getData().r == temp.r) && (curr->getData().c == temp.c))
                            {
                                if (m_cross == nullptr)
                                {
                                    m_cross = new Node<Point>(temp, nullptr);
                                }
                                else
                                {
                                    Node<Point>* surr = m_cross;
                                    while (surr->getLink() != nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            break;
                                        }
                                        surr = surr->getLink();
                                    }

                                    if (surr->getLink() == nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            Node<Point>* add = new Node<Point>(temp, nullptr);
                                            surr->setLink(add);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                exited = true;
                                break;
                            }
                            curr = curr->getLink();
                        }

                        if (curr->getLink() == nullptr)
                        {
                            if ((curr->getData().r == temp.r) && (curr->getData().c == temp.c))
                            {
                                if (m_cross == nullptr)
                                {
                                    m_cross = new Node<Point>(temp, nullptr);
                                }
                                else
                                {
                                    Node<Point>* surr = m_cross;
                                    while (surr->getLink() != nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            break;
                                        }
                                        surr = surr->getLink();
                                    }

                                    if (surr->getLink() == nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            Node<Point>* add = new Node<Point>(temp, nullptr);
                                            surr->setLink(add);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                exited = true;
                            }
                        }
                        else
                        {
                            ; // already set exited == true
                        }


                        if (exited == true)
                        {
                            exited = false;
                        }
                        else
                        {
                            Node<Point>* curr = m_head;
                            while (curr->getLink() != nullptr)
                            {
                                curr = curr->getLink();
                            }
                            Node<Point>* add = new Node<Point>(temp, nullptr);
                            curr->setLink(add);
                            if (m_cross == nullptr)
                            {
                                m_cross = new Node<Point>(temp, nullptr);
                            }
                            else
                            {
                                Node<Point>* surr = m_cross;
                                while (surr->getLink() != nullptr)
                                {
                                    surr = surr->getLink();
                                }

                                Node<Point>* add = new Node<Point>(temp, nullptr);
                                surr->setLink(add);
                            }
                            success = true;
                            return(temp);
                        }

                    }
                }
                else if (r_size > 0)
                {
                    int i = randInt(r_size) + 1;
                    Point temp(m_centerOfCross.r, (m_centerOfCross.c + i));
                    if (m_head == nullptr)
                    {
                        m_head = new Node<Point>(temp, nullptr);
                        if (m_cross == nullptr)
                        {
                            m_cross = new Node<Point>(temp, nullptr);
                        }
                        else
                        {
                            Node<Point>* surr = m_cross;
                            while (surr->getLink() != nullptr)
                            {
                                surr = surr->getLink();
                            }

                            Node<Point>* add = new Node<Point>(temp, nullptr);
                            surr->setLink(add);
                        }
                        success = true;
                        return(temp);
                    }
                    else
                    {
                        Node<Point>* curr = m_head;
                        while (curr->getLink() != nullptr)
                        {
                            if ((curr->getData().r == temp.r) && (curr->getData().c == temp.c))
                            {
                                if (m_cross == nullptr)
                                {
                                    m_cross = new Node<Point>(temp, nullptr);
                                }
                                else
                                {
                                    Node<Point>* surr = m_cross;
                                    while (surr->getLink() != nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            break;
                                        }
                                        surr = surr->getLink();
                                    }

                                    if (surr->getLink() == nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            Node<Point>* add = new Node<Point>(temp, nullptr);
                                            surr->setLink(add);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                exited = true;
                                break;
                            }
                            curr = curr->getLink();
                        }

                        if (curr->getLink() == nullptr)
                        {
                            if ((curr->getData().r == temp.r) && (curr->getData().c == temp.c))
                            {
                                if (m_cross == nullptr)
                                {
                                    m_cross = new Node<Point>(temp, nullptr);
                                }
                                else
                                {
                                    Node<Point>* surr = m_cross;
                                    while (surr->getLink() != nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            break;
                                        }
                                        surr = surr->getLink();
                                    }

                                    if (surr->getLink() == nullptr)
                                    {
                                        if ((surr->getData().r == temp.r) && (surr->getData().c == temp.c))
                                        {
                                            ;
                                        }
                                        else
                                        {
                                            Node<Point>* add = new Node<Point>(temp, nullptr);
                                            surr->setLink(add);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                exited = true;
                            }
                        }
                        else
                        {
                            ; // already set exited == true
                        }

                        if (exited == true)
                        {
                            exited = false;
                        }
                        else
                        {
                            Node<Point>* curr = m_head;
                            while (curr->getLink() != nullptr)
                            {
                                curr = curr->getLink();
                            }
                            Node<Point>* add = new Node<Point>(temp, nullptr);
                            curr->setLink(add);
                            if (m_cross == nullptr)
                            {
                                m_cross = new Node<Point>(temp, nullptr);
                            }
                            else
                            {
                                Node<Point>* surr = m_cross;
                                while (surr->getLink() != nullptr)
                                {
                                    surr = surr->getLink();
                                }

                                Node<Point>* add = new Node<Point>(temp, nullptr);
                                surr->setLink(add);
                            }
                            success = true;
                            return(temp);
                        }

                    }
                }
            }
        }

        Node<Point>* surr = m_cross;
        while (surr != nullptr)
        {
            Node<Point>* Next = surr->getLink();
            delete surr;
            surr = Next;
        }
        m_cross = nullptr;
        m_state = 1;
        if (m_head == nullptr)
        {
            Point point(game().randomPoint());
            m_head = new Node<Point>(point, nullptr);
            return(point);
        }
        else
        {
            Node<Point>* curr = m_head;
            Point point(0, 0);
            bool exit = false;
            bool success = false;
            while (!success)
            {
                curr = m_head;
                Point temp(game().randomPoint());
                point.r = temp.r;
                point.c = temp.c;
                while (curr != nullptr)
                {
                    if ((curr->getData().r == point.r) && (curr->getData().c == point.c))
                    {
                        exit = true;
                        break;
                    }
                    curr = curr->getLink();
                }

                if (curr == nullptr)
                {
                    success = true;
                }

                if (exit)
                {
                    exit = false;
                    success = false;    // just in case
                }
            }

            curr = m_head;
            while (curr->getLink() != nullptr)
            {
                curr = curr->getLink();
            }
            Node<Point>* add = new Node<Point>(point, nullptr);
            curr->setLink(add);
            return(point);
        }
    }

}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    m_lastCellAttacked.r = p.r;
    m_lastCellAttacked.c = p.c;
    if (m_state == 1)
    {
        if ((validShot == true) && (shotHit == true) && (shipDestroyed == false))
        {
            m_state = 2;
            m_centerOfCross.r = p.r;
            m_centerOfCross.c = p.c;
            l_size = Lvalid(m_lastCellAttacked);
            r_size = Rvalid(m_lastCellAttacked);
            u_size = Uvalid(m_lastCellAttacked);
            d_size = Dvalid(m_lastCellAttacked);
        }
        else
        {
           ; // stay in m_state == 1
        }
    }
    else if (m_state == 2)
    {
        if ((validShot == true) && (shotHit == true) && (shipDestroyed == true))
        {
            m_state = 1;
        }
        else
        {
            ; // stay in m_state == 2
        }
    }
    
}

//*********************************************************************
//  GoodPlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.

class GoodPlayer : public Player
{
public:
    GoodPlayer(string nm, const Game& g);
    ~GoodPlayer();
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    
private:
    bool CheckCross(Point ourShip, Node<OnCrossData>* ThierShip);
    bool OnCross(Board& b, int shipLength, Point point, Direction Dir);
    bool recursivePlace(Board& b, Point point, int shipId, int i);
    bool recursivePlace(Board& b, int nShips, Point point, bool backtrack);
    bool recursivePlace(Board& b, int nShips, Point point, bool backtrack, int& depth);
    Node<OnCrossData>* m_head;
    TotalDistribution TransitionMatrix;
    int m_rows;
    int m_cols;
};

GoodPlayer::GoodPlayer(string nm, const Game& g)
    : Player(nm, g), m_head(nullptr), m_rows(g.rows()), m_cols(g.cols()), TransitionMatrix(g)
{
}
GoodPlayer::~GoodPlayer()
{
    Node<OnCrossData>* curr = m_head;
    while (curr != nullptr)
    {
        Node<OnCrossData>* Next = curr->getLink();
        delete curr;
        curr = Next;
    }
    m_head = nullptr;
}

bool GoodPlayer::CheckCross(Point shipbeingplaced, Node<OnCrossData>* ThierShip)
{
    // we don't want ourship to be on the cross position with respect to TheirShip
    if (ThierShip != nullptr)
    {
        Point theirShip(ThierShip->getData().getpoint()); // there is an error here how do I get rid of it
        int length = ThierShip->getData().getlength();
        if (ThierShip->getData().getdir() == VERTICAL)
        {
            for (int r = 0; r < length; r++)
            {
                shipbeingplaced.r = theirShip.r + r;
                if ((shipbeingplaced.r == theirShip.r) && ((theirShip.c - 4) <= shipbeingplaced.c) && ((theirShip.c + 4) >= shipbeingplaced.c))
                {
                    return(true);
                }

                if ((shipbeingplaced.c == theirShip.c) && ((theirShip.r - 4) <= shipbeingplaced.r) && ((theirShip.r + 4) >= shipbeingplaced.r))
                {
                    return(true);
                }
            }
        }
        else // HORIZONTAL
        {
            for (int c = 0; c < length; c++)
            {
                shipbeingplaced.c = theirShip.c + c;
                if ((shipbeingplaced.r == theirShip.r) && ((theirShip.c - 4) <= shipbeingplaced.c) && ((theirShip.c + 4) >= shipbeingplaced.c))
                {
                    return(true);
                }

                if ((shipbeingplaced.c == theirShip.c) && ((theirShip.r - 4) <= shipbeingplaced.r) && ((theirShip.r + 4) >= shipbeingplaced.r))
                {
                    return(true);
                }
            }
        }
    }
    return(false);
}
bool GoodPlayer::OnCross(Board& b, int shipLength, Point topOrleft, Direction Dir)
{
    Node<OnCrossData>* curr = m_head;

    while (curr != nullptr)
    {
        if (Dir == VERTICAL)
        {
            for (int r = 0; r < shipLength; r++)
            {
                Point temp((topOrleft.r + r), topOrleft.c);
                if (CheckCross(temp, curr))
                {
                    return(true);
                }
            }
        }
        else // HORIZONTAL
        {
            for (int c = 0; c < shipLength; c++)
            {
                Point temp(topOrleft.r, (topOrleft.c + c));
                if (CheckCross(temp, curr))
                {
                    return(true);
                }
            }
        }
        curr = curr->getLink();
    }

    return(false);
}
bool GoodPlayer::recursivePlace(Board& b, Point point, int shipId, int i)
{
    if (i == 50)
    {
        return(false);
    }

    if (randInt(2) == 0)
    {
        if (b.placeShip(point, shipId, VERTICAL))
        {
            return(true);
        }
        else
        {
            if (b.placeShip(point, shipId, HORIZONTAL))
            {
                return(true);
            }
            else
            {
                return(recursivePlace(b, game().randomPoint(), shipId, (i + 1)));
            }
        }
    }
    else
    {
        if (b.placeShip(point, shipId, HORIZONTAL))
        {
            return(true);
        }
        else
        {
            if (b.placeShip(point, shipId, VERTICAL))
            {
                return(true);
            }
            else
            {
                return(recursivePlace(b, game().randomPoint(), shipId, (i + 1)));
            }
        }
    }
}
bool  GoodPlayer::recursivePlace(Board& b, int nShips, Point point, bool backtrack, int& depth)
{
    depth++;
    if (depth == 200)
    {
        return(false);
    }
    if (nShips == game().nShips())
    {
        return(true);
    }

    if (backtrack == false)
    {
        if ((point.r == (game().rows() - 1)) && (point.c == (game().cols() - 1)))
        {
            if (nShips == 0)
            {
                return(false);
            }

            if ((nShips == (game().nShips() - 1)) && (b.placeShip(point, nShips, HORIZONTAL) == true))  // ship of length one at the last spot
            {
                return(true);
            }

            backtrack = true;
            recursivePlace(b, (nShips - 1), point, backtrack, depth);
        }

        if (b.placeShip(point, nShips, VERTICAL) == true)   // ALWAYS PLACES VERTICALLY IF IT CAN
        {
            Point start(0, 0);
            return(recursivePlace(b, (nShips + 1), start, backtrack, depth));
        }

        if (b.placeShip(point, nShips, HORIZONTAL) == true)
        {
            Point start(0, 0);
            return(recursivePlace(b, (nShips + 1), start, backtrack, depth));
        }


        if (point.c == (game().cols() - 1))
        {
            point.r = point.r + 1;
            point.c = 0;
        }
        else
        {
            point.c = point.c + 1;
        }
        return(recursivePlace(b, nShips, point, backtrack, depth));
    }
    else
    {
        if (b.unplaceShip(point, nShips, VERTICAL) == true)
        {
            if (b.placeShip(point, nShips, HORIZONTAL) == true)
            {
                nShips++;
                Point start(0, 0);
                backtrack = false;
                return(recursivePlace(b, nShips, start, backtrack, depth));
            }

            if (point.r == (game().rows() - 1))
            {
                if (point.c == (game().cols() - 1))
                {
                    ;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }
            else
            {
                if (point.c == (game().cols() - 1))
                {
                    point.r = point.r + 1;
                    point.c = 0;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }

            backtrack = false;
            return(recursivePlace(b, nShips, point, backtrack, depth));
        }

        if (b.unplaceShip(point, nShips, HORIZONTAL) == true)
        {
            if (point.r == (game().rows() - 1))
            {
                if (point.c == (game().cols() - 1))
                {
                    ;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }
            else
            {
                if (point.c == (game().cols() - 1))
                {
                    point.r = point.r + 1;
                    point.c = 0;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }

            backtrack = false;
            return(recursivePlace(b, nShips, point, backtrack, depth));
        }

        if (point.c == 0)
        {
            if (point.r == 0)   // this case is not possible
            {
                return(false);
            }
            else
            {
                point.c = game().cols() - 1;
                point.r = point.r - 1;
            }
        }
        else
        {
            point.c = point.c - 1;
        }

        return(recursivePlace(b, nShips, point, backtrack, depth));
    }
}
bool GoodPlayer::recursivePlace(Board& b, int nShips, Point point, bool backtrack)
{
    if (nShips == game().nShips())
    {
        return(true);
    }

    if (backtrack == false)
    {
        if ((point.r == (game().rows() - 1)) && (point.c == (game().cols() - 1)))
        {
            if (nShips == 0)
            {
                return(false);
            }

            if ((nShips == (game().nShips() - 1)) && (b.placeShip(point, nShips, HORIZONTAL) == true))  // ship of length one at the last spot
            {
                return(true);
            }

            backtrack = true;
            recursivePlace(b, (nShips - 1), point, backtrack);
        }

        if (b.placeShip(point, nShips, VERTICAL) == true)   // ALWAYS PLACES VERTICALLY IF IT CAN
        {
            Point start(0, 0);
            return(recursivePlace(b, (nShips + 1), start, backtrack));
        }

        if (b.placeShip(point, nShips, HORIZONTAL) == true)
        {
            Point start(0, 0);
            return(recursivePlace(b, (nShips + 1), start, backtrack));
        }


        if (point.c == (game().cols() - 1))
        {
            point.r = point.r + 1;
            point.c = 0;
        }
        else
        {
            point.c = point.c + 1;
        }
        return(recursivePlace(b, nShips, point, backtrack));
    }
    else
    {
        if (b.unplaceShip(point, nShips, VERTICAL) == true)
        {
            if (b.placeShip(point, nShips, HORIZONTAL) == true)
            {
                nShips++;
                Point start(0, 0);
                backtrack = false;
                return(recursivePlace(b, nShips, start, backtrack));
            }

            if (point.r == (game().rows() - 1))
            {
                if (point.c == (game().cols() - 1))
                {
                    ;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }
            else
            {
                if (point.c == (game().cols() - 1))
                {
                    point.r = point.r + 1;
                    point.c = 0;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }

            backtrack = false;
            return(recursivePlace(b, nShips, point, backtrack));
        }

        if (b.unplaceShip(point, nShips, HORIZONTAL) == true)
        {
            if (point.r == (game().rows() - 1))
            {
                if (point.c == (game().cols() - 1))
                {
                    ;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }
            else
            {
                if (point.c == (game().cols() - 1))
                {
                    point.r = point.r + 1;
                    point.c = 0;
                }
                else
                {
                    point.c = point.c + 1;
                }
            }

            backtrack = false;
            return(recursivePlace(b, nShips, point, backtrack));
        }

        if (point.c == 0)
        {
            if (point.r == 0)   // this case is not possible
            {
                return(false);
            }
            else
            {
                point.c = game().cols() - 1;
                point.r = point.r - 1;
            }
        }
        else
        {
            point.c = point.c - 1;
        }

        return(recursivePlace(b, nShips, point, backtrack));
    }
}
bool GoodPlayer::placeShips(Board& b)
{
    
    if (game().nShips() >= 3)
    {
        bool placed = false;
        Point point(game().randomPoint());
        for (int i = 0; i < 3; i++)
        {
            int count = 0;
            placed = false;
            while ((!placed) && (count < 50))
            {
                if (randInt(2) == 0)
                {
                    if (!OnCross(b, game().shipLength(i), point, VERTICAL))
                    {
                        if (b.placeShip(point, i, VERTICAL))
                        {
                            OnCrossData data(point, game().shipLength(i), VERTICAL);
                            placed = true;
                            if (m_head == nullptr)
                            {
                                m_head = new Node<OnCrossData>(data, nullptr);
                            }
                            else
                            {
                                Node<OnCrossData>* curr = m_head;
                                while (curr->getLink() != nullptr)
                                {
                                    curr = curr->getLink();
                                }
                                Node<OnCrossData>* add = new Node<OnCrossData>(data, nullptr);
                                curr->setLink(add);
                            }
                        }
                    }
                    else if (!OnCross(b, game().shipLength(i), point, HORIZONTAL))
                    {
                        if (b.placeShip(point, i, HORIZONTAL))
                        {
                            OnCrossData data(point, game().shipLength(i), HORIZONTAL);
                            placed = true;
                            if (m_head == nullptr)
                            {
                                m_head = new Node<OnCrossData>(data, nullptr);
                            }
                            else
                            {
                                Node<OnCrossData>* curr = m_head;
                                while (curr->getLink() != nullptr)
                                {
                                    curr = curr->getLink();
                                }
                                Node<OnCrossData>* add = new Node<OnCrossData>(data, nullptr);
                                curr->setLink(add);
                            }
                        }
                    }
                }
                else
                {
                    if (!OnCross(b, game().shipLength(i), point, HORIZONTAL))
                    {
                        if (b.placeShip(point, i, HORIZONTAL))
                        {
                            OnCrossData data(point, game().shipLength(i), HORIZONTAL);
                            placed = true;
                            if (m_head == nullptr)
                            {
                                m_head = new Node<OnCrossData>(data, nullptr);
                            }
                            else
                            {
                                Node<OnCrossData>* curr = m_head;
                                while (curr->getLink() != nullptr)
                                {
                                    curr = curr->getLink();
                                }
                                Node<OnCrossData>* add = new Node<OnCrossData>(data, nullptr);
                                curr->setLink(add);
                            }
                        }
                    }
                    else if (!OnCross(b, game().shipLength(i), point, VERTICAL))
                    {
                        if (b.placeShip(point, i, VERTICAL))
                        {
                            OnCrossData data(point, game().shipLength(i), VERTICAL);
                            placed = true;
                            if (m_head == nullptr)
                            {
                                m_head = new Node<OnCrossData>(data, nullptr);
                            }
                            else
                            {
                                Node<OnCrossData>* curr = m_head;
                                while (curr->getLink() != nullptr)
                                {
                                    curr = curr->getLink();
                                }
                                Node<OnCrossData>* add = new Node<OnCrossData>(data, nullptr);
                                curr->setLink(add);
                            }
                        }
                    }
                }


                Point temp = game().randomPoint();
                point.r = temp.r;
                point.c = temp.c;
                count++;

                if (count >= 50)
                {
                    Point rando(game().randomPoint());
                    if (recursivePlace(b, rando, i, 0) == false)
                    {
                        return(false);
                    }

                }
            }
        }

        b.block();
        Point POint(0, 0);
        bool backtrack = false;
        int i = 0;
        int depth = 0;
        while ((recursivePlace(b, 3, POint, backtrack, depth) == false) && (i < 50))
        {
            depth = 0;
            b.clear();
            b.block();
            i++;
            if (i >= 50)
            {
                return(false);
            }
        }
        b.unblock();
        return(true);
    }
    else
    {
        b.block();
        Point point(0, 0);
        bool backtrack = false;
        int i = 0;
        while ((recursivePlace(b, 3, point, backtrack) == false) && (i < 50))
        {
            b.unblock();
            b.block();
            i++;
        }
        b.unblock();
        if (i >= 50)
        {
            return(false);
        }
        else
        {
            return(true);
        }

    }

    return(true);
}

Point GoodPlayer::recommendAttack()
{
    return(TransitionMatrix.MostProbableLocation(game()));
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
    TransitionMatrix.UpdateDist(p, validShot, shotHit, shipDestroyed, shipId, game());
}

void GoodPlayer::recordAttackByOpponent(Point p)
{}

//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };

    int pos;
    for (pos = 0; pos != sizeof(types) / sizeof(types[0]) &&
        type != types[pos]; pos++)
        ;
    switch (pos)
    {
    case 0:  return new HumanPlayer(nm, g);
    case 1:  return new AwfulPlayer(nm, g);
    case 2:  return new MediocrePlayer(nm, g);
    case 3:  return new GoodPlayer(nm, g);
    default: return nullptr;
    }
}