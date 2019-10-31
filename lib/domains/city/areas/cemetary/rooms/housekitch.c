/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "a kitchen in a house in a cemetary";
    
    long_desc = 
        "You stand in a kitchen. There is a sink here. There is a door to\n"
        + "the north leading north into the backyard. South of here you can see\n"
        + "the living room.\n";
items = ({
	"sink","You notice nothing special",
	});
    dest_dir = 
        ({
        "/domains/areas/city/cemetary/room/houseliv", "south",
        "/domains/areas/city/cemetary/room/houseyard", "north",
        });
}

