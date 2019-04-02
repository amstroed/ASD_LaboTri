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
#include <type_traits>
#include "CountingSort.h"

using namespace std;
using namespace std::chrono;
using namespace asd1;


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
	}

}


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

	quickSort(begin, i);
	quickSort(i + 1, end);
}

int max_key(int i) {
	return i;
}

//Calculs de temps
double calculTriRadix(vector<unsigned> v)
{
	vector<int> v2(v.size());
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	asd1::RadixSort(v);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<milliseconds>(t2 - t1).count();
}

double calculTriComptage(vector<unsigned> v)
{
	vector<unsigned> v2(v.size());
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	CountingSort(v.begin(), v.end(), v2.begin(), max_key);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<milliseconds>(t2 - t1).count();
}

double calculTriRapide(vector<unsigned> v)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	quickSort(v.begin(), v.end());
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<milliseconds>(t2 - t1).count();
}

double calculTriSelection(vector<unsigned> v)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	selectionSort(v.begin(), v.end());
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	return duration_cast<milliseconds>(t2 - t1).count();
}

void calculTempsTri(const unsigned tailleVect, const unsigned nbSimulations, unsigned maxVal) {

	srand(time(NULL));

	vector<unsigned> vTemp;

	double tempsTotalTriSelect = 0.;
	double tempsTotalTriRapide = 0.;
	double tempsTotalTriComptage = 0.;
	double tempsTotalTriRadix = 0.;

	//Boucle pour générer N résultats différents pour chaque tri
	for (unsigned i = 0; i < nbSimulations; ++i)
	{
		//Insértion des données dans un vecteur servant d'exemple pour les valeurs
		for (unsigned j = 0; j < tailleVect; ++j)
		{
			//Valeurs entières entre 1 et 100
			vTemp.push_back(rand() % maxVal + 1);
		}
		//Appel des différentes fonctions de calcul de temps pour chaque tri
		tempsTotalTriSelect += calculTriSelection(vTemp);
		tempsTotalTriRapide += calculTriRapide(vTemp);
		tempsTotalTriComptage += calculTriComptage(vTemp);
		tempsTotalTriRadix += calculTriRadix(vTemp);
	}

	cout << "Resultats des calculs sur des vecteur de " << tailleVect << " elements, sur " << nbSimulations <<
		" simulations avec des nombres entre 1 et " << maxVal << "(compris)" << endl;

	cout << "Temps moyen du tri par selection : " << tempsTotalTriSelect / nbSimulations << endl;
	cout << "Temps moyen du tri rapide : " << tempsTotalTriRapide / nbSimulations << endl;
	cout << "Temps moyen du tri compatge : " << tempsTotalTriComptage / nbSimulations << endl;
	cout << "Temps moyen du tri radix : " << tempsTotalTriRadix / nbSimulations << endl;
}

int main()
{
	calculTempsTri(100, 100, 100);
	calculTempsTri(100000, 30, 1000000);
	cout << endl << endl;
	system("PAUSE");
}