#include "../backbone.h"
inherit STD_WEAPON;

void setup(void){
    
    
   set_name("crowbar");
   set_alias(({"weapon","bar"}));
   set_short("a crowbar");
   set_long("Crowbars can be used as both weapons, and as a tool to open things.\n");
   set_wc(8);
   set_value(20);
   set_weight(3);
}
