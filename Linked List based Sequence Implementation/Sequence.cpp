#include"Sequence.h"
#include<string>
#include<iostream>

int subsequence(const Sequence& seq1, const Sequence& seq2)	// checks if seq2 is a consecutive subsequence of seq1
{
	if (seq2.empty() == true)
	{
		return(-1);
	}

	int numberofsame = 0;
	ItemType start, matched_start, testseq1, testseq2;
	seq2.get(0, start);

	for (int k = 0; k < seq1.size(); k++)
	{
		seq1.get(k, matched_start);
		if (matched_start == start)
		{
			for (int m = 0; ((m < seq2.size()) && ((k + m) < seq1.size())); m++)
			{
				seq1.get((k + m), testseq1);
				seq2.get(m, testseq2);
				if (testseq1 == testseq2)
				{
					numberofsame++;
				}
				else
				{
					break;
				}
			}

			if (numberofsame == seq2.size())
			{
				return(k);
			}
			else
			{
				numberofsame = 0;
			}
		}
	}
	
		
	return(-1);
}






void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	
	if ((seq1.empty() && (!seq2.empty())))
	{
		result = seq2;
	}
	else if ((seq2.empty() && (!seq1.empty())))
	{
		result = seq1;
	}
	else if ((seq1.empty() && seq2.empty()))
	{
		result = seq1; // choice of seq1 or seq2 doesn't matter
	}
	else // ((!seq2.empty()) && (!seq1.empty()))
	{
		Sequence empty;
		result = empty;

		ItemType insert;

		bool addseq1 = true;
		bool addseq2 = false;

		if (seq1.size() > seq2.size())
		{
			int i = 0, seq1_i = 0, seq2_i = 0;
			for (; i < (2*seq2.size()); i++)
			{
				if (addseq1)
				{
					seq1.get(seq1_i, insert);
					seq1_i++;
					result.insert(i, insert);
					addseq1 = false;
					addseq2 = true;
				}
				else if (addseq2)
				{
					seq2.get(seq2_i, insert);
					seq2_i++;
					result.insert(i, insert);
					addseq2 = false;
					addseq1 = true;
				}
			}

			for (; i < (seq1.size() + seq2.size()); i++)
			{
				seq1.get(seq1_i, insert);
				seq1_i++;
				result.insert(i, insert);
			}
		}
		else if (seq2.size() > seq1.size())
		{
			int k = 0, seq1_k = 0, seq2_k = 0;
			for (; k < (2 * seq1.size()); k++)
			{
				if (addseq1)
				{
					seq1.get(seq1_k, insert);
					seq1_k++;
					result.insert(k, insert);
					addseq1 = false;
					addseq2 = true;
				}
				else if (addseq2)
				{
					seq2.get(seq2_k, insert);
					seq2_k++;
					result.insert(k, insert);
					addseq2 = false;
					addseq1 = true;
				}
			}

			for (; k < (seq1.size() + seq2.size()); k++)
			{
				seq2.get(seq2_k, insert);
				seq2_k++;
				result.insert(k, insert);
			}
		}
		else	//seq2.size() == seq1.size()
		{
			int i = 0, seq1_i = 0, seq2_i = 0;
			for (; i < (seq1.size() + seq2.size()); i++)
			{
				if (addseq1)
				{
					seq1.get(seq1_i, insert);
					seq1_i++;
					result.insert(i, insert);
					addseq1 = false;
					addseq2 = true;
				}
				else if (addseq2)
				{
					seq2.get(seq2_i, insert);
					seq2_i++;
					result.insert(i, insert);
					addseq2 = false;
					addseq1 = true;
				}
			}
		}
	}
}



///////////////////////////////////////////// PUBLIC FUNCTIONS ///////////////////////////////////////////////////

ItemTypeNode::ItemTypeNode()
{
	m_next_link = nullptr;
	m_prev_link = nullptr;
	// empty node
}

