/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";

int fkey,dstat;
reset(arg) {
fkey = 0;
dstat = 0;
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "a cemetary house";
    
    long_desc = 
"You stand inside an old house in the cemetary. There is a staircase\n"+
"leading up. There are doors leading south and west.\n"+
"There is a trapdoor on the floor.\n";
items = ({
	"door","It's a huge wooden door",
	});
    dest_dir = 
        ({
"/domains/areas/city/cemetary/room/cem8","south",
	"/domains/areas/city/cemetary/room/houseliv", "west",
	"/domains/areas/city/cemetary/room/houseatt", "up",
	"/domains/areas/city/cemetary/room/housecell", "down",
        });
items = ({ ({ "trapdoor","trap" }) , "#trap",
	     "staircase", "It's a rusty staircase",
	   });
}

init(){
	::init();
	add_action("south","south");
}
trap () {
	write(
"It's a trapdoor leading down into the cellar. It looks dark down there.\n");
}

south(){
 writef("You open the door and quickly leave through it.\n");
 return 0;
}
