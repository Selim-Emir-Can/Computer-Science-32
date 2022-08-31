#include"Sequence.h"
#include<cstddef>
#include<iostream>
#include<string>
#include<cstdlib>

Sequence::Sequence() // Create an empty sequence (i.e., one whose size() is 0). 
{
	m_size = 0;
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









bool Sequence::empty() const  // Return true if the sequence is empty, otherwise false. 
{
	if (m_size == 0)
	{
		return(true);
	}

	return(false);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








int Sequence::size() const 
{
	return(m_size);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int Sequence::insert(int pos, const ItemType& value)	// Insert value into the sequence so that it becomes the item at // position pos.  The original item at position pos and those that
{														// follow it end up at positions one greater than they were at before. // Return pos if 0 <= pos <= size() and the value could be
														// inserted.  (It might not be, if the sequence has a fixed capacity, // e.g., because it's implemented using a fixed-size array.)  Otherwise,
														// leave the sequence unchanged and return -1.  Notice that // if pos is equal to size(), the value is inserted at the end.

	if ((0 <= pos) && (pos <= m_size) && (m_size != DEFAULT_MAX_ITEMS))
	{
		for (int i = (m_size - 1); i > (pos - 1); i--)		// ACCOUNTS FOR ONE ELEMENT EDGE CASE AND INSERTING AT THE END OF AN ARRAY
		{
			m_array[i + 1] = m_array[i];
		}

		m_array[pos] = value;		// ACCOUNTS FOR ZERO ELEMENT EDGE CASE
		m_size++;
		return(pos);
	}

	return(-1);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Sequence::insert(const ItemType& value)			// Let p be the smallest integer such that value <= the item at // position p in the sequence; if no such item exists (i.e.,
{													// value > all items in the sequence), let p be size().  Insert // value into the sequence so that it becomes the item in position
													// p.  The original item at position p and those that follow it end // up at positions one greater than before.  Return p if the value
													// was actually inserted.  Return -1 if the value was not inserted // (perhaps because the sequence has a fixed capacity and is full).

	int p = -1;
	bool no_such_item = true;
	if (m_size != DEFAULT_MAX_ITEMS)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (value <= m_array[i])
			{
				no_such_item = false;
				p = i;
				break;
			}
		}

		if (no_such_item)
		{
			p = m_size;
		}

		for (int i = (m_size - 1); i > (p - 1); i--)		// ACCOUNTS FOR ONE ELEMENT EDGE CASE AND INSERTING AT THE END OF AN ARRAY
		{
			m_array[i + 1] = m_array[i];
		}

		m_array[p] = value;		// ACCOUNTS FOR ZERO ELEMENT EDGE CASE
		m_size++;
	}

	return(p);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








bool Sequence::erase(int pos) // If 0 <= pos < size(), remove the item at position pos from // the sequence (so that all items that followed that item end up at
{							 // positions one lower than they were at before), and return true. // Otherwise, leave the sequence unchanged and return false.

	if ((0 <= pos) && (pos < m_size))	// ACCOUNTS FOR THE ZERO ELEMENT ARRAY EDGE CASE
	{
		for (int i = pos; i < (m_size - 1); i++)	// ACCOUNTS FOR DELETING ELEMENTS IN THE MIDDLE PART OF THE ARRAY
		{
			m_array[i] = m_array[i + 1];
		}

		m_size--;		// ACCOUNTS FOR THE ONE ELEMENT ARRAY EDGE CASE AND DELETING THE LAST ELEMENT IN ARRAY BECAUSE FOR LOOP DOESN'T RUN

		return(true);
	}

	return(false); // RETURNS FALSE FOR THE EDGE CASE OF ZERO ELEMENTS IN THE ARRAY
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










int Sequence::remove(const ItemType& value)		// Erase all items from the sequence that == value.  Return the
{												// number of items removed (which will be 0 if no item == value).

	int count = 0;
	if (m_size == 0)	// ACOUNTS FOR 0 LENGTH ARRAY
	{
		return(count);
	}

	if (m_size == 1)	// ACCOUNTS FOR ONE ELEMENT ARRAY
	{
		if (m_array[0] == value)
		{
			m_size--;
			count++;
		}

		return(count);
	}

	for (int i = 0; i < m_size; i++)		// ACCOUNTS FOR ARRAYS WITH MORE THAN ONE ELEMENT
	{
		if (m_array[i] == value)
		{
			for (int k = i; k < (m_size - 1); k++)
			{
				m_array[k] = m_array[k + 1];
			}

			count++;
			m_size--;
			i--;		// ACCOUNTS FOR REPEATED ELEMENT CASE
		}

	}

	if (m_array[(m_size - 1)] == value)	// ACCOUNTS FOR LAST ELEMENT EDGE CASE
	{
		m_size--;
		count++;
	}
	

	return(count);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










bool Sequence::get(int pos, ItemType& value) const	// If 0 <= pos < size(), copy into value the item at position pos
{												// of the sequence and return true.  Otherwise, leave value unchanged // and return false.
	if ((0 <= pos) && (pos < m_size))
	{
		value = m_array[pos];
		return(true);
	}
	return(false);		// RETURNS FALSE FOR THE EDGE CASE OF ZERO ELEMENTS IN THE ARRAY
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









bool Sequence::set(int pos, const ItemType& value) // If 0 <= pos < size(), replace the item at position pos in the
{													// sequence with value and return true.  Otherwise, leave the sequence // unchanged and return false.
	if ((0 <= pos) && (pos < m_size))
	{
		m_array[pos] = value;
		return(true);
	}
	return(false);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









int Sequence::find(const ItemType& value) const  // Let p be the smallest integer such that value == the item at
{											       // position p in the sequence; if no such item exists, let p be -1 // Return p.
	int p = -1;

	for (int i = 0; i < m_size; i++)
	{
		if (m_array[i] == value)
		{
			p = i;
			break;
		}
	}

	return(p);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











void Sequence::swap(Sequence& other) // Exchange the contents of this sequence with the other one.
{
	int lower_size = 0, upper_size = 0, temp_size = 0;
	ItemType temp;

	if ((m_size == 0) && (other.m_size != 0))
	{
		for (int i = 0; (i < other.m_size); i++)
		{
			m_array[i] = other.m_array[i];
		}

		temp_size = other.m_size;	// bigger size
		other.m_size = m_size;
		m_size = temp_size;
	}
	else if ((m_size != 0) && (other.m_size == 0))
	{
		for (int i = 0; (i < m_size); i++)
		{
			other.m_array[i] = m_array[i];
		}

		temp_size = m_size;	//bigger size
		m_size = other.m_size;
		other.m_size = temp_size;
	}
	else if (m_size == other.m_size) // sizes are equal 
	{
		for (int i = 0; (i < m_size); i++)			// NOTE: THIS ACCOUNTS FOR THE EDGE CASE WHERE WE HAVE AN ARRAY OF SIZE ZERO FOR BOTH SEQUENCES
		{
			temp = m_array[i];
			m_array[i] = other.m_array[i];
			other.m_array[i] = temp;
		}
	}
	else if (m_size > other.m_size)		// the resulting other.m_size will be bigger
	{
		lower_size = other.m_size;
		upper_size = m_size;
		
		for (int i = 0; (i < lower_size); i++)
		{
			temp = m_array[i];
			m_array[i] = other.m_array[i];
			other.m_array[i] = temp;
		}

		for (int k = lower_size; k < upper_size; k++)
		{
			other.m_array[k] = m_array[k];
		}

		m_size = lower_size;			// current m_size is bigger than other.m_size, so after we swap the resulting m_size will have a lower size
		other.m_size = upper_size;
	}
	else if (m_size < other.m_size)  // the resulting m_size will be bigger
	{
		lower_size = m_size;
		upper_size = other.m_size;

		for (int i = 0; (i < lower_size); i++)
		{
			temp = m_array[i];
			m_array[i] = other.m_array[i];
			other.m_array[i] = temp;
		}

		for (int k = lower_size; (k < upper_size); k++)
		{
			m_array[k] = other.m_array[k];
		}

		other.m_size = lower_size;		//other.m_size is bigger than m_size, so after we swap the resulting other.m_size will have a lower value
		m_size = upper_size;
	}
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////