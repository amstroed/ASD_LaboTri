/**
 \file main.cpp
 \author Arthur Bécaud, Bruno Egremy et Loïc Geinoz
 \date 03.04.2019
Labo 3 :    Mise à disposition de quatre algorithmes de tris génériques (sauf radixSort)
            avec deux fonctions qui mesurent le temps nécessaire pour trier dans deux cas :
               1. Taille différente avec n = {10^m | m ∈ [1,2, … ,6]} et entiers positifs générés aléatoirement entre 1 et 100.
               2. Taille fixe avec n = 10^5 = 100'000 et entiers positifs générés aléatoirement entre 1 et k = {10^m | m ∈ [1,2, … ,6]}.
            Chacun des tris dans chacun des deux cas cités est simulé 50x pour obtenir un résultat plus précis. Cette valeur est
            modifiable dans chacune des fonctions.

Remarques : Le tri par sélection n'est pas tester dans tous les cas pour une raison d'économie de temps.
            Tous les tri ont été validés sur les sites codecheck suivant :
            Sélection :      http://codecheck.it/codecheck/files/1504101254jdrhpsf6a3ryw592ev0i12bm
            Rapide :         http://codecheck.it/codecheck/files/15041012286fbwu62wva03nmj1ywzclp7fa
            Casier et base : http://codecheck.it/files/1903181536dxcdyxo4gjk1l7wzpj8xyudjf
*/

#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace std::chrono;

/**
 * @brief Tri par sélection
 * @tparam RandomAccessIterator
 * @param begin Itérateur de début de tableau
 * @param end Itérateur de fin de tableau
 */
template < typename RandomAccessIterator >
void selectionSort(RandomAccessIterator begin,
                   RandomAccessIterator end);

/**
 * @brief Choix de pivot pour le tri rapide
 * @tparam RandomAccessIterator
 * @param begin Itérateur de début de tableau
 * @param end Itérateur de fin de tableau
 * @return La position du pivot
 */
template < typename RandomAccessIterator >
RandomAccessIterator selectPivot( const RandomAccessIterator begin,
                                  const RandomAccessIterator end );

/**
 * @brief Partitionne un tableau pour le tri rapide
 * @tparam RandomAccessIterator
 * @param begin Itérateur de début de tableau
 * @param end Itérateur de fin de tableau
 * @return La position de partionnage
 */
template < typename RandomAccessIterator >
RandomAccessIterator partition( RandomAccessIterator begin,
                                RandomAccessIterator end );

/**
 * @brief Tri rapide
 * @tparam RandomAccessIterator
 * @param begin Itérateur de début de tableau
 * @param end Itérateur de fin de tableau
 */
template < typename RandomAccessIterator >
void quickSort( RandomAccessIterator begin,
                RandomAccessIterator end );

/**
 * @brief Tri casier
 * @tparam RandomAccessIterator
 * @tparam Fn
 * @param first Itérateur du premier élément du tableau
 * @param last Itérateur du dernier élément du tableau
 * @param output Début du tableau où le résultat sera écrit
 * @param key Fonction clé déterminant le casier d'une valeur
 * @param max_key Valeur maximale pouvant être retournée par key
 */
template<typename RandomAccessIterator, typename Fn>
void countingSort(RandomAccessIterator first,
                  RandomAccessIterator last,
                  RandomAccessIterator output,
                  Fn key,
                  size_t max_key = -1);

/**
 * @brief Tri par base
 * @param v Tableau à trier
 */
void radixSort(std::vector<unsigned int>& v);

/**
 * @brief Mesure du temps de tri de différent algorithme avec un nombre croissant d'éléments et une même distribution
 */
void calculTempsTris_DonneesTaillesDifferentes();

/**
 * @brief Mesure du temps de tri de différent algorithme avec un même nombre d'éléments et une distribution croissante
 */
void calculTempsTris_DonneesMemesTailles();

int main(int argc, const char * argv[]) {

   // Exécution des estimations du temps de calcul
   calculTempsTris_DonneesTaillesDifferentes();
   cout << endl;
   calculTempsTris_DonneesMemesTailles();

   return EXIT_SUCCESS;

}

template < typename RandomAccessIterator >
void selectionSort(RandomAccessIterator begin, RandomAccessIterator end) {

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
      iter_swap(begin + i, begin + iMin);
   }
}

template < typename RandomAccessIterator >
RandomAccessIterator selectPivot( const RandomAccessIterator begin,
                                  const RandomAccessIterator end ) {
   RandomAccessIterator p1 = begin;
   RandomAccessIterator p2 = begin + ( end-begin ) / 2;
   RandomAccessIterator p3 = end-1;

   if(*p1 < *p2) {
      if( *p2 < *p3 ) return p2;
      else if(*p1 < *p3) return p3;
      return p1;
   } else {
      if( *p1 < *p3 ) return p1;
      else if(*p2 < *p3) return p3;
      return p2;
   }
}