ItemTypeNode::ItemTypeNode(ItemType theData, ItemTypeNode* nextLink, ItemTypeNode* prevLink)
	: m_data(theData), m_next_link(nextLink), m_prev_link(prevLink)
{

}

ItemTypeNode* ItemTypeNode::getnextLink() const
{
	return(m_next_link);
}

ItemTypeNode* ItemTypeNode::getprevLink() const
{
	return(m_prev_link);
}

ItemType ItemTypeNode::getData() const
{
	return(m_data);
}

void ItemTypeNode::setnextLink(ItemTypeNode* nextLink)
{
	m_next_link = nextLink;
}

void ItemTypeNode::setprevLink(ItemTypeNode* prevLink)
{
	m_prev_link = prevLink;
}

void ItemTypeNode::setData(ItemType theData)
{
	m_data = theData;
}


/////////////////////////////////////////////////////////// END OF NODE CLASS //////////////////////////////////////////////////////////////////////////////////////////

Sequence::Sequence()	// empty sequence
{
	m_head = nullptr;
	m_size = 0;
}	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











Sequence::~Sequence()
{
	ItemTypeNode* current = m_head;
	while (current != nullptr)
	{
		ItemTypeNode* next = current->getnextLink();
		delete current;
		current = next;
	}
	m_head = nullptr;
}	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











Sequence::Sequence(const Sequence& CopyMe)
{
	if (CopyMe.m_head == nullptr)	// empty linked list
	{
		m_head = nullptr;
	}
	else	//one element linked list AND multiple element linked list
	{
		ItemTypeNode* search = CopyMe.m_head;
		ItemTypeNode* current = new ItemTypeNode;
		m_head = current;

		
		current->setData(search->getData());			//initialize data

		current->setprevLink(nullptr);					// set prev link for first element

		while (search->getnextLink() != nullptr)
		{
			ItemTypeNode* next = new ItemTypeNode;
			current->setnextLink(next);
			next->setprevLink(current);
			current = next;
			search = search->getnextLink();

			current->setData(search->getData());
		}

		current->setnextLink(nullptr);
	}

	m_size = CopyMe.m_size;
}	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











Sequence& Sequence::operator =(const Sequence& AssignMe)
{
	if (this != &AssignMe)
	{
		if (AssignMe.m_head == nullptr)	// RHS is an empty linked list
		{
			if (m_head == nullptr)	// empty linked list
			{
				//do nothing
			}
			else	// one element linked list AND multiple element linked list
			{
				ItemTypeNode* current = m_head;
				ItemTypeNode* next = current->getnextLink();

				while (next != nullptr)
				{
					delete current;
					current = next;
					next = current->getnextLink();
				}

				delete current;
				m_head = nullptr;
			}

		}
		else // one element linked list AND multiple element linked list
		{
			if (m_head == nullptr)	// same as copy constructor	one element linked list AND multiple element linked list
			{
				ItemTypeNode* search = AssignMe.m_head;
				m_head = new ItemTypeNode;
				ItemTypeNode* current = m_head;


				current->setData(search->getData());			//initialize data

				current->setprevLink(nullptr);					// set prev link for first element

				while (search->getnextLink() != nullptr)
				{
					ItemTypeNode* next = new ItemTypeNode;
					current->setnextLink(next);
					next->setprevLink(current);
					current = next;
					search = search->getnextLink();

					current->setData(search->getData());
				}

				current->setnextLink(nullptr);
			}
			else // one element linked list AND multiple element linked list
			{
				ItemTypeNode* search = AssignMe.m_head;
				ItemTypeNode* head = new ItemTypeNode;
				ItemTypeNode* current = head;


				current->setData(search->getData());			//initialize data

				current->setprevLink(nullptr);					// set prev link for first element

				while (search->getnextLink() != nullptr)
				{
					ItemTypeNode* next = new ItemTypeNode;
					current->setnextLink(next);
					next->setprevLink(current);
					current = next;
					search = search->getnextLink();

					current->setData(search->getData());
				}

				current->setnextLink(nullptr);

				////////////////////////////////////////////////////////////
				ItemTypeNode* delete_current = m_head;
				ItemTypeNode* delete_next = delete_current->getnextLink();

				while (delete_next != nullptr)
				{
					delete delete_current;
					delete_current = delete_next;
					delete_next = delete_current->getnextLink();
				}

				delete delete_current;
				m_head = head;
			}
		}


		m_size = AssignMe.m_size;
	}

	return(*this);
}	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











