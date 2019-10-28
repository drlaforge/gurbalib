#include "../backbone.h"
inherit STD_M_MONSTER;

void setup(void){
    
    
   add_object(WEAPON+"whip",1,"wield whip");
   set_name("lady");
   set_alias("streetlady");
   set_short("a streetlady");
   set_gender(2);
   set_race("human");
   set_long_f("The street lady is very rough looking and she knows how to fight. "+
      "She has painted war symbols in her face, something you don't see everyday.\n");
   set_level(14);
   load_a_chat(20,({
      "Streetlady says: Come on, you can do better!\n",
      "Streetlady says: You're nothing but a whimp!\n",
      "Streetlady says: Ouuuhh!\n",
      "Streetlady says: I'll get you!\n",
   }));
}