template < typename RandomAccessIterator >
RandomAccessIterator partition( RandomAccessIterator begin,
                                RandomAccessIterator end ) {
   RandomAccessIterator i = begin - 1;
   RandomAccessIterator j = end;

   while(true) {

      do {
         ++i;
      } while(*i < *end);

      do {
         --j;
      } while(j > begin and *end < *j);

      if (i >= j) {
         break;
      }

      iter_swap(i, j);
   }
   iter_swap(i, end);

   return i;
}

template < typename RandomAccessIterator >
void quickSort( RandomAccessIterator begin,
                RandomAccessIterator end ) {
   RandomAccessIterator hi = end - 1;

   if(hi <= begin) {
      return;
   }

   RandomAccessIterator p = selectPivot(begin, end);
   iter_swap(hi, p);

   RandomAccessIterator i = partition(begin, hi);

   quickSort(begin, i);
   quickSort(i + 1, end);
}

template<typename RandomAccessIterator, typename Fn>
void countingSort(RandomAccessIterator first,
                  RandomAccessIterator last,
                  RandomAccessIterator output,
                  Fn key,
                  size_t max_key) {

   //Recherche de la valeur key maximale
   //La key la plus grande est gardée comme max_key
   if(max_key == (size_t)(-1)){
      max_key = key(*first);
      for(RandomAccessIterator i = first; i != last; i++){
         if(key(*i) > max_key){
            max_key = key(*i);
         }
      }
   }

   std::vector<unsigned> cpt(max_key + 1);

   //Comptage des éléments de chaque type
   for(RandomAccessIterator i = first; i != last; i++){
      ++cpt[key(*i)];
   }

   //Parce que l'on connait le nombre d'élément de chaque type,
   //on peut connaître la position du dernier élément de chaque
   //type dans le tableau output
   for(size_t j = 1; j < cpt.size(); ++j){
      cpt[j] += cpt[j - 1];
   }

   for(RandomAccessIterator k = last - 1; k != first - 1; --k) {
      output[cpt[key(*k)] - 1] = *k;
      --cpt[key(*k)];
   }
}

void radixSort(std::vector<unsigned int>& v) {
   std::vector<unsigned int> t(v.size());

   //Découper en 4 bytes de 8bits : int 32bits -> 0b[byte3][byte2][byte1][byte0]
   //Les tris se font dans l'ordre suivant :
   // 1. par byte0
   // 2. par byte1
   // 3. par byte2
   // 4. par byte3

   //(x >>(8*posByte))& 0xff) permet d'isoler le "posByte"ème byte.
   //Les 32 bits sont shifter à droite de 8*posByte vers la droite
   //Ainsi les 8 bits qui nous intéressent sont dans le byte de poids faible
   //Pour les bytes 0 à 2, après leur shift logique, les bits de poids fort après
   //le bit 7, ne sont pas forcément à 0 donc, il faut appliquer la fonction
   //logique AND avec 0xff afin de mettre à 0 ces bits là.
   for(size_t posByte = 0; posByte < 4; ++posByte){
      countingSort(v.begin(), v.end(), t.begin(), [&](unsigned int x){return (x >> (8 * posByte)) & 0xff;}, 255);
      v = t;
   }
}

size_t cleEntierPositifTriComptage(const unsigned entier) {
   return entier - 1u;
}

