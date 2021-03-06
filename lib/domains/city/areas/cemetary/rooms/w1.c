
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You stand in a tunnel leading west and east.\n"
        + "To the north you can see some light coming out from a small tunnel.\n";
    dest_dir = ({
        "/domains/areas/city/cemetary/room/hole2", "east",
        "/domains/areas/city/cemetary/room/w2", "west",
        "/domains/areas/city/cemetary/room/n1", "north",
        });
    items = ({
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

