
void removeBad(vector<Restaurant*>& v)
{
	if (v.size() == 1)
	{
		std::vector<Restaurant*>::const_iterator p = v.begin();
		if (((*p)->stars()) <= 2)
		{
			(*p)->~Restaurant();
			v.erase(p);
		}
	}
	else if (v.size() > 1)
	{
		std::vector<Restaurant*>::iterator current = v.begin();
		std::vector<Restaurant*>::iterator odd = v.begin();
		bool ODD = false;
		bool onlydidthisonce = false;
		for (unsigned int i = 0; current != v.end(); )
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
				v.erase(current);
				current = v.begin();
				odd = v.begin();
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

