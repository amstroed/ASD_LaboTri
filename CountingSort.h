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
      if(max_key == (-1)){
         max_key = key(*first);
         for(RandomAccessIterator i = first; i != last; i++){
            if(key(*i) > max_key){
               max_key = key(*i);
            }
         }
      }

      std::vector<unsigned> cpt(max_key + 1);

      //Comptage
      for(RandomAccessIterator i = first; i != last; i++){
         ++cpt.at(key(*i));
      }

      //Tri
      for(size_t i = 0; i < cpt.size(); ++i){
         unsigned nbATrier = cpt.at(i);
         unsigned trie     = 0;
         for(RandomAccessIterator j = first; j != last; j++){
            //Si la valeur est de type i alors il faut la mettre dans le container output
            //La position d'écriture dans l'output doit augmenter de 1 et
            //Le nb de valeurs de type i triée augmente également de 1
            if(key(*j) == i){
               *output = *j;
               ++output;
               ++trie;

               //Si nbATrier valeurs de type i sont triées,
               //passer au prochain type
               if(trie == nbATrier){
                  break;
               }
            }
         }
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
// a compléter
   }
}

#endif /* CountingSort_h */