bool Sequence::empty() const
{
	if (m_size == 0)
	{
		return(true);
	}

	return(false);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











int Sequence::size() const
{
	return(m_size);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











int Sequence::insert(int pos, const ItemType& value)	// Insert value into the sequence so that it becomes the item at // position pos.  The original item at position pos and those that
{														// follow it end up at positions one greater than they were at before. // Return pos if 0 <= pos <= size() and the value could be
														// inserted.  (it can always be inserted since we are using a linked list) Notice that // if pos is equal to size(), the value is
														// inserted at the end.

	if ((0 <= pos) && (pos <= m_size))
	{
		if (m_head == nullptr)	// empty linked list
		{
			m_head = new ItemTypeNode;	// (0 <= pos) && (pos <= m_size) implies pos == 0 since m_size == 0
			m_head->setData(value);
			m_head->setnextLink(nullptr);
			m_head->setprevLink(nullptr);
		}
		else	// single element AND multiple element linked list
		{
			if (pos == 0)	// insert at the head
			{
				ItemTypeNode* newHead = new ItemTypeNode;
				newHead->setData(value);
				newHead->setnextLink(m_head);
				newHead->setprevLink(nullptr);

				m_head->setprevLink(newHead);
				m_head = newHead;
			}
			else  if (pos == m_size)	// insert at the endmarker
			{
				ItemTypeNode* current = m_head;

				for (int i = 0; i < (pos - 1); i++)	// loop doesn't run for single element linked list
				{
					current = current->getnextLink();
				}

				ItemTypeNode* insert = new ItemTypeNode;
				insert->setData(value);
				insert->setnextLink(nullptr);
				insert->setprevLink(current);
				current->setnextLink(insert);
			}
			else	// insert in the middle	// single element linked list only has a head and an endmarker, this will never run for a single element linked list
			{
				ItemTypeNode* current = m_head;
				for (int i = 0; i < pos; i++)
				{
					current = current->getnextLink();
				}

				ItemTypeNode* insert = new ItemTypeNode;
				insert->setData(value);

				ItemTypeNode* prev = current->getprevLink();
				prev->setnextLink(insert);
				current->setprevLink(insert);

				insert->setnextLink(current);
				insert->setprevLink(prev);
			}
		}

		m_size++;
		return(pos);
	}

	return(-1);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











int Sequence::insert(const ItemType & value)		// Let p be the smallest integer such that value <= the item at // position p in the sequence; if no such item exists (i.e.,
{													// value > all items in the sequence), let p be size().  Insert // value into the sequence so that it becomes the item in position
													// p.  The original item at position p and those that follow it end // up at positions one greater than before.  Return p if the value
													// was actually inserted (it will always be inserted).
	int p = 0;
	bool no_such_item = true;

	
	if (m_head != nullptr)	// handling empty linked list // runs for single element linked lists AND multiple element linked lists
	{
		ItemTypeNode* current = m_head;
		while (current->getnextLink() != nullptr)	// loop doesn't run for single element linked list
		{
			if (value <= current->getData())
			{
				no_such_item = false;
				break;
			}
			p++;
			current = current->getnextLink();
		}

		if (value <= current->getData())
		{
			no_such_item = false;
		}
	}

	if (no_such_item)
	{
		p = m_size;
	}

	// found p	// Following line of code is same as int Sequence::insert(int pos, const ItemType& value)

	if (m_head == nullptr)	// empty linked list
	{
		m_head = new ItemTypeNode;	// empty linked list implies p == 0 since m_size == 0
		m_head->setData(value);
		m_head->setnextLink(nullptr);
		m_head->setprevLink(nullptr);
	}
	else	// single element AND multiple element linked list
	{
		if (p == 0)	// insert at the head
		{
			ItemTypeNode* newHead = new ItemTypeNode;
			newHead->setData(value);
			newHead->setnextLink(m_head);
			newHead->setprevLink(nullptr);

			m_head->setprevLink(newHead);
			m_head = newHead;
		}
		else  if (p == m_size)	// insert after the endmarker
		{
			ItemTypeNode* current = m_head;

			for (int i = 0; i < (p - 1); i++)	// loop doesn't run for single element linked list
			{
				current = current->getnextLink();
			}

			ItemTypeNode* insert = new ItemTypeNode;
			insert->setData(value);
			insert->setnextLink(nullptr);
			insert->setprevLink(current);
			current->setnextLink(insert);
		}
		else	// insert in the middle	// single element linked list only has a head and an endmarker, this will never run for a single element linked list
		{
			ItemTypeNode* current = m_head;
			for (int i = 0; i < p; i++)
			{
				current = current->getnextLink();
			}

			ItemTypeNode* insert = new ItemTypeNode;
			insert->setData(value);

			ItemTypeNode* prev = current->getprevLink();
			prev->setnextLink(insert);
			current->setprevLink(insert);

			insert->setnextLink(current);
			insert->setprevLink(prev);
		}
	}

	m_size++;
	return(p);
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











bool Sequence::erase(int pos) // If 0 <= pos < size(), remove the item at position pos from // the sequence (so that all items that followed that item end up at
{							 // positions one lower than they were at before), and return true. // Otherwise, leave the sequence unchanged and return false.

	if (m_head != nullptr) // handling empty linked list
	{
		if ((0 <= pos) && (pos < m_size))
		{
			if (m_head->getnextLink() == nullptr)	// single linked list
			{
				delete m_head;			// deleted return false if pos != 0
				m_head = nullptr;
				m_size--;
				return(true);
			}
			else	// multiple element linked list
			{
				if (pos == 0)	//erase head
				{
					ItemTypeNode* newHead = m_head->getnextLink();
					newHead->setprevLink(nullptr);						// if we had a single list we would be dereferencing a nullptr

					delete m_head;
					m_head = newHead;
					m_size--;
					return(true);
				}
				else if (pos == (m_size - 1))	// erase endmarker
				{
					ItemTypeNode* current = m_head;
					for (int i = 0; i < pos; i++)
					{
						current = current->getnextLink();
					}

					ItemTypeNode* prev = current->getprevLink();
					delete current;
					current = prev;
					current->setnextLink(nullptr);
					m_size--;
					return(true);
				}
				else	// erase middle element in linked list
				{
					ItemTypeNode* current = m_head;
					for (int i = 0; i < pos; i++)
					{
						current = current->getnextLink();
					}

					ItemTypeNode* prev = current->getprevLink();
					ItemTypeNode* next = current->getnextLink();

					prev->setnextLink(next);
					next->setprevLink(prev);
					delete current;
					m_size--;
					return(true);
				}
			}
		}
	}

	return(false); // handling empty linked list
}










int Sequence::remove(const ItemType& value)		// Erase all items from the sequence that == value.  Return the
{												// number of items removed (which will be 0 if no item == value).

	int count = 0;
	if (m_head != nullptr)	// handling empty list
	{
		if (m_head->getnextLink() == nullptr)	// single element linked list
		{
			if (value == m_head->getData())
			{
				
				delete m_head;
				m_head = nullptr;
				count++;
				m_size--;
			}
		}
		else	// multiple element linked list
		{
			ItemTypeNode* current = m_head;

			while (current->getnextLink() != nullptr)	// guaranteed to iterate at least once
			{
				if ((current->getprevLink() == nullptr) && (current->getnextLink() != nullptr))	// we are at the head and not at the end // not a single element linked list
				{
					if (value == current->getData())	// remove head
					{
						ItemTypeNode* newHead = m_head->getnextLink();
						newHead->setprevLink(nullptr);						// if we had a single list we would be dereferencing a nullptr

						delete current;
						m_head = newHead;
						current = m_head;	// current is now the new m_head

						count++;
						m_size--;
					}
					else
					{
						current = current->getnextLink();
					}
				}
				else if ((current->getnextLink() != nullptr))	// we are at a middle element in linked list // we are not a single element list or an endmarker
				{
					if (value == current->getData())	// remove middle element
					{
						ItemTypeNode* prev = current->getprevLink();
						ItemTypeNode* next = current->getnextLink();

						prev->setnextLink(next);
						next->setprevLink(prev);
						delete current;
						current = next;

						count++;
						m_size--;
					}
					else
					{
						current = current->getnextLink();
					}
				}
			}

			if ((current->getnextLink() == nullptr) && (value == current->getData()) && (m_size == 1)) // remove single element linked list
			{
				
				delete current;
				current = nullptr;
				m_head = nullptr;
				count++;
				m_size--;
			}
			else if ((current->getnextLink() == nullptr) && (value == current->getData()))	// remove endmarker
			{
				ItemTypeNode* prev = current->getprevLink();
				delete current;
				current = prev;
				current->setnextLink(nullptr);

				count++;
				m_size--;
			}
		}
	}
	
	return(count);
}











bool Sequence::get(int pos, ItemType& value) const	// If 0 <= pos < size(), copy into value the item at position pos
{												// of the sequence and return true.  Otherwise, leave value unchanged // and return false.
	if (m_head != nullptr)
	{
		if ((0 <= pos) && (pos < m_size))
		{
			if (pos == 0)
			{
				value = m_head->getData();
				return(true);
			}
			else
			{
				ItemTypeNode* current = m_head;
				int i = 0;
				while ((current->getnextLink() != nullptr) && (i < pos))
				{
					current = current->getnextLink();
					i++;
				}

				value = current->getData();
				return(true);
			}
		}
	}

	return(false);		// returns false for empty linked list
}	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT












bool Sequence::set(int pos, const ItemType& value) // If 0 <= pos < size(), replace the item at position pos in the
{													// sequence with value and return true.  Otherwise, leave the sequence // unchanged and return false.
	if (m_head != nullptr)
	{
		if ((0 <= pos) && (pos < m_size))
		{
			if (pos == 0)
			{
				m_head->setData(value);
				return(true);
			}
			else
			{
				ItemTypeNode* current = m_head;
				int i = 0;
				while ((current->getnextLink() != nullptr) && (i < pos))
				{
					current = current->getnextLink();
					i++;
				}

				current->setData(value);
				return(true);
			}
		}
	}

	return(false);		// returns false for empty linked list
}	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT












int Sequence::find(const ItemType& value) const  // Let p be the smallest integer such that value == the item at
{											       // position p in the sequence; if no such item exists, let p be -1 // Return p.
	
	int p = 0;
	bool exectuted = false;

	if (m_head != nullptr)	// empty linked list
	{
		ItemTypeNode* current = m_head;
		while (current != nullptr)
		{
			if (current->getData() == value)
			{
				exectuted = true;
				break;
			}
			p++;
			current = current->getnextLink();
		}
	}

	if (exectuted)
	{
		return(p);
	}
	else
	{
		return(-1);
	}
}	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT











void Sequence::swap(Sequence& other) // Exchange the contents of this sequence with the other one.
{
	Sequence* temp_seq = new Sequence(other);

	other = *this;
	*this = *temp_seq;

	delete temp_seq;
}	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////RIGHT


////////////////////////////////////////////////////////////////////////END OF SEQUENCE CLASS/////////////////////////////////////////////////////////////////////////////