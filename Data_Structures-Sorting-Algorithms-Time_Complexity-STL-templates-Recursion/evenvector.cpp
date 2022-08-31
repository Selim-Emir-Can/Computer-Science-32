
void removeEven(vector<int>& v)
{
	if (v.size() == 1)
	{
		std::vector<int>::const_iterator p = v.begin();
		if (((*p) % 2) == 0)
		{
			v.erase(p);
		}
	}
	else if (v.size() > 1)
	{
		std::vector<int>::iterator current = v.begin();
		std::vector<int>::iterator odd = v.begin();
		bool ODD = false;
		bool onlydidthisonce = false;
		for (int i = 0; current != v.end(); )
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
				v.erase(current);
				current = v.begin();
				odd = v.begin();
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


