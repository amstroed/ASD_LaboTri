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


void calculTri(int tailleVecteur, int nbVecteurs)
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
			v.push_back(rand() % (1001) + 0);
		}
		t1 = high_resolution_clock::now();
		quickSort(v.begin(), v.end());
		t2 = high_resolution_clock::now();
		tempsTotal += duration_cast<nanoseconds>(t2 - t1).count();
		v.clear();
	}
	tempsMoyen = tempsTotal / 100;
	cout << "Temps moyen pour " << nbVecteurs << " vecteurs (int) de " <<
		tailleVecteur << " valeurs : " << tempsMoyen << endl;
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

	//tri rapide
	 //Calcul du temps de tri pour des séries de données de taille différente de même distribution

	 //string 1 (21 char)
	string s("EXEMPLE_DE_TRI_RAPIDE");
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	quickSort(s.begin(), s.end());
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps string 1 (21 char) :" << temps << endl << endl;

	//string 2 (42 char)
	s = "CECI_EST_UN_AUTRE_EXEMPLE_DE_TRI_RAPIDE_ID";
	t1 = high_resolution_clock::now();
	quickSort(s.begin(), s.end());
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps string 2 (42 char, le double du premier) :" << temps << endl << endl;

	//string 3 (63 char)
	s = "CECI_EST_ENCORE_UN_AUTRE_EXEMPLE_DE_TRI_RAPIDE_MAIS_ENCORE_PLUS";
	t1 = high_resolution_clock::now();
	quickSort(s.begin(), s.end());
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps string 3 (63 char, le triple du premier) :" << temps << endl << endl;


	//Calcul du temps de tri pour des séries de données de même taille et de distribution différente
	//string de 14 caractères
	s = "EXEMPLE_DE_TRI";
	t1 = high_resolution_clock::now();
	quickSort(s.begin(), s.end());
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps string (14 char) :" << temps << endl;

	//Vecteur de 14 doubles
	vector<double> vd{ 0.1, 1.2, 3.5, 1.8, 0.4, 10.2, -0.4, 5.8, 6.9, 12.5, 24.3, 0.6, 12.2, 4.5 };
	cout << endl;
	t1 = high_resolution_clock::now();
	quickSort(vd.begin(), vd.end());
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps vecteur doubles (14 doubles) :" << temps << endl;

	//Tableau de 14 entiers
	int array[] = { 7, 3, 6, 1, 9, 2, 0, 10, 12, -3, 48, 5, 13, -1 };
	cout << endl;
	t1 = high_resolution_clock::now();
	quickSort(array, array + 10);
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps tableau (14 entiers) :" << temps << endl;

	return 0;
}