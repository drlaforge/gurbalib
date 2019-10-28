/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

object harry;
int not_following;
int count;
string chat_str;	/* This variable is only initialized once. */
string a_chat_str;
string func, type, match;

void setup(void) {
    set_light(1);
    set_outdoors(1);
    short_desc = "City Central Square";
    
 
    set_long_f(
       "You are standing on a wide open area in the center of the city. "+
       "The concrete slab of this square is worn and pitted, and the "+
       "buildings around you look deserted and rundown. The main street "+
       "continues to the east and west, and it has been worn "+
       "smooth by the passage of many people. As you look around a bit, "+
       "you see that someone has opened a store in one of the buildings "+
       "to the north. A slightly dirty set of stairs leads "+
       "down to the Central Square Subway station, and a wide "+
       "alleyway opens to the south, ending at the entrance of "+
       "a school.\n");

    items_arr = ({
      "floor", 
      "It is smooth from the passage of many feet and looks well used.",
      "street",
      "It continues to the east and west and looks well travelled.",
      ({"buildings","building"}),
      "Most of them look very old and empty, but one to the north is open",
      "alleyway",
      "It leads to a large building that looks like a school.",
      "stairs", 
      "They look a little dirty, but you can easily go down them.",
      "&Every now and then, you can faintly hear the rumble of a train.",
      "school",
      "The entrance looks very inviting... Maybe you should take a look.",
      "store", 
      "Located to the north, you can hear voices coming from it.",
      "&You can hear faint voices.",
    });

    dest_dir = 
      ({ 
	ROOM+"west_square1","west",
	ROOM+"east_square1","east",
	ROOM+"school_entr","south",
/* 	ROOM+"central_under","down", */
"/domains/Areas/city/tramstation/room/tram_station1","down",
	ROOM+"shop","north"
      }); 
  
  /* if(!present("statue",this_object()))
    move_object(clone_object("/domains/required/objects/statue"),this_object());
*/
}

/*
down() {
   call_other(this_player(), "move_player", "down#room/station");
   return 1;
}
*/
