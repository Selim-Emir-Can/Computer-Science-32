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

/*
If the start location is equal to the ending location, then we've
solved the maze, so return true.
Mark the start location as visted.
For each of the four directions,
If the location one step in that direction(from the start
	location) is unvisited,
	then call pathExists starting from that location(and
		ending at the same ending location as in the
		current call).
	If that returned true,
	then return true.
	Return false.
*/
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

//A 2 - dimensional 10x10 character array of Xs and dots that represents the maze.Each 'X' represents a wall, and each '.' represents a walkway.
//The starting coordinates in the maze : sr, sc; the row numberand column number range from 0 to 9.
//The ending coordinates in the maze : er, ec; the row numberand column number range from 0 to 9.
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	

	Coord start(sr, sc);
	Coord end(er, ec);
	
	maze[start.r()][start.c()] = 'B'; // visited start location.
	if ((start.r() == end.r()) && (start.c() == end.c()))
	{
		return(true);
	}


	bool w = false, e = false, s = false, n = false;
	if ((maze[start.r()][(start.c() - 1)] == '.') && ((!w) && (!n) && (!e) && (!s))) // west
	{
		 w = pathExists(maze, start.r(), (start.c() - 1), er, ec);
	}
	
	if ((maze[(start.r() - 1)][start.c()] == '.') && ((!w) && (!n) && (!e) && (!s))) // north
	{
		n = pathExists(maze, (start.r() - 1), start.c(), er, ec);
	}
	
	if ((maze[start.r()][(start.c() + 1)] == '.') && ((!w) && (!n) && (!e) && (!s))) // east
	{
		e = pathExists(maze, start.r(), (start.c() + 1), er, ec);
	}
	
	if ((maze[(start.r() + 1)][start.c()] == '.') && ((!w) && (!n) && (!e) && (!s))) // south
	{
		s = pathExists(maze, (start.r() + 1), start.c(), er, ec);
	}

	if (w || n || e || s)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}