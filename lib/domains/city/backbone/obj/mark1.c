/* Wishbone Dec04 - used for Generosity quest */
#include "../backbone.h"
inherit STD_ARMOUR;

void setup(void){
    
    
   set_name("boots");
   set_alias("marker1");
   set_short("a pair of old boots");
   set_long_f("These boots are very old but pretty sturdy.\n");
   set_type("boot");
   set_class(7);
   set_weight(3);
   set_value(350);
}

init(){
   ::init();
   call_out("check_it",2);
}

check_it(){
   if(present("marker2",TP)){
      string quests;
      int i;
      if(TP->query_quests()){
         quests = explode(TP->query_quests(),"#");
         for(i = 0; i < sizeof(quests); i++){
            if(quests[i] == "generosity")
               return 1;
         }
      }   
      TP->set_quest("generosity");
      WF("You suddenly feel more experienced. Must have have been all that generousity!\n");
      TP->add_exp(2500);
      return 1;
   }
}
