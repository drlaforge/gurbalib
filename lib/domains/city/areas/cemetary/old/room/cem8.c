/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";
int cut;

reset(arg) {
    if (arg) return;

    cut=0;
    set_outdoors(1);
    set_light(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand on a path running north and south through the cemetary.\n"
        + "The vegetation is very dense here, which makes you unsure if you will\n"
        + "make it further north of here. You can see a house to the north.\n";
items = ({
	"path","The path seems to get more vegetated the further north",
	"cemetary","You stand in the middle of the cemetary",
	"vegetation","#vege",
	"house","It's look like the cremathory",
	});
    dest_dir = 
        ({
	"/room/cemetary/cem5","south",0,
	"/room/cemetary/cem7","west",0,
        "/room/cemetary/cem9", "east",0,
	"room/cemetary/cem11","north","#mnorth",
        });
}

init(){
	::init();
	add_action ("cut","cut");
	add_action("dig","dig");
}

vege() {
 write ("It's very thick.\nYou cant go further north without something to cut with.\n");
}

mnorth() {
 if(present("machete",this_player()) ||
    present("sword",this_player()) ||
    present("knife",this_player())) {
  if (!cut) { write ("You cut the vegetation.\n"); cut++; }
  write("You walk your way through the vegetation.\n");
  return 0;
 }
 if(!cut) {
  write("The vegetation is to thick to go that way. You need something to cut your way\n"+
  "through the vegetation.\n");
  say(this_player()->query_name()+" failed to go through the vegetation.\n");
  return 1;
 }
}

cut () { write ("Just walk north. It will cut automatically.\n"); return 1; }

dig(){
	write("You dig but don't find anything.\n");
	return 1;
}
