////
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
#include<ctime>
#include <limits>

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
			v.push_back(rand() % (1001) + 0);
		}
		t1 = high_resolution_clock::now();
		selectionSort(v.begin(), v.end());
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
		selectionSort(v.begin(), v.end());
		t2 = high_resolution_clock::now();
		tempsTotal += duration_cast<nanoseconds>(t2 - t1).count();
		v.clear();
	}
	tempsMoyen = tempsTotal / nbVecteurs;
	return tempsMoyen;
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

	//calculTri(100, 1000);
	//calculTri(1000, 1000);
	//calculTri(10000, 1000);


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