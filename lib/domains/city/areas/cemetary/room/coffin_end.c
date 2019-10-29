
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "a passage";
    
    long_desc = 
        "The passage leads north and south.\n"
        + "The roof is very low.\n";
    dest_dir = ({
        "/domains/areas/city/cemetary/room/star", "north",
        "/domains/areas/city/cemetary/room/stairs", "south",
        });
    items = ({
              "roof",
              "The roof is very low here. About 3 feet high.",
              "passage",
              "The passage is dark, and leads south and north",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

