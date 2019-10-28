/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"
 
void setup(void) {
     
    set_light(1);
    short_desc = "Christopher Lange Street - East";
 
    long_desc = "This is a private road called Christopher Lange street.\n" +
                "This road is paved with asphalt that looks very clean.\n" +
                "The grass is green on both sides of the road and there is\n" +
                "an air of quietness here. There are two street lamps with\n" +
                "concrete poles on the north and south sides of the street.\n" +
                "You feel out of place on this quiet, clean road, when you\n" +
                "think of the busy world from whence you came.\n" +
                "The street continues to the west from here.\n";
               
    dest_dir = ({
                ROOM+"clst1", "east",
                ROOM+"clsq", "west",
            });
    items_arr = ({
            "asphalt", "Black asphalt covering the entire road. It is two lanes.",
            ({"green grass", "grass"}),
            "Real grass, which is very green.",
            ({"lamp","lamps","street lamp","street lamps"}),
            "Very high street lamps that are on top of concrete poles.",
            ({"pole","poles","concrete pole","concrete poles"}),
            "Two concrete poles, each supporting one lamp.",
            "street",
            "It goes west and east from here.",
            });
}
