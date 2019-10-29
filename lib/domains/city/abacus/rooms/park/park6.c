inherit "std/room";
#include "../../area.h"
void setup(void){
 
	 
add_object(ROOM+"park/mrx", 1);
	set_outdoors(1);
	set_light(1);
	set_short("Nuclear Winter Park");
	set_long_f("This corner of the park is very decrepit and very different from the rest of "+
                   "the park. It seems to be abused a lot by various people. Around the ground are "+
                    "syringes, empty packs and bottles probably containing illegal substances. "+
                   "This is not a safe area for the likes of you and it is best you do not stay "+
                   "here for too long.");
		
        add_item(({"corner","park","corner of the park","park area","area"}),"This is dangereous run down are of the park, used by drug addicts");
        add_item("nuclear winter park","You're stood in the park");
        add_item(({"syringes","containers","container","empty pack","syringe","packs","empty packs","bottles","bottle"}),"Various containers which contained illegal substances.");
        add_item("ground","The ground is littered with bottles");
        add_item("litter","Litter on the ground");
        add_item(({"illegal substances","substances"}),"Illegal substances");
	add_exit("north",ROOM+"park/park7");
        add_exit("west",ROOM+"park/park5");
}

