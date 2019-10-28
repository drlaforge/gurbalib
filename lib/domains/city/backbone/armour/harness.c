#include "../backbone.h"
inherit STD_ARMOUR;
void setup(void){
    
    
   set_name("harness");
   set_alias("metal harness");
   set_short("a metal harness");
   set_long_f("It's a strong metal harness that fits around your body. "+
      "It leaves quite a lot of you exposed so it doesn't offer you the best protection.\n");
   set_ac(18);
   set_weight(6);
   set_type ("armour");
   set_value (2000);
}
