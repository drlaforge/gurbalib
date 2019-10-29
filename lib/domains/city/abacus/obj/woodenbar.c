#include "../backbone.h"
inherit STD_WEAPON;

void setup(void){
    
    
   set_name("small wooden bar");
   set_alias(({"bar","wooden bar","small bar","weapon"}));
   set_short("a small wooden bar");
   set_long("The bar is about two thirds of a meter long and about five centimeters wide.\n");
   set_wc(7);
   set_value(15);
   set_weight(1);
}
