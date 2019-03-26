#ifndef QUICKSORT_H
#define QUICKSORT_H

using namespace std;

template<typename T>
typename vector<T>::iterator partitionner(vector<T>& vect, typename vector<T>::iterator lo, typename vector<T>::iterator hi)
{
	typename vector<T>::iterator i = lo == vect.begin() ? vect.begin() : lo - 1;
	typename vector<T>::iterator j = hi;
	while (true)
	{
		do
		{
			++i;
		} while (*i < *hi);
		do
		{
			--j;
		} while (j > lo && *hi < *j);
		if (i >= j)
		{
			break;
		}
		swap(*i, *j);
	}
	swap(*i, *hi);
	return i;
}

template<typename T>
void  quickSort(vector<T>& vect, typename vector<T>::iterator lo, typename vector<T>::iterator hi)
{
	if (hi <= lo)
	{
		return;
	}
	typename vector<T>::iterator p = lo + 1;
	swap(*hi, *p);
	typename vector<T>::iterator i = partitionner(vect, lo, hi);
	quickSort(vect, lo, i - 1);
	quickSort(vect, i + 1, hi);
}
#endif