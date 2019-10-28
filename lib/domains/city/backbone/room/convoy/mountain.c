
#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"

string *names;

void setup(){
    
    
   set_light(1);
   set_outdoors(1);
   set_short("Plateau in the Kiran Mountains");
   /* First player here gets to name the mountain :> */
   set_long_f("You stand at a plateau in the range. There is a snow all around you and it is really "+
      "cold! You have no idea what you're doing here. You can't really make out anywhere to go and or other "+
      "details of the area. It's just so cold! You see the tracks of a huge vehicle north to south, hopefully "+
      "it will be by soon!");
   add_item(({"track","tracks","vehicle","huge vehicle"}),
		"You realise these are bus tracks. If you wait a bus will come by");
   add_item(({"mountain","mountains"}), "Mountains, lots of them, they're big!");
   add_item("snow", "#snowShow");
   add_object(ROOM+"convoy/bench.c", 1);
   names = ({ });
}

void init(){
   ::init();
   add_action("pee", "pee");
}

int pee(string str){
   if( str ) return 0;
   write("You dexteriously write your name in the snow. How fun!\n");
   if( member_array(TP->QN, names) == -1 )
      names += ({ TP->QN });
   return 1;
}

int snowShow(){
   int i;
   string out;
   out = "A lot of snow, it's everywhere!\n";
   if( sizeof(names) ){
      out += "You see ";
      if( sizeof(names) == 1 ) 
         out += names[0];
      else {
         for(i=0; i<sizeof(names)-1; i++){
            out += names[i]+", ";
         }
         out += names[sizeof(names)-1];
      }
      out += " written in the snow, in urine - how lovely.";
   }
   writef(out);
}

