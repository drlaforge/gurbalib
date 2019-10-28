#include "../backbone.h"
inherit STD_MONSTER;
string *namelist;
string *weaponlist;
int x;

void setup(void){
    
    
   namelist=({
      "rob",
      "ken",
      "trash",
      "bull",
      "chip",
      "bran",
      "killroy",
      "lennie",
      "mark",
      "paul",
      "jon",
      "andy",
      "adam",
      "phil",
      "trev",
      "brian",
      "jonty",
   });
   weaponlist=({
      OBJ+"chain",
      OBJ+"woodenbar",
      OBJ+"crowbar",
      OBJ+"ramboknife",
   });
   x=random(sizeof(namelist));
   set_name(namelist[x]);
   set_alias("warrior");
   set_short(C(namelist[x])+" the warrior of the Devils");
   set_long_f("He's a warrior of the street gang 'The Devils'. The Devils are an "+
      "annoying gang made up of mostly juvenile delinquents. "+C(namelist[x])+" looks about "+
      "fifteen years old.\n");
   set_level(random(2)+1);
   set_aggressive(1);
   add_money(random(20));
   set_gender(1);
   set_race("human");
   x=random(sizeof(weaponlist));
   add_object(weaponlist[x],1,"wield weapon");
}
