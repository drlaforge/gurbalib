/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

void setup(void) {
    set_light(1);
    /*set_outdoors(1); */
    set_short("City Central Square");
    set_long(
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

    add_item("floor","It is smooth from the passage of many feet and looks well used.");
      add_item("street","It continues to the east and west and looks well travelled.");
      add_item("buildings","building","Most of them look very old and empty, but one to the north is open");
      add_item("alleyway","It leads to a large building that looks like a school.");
      add_item("stairs","They look a little dirty, but you can easily go down them.");
      add_item("school","The entrance looks very inviting... Maybe you should take a look.");
      add_item("store","Located to the north, you can hear voices coming from it.");
    set_exits((["west" : ROOMS+"west_square1",
	"east" : ROOMS+"east_square1",
	"south" : ROOMS+"school_entr",
"down" : "/domains/Areas/city/tramstation/room/tram_station1",
	"north" : ROOMS+"shop"]));   
}


