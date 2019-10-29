#include "../backbone.h"
inherit STD_DRUG;

void setup(void){
    
    
   set_name("joint");
   set_short("a joint");
   set_take(2);   /*  smoke */   set_long("It's a marijuana joint that you could smoke.\n");
   set_heal(5);
   set_strength(5);
   set_consumer_mess("You inhale what's left of the joint");
   set_consuming_mess("smokes a joint");
}
