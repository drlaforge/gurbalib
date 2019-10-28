inherit "std/room";
#include "../area.h"

void setup(void) {
    set_outdoors(1);
    set_light(1);
    short_desc = "Construction Site";
    long_desc = 
          "You stand at the edge of a construction site.  It looks like they are\n"
        + "starting to build a new skyscraper.   Right now its nothing more\n"
        + "than a big hole in the ground as they start building the \n"
        + "foundation.  It looks like only a small crew is here working\n"
        + "at the moment.  There are some earthmovers and other equipment.\n";
    dest_dir = ({
        ROOM+"nangels1","east",
        });
    items_arr = ({
    ({"headquarters","world headquarters"}),
       "The place that Muncher industries run its operations from.",
    ({"hole","big hole"}),
       "A large hole in the ground where the foundation of the building will go.",
    "foundation",
       "The pylons and girders that the skyscraper will be built upon.",
    ({"crew","small crew"}),
       "A bunch of people working on the construction of the building.",
    "earthmovers",
       "Equipment for digging and getting the ground ready for construction.",
    ({"equipment","other equipment"}),
       "Other equipment used in constructing a foundation.",
    ({"sign","large sign"}),
       "#mysign",
    ({"girders","pylons"}),
       "Girders and pylons that form the foundation",
          });
}

mysign(str) {
  if (!(str=="sign")) return 0;
     write( "--------------------------\n"
           +"|   Muncher Industries   |\n"
           +"| New World Headquarters |\n"
           +"|     Opening Soon!!!    |\n"
           +"|         ----           |\n"
           +"|   Construction  Area   |\n"
           +"|   Hardhats  Required   |\n"
           +"--------------------------\n");
     return 1;
}

