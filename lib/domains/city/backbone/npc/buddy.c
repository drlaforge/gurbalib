#include "../backbone.h"
inherit STD_MONSTER;

void setup(void){
    
    
   add_object(ARMOUR+"apron",1,"wear apron");
   add_object(WEAPON+"meatsaw",1,"wield saw");
   set_name("buddy");
   set_alias("bar keeper");
   set_short("Buddy the barkeeper");
   set_long_f("Buddy is a large sized man in his middle ages. "+
      "He seems to have been training at a gym for several "+
      "years. Although he's not the violent type, he's willing "+
      "to put up a good fight if it comes to it.\n");
   set_level(15);
   set_gender(1);
   set_race("human");
}
