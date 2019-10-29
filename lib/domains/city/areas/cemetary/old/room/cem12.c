/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";

reset(arg) {
	if(!present("man",this_object()))
move_object(clone_object("/obj/cemetary/man"),this_object());
	if (arg) return;

    set_outdoors(1);
    set_light(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand in the corner of the cemetary. There is a fence blocking the way\n"
        + "to the east and north. You can see a house to the west but you doubt you \n"
        + "can go there because of the extremely thick vegetation.\n"+
          "There is a small toolshed to the east.\n";
items = ({
	"cemetary","You stand at the northeast side of the cemetary",
       "toolshed", "You can enter it",
	"fence","The fence is very high",
	"house","It's made of stone and looks very old",
	"vegetation","You doubt that you can go west of here because of the thick vegetation",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem9", "south",
        "/room/cemetary/toolshed", "east",
        });
}

