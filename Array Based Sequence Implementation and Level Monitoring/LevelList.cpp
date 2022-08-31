
#include"LevelList.h"
#include<cstdlib>
#include<iostream>

LevelList::LevelList()       // Create an empty level list.
	: m_sequence()
{

}


bool LevelList::add(unsigned long level)	// If the level is valid (a value from 30 to 400) and the level list
{											// has room for it, add it to the level list and return true.
											// Otherwise, leave the level list unchanged and return false.
	if ((30 <= level) && (level <= 400))
	{
		int p = 0;
		p = m_sequence.insert(level);

		if (p == -1)
		{
			return(false);
		}

		return(true);
	}

	return(false);
}






bool LevelList::remove(unsigned long level) // Remove one instance of the specified level from the level list.
{											// Return true if a level was removed; otherwise false.
	int p = 0;
	bool erased = false;
	p = m_sequence.find(level);
	erased = m_sequence.erase(p);

	return(erased);
}






int LevelList::size() const	// Return the number of levels in the list.
{
	return(m_sequence.size());
}




unsigned long LevelList::minimum() const	// Return the lowest-valued level in the level list.  If the list is
{											// empty, return NO_LEVEL.
	long unsigned min = 0;
	long unsigned temp = 0;

	if (m_sequence.empty())
	{
		return(NO_LEVEL);
	}

	m_sequence.get(0, min);

	for (int i = 0; i < m_sequence.size(); i++)
	{
		m_sequence.get(i, temp);
		if (temp < min)
		{
			min = temp;
		}
	}

	return(min);
}



unsigned long LevelList::maximum() const	// Return the highest-valued level in the level list.  If the list is
{											// empty, return NO_LEVEL.
	long unsigned max = 0;
	long unsigned temp = 0;

	if (m_sequence.empty())
	{
		return(NO_LEVEL);
	}

	m_sequence.get(0, max);

	for (int i = 0; i < m_sequence.size(); i++)
	{
		m_sequence.get(i, temp);
		if (temp > max)
		{
			max = temp;
		}
	}

	return(max);
}

