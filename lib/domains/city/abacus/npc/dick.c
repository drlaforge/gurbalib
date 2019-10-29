#include "../backbone.h"
inherit STD_MONSTER;

void setup(void){
    
    
   add_object(OBJ+"perfume",1);
   add_object(WEAPON+"brokenglass",1,"wield glass");
   set_name("dick");
   set_alt_name("drunkard");
   set_short("Dick the drunkard");
   set_long_f("Dick is a poor sucker, who lost the link with reality. "+
      "He spends most of his time and money on some sort of alcohol. "+
      "His nose is extremely red and it looks like he doesn't know "+
      "where he is, or what's going on.\n");
   set_race("human");
   set_level(16);
   set_gender(1);
   set_chance(18);
   set_spell_mess1("Dick swings his broken glass");
   set_spell_mess2("Dick cuts you with his broken glass");
   set_spell_dam(15);
   add_money(7);
   load_chat(15,({
      "Dick says: Deboodie giadoodie *hic* blurgh!\n",
      "Dick doubles over and pukes at you.\n",
      "Dick mumbles something unhearable.\n",
      "Something drops from Dick's nose.\n",
      "Dick drinks from a dirty bottle of parfume.\n",
      "Dick hiccups.\n",
      "Dick spits on the ground.\n",
      "Dick sings: heell aand coore... chong up fall and allan...\n",
    }));
   load_a_chat(18,({
      "Dick yells: Hey you.. Don't try to steal my drink!!!!\n",
      "Dick screams: Another drink will make all good.\n",
      "Dick pees on you.\n"
   }));
}
