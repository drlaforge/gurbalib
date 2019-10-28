#include "../backbone.h"
inherit STD_M_MONSTER;

void setup(void){
    
    
   set_name("bertha");
   set_alias("bertha");
   set_gender(2);
   set_level(18);
   set_short("Bertha");
   set_long_f("Bertha is a stern looking woman standing behind the counter ready to take "+
      "your order. If you are ready to order just type 'order' and what you want.\n");
   set_chance(40);
   set_spell_dam(20);
   set_spell_mess1("Panggg.....");
   set_spell_mess2("Panggg, Bertha hits you with a big iron skillet.");
}
