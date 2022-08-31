
void removeEven(list<int>& li)
{
	if (li.size() == 1)
	{
		std::list<int>::const_iterator p = li.begin();
		if (((*p) % 2) == 0)
		{
			li.erase(p);
		}
	}
	else if (li.size() > 1)
	{
		std::list<int>::iterator current = li.begin();
		std::list<int>::iterator odd = li.begin();
		bool ODD = false;
		bool onlydidthisonce = false;
		for (int i = 0; current != li.end(); )
		{
			if (onlydidthisonce == false)
			{
				if (((*odd) % 2) == 0)
				{
					odd++;
				}
				else
				{
					ODD = true;
				}
			}

			if (((*current) % 2) == 0)
			{
				li.erase(current);
				current = li.begin();
				for (int k = 0; k < i; k++)
				{
					current++;
				}
			}
			else
			{

				if ((((*current) % 2) != 0) && ((*odd) != (*current)) && (ODD == true) && (onlydidthisonce == false))
				{
					int temp = *odd;
					*odd = *current;
					*current = temp;
					onlydidthisonce = true;
				}
				i++;
				current++;
			}
		}
	}
}
