#include "../backbone.h"
inherit STD_MONSTER;

void setup(void){
    
    
   add_object(OBJ+"joint",1);
   add_object(ARMOUR+"harness",1,"wear harness");
   set_name("larry");
   set_alias("mutant");
   set_short("Larry the mutant");
   set_long_f("Larry has suffered bad toxic. His body is badly changed from nuclear radiation. "+
      "Addicted to anything that will take away his pain, he is a sorry sight. "+
      "His mutated limbs flail around and his left eye bulged out of it's socket while he dribbles "+
      "soliver over himself.\n");
   set_level(12);
   set_race("mutant");
   set_gender(1);
   load_chat(5,({
      "Larry smokes his joint.\n",
      "Larry adjusts his harness.\n",
      "Larry says: I gUeSs YoU aRe qUiTe JeaLouS, Eh?\nLarry points at his harness.\n",
      "Larry says: YoU ProBaBly wiSHed YoU hAd A HarNeSS LIke ThIs !\n",
   }));
   load_a_chat (5,({
      "Larry screams!\n",
      "Larry growls: Lay off!\n",
      "Larry tries to bite you!\n",
   }));
}