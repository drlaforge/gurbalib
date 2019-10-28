inherit "std/room";
#include "../area.h"
string str;

init() {
   ::init();
   add_action("mysign","read");
}

void setup(void) {
     
    set_outdoors(1);
    set_light(1);
    short_desc = "Edge of the Great Swamp.";
    long_desc = 
          "Your are standing at the edge of a great swamp which stretches\n"
        + "ahead to the north. It looks dark and dank in there.\n"
        + "Be careful not to get lost in there, you may never be\n"
        + "found. There is a strange smell coming from the quagmire.\n"
        + "A rickety old sign stands here.\n";
    dest_dir = ({
        ROOM+"swampedge","south",
        });
    items_arr = ({
     ({"east","north","swamp"}),
       "The swamp, dense with plants and tall swamp trees.",
     ({"south","civilization"}),
       "Civilization, back towards the city of Abacus.",
     "water",
       "Water up to your knees, there are shadows of things in the water.",
     ({"plant","plants"}),
       "A copius quantity of dense green plants.",
     ({"tree","trees","tall trees","tall swamp trees","swamp trees"}),
       "Tall mangled swamp trees that blot out the sun.",
     "bushes",
       "Small plants that fill the area.",
     "quagmire",
       "You see muck and slime that makes up the floor of the swamp.",
     ({"sign","rickety sign","old sign","rickety old sign"}),
         "A very old sign, it looks like it dates back to before the wars.\nDespite its age, the sign is still readable.",
           });
     add_smell("swamp","You smell the rancid odor of decay.");
}

mysign(str) {
   if (!(str=="sign")) return 0;
    write( "------------------------\n"
		+"|   NO TRESPASSING     |\n"
		+"|     Government       |\n"
		+"|  Protected  Lands    |\n"
		+"|        ----          |\n"
		+"| Trespassers will be  |\n"
		+"|    shot on sight.    |\n"
		+"------------------------\n");
	say(this_player()->query_name()+" is looking at the sign.\n");
	return 1;
}

