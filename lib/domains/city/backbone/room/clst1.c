/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"
 
void setup(void) {
     
    set_light(1);
    short_desc = "Christopher Lange Street - East";
 
    long_desc = "This is a private road called Christopher Lange street.\n" +
                "This road ends here at the intersection with Eve Street.\n"+
		"Grass is on the north and south of the road.\n"+
		"The road is made of clean asphalt. This place feels warm\n"+
		"and quiet. A street lamp is on the south of the road.\n"+
		"There seems to be some sort of building to the north as\n"+
		"well. The road goes west, and a building is north.\n";

    dest_dir = ({
                ROOM+"clst2", "west",
                ROOM+"eve_street4","east",
            });
    items_arr = ({
            "stop", "The stop is marked by a sidewalk.",
            "sidewalk", "The sidewalk marks the end of the street, and goes\n" +
            "around the west, north and south parts of the street.",
            ({"clean asphalt","asphalt"}),
            "Black asphalt covering the entire road. It is two lanes.",
            ({"green grass", "grass"}),
            "Real grass, which is very green.",
            ({"lamp","street lamp"}),
            "Very high street lamps that are on top of concrete poles.",
            ({"pole","concrete pole"}),
            "Two concrete poles, each supporting one lamp.",
            "street",
            "It goes east from here.",
            "building", "A small building to the north.",
            });
}
