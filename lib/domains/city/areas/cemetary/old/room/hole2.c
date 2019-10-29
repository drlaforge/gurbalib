
inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You stand in the nightbreeders territory now.\n"
        + "There are tunnels leading to the north,south and east.\n"
        + "The walls are lit up alittle by small torches on the wall.\n";
    items = ({
      "torches","There are a few on the wall",
    });
    dest_dir = 
        ({
        "/room/cemetary/hole1", "south",
        "/room/cemetary/hole3", "north",
        "/room/cemetary/hole_east1", "east",
        "/room/cemetary/w1", "west",
        });
}