void calculTempsTris_DonneesTaillesDifferentes() {

   const size_t                      NB_TEST        = 50,
                                     ENTIER_DE_BASE = 10,
                                     ENTIER_MAX     = 100,
                                     PUISSANCE_MIN  = 1,
                                     PUISSANCE_MAX  = 6,
                                     LARG_COL_N     = 6;
   const vector<size_t>              LARG_COL_TRIS  = {16, 12, 15, 12};
   high_resolution_clock::time_point t1,
                                     t2;
   vector<long double>               temps;
   vector<unsigned>                  v,
                                     copie;

   // Titre et label des colonnes du test
   cout << "+-------+-----------------+-------------+----------------+-------------+" << endl
        << "|       | selectionSort() | quickSort() | countingSort() | radixSort() |" << endl
        << "+-------+-----------------+-------------+----------------+-------------+" << endl
        << "|          taille differente (n) et meme distribution (k=100)          |" << endl
        << "+-------+-----------------+-------------+----------------+-------------+" << endl
        << "|   n   |                          temps (ns)                          |" << endl
        << "+-------+-----------------+-------------+----------------+-------------+" << endl;

   // Nombre de test sur différente taille
   for (size_t puissance = PUISSANCE_MIN; puissance <= PUISSANCE_MAX; ++puissance) {

      // Réinitialise les temps
      temps.clear();
      temps.resize(4,0.);

      for(size_t test = 1; test <= NB_TEST; ++test) {

         // Remplir le vecteur avec des valeurs appartenant à [1, ENTIER_MAX]
         for (int i = 0; i < pow((double)(ENTIER_DE_BASE), (double)(puissance)); ++i) {
            v.push_back((rand() % ENTIER_MAX) + 1u);
         }

         // Fait une copie du vecteur à trier
         copie = v;

         // Fait les tris en calculant le temps d'exécution
         // Arrête le tri par à partir de 10^5 éléments pour économiser du temps
         if(puissance < 5) {
            t1 = high_resolution_clock::now();
            selectionSort(v.begin(), v.end());
            t2 = high_resolution_clock::now();
            temps.at(0) += duration_cast<nanoseconds>(t2 - t1).count();
         }

         v = copie;
         t1 = high_resolution_clock::now();
         quickSort(v.begin(), v.end());
         t2 = high_resolution_clock::now();
         temps.at(1) += duration_cast<nanoseconds>(t2 - t1).count();

         v = copie;
         t1 = high_resolution_clock::now();
         countingSort(copie.begin(), copie.end(), v.begin(), cleEntierPositifTriComptage, ENTIER_MAX - 1u);
         t2 = high_resolution_clock::now();
         temps.at(2) += duration_cast<nanoseconds>(t2 - t1).count();

         v = copie;
         t1 = high_resolution_clock::now();
         radixSort(v);
         t2 = high_resolution_clock::now();
         temps.at(3) += duration_cast<nanoseconds>(t2 - t1).count();

         // Vide le vecteur pour la prochain test
         v.clear();
      }

      // Affiche chaque ligne de test
      cout << fixed << "|"  << setw(LARG_COL_N) << to_string(ENTIER_DE_BASE) + '^' + to_string(puissance) << " |";
      for(size_t i = 0; i < temps.size(); ++i) {
         cout << setw(LARG_COL_TRIS.at(i)) << (size_t)(temps.at(i) / (double)(NB_TEST)) << " |";
      }
      cout << endl;
   }
   cout << "+-------+-----------------+-------------+----------------+-------------+" << endl;
}

void calculTempsTris_DonneesMemesTailles() {

   const size_t                      NB_TEST        = 50,
                                     ENTIER_DE_BASE = 10,
                                     N_MAX          = 100000,
                                     PUISSANCE_MIN  = 1,
                                     PUISSANCE_MAX  = 6,
                                     LARG_COL_N     = 6;
   high_resolution_clock::time_point t1,
                                     t2;
   const vector<size_t>              LARG_COL_TRIS  = {16, 12, 15, 12};
   vector<double>                    temps;
   vector<unsigned>                  v,
                                     copie;

   // Titre et label des colonnes du test
   cout << "+-------+-----------------+-------------+----------------+-------------+" << endl
        << "|       | selectionSort() | quickSort() | countingSort() | radixSort() |" << endl
        << "+-------+-----------------+-------------+----------------+-------------+" << endl
        << "|        meme taille (n=100'000) et distribution differente (k)        |" << endl
        << "+-------+-----------------+-------------+----------------+-------------+" << endl
        << "|   k   |                          temps (ns)                          |" << endl
        << "+-------+-----------------+-------------+----------------+-------------+" << endl;

   for (size_t puissance = PUISSANCE_MIN; puissance <= PUISSANCE_MAX; ++puissance) {

      // Réinitialise les temps
      temps.clear();
      temps.resize(4, 0.);

      for(size_t test = 1; test <= NB_TEST; ++test) {
         // Remplir le vecteur avec des valeurs appartenant à [1, 10^puissance]
         for (int i = 0; i < N_MAX; ++i) {
            v.push_back((rand() % (size_t)(pow((double)(ENTIER_DE_BASE), (double)(puissance)))) + 1u);
         }
         copie = v;

         // Fait les tris en calculant le temps d'exécution
         t1 = high_resolution_clock::now();
         quickSort(v.begin(), v.end());
         t2 = high_resolution_clock::now();
         temps.at(1) += duration_cast<nanoseconds>(t2 - t1).count();

         v = copie;
         t1 = high_resolution_clock::now();
         countingSort(copie.begin(), copie.end(), v.begin(),
                 cleEntierPositifTriComptage,
                 (size_t)pow((double)(ENTIER_DE_BASE), (double)(puissance)) - 1u);
         t2 = high_resolution_clock::now();
         temps.at(2) += duration_cast<nanoseconds>(t2 - t1).count();

         v = copie;
         t1 = high_resolution_clock::now();
         radixSort(v);
         t2 = high_resolution_clock::now();
         temps.at(3) += duration_cast<nanoseconds>(t2 - t1).count();

         // Vide le vecteur pour la prochain test
         v.clear();
      }

      // Affiche chaque ligne de test
      cout << fixed << "|"  << setw(LARG_COL_N) << to_string(ENTIER_DE_BASE) + '^' + to_string(puissance) << " |";
      for(size_t i = 0; i < temps.size(); ++i) {
         cout << setw(LARG_COL_TRIS.at(i)) << (size_t)(temps.at(i) / (double)(NB_TEST)) << " |";
      }
      cout << endl;
   }
   cout << endl
        << "+-------+-----------------+-------------+----------------+-------------+" << endl;
}