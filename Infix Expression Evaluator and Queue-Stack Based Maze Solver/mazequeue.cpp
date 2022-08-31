#include<iostream>
#include<cstddef>
#include<cassert>
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
class Queue
{
public:
	Queue();	//Initializes the object to an empty queue.
	Queue(const Queue<T>& aQueue);
	Queue<T>& operator =(const Queue<T>& rightSide);
	virtual ~Queue();
	void add(T item);	//Postcondition: item has been added to the back of the queue.
	T remove();	//Precondition: The queue is not empty. //Returns the item at the front of the queue //and removes that item from the queue.
	bool isEmpty() const;	//Returns true if the queue is empty. Returns false otherwise.
private:
	Node<T>* front; //Points to the head of a linked list. //Items are removed at the head
	Node<T>* back; //Points to the node at the other end of the //linked list. //Items are added at this end.
};

//////////////////////////////////////////////////////////// Queue CLASS DECLARATION //////////////////////////////////////////////////////////

template<class T>
Queue<T>::Queue() : front(nullptr), back(nullptr)
{

}

template<class T>
Queue<T>::Queue(const Queue<T>& aQueue)
{
	if (aQueue.isEmpty())
		front = back = nullptr;
	else
	{
		Node<T>* temp = aQueue.front;//temp moves
		//through the nodes from front to back of aQueue.
		back = new Node<T>(temp->getData(), nullptr);
		front = back;
		//First node created and filled with data.
		//New nodes are now added AFTER this first node.
		temp = temp->getLink();//temp now points to second
		//node or nullptr if there is no second node.
		while (temp != nullptr)
		{
			back->setLink(new Node<T>(temp->getData(), nullptr));
			back = back->getLink();
			temp = temp->getLink();
		}
		//back->link == nullptr
	}
}

template<class T>
Queue<T>& Queue<T>::operator =(const Queue<T>& rightSide)
{
	if (front == rightSide.front)//if the queues are the same
		return *this;
	else//send left side back to freestore
	{
		while (!isEmpty())
			T next = remove();//remove calls delete.
	}
	if (rightSide.isEmpty())
	{
		front = back = nullptr;
		return *this;
	}
	else
	{
		Node<T>* temp = rightSide.front;//temp moves
		//through the nodes from front to back of rightSide.
		back = new Node<T>(temp->getData(), nullptr);
		front = back;
		//First node created and filled with data.
		//New nodes are now added AFTER this first node.
		temp = temp->getLink();//temp now points to second
		//node or nullptr if there is no second node.
		while (temp != nullptr)
		{
			back->setLink(
				new Node<T>(temp->getData(), nullptr));
			back = back->getLink();
			temp = temp->getLink();
		}
		//back->link == nullptr;
		return *this;
	}
}

template<class T>
bool Queue<T>::isEmpty() const
{
	return (back == nullptr);//front == nullptr would also work
}

template<class T>
void Queue<T>::add(T item)
{
	if (isEmpty())
		front = back = new Node<T>(item, nullptr);//Sets both
		//front and back to point to the only node
	else
	{
		back->setLink(new Node<T>(item, nullptr));
		back = back->getLink();
	}
}
//Uses cstdlib and iostream:
template<class T>
T Queue<T>::remove()
{
	if (isEmpty())
	{
		cerr << "Error: Removing an item from an empty queue.\n";
		exit(1);
	}
	T result = front->getData();
	Node<T>* discard;
	discard = front;
	front = front->getLink();
	if (front == nullptr)//if you removed the last node
		back = nullptr;
	delete discard;
	return result;
}

template<class T>
Queue<T>::~Queue()
{
	while (!isEmpty())
		T next = remove();//remove calls delete.
}

//////////////////////////////////////////////////////////// Queue CLASS IMPLEMENTATION //////////////////////////////////////////////////////////



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

Coord removeTop(Queue<Coord>& walker);	// need to pass by reference

Coord removeTop(Queue<Coord>& walker)
{
	Coord temp(0, 0);
	Queue<Coord> Temp;

	while (!walker.isEmpty())
	{
		temp = walker.remove();
		if (!walker.isEmpty())
		{
			Temp.add(temp);
		}
	}

	walker = Temp;

	return(temp);
}

int canMove(char maze[][10], Queue<Coord> walker, Coord insert);	// don't need to pass by reference
//Precondition: valid coordinates and we have already pushed the starting position inside walker
//-2 error
//-1 can't move, empty stack
// 1 can move
// 2 can't move, we have a wall
// 3 can't move we have been to this place

int canMove(char maze[][10], Queue<Coord> walker, Coord insert)
{
	if (walker.isEmpty())   // starting position
	{
		return(-1);
	}
	else
	{
		if (((insert.c() >= 0) && (insert.c() <= 9)) && ((insert.r() >= 0) && (insert.r() <= 9))) // will we be in bounds?
		{
			Coord curr = removeTop(walker);
			walker.add(curr);

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

bool updateMaze(char maze[][10], Queue<Coord>& walker, Coord insert);
//Precondition: valid coordinates and we have already pushed the starting position inside walker
// if we can move, then we move

bool updateMaze(char maze[][10], Queue<Coord>& walker, Coord insert)
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
		walker.add(insert);
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
	Queue<Coord> walker;
	Coord start(sr, sc);
	Coord end(er, ec);

	walker.add(start);
	maze[start.r()][start.c()] = 'B';

	while (!walker.isEmpty())
	{
		Coord curr = removeTop(walker);
		walker.add(curr);

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
			removeTop(walker);
		}
		else if ((canMove(maze, walker, south) != 1) && (canMove(maze, walker, east) != 1) && (canMove(maze, walker, north) != 1) && (canMove(maze, walker, west) != 1) && ((curr.r() == er) && (curr.c() == ec)))
		{
			removeTop(walker);
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