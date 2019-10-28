#include "convoy.h"

inherit STD_ROOM; 
#include "../area.h"

static object ControlObj;

void setControl(object ob){
   ControlObj = ob;
   return;
}

string query_peace(){
   return "The driver yells: Not on MY APC! SIT DOWN!";
}

void setup(){
    
    
   set_no_boost(1);
   set_no_clean_up(1);
   set_light(1);
   set_outdoors(0);
   set_short("a battered APC");
   set_long_f("The APC is a fully armoured vehicle which was designed to deliver soldiers into "+
      "combat zones. This particular APC however seems to have seen quite a few wars however. "+
      "The armour plating is dented in places and the paint has worn away from a lot of the "+
      "metalwork. The interior is basic and functional only with hard uncomfortable seats.  "+
      "A blast mark in the side now works as a window and the driver has some view holes "+
      "at the front.\n");
   add_object( "/domains/NG/Areas/merc/npc/apc_guard.c", 1 );
   add_item(({"apc","vehicle"}),"You're in the APC.");
   add_item(({"armour plating","plating","plates"}),"The armour plating is not as effective as it used to be. It might not\n"+
      "survive another rocket attack.");
   add_item("paint","The APC was painted grey and olive drab, but over the years a lot of the\n"+
      "paint has worn away exposing the metal.");
   add_item(({"blast mark","hole","window","windows","scenery","out"}),"#special_desc");
   add_item("driver","The driver uses the APC as a transport vehicle for anyone who wants a ride.");
   add_item(({"view holes","holes"}),"The driver uses the view holes to see where he's going.");
   add_item(({"exit","door","closed door","open door"}), "It's a door. That's all");
   add_exit("out", "OffTheBus", "#catchOut");
}

void special_desc(){
   string out;
   if( ControlObj )
      {
      out = "You can't make out much. ";
      switch( ControlObj->query_location() ){
         case 3 :
         out += "You see the wilderness all around you, a jungle to the north and the plains to the south and east. ";
         break;
         case 2 :
         out += "You see the Kiran Mountains to your east, wow - they're big! ";
         break;
         case 1 :
         out += "You see the lights of a carnival - an old crappy carnival. ";
         break;
         case 0 :
         out += "You see the Abacus City bus stop to the west. ";
         break;
         case -1 :
         out += "The desolate and barren lands of the Wasteland are all around you.";
         break;
         case -3 :
         out += "Nothing but desert - lifeless desert - how boring. ";
         break;
         case -2 :
         out += "You see the walls of Ded City and desert all around it. ";
         break;
         default : break;
      }
      if( ControlObj->query_moving() )
         out += "\nThe scenery is flying by you as the APC barrels down the road.";
      
      writef(out, 75);
   }
   return;
}

int catchOut(){
   string room;
   if(!ControlObj){
      write("Something is wrong - the driver freaks out and takes you back to Abacus City!\n");
      TP->move_player("out of the APC#"+Abacus);
      destruct(TO);
      return 1;
   }
   if( ControlObj->query_moving() ){
      write("Not wise to exit a moving vehicle.\n");
      return 1;
   }
   
   room = ( (mapping)ControlObj->query_locations() )[(int)ControlObj->query_location()];
   TP->move_player("out of the APC#"+room);
   return 1;
}

