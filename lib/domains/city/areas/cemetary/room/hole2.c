
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
        "/domains/areas/city/cemetary/room/hole1", "south",
        "/domains/areas/city/cemetary/room/hole3", "north",
        "/domains/areas/city/cemetary/room/hole_east1", "east",
        "/domains/areas/city/cemetary/room/w1", "west",
        });
}

