#include"History.h"		// MAY NEED TO INCLUDE PLAYER.H AND GARK.H BECAUSE MESA IMPLEMENTATION USES IT (HOWEVER, THIS IS DONE IN MESA.CPP)

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>

using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
		{
			m_grid[r][c] = '.';
		}
	}
	// told in specification that we assume nRows and nCols are valid inputs
}

bool History::record(int r, int c) // assumes gark was not killed
{
	
	if ((r > m_rows) || (r <= 0) || (c > m_cols) || (c <= 0))
	{
		return(false);
	}

	c = c - 1; // orient letters correctly
	r = r - 1; // orient letters correctly
	
		switch (m_grid[r][c])
		{
		case('A'):
			m_grid[r][c] = 'B';
			break;
		case('B'):
			m_grid[r][c] = 'C';
			break;
		case('C'):
			m_grid[r][c] = 'D';
			break;
		case('D'):
			m_grid[r][c] = 'E';
			break;
		case('E'):
			m_grid[r][c] = 'F';
			break;
		case('F'):
			m_grid[r][c] = 'G';
			break;
		case('G'):
			m_grid[r][c] = 'H';
			break;
		case('H'):
			m_grid[r][c] = 'J';
			break;
		case('J'):
			m_grid[r][c] = 'K';
			break;
		case('K'):
			m_grid[r][c] = 'L';
			break;
		case('L'):
			m_grid[r][c] = 'M';
			break;
		case('M'):
			m_grid[r][c] = 'N';
			break;
		case('N'):
			m_grid[r][c] = 'O';
			break;
		case('O'):
			m_grid[r][c] = 'P';
			break;
		case('P'):
			m_grid[r][c] = 'Q';
			break;
		case('Q'):
			m_grid[r][c] = 'R';
			break;
		case('R'):
			m_grid[r][c] = 'S';
			break;
		case('S'):
			m_grid[r][c] = 'T';
			break;
		case('T'):
			m_grid[r][c] = 'U';
			break;
		case('U'):
			m_grid[r][c] = 'V';
			break;
		case('V'):
			m_grid[r][c] = 'W';
			break;
		case('W'):
			m_grid[r][c] = 'X';
			break;
		case('X'):
			m_grid[r][c] = 'Y';
			break;
		case('Y'):
			m_grid[r][c] = 'Z';
			break;
		case('Z'): // Z if 26 or more attacks
			break;
		default:
			m_grid[r][c] = 'A';
			break;
		}

	return(true);
}

void History::display() const // may need to include globals.h IF MESA.H DOES NOT ALREADY INCLUDE GLOBALS.H
{
	// Position (row,col) in mesa coordinate system is represented in
   // the array element grid[row-1][col-1]
	
	int r, c;
	clearScreen();
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
			cout << m_grid[r][c];
		cout << endl;
	}
	cout << endl;
}