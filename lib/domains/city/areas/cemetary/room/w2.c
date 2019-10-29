
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You stand in a tunnel leading west and east.\n"
        + "To the north there is a hole which looks like a living quarter.\n";
    dest_dir = ({
        "/domains/areas/city/cemetary/room/n2", "north",
        "/domains/areas/city/cemetary/room/w3", "west",
        "/domains/areas/city/cemetary/room/w1", "east",
        });
    items = ({
              "hole",
              "The hole is north from here. It looks like someone is living there",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

