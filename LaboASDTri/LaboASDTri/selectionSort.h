#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

using namespace std;

template<typename T>
inline void selectionSort(vector<T>& vect)
{
	typename vector<T>::iterator iMin;
	typename vector<T>::iterator i;
	typename vector<T>::iterator j = vect.begin();

	while (j != vect.end())
	{
		iMin = j;
		i = (j + 1);
		while (i != vect.end())
		{
			if (*i < *iMin)
			{
				iMin = i;
			}
			++i;
		}
		swap(*iMin, *j);
		++j;
	}
}

#endif