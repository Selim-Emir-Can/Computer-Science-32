// Return false if the somePredicate function returns true for at
	  // least one of the array elements; return true otherwise.
bool allFalse(const std::string a[], int n)
{
	if (n <= 0)
	{
		return(true);	// otherwise return true
	}
	else if (n > 1)
	{
		if (somePredicate(a[(n - 1)]) == true)
		{
			return(false);
		}
		else
		{
			return(allFalse(a, (n - 1)));
		}
	}
	else // (n  == 1) or ((n - 1) == 0)
	{
		if (somePredicate(a[(n - 1)]) == true)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}

}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const std::string a[], int n)
{
	if (n <= 0)
	{
		return(0);		// we could not search so we did not count any falses // i.e. return 0
	}
	else if (n > 1)
	{
		if (somePredicate(a[(n - 1)]) == false)
		{
			return((countFalse(a, (n - 1)) + 1));
		}
		else
		{
			return(countFalse(a, (n - 1)));
		}
	}
	else // (n == 1) or ((n - 1) == 0)
	{
		if (somePredicate(a[(n - 1)]) == false)
		{
			return(1);
		}
		else
		{
			return(0);
		}
	}

}

/*
int firstFalseHelper(const std::string a[], int n, int curr_n, int ans);	// Precondtiion: n  > 0, curr_n == 0, ans == -1
int firstFalseHelper(const std::string a[], int n, int curr_n, int ans)
{
	if (curr_n == (n - 1))
	{
		if ((somePredicate(a[curr_n]) == false) && (ans == -1))
		{
			ans = curr_n;
		}
		return(ans);
	}
	else
	{
		if ((somePredicate(a[curr_n]) == false) && (ans == -1))
		{
			ans = curr_n;
			return(ans);
		}
	}
	return(firstFalseHelper(a, n, (curr_n + 1), ans));
}
*/

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const std::string a[], int n)
{
	if (n <= 0)
	{
		return(-1);		// we cannot search so there is no false in the first place
	}
	else
	{
		if ((n - 1) == 0)
		{
			if ((somePredicate(a[(n - 1)]) == false))
			{
				return(0);
			}
			else
			{
				return(-1);
			}
		}
		else
		{
			if ((somePredicate(a[(n - 1)]) == false))
			{
				int m = firstFalse(a, (n - 1));
				if (m != -1)
				{
					return(m);
				}
				else
				{
					return((n - 1));
				}
			}
		}
		return(firstFalse(a, (n - 1)));
	}
}

/*
int positionOfLeastHelper(const std::string a[], int n, int m, int curr_n);	// Precondtiion: n  > 0, curr_n == 0, ans == -1
int positionOfLeastHelper(const std::string a[], int n, int m, int curr_n)
{
	if (curr_n == (n - 1))
	{
		if (a[m] <= a[curr_n])
		{
			return(m);
		}
		else
		{
			return(-1);
		}
	}
	else if ((a[m] <= a[curr_n]) && (curr_n < (n - 1)))
	{
		return(positionOfLeastHelper(a, n, m, (curr_n + 1)));
	}
	else if ((a[m] > a[curr_n]) && (curr_n < (n - 1)))
	{
		return(-1);
	}
}
int positionOfLeastHelperHelper(const std::string a[], int n, int m, int curr_n);	// Precondtiion: n  > 0, curr_n == 0, m == 0, ans == -1
int positionOfLeastHelperHelper(const std::string a[], int n, int m, int curr_n)
{
	if (m == (n - 1))
	{
		if (positionOfLeastHelper(a, n, m, curr_n) != -1)
		{
			return(positionOfLeastHelper(a, n, m, curr_n));
		}
		else
		{
			return(-1);
		}
	}
	else if ((positionOfLeastHelper(a, n, m, curr_n) != -1) && (m < (n - 1)))
	{
		return(positionOfLeastHelper(a, n, m, curr_n));	// returned value of m
	}
	else if ((positionOfLeastHelper(a, n, m, curr_n) == -1) && (m < (n - 1)))
	{
		return(positionOfLeastHelperHelper(a, n, (positionOfLeastHelper(a, n, m, curr_n) + 1), curr_n)); // returned value of m + 1 is used
	}
	
}
*/

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no strings are to
// be considered in the array, return -1.
int positionOfLeast(const std::string a[], int n)
{
	if (n <= 0)
	{
		return(-1);
	}
	else if ((n - 1) == 0)
	{
		return(0);
	}
	else if ((n - 1) == 1)
	{
		if (a[0] <= a[1])	// if a[0] == a[1] we return the smallest subscript 0
		{
			return(0);
		}
		else
		{
			return(1);
		}
	}
	else
	{
		int m = positionOfLeast(a, (n - 1));

		if (a[m] <= a[(n - 1)])	// if a[m] == a[(n-1)] we return the smallest subscript m (we are guaranteed to have m < (n-1))
		{
			return(m);
		}
		else
		{
			return((n - 1));
		}
	}
}

/*
int hasHelper(const std::string a1[], int n1, const std::string a2[], int n2, int p1, int p2);	// Precondtiion: n1 > 0,  p1 >= 0
int hasHelper(const std::string a1[], int n1, const std::string a2[], int n2, int p1, int p2)
{
	if (p1 == (n1 - 1))
	{
		if (a1[p1] == a2[p2])
		{
			return(p1);
		}
		else
		{
			return(-1);
		}
	}
	else if ((a1[p1] != a2[p2]) && (p1 < (n1 - 1)))
	{
		return(hasHelper(a1, n1, a2, n2, (p1 + 1), p2));
	}
	else if ((a1[p1] == a2[p2]) && (p1 < (n1 - 1)))
	{
		return(p1);
	}
	else // after all elements are checked we go out of bounds meaning we have not found any of the non-contigous substring
	{
		return(-1);
	}
}
int hasHelperHelper(const std::string a1[], int n1, const std::string a2[], int n2, int p1, int p2);	// Precondtiion: n1  > 0, p1 == 0, p2 == 0, ans == -1
int hasHelperHelper(const std::string a1[], int n1, const std::string a2[], int n2, int p1, int p2)
{
	
	if (p2 == (n2 - 1))
	{
		if (hasHelper(a1, n1, a2, n2, p1, p2) != -1)
		{
			return(p2);
		}
		else
		{
			return(-1);
		}
	}
	else if ((hasHelper(a1, n1, a2, n2, p1, p2) != -1) && (p2 < (n2 - 1)))
	{
		return(hasHelperHelper(a1, n1, a2, n2, (hasHelper(a1, n1, a2, n2, p1, p2) + 1), (p2 + 1)));	// returned value of p + 1 is used
	}
	else if ((hasHelper(a1, n1, a2, n2, p1, p2) == -1) && (p2 < (n2 - 1)))
	{
		return(-1);
	}

}
*/

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "merida" "tiana" "raya" "belle" "tiana" "raya" "moana"
// then the function should return true if a2 is
//    "tiana" "belle" "moana"
// or
//    "tiana" "raya" "raya"
// and it should return false if a2 is
//    "tiana" "moana" "belle"
// or
//    "merida" "belle" "belle"
bool has(const std::string a1[], int n1, const std::string a2[], int n2)
{
	if (n2 == 0)
	{
		return(true);
	}
	else if ((n1 == 0) || (n2 > n1))
	{
		return(false);
	}
	else
	{
		if (a1[0] == a2[0])
		{
			return(has((a1 + 1), (n1 - 1), (a2 + 1), (n2 - 1)));
		}
		else
		{
			return(has((a1 + 1), (n1 - 1), a2, n2));
		}
	}
}