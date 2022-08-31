
void removeBad(list<Restaurant*>& li)
{
	if (li.size() == 1)
	{
		std::list<Restaurant*>::const_iterator p = li.begin();
		if (((*p)->stars()) <= 2)
		{
			(*p)->~Restaurant();
			li.erase(p);
		}
	}
	else if (li.size() > 1)
	{
		std::list<Restaurant*>::iterator current = li.begin();
		std::list<Restaurant*>::iterator odd = li.begin();
		bool ODD = false;
		bool onlydidthisonce = false;
		for (unsigned int i = 0; current != li.end(); )
		{
			if (onlydidthisonce == false)
			{
				if (((*odd)->stars()) <= 2)
				{
					odd++;
				}
				else
				{
					ODD = true;
				}
			}

			if (((*current)->stars()) <= 2)
			{
				(*current)->~Restaurant();
				li.erase(current);
				current = li.begin();
				for (unsigned int k = 0; k < i; k++)
				{
					current++;
				}
			}
			else
			{

				if ((((*current)->stars()) > 2) && (((*odd)->stars()) != ((*current)->stars())) && (ODD == true) && (onlydidthisonce == false))
				{
					int temp = (*odd)->stars();
					(*odd) = new Restaurant((*current)->stars());
					(*current) = new Restaurant(temp);
					onlydidthisonce = true;
				}
				i++;
				current++;
			}
		}
	}
}



