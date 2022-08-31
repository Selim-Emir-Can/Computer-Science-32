#include<iostream>
#include<cassert>
#include<cstddef>
using namespace std;

template < class T>
class Node
{
public:
    Node() {}
    Node(T theData, Node<T>* theLink) : data(theData), link(theLink) {}
    Node<T>* getLink() const { return link; }
    const T getData() const { return data; }
    void setData(const T& theData) { data = theData; }
    void setLink(Node<T>* pointer) { link = pointer; }
private:
    T data;
    Node<T>* link;
};


//////////////////////////////////////////////////////////// Node CLASS //////////////////////////////////////////////////////////

template < class T>
class Stack
{
public:
    Stack();        //Initializes the object to an empty stack.
    Stack(const Stack<T>& aStack);
    Stack<T>& operator =(const Stack<T>& rightSide);

    virtual ~Stack();
    void push(T stackFrame);
    //Postcondition: stackFrame has been added to the stack.
    T pop();
    //Precondition: The stack is not empty.
        //Returns the top stack frame and removes that top
        //stack frame from the stack.
    bool isEmpty() const;
    //Returns true if the stack is empty. Returns false otherwise.
private:
    Node<T>* top;
};

//////////////////////////////////////////////////////////// Stack CLASS DECLARATION //////////////////////////////////////////////////////////


template < class T>
Stack<T>::Stack()
{
    top = nullptr;
}

template < class T>
Stack<T>::Stack(const Stack<T>& aStack)
{
    if (aStack.isEmpty())
        top = nullptr;
    else
    {
        Node<T>* temp = aStack.top; //temp moves through
        //the nodes from top to bottom of aStack.
        Node<T>* end; //Points to end of the new stack.
        end = new Node<T>(temp->getData(), nullptr);
        top = end;
        //First node created and filled with data.
        //New nodes are now added AFTER this first node.
        temp = temp->getLink();//move temp to second node
        //or nullptr if there is no second node.
        while (temp != nullptr)
        {
            end->setLink(
                new Node<T>(temp->getData(), nullptr));
            temp = temp->getLink();
            end = end->getLink();
        }
        //end->link == nullptr;
    }
}

template < class T>
Stack<T>& Stack<T>::operator =(const Stack<T>& rightSide)
{
    if (top == rightSide.top)//if two stacks are the same
    {
        return *this;
    }
    else //send left side back to freestore
    {
        T next;
        while (!isEmpty())
            next = pop();//remove calls delete.
    }

    if (rightSide.isEmpty())
    {
        top = nullptr;
        return *this;
    }
    else
    {
        Node<T>* temp = rightSide.top;//temp moves through
            //the nodes from front top to bottom of rightSide.
        Node<T>* end;//Points to end of the left-side stack.
        end = new Node<T>(temp->getData(), nullptr);
        top = end;;
        //First node created and filled with data.
        //New nodes are now added AFTER this first node.
        temp = temp->getLink();//Move temp to second node
        //or set to nullptr if there is no second node.
        while (temp != nullptr)
        {
            end->setLink(
                new Node<T>(temp->getData(), nullptr));
            temp = temp->getLink();
            end = end->getLink();
        }
        //end->link == nullptr;
        return *this;
    }
}


template < class T>
Stack<T>::~Stack()
{
    //T next; // the Coord Class does not have a default constructor
    while (!isEmpty())
    {
        T next = pop(); //pop calls delete.
    }
}

template < class T>
bool Stack<T>::isEmpty() const
{
    return (top == nullptr);
}

template < class T>
void Stack<T>::push(T stackFrame)
{
    top = new Node<T>(stackFrame, top);
}

template < class T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        cerr << "Error: popping an empty stack.\n";
        exit(1);
    }
    T result = top->getData();
    Node<T>* discard;
    discard = top;
    top = top->getLink();
    delete discard;
    return result;
}

//////////////////////////////////////////////////////////// Stack CLASS IMPLEMENTATION //////////////////////////////////////////////////////////


class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

//////////////////////////////////////////////////////////// Coord CLASS DECLARATION //////////////////////////////////////////////////////////

int canMove(char maze[][10], Stack<Coord> walker, Coord insert); // don't need to pass by reference
//Precondition: valid coordinates and we have already pushed the starting position inside walker
//-2 error
//-1 can't move, empty stack
// 1 can move
// 2 can't move, we have a wall
// 3 can't move we have been to this place

int canMove(char maze[][10], Stack<Coord> walker, Coord insert)
{
    if (walker.isEmpty())   // starting position
    {
        return(-1);
    }
    else
    {
        if (((insert.c() >= 0) && (insert.c() <= 9)) && ((insert.r() >= 0) && (insert.r() <= 9))) // will we be in bounds?
        {
            Coord curr = walker.pop();
            walker.push(curr);

            bool rplusone = ((curr.r() + 1) == insert.r()) && (curr.c() == insert.c());
            bool rminusone = ((curr.r() - 1) == insert.r()) && (curr.c() == insert.c());
            bool cplusone = ((curr.c() + 1) == insert.c()) && (curr.r() == insert.r());
            bool cminusone = ((curr.c() - 1) == insert.c()) && (curr.r() == insert.r());

            if (rplusone || rminusone || cplusone || cminusone)   // moving one step at a time
            {
                if (maze[insert.r()][insert.c()] == '.')    // we have not been to this place
                {
                    return(1);
                }
                else if (maze[insert.r()][insert.c()] == 'X')   // there is a wall
                {
                    return(2);
                }
                else if (maze[insert.r()][insert.c()] == 'B')   // we have been to this place
                {
                    return(3);
                }
            }
        }
    }

    return(-2);
}

