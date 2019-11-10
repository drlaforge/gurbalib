#include "../area.h"

inherit STD_ROOM;

void setup(void) {
    /*set_outdoors(1);*/
    set_light(1);
    set_short("Construction Site");
    set_long("You stand at the edge of a construction site.  It looks like they are\n"
        + "starting to build a new skyscraper.   Right now its nothing more\n"
        + "than a big hole in the ground as they start building the \n"
        + "foundation.  It looks like only a small crew is here working\n"
        + "at the moment.  There are some earthmovers and other equipment.\n");
	add_exit("east", ROOMS + "nangels1");
  
    add_item("headquarters","world headquarters",
       "The place that Muncher industries run its operations from.");
    add_item("hole","big hole",
       "A large hole in the ground where the foundation of the building will go.");
    add_item("foundation",
       "The pylons and girders that the skyscraper will be built upon.");
    add_item("crew","small crew",
       "A bunch of people working on the construction of the building.");
    add_item("earthmovers",
       "Equipment for digging and getting the ground ready for construction.");
    add_item("equipment","other equipment",
       "Other equipment used in constructing a foundation.");
    add_item("sign","large sign","A large sign, try 'read sign' ");
    add_item("girders","pylons",
       "Girders and pylons that form the foundation");
	   
	set_objects(OBJ + "muncher_sign.c");
}
