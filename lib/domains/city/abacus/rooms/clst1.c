/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"
 
void setup(void) {
    set_light(1);
    set_short("Christopher Lange Street - East");
    set_long("This is a private road called Christopher Lange street.\n" +
                "This road ends here at the intersection with Eve Street.\n"+
		"Grass is on the north and south of the road.\n"+
		"The road is made of clean asphalt. This place feels warm\n"+
		"and quiet. A street lamp is on the south of the road.\n"+
		"There seems to be some sort of building to the north as\n"+
		"well. The road goes west, and a building is north.\n");

    set_exits((["west" : ROOMS+"clst2",
                "east" : ROOMS+"eve_street4"]));
    add_item("stop", "The stop is marked by a sidewalk.");
            add_item("sidewalk", "The sidewalk marks the end of the street, and goes\n" +
            "around the west, north and south parts of the street.");
            add_item("clean asphalt","asphalt","Black asphalt covering the entire road. It is two lanes.");
            add_item("green grass","grass","Real grass, which is very green.");
            add_item("lamp","street lamp","Very high street lamps that are on top of concrete poles.");
            add_item("pole","concrete pole","Two concrete poles, each supporting one lamp.");
            add_item("street","It goes east from here.");
            add_item("building","A small building to the north.");
}

