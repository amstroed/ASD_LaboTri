//
//  qsort.cpp
//
//  Created by Olivier Cuisenaire on 10.04.15.
//  Copyright (c) 2015 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <string>
#include <chrono>
#include <limits>

using namespace std;
using namespace std::chrono;

// selectPivot(begin,end)
//
// choisit un pivot pour le tri rapide parmi le tableau
// entre begin et end (non inclus). Calcule la médiane
// entre le premier, le dernier et l'élément central.
// retourne un iterateur du même type que begin et end
// pointant sur la valeur choisie.
//
// NE RIEN MODIFIER DANS CETTE FONCTION

template < typename RandomAccessIterator >
RandomAccessIterator selectPivot(const RandomAccessIterator begin,
	const RandomAccessIterator end)
{
	RandomAccessIterator p1 = begin;
	RandomAccessIterator p2 = begin + (end - begin) / 2;
	RandomAccessIterator p3 = end - 1;

	if (*p1 < *p2) {
		if (*p2 < *p3) return p2;
		else if (*p1 < *p3) return p3;
		return p1;
	}
	else {
		if (*p1 < *p3) return p1;
		else if (*p2 < *p3) return p3;
		return p2;
	}
}

// display
//
// Affiche les valeur entre begin et end (non inclus)
// en entourant de [] la valeur du pivot située entre
// begin et end.
//
// NE RIEN MODIFIER DANS CETTE FONCTION

template < typename RandomAccessIterator >
void display(const RandomAccessIterator begin,
	const RandomAccessIterator pivot,
	const RandomAccessIterator end)
{
	for (auto it = begin; it < pivot; ++it) cout << *it << " ";
	cout << "[" << *pivot << "] ";
	for (auto it = pivot + 1; it < end; ++it) cout << *it << " ";
	cout << endl;
}

template < typename RandomAccessIterator >
RandomAccessIterator partition(RandomAccessIterator begin,
	RandomAccessIterator end)
{
	RandomAccessIterator i = begin - 1;
	RandomAccessIterator j = end;

	while (true) {

		do {
			++i;
		} while (*i < *end);

		do {
			--j;
		} while (j > begin and *end < *j);

		if (i >= j) {
			break;
		}

		swap(*i, *j);
	}
	swap(*i, *end);

	return i;
}

// quickSort
//
// Effectue le tri rapide des éléments entre begin
// et end (non inclus). Doit appeler selectPivot(...)
// pour le choix du pivot, et display() après chaque
// partition
//
// A COMPLETER

template < typename RandomAccessIterator >
void quickSort(RandomAccessIterator begin,
	RandomAccessIterator end)
{
	RandomAccessIterator hi = end - 1;
	if (hi <= begin) {
		return;
	}

	RandomAccessIterator p = selectPivot(begin, end);
	swap(*hi, *p);

	RandomAccessIterator i = partition(begin, hi);

	//display(begin, i, end);

	quickSort(begin, i);
	quickSort(i + 1, end);
}


void calculTri(const int tailleVecteur, const int nbVecteurs)
{
	double tempsMoyen = 0.;
	double tempsTotal = 0.;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	vector<int> v;
	for (int i = 0; i < nbVecteurs; ++i)
	{
		for (int j = 0; j < tailleVecteur; ++j)
		{
			v.push_back(rand() % 1001);
		}
		t1 = high_resolution_clock::now();
		quickSort(v.begin(), v.end());
		t2 = high_resolution_clock::now();
		tempsTotal += duration_cast<nanoseconds>(t2 - t1).count();
		v.clear();
	}
	tempsMoyen = tempsTotal / nbVecteurs;
	cout << "Temps moyen pour " << nbVecteurs << " vecteurs (int) de " <<
		tailleVecteur << " valeurs : " << tempsMoyen << endl;
}
template < typename T >
int calculTriGenerique(vector<T>& v, const int tailleVecteur, const int nbVecteurs)
{
	double tempsMoyen = 0.;
	double tempsTotal = 0.;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	for (int i = 0; i < nbVecteurs; ++i)
	{
		for (int j = 0; j < tailleVecteur; ++j)
		{
			v.push_back(rand() % numeric_limits<int>::max() + 1);
		}
		t1 = high_resolution_clock::now();
		quickSort(v.begin(), v.end());
		t2 = high_resolution_clock::now();
		tempsTotal += duration_cast<nanoseconds>(t2 - t1).count();
		v.clear();
	}
	tempsMoyen = tempsTotal / nbVecteurs;
	return tempsMoyen;
}

// main
//
// Programme testant la mise en oeuvre de quickSort
// appelle cette fonction avec une string, un tableau
// C d'entiers et un std::vector<double>
//
//
// NE RIEN MODIFIER DANS CETTE FONCTION

int main(int argc, const char * argv[]) {

	//Calcul du temps de tri moyen pour des séries de données de taille différente de même distribution
	calculTri(100, 1000);
	calculTri(1000, 1000);
	calculTri(10000, 1000);
	cout << endl << endl;
	//Calcul du temps de tri moyen pour des séries de données de même taille et de distribution différente

	//Vecteurs d'entiers
	vector<int> v1;
	int tempsMoyen = calculTriGenerique(v1, 100, 1000);
	cout << "Temps moyen pour 1000 vecteurs (int) de 100 valeurs : "
		<< tempsMoyen << endl;

	//Vecteurs de doubles
	vector<short> v2;
	tempsMoyen = calculTriGenerique(v2, 100, 1000);
	cout << "Temps moyen pour 1000 vecteurs (double) de 100 valeurs : "
		<< tempsMoyen << endl;

	//Vecteurs de char
	vector<char> v3;
	tempsMoyen = calculTriGenerique(v3, 100, 1000);
	cout << "Temps moyen pour 1000 vecteurs (char) de 100 valeurs : "
		<< tempsMoyen << endl;

	return 0;
}