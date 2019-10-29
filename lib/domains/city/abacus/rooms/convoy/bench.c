#include <def.h>

inherit STD_OBJ;

static int broken;

void setup(){
    
    
   broken = 3;
   set_id(({"bench", "old bench", "rusty old bench"}));
   set_short("A rusty old bench");
   set_long_f("A rusty old bench, it doesn't look too sturdy. Perhaps you should just "+
      "stand here and wait for the bus, this thing might break if you sat on it.\n");
   set_weight(10000);
   set_gettable(0);
}

void init(){
   ::init();
   add_action("sit", "sit");
}

int sit(string str){
   if(!str) return 0;
   sscanf(str, "on %s", str);
   if( id(str) )
      {
      if( !broken ){
         write("The bench is broken, you don't want sharp rusty metal in your ass, do you?\n");
         return 1;
      }
      broken --;
      if( !broken ){
         write("You sit down on the bench and break it! Good job fat ass!\n");
         set_short("A broken old bench");
         set_long_f("Obviously it used to be a bench. It's all rusted and broken, looks like some "+
            "rather large person sat on it and did it in. Oh well.");
         set_id(({"broken bench","broken old bench", "broken rusty bench"}));
         return 1;
      }
      write("You sit on the bench and it creaks under your weight - you stand up.\n");
      return 1;
   }
   return 0;
}

