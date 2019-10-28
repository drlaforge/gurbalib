inherit "std/room";
#include "../area.h"

string locked;

init() {
  ::init();
/*   add_action ("down","down"); */  add_action ("open","open");
  add_action ("unlock","unlock");
  /*  add_action ("east","east"); */
}

void setup(void) {
     

    locked=0;
    set_outdoors(1);
    set_light(1);
    short_desc = "in an alley";
    
    long_desc = 
        "You stand in an alley leading south-north.\n"
        + "You see an opening in the eastern wall.\n";
    dest_dir = ({
        ROOM+"alley_03", "north",
        ROOM+"alley_05", "south",
	ROOM+"building1","east",
    });
    items_arr = ({
              "alley","It's really dark and gloomy",
              ({"sewer","hatch"}),
	      "#down_check",
	      ({"opening","wall"}),"The opening in the eastern wall leads into a large building",
	      "building","You see nothing but darkness in the building",
              "ladder","The ladder is bolted to the sewers",
          });
}

down() 
{
  if(locked) 
  { write ("The sewer hatch is closed.\n"); 
   return 1; 
  }
}

down_check () {
   write ("It's a hatch to the sewers.\n");
   if (locked) write ("The hatch is closed.\n");
   else write ("You see a ladder leading downwards into a dark, wet sewer.\n");
   return 1;
}

open (str) {
   if (!str || (str!="hatch" && str!="sewer")) return 0;
   if (!locked) { write ("It's already open.\n"); return 1; }
   if (locked==2) { write ("The hatch is locked.\n"); return 1; }
   if (this_player()->query_str() < 5) { write ("You try, but you are too weak.\n"); return 1; }
   locked--;
   write ("Ok.\n");
   say (this_player()->query_name ()+" opens the sewer hatch.\n");
   return 1;
}

unlock (str) {
   if (!str || (str!="hatch" && str!="sewer")) return 0;
   if (locked<2) { write ("It's not locked.\n"); return 1; }
   if (!present ("sewer_key",this_player())) {
     write ("You don't got the right key!\n"); return 1; }
   locked--;
   write ("Ok.\n");
   say (this_player()->query_name ()+" unlocks the sewer hatch.\n");
   return 1;
}

east () {
  write ("There is too much rubbish in your way.\n");
  write ("At the moment, it seems impossible to get in.\n");
  return 1;
}

set_locked (s) { locked=s; }
query_locked () { return locked; }
