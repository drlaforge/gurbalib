/* Wishbone Dec04 - used for Generosity quest */
#include "../backbone.h"

inherit STD_ARMOUR;

void setup(void){
    
   set_name("glasses");
   set_short("a pair of dark glasses");
   set_long_f("A pair of dark glasses like a blind person would wear.\n");
   set_alias("marker2");
   set_class(3);
   set_type("helmet");
   set_weight(3);
   set_value(50);
}

init(){
   ::init();
   call_out("check_it",2);
}

check_it(){
   string quests;
   int i;
   if(present("marker1",TP)){
      if(TP->query_quests()){
         quests = explode(TP->query_quests(),"#");
         for(i = 0; i < sizeof(quests); i++){
            if(quests[i] == "generosity")
               return 1;
         }
      }
      TP->set_quest("generosity");
      W("You suddenly feel more experienced. Must have have been all that generousity!\n");
      TP->add_exp(2500);
      return 1;
   }
}