bool updateMaze(char maze[][10], Stack<Coord>& walker, Coord insert); // pass by reference
//Precondition: valid coordinates and we have already pushed the starting position inside walker
// if we can move, then we move

bool updateMaze(char maze[][10], Stack<Coord>& walker, Coord insert)
{
    //-2 error
    //-1 can't move, empty stack
    // 1 can move
    // 2 can't move, we have a wall
    // 3 can't move we have been to this place

    switch (canMove(maze, walker, insert))
    {
    default:
    case(-2):
        exit(1);
        break;
    case(1):
        maze[insert.r()][insert.c()] = 'B';
        walker.push(insert);
        return(true);
        break;
    case(-1):
    case(2):
    case(3):
        return(false);
        break;
    }

    return(false);
}

void restoreMaze(char maze[][10]);
//Precondition: assumes 10 by 10 array
//Postcondition: all 'B's are turned to '.'

void restoreMaze(char maze[][10])
{
    for (int i = 0; i <= 9; i++)
    {
        for (int k = 0; k <= 9; k++)
        {
            if (maze[i][k] == 'B')
            {
                maze[i][k] = '.';
            }
        }
    }
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
//Precondition:sr,sc and er,ec are valid coordinates. Starting position is a '.' and not a 'X'
/*
Push the starting coordinate(sr, sc) onto the coordinate stack and
update maze[sr][sc] to indicate that the algorithm has encountered
it(i.e., set maze[sr][sc] to have a value other than '.').
While the stack is not empty,
{ Pop the top coordinate off the stack.This gives you the current
        (r,c) location that your algorithm is exploring.
    If the current(r,c) coordinate is equal to the ending coordinate,
        then we've solved the maze. Set all char's that are not X or . to . and return true!
    Check each place you can move from the current cell as follows :
        If you can move WEST and haven't encountered that cell yet,
            then push the coordinate(r,c - 1) onto the stack and update
            maze[r][c - 1] to indicate the algorithm has encountered it.
        If you can move NORTH and haven't encountered that cell yet,
            then push the coordinate(r - 1,c) onto the stack and update
            maze[r - 1][c] to indicate the algorithm has encountered it.
        If you can move EAST and haven't encountered that cell yet,
            then push the coordinate(r,c + 1) onto the stack and update
            maze[r][c + 1] to indicate the algorithm has encountered it.
        If you can move SOUTH and haven't encountered that cell yet,
            then push the coordinate(r + 1,c) onto the stack and update
            maze[r + 1][c] to indicate the algorithm has encountered it.
        If you cannot move to a new cell and position != starting position,
            pop your current coordinate off the stack
        If you cannot move to a new cell and position == starting position
        return false
}
There was no solution, so return false
*/

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)        // Return true if there is a path from (sr,sc) to (er,ec)
{                                                                       // through the maze; return false otherwise
    Stack<Coord> walker;
    Coord start(sr, sc);
    Coord end(er, ec);

    walker.push(start);
    maze[start.r()][start.c()] = 'B';

    while (!walker.isEmpty())
    {
        Coord curr = walker.pop();
        walker.push(curr);

        Coord west(curr.r(), (curr.c() - 1));
        Coord east(curr.r(), (curr.c() + 1));
        Coord north((curr.r() - 1), curr.c());
        Coord south((curr.r() + 1), curr.c());

        if ((curr.r() == er) && (curr.c() == ec))
        {
            restoreMaze(maze);
            return(true);
        }
        else if (canMove(maze, walker, west) == 1)
        {
            updateMaze(maze, walker, west);
        }
        else if (canMove(maze, walker, north) == 1)
        {
            updateMaze(maze, walker, north);
        }
        else if (canMove(maze, walker, east) == 1)
        {
            updateMaze(maze, walker, east);
        }
        else if (canMove(maze, walker, south) == 1)
        {
            updateMaze(maze, walker, south);
        }
        else if ((canMove(maze, walker, south) != 1) && (canMove(maze, walker, east) != 1) && (canMove(maze, walker, north) != 1) && (canMove(maze, walker, west) != 1) && (!((curr.r() == er) && (curr.c() == ec))))
        {
            walker.pop();
        }
        else if ((canMove(maze, walker, south) != 1) && (canMove(maze, walker, east) != 1) && (canMove(maze, walker, north) != 1) && (canMove(maze, walker, west) != 1) && ((curr.r() == er) && (curr.c() == ec)))
        {
            walker.pop();
            restoreMaze(maze);
            return(true);
        }
    }

    return(false);
}



int main()
{
    char maze[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X' },
                { 'X','.','X','.','.','.','X','.','.','X' },
                { 'X','.','X','.','X','X','X','X','.','X' },
                { 'X','.','X','.','.','X','.','X','.','X' },
                { 'X','.','X','X','.','X','.','.','.','X' },
                { 'X','.','.','.','.','.','.','X','X','X' },
                { 'X','.','X','X','X','X','.','X','.','X' },
                { 'X','.','.','.','.','X','X','X','.','X' },
                { 'X','.','X','.','.','X','.','.','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 5, 6, 8, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    return(0);
}