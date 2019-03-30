//
//  select.cpp
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

// display
//
// Affiche les valeur entre begin et end (non inclus)
// en entourant de [] les valeurs pointées par it1 et
// it2 (it1<=it2) pour souligner les valeurs échangées
// par le tri par sélection
//
// NE RIEN MODIFIER A CETTE FONCTION

template < typename RandomAccessIterator >
void display(const RandomAccessIterator begin,
	const RandomAccessIterator it1,
	const RandomAccessIterator it2,
	const RandomAccessIterator end)
{
	for (auto it = begin; it < it1; ++it) cout << " " << *it << " ";
	if (it1 < end) cout << "[" << *it1 << "]";
	for (auto it = it1 + 1; it < it2; ++it) cout << " " << *it << " ";
	if (it2 < end && it1 != it2) cout << "[" << *it2 << "]";
	for (auto it = it2 + 1; it < end; ++it) cout << " " << *it << " ";
	cout << endl;
}

// selectionSort
//
// Effectue le tri par sélection des éléments entre begin
// et end (non inclus). Doit appeler display() après chaque
// échange.
//
// A COMPLETER

template < typename RandomAccessIterator >
void selectionSort(RandomAccessIterator begin,
	RandomAccessIterator end)
{

	size_t taille = distance(begin, end);
	size_t iMin;

	// Parcours tout le tableau 
	for (size_t i = 0; i < taille - 1; ++i) {
		// Définis la position actuelle comme étant la plus petite
		iMin = i;
		// Parcours le reste tableau 
		for (size_t j = i + 1; j < taille; ++j) {
			// Test quelle valeur des positions i et j est la plus petite
			if (*(begin + j) < *(begin + iMin)) {
				// Définis la valeur de la nouvelle position comme étant plus petite
				iMin = j;
			}
		}
		// Echange les valeurs en position i et j
		swap(*(begin + i), *(begin + iMin));
		// Affiche l'état du tri
		//display(begin, begin + i, begin + iMin, end);
	}

}

// main
//
// Programme testant la mise en oeuvre de selectionSort
// appelle cette fonction avec une string, un tableau
// C d'entiers et un std::vector<double>
//
// NE RIEN MODIFIER A CETTE FONCTION

int main(int argc, const char * argv[]) {

	//tri rapide
	 //Calcul du temps de tri pour des séries de données de taille différente de même distribution

	 //string 1 (21 char)
	string s("EXEMPLE_DE_TRI_RAPIDE");
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	selectionSort(s.begin(), s.end());
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps string 1 (21 char) :" << temps << endl << endl;

	//string 2 (42 char)
	s = "CECI_EST_UN_AUTRE_EXEMPLE_DE_TRI_RAPIDE_ID";
	t1 = high_resolution_clock::now();
	selectionSort(s.begin(), s.end());
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps string 2 (42 char, le double du premier) :" << temps << endl << endl;

	//string 3 (63 char)
	s = "CECI_EST_ENCORE_UN_AUTRE_EXEMPLE_DE_TRI_RAPIDE_MAIS_ENCORE_PLUS";
	t1 = high_resolution_clock::now();
	selectionSort(s.begin(), s.end());
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps string 3 (63 char, le triple du premier) :" << temps << endl << endl;


	//Calcul du temps de tri pour des séries de données de même taille et de distribution différente
	//string de 14 caractères
	s = "EXEMPLE_DE_TRI";
	t1 = high_resolution_clock::now();
	selectionSort(s.begin(), s.end());
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps string (14 char) :" << temps << endl;

	//Vecteur de 14 doubles
	vector<double> vd{ 0.1, 1.2, 3.5, 1.8, 0.4, 10.2, -0.4, 5.8, 6.9, 12.5, 24.3, 0.6, 12.2, 4.5 };
	cout << endl;
	t1 = high_resolution_clock::now();
	selectionSort(vd.begin(), vd.end());
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps vecteur doubles (14 doubles) :" << temps << endl;

	//Tableau de 14 entiers
	int array[] = { 7, 3, 6, 1, 9, 2, 0, 10, 12, -3, 48, 5, 13, -1 };
	cout << endl;
	t1 = high_resolution_clock::now();
	selectionSort(array, array + 10);
	t2 = high_resolution_clock::now();
	temps = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "temps tableau (14 entiers) :" << temps << endl;


	return 0;

}