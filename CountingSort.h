//
//  CountingSort.h
//

#ifndef CountingSort_h
#define CountingSort_h

#include <vector>
#include <algorithm>
#include <type_traits>

namespace asd1 {

   /**
    Tri comptage générique

    https://en.wikipedia.org/wiki/Counting_sort

    @param first  [first,last] est la plage d'éléments d'un tableau à trier.
    @param last   [first,last] est la plage d'éléments d'un tableau à trier.
    @param output début du tableau où écrire le résultat. Doit être différent
                  du tableau d'entrée
    @param key fonction prenant un élément en entrée et retourant sa position
               dans le tableau de comptage
    @param max_key valeur maximale pouvant être retournée par key(...). Si -1,
                   la fonction calcule cette valeur en parcourant le tableau une
                   fois de plus
    */
   template<typename RandomAccessIterator, typename Fn>
   void CountingSort(RandomAccessIterator first,
                     RandomAccessIterator last,
                     RandomAccessIterator output,
                     Fn key,
                     size_t max_key = -1)
   {
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


   /**
    Tri par base d'entiers non signés sur 32 bits mis en oeuvre en appelant
    4 fois le tri comptage en triant successivement par groupe de 8 bits.

    https://en.wikipedia.org/wiki/Radix_sort

    @param v vecteur à trier, modifié par cette fonction
    */
   void RadixSort(std::vector<unsigned int>& v)
   {
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
         CountingSort(v.begin(), v.end(), t.begin(), [&](unsigned int x){return (x >> (8 * posByte)) & 0xff;}, 255);
         v = t;
      }
   }
}

#endif /* CountingSort_h */