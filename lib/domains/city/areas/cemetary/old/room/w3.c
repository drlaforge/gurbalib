
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeder territory";
    
    long_desc = 
        "You stand in a tunnel leading west and east.\n"
        + "To the north there is a small tunnel.\n";
    dest_dir = ({
        "/room/cemetary/n3", "north",
        "/room/cemetary/w4", "west",
        "/room/cemetary/w2", "east",
        });
    items = ({
              "tunnel",
              "The tunnel north looks like it is getting bigger in the end",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

