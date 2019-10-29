inherit "std/room";
#include "../area.h"
 
void setup(void) {
    set_light(1);
    set_short("Christopher Lange Street - West");
    set_long("This is the eastern section of a private road.\n" +
                "This road stops to the west, where you can see a building\n" +
                "being constructed. This building has slanted support beams\n" +
                "meeting at the top, looking somewhat like a pyramid. The\n" +
                "road is blocked by a fence. There is a large sign on the fence.\n" +
                "Normally, this area is clear of anything, except the fence\n" +
                "and the road. Now, however, and temporarily, a spectacular\n" +
                "display of the Corporation's prestige is evident. At the side\n" +
                "of the road, there lies a stage. Around the stage are placed\n" +
                "seven banners. One behind a podium, on the stage, and 3 along\n" +
                "each side. The back of the stage is surrounded by nice, green\n" +
                "shrubs. Christopher Lange continues eastwards and Independent\n"+
		"street goes south.\n");

    set_exits((["east" : ROOMS+"clsq",
		"south" : ROOMS+"ind_street1"]));
    add_item("building","An extremely large building, not completely finished.");
            add_item("support beam","beams","beam","support beams","Metal beams that meet at the top of the building.");
            add_item("pyramid", "The building looks vaguely like a pyramid.");
            add_item("fence","A steel mesh fence with barbed wire at the top.");
            add_item("sign", "Read the sign.");
            add_item("display","spectacular display","Many things not seen in a City like this.");
            add_item("side of the road","side","roadside","There is a stage on the side of the road.");
            add_item("stage", "The stage is definitely makeshift, but is not made out of trashy materials.");
            add_item("banner","seven banners","banners","flags","The banners are long, about 10 feet high, and about 3 feet wide. They are\n" +
            "standard Tyrell Corporation flags, hanging vertically.");
            add_item("shrub","shrubs","green shrubs","nice shrubs","hedges","Green hedges about 15 feet high.");
            add_item("podium","small structure","structure","The podium is just a small structure along the middle of the\n" +
                     "stage, fixed with devices to record and amplify sound and pictures of the\n" +
                     "speaker.");
			 add_item("street","The very end of Christopher Lange Street.");
			 add_item("devices","Devices to record and amplify sounds and pictures.");
			 add_item("wire","Just a wire made of copper.");
    /*move_object(clone_object("/players/berne/area/pedestal"),this_object()); //will be added later*/
    add_action("read","read");
    }
 
int read(string str) {
    if (str != "sign") return 0;
    else {
        write ( "The sign reads:\n" +
                "TYRELL CORPORATION ABACUS HEADQUARTERS\n" +
                "--------------------------------------\n" +
                "This building is being constructed to revitalize the city of\n" +
                "Abacus. More information will be provided upon request to the\n" +
                "Tyrell Corporation, or the Abacus HQ Co-Ordinator, Berne\n" +
                "Tyrell.\n" +
                "TYRELL CORPORATION: Making life better.\n");
        return 1;
            }
        }

/*Is this needed in new lib? - Exash 19.10.29 */ 
int query_peace() {
    return 1;
}

