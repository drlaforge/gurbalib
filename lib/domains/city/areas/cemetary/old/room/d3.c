
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "Nightbreeder mines";
    
    long_desc = 
        "You stand in the mines of the nightbreeders.\n"
        + "The cave is very narrow all over in here and the caves seems\n"
	+ "to continue to the north.\n";
    dest_dir = ({
        "/room/cemetary/d2", "north",
        });
    items = ({
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }


