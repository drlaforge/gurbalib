

inherit "room/room";
int dug;

reset(arg) {
dug = 0;
    if (arg) return;

    set_light(1);
    set_outdoors(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand on a path running north and south through the cemetary.\n"
        + "There are tombstones standing beside the path, most of them broken\n"
        + "with unreadable inscriptions. You can see a building further to the\n"
        + "north.\n";
items = ({
	"path","It's a path leading north and south. It looks quite well used after all",
	"tombstones","Most of them are broken",
	"tombstone","You find a tombstone with a readable inscription saying: unknown",
	"inscriptions","Most of them unreadable. You can see one description saying: unknown",
	"building","The building is further to the north from here",
	"inscription","You notice a readable inscription saying: unknown",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem2", "south",
        "/room/cemetary/cem8", "north",
        "/room/cemetary/cem4", "west",
        "/room/cemetary/cem6", "east",
        });
}

query_light() {
    return 1;
}
query_room_maker() {
    return 101;
}

/*
    remove the comments around the "room is modified()" code
    below to prevent changes you have done to this room to
    to be lost by using the room maker
*/
/*
room_is_modified() {
    return 1;
}
*/

/*
 make your additions below this comment, do NOT remove this comment
--END-ROOM-MAKER-CODE--
*/

init(){
	add_action("read","read");
	add_action("dig","dig");
	::init();
}
read(str){
	if(str=="tombstone"||str=="inscription"){
	write("You read an inscription saying: unknown.\n");
	return 1;
	}
}
dig(){
int mon;
	if(!present("shovel",this_player())){
	write("You need a shovel to dig.\n");
	return 1;
	}
	if(dug==1){
	write("You notice the grave is already dug up.\n");
	return 1;
	}
	dug = 1;
mon = 50 + random(50);
	write("You dig for a while and find a corpse containing "+mon+" dollars.\n");
	write("You decide to take the money.\n");
	this_player()->add_money(mon);
	return 1;
	}

