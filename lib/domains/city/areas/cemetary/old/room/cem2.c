

inherit "room/room";

object ob;
int i;

reset(arg) {
    if (arg) return;
    move_object(clone_object("/obj/cemetary/butterfly"),this_object());
    set_light(1);
    set_outdoors(1);
    short_desc = "cemetary";
    
    long_desc = 
        "You stand at the entrance of the cemetary. There is a path going to the \n"
        + "north that leads to what looks like a building. All around you there are\n"
        + "tombstones. Some of them are still standing up, but in most cases they have\n"
        + "been destroyed and lays broken on the ground.\n";
items =	({
	"entrance","You look around at all these brooken tombstones",
	"path","It looks like people has been walking the path recently",
	"building","The building is far away to the north",
	"tombstones","Most of them are destroyed. You notice nothing special",
	"tombstone","There is nothing special. Just a broken tombstone",
	});
    dest_dir = 
        ({
        "/room/cemetary/ent", "south",
        "/room/cemetary/cem5", "north",
        "/room/cemetary/cem1", "west",
        "/room/cemetary/cem3", "east",
        });
    i=0;
    while (i<9) 
   {
        ob = clone_object ("obj/cemetary/bird");
        move_object (ob,this_object());
        i++;
    }
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

init(){ ::init();
add_action("south","south");
}
south(){
if(this_object()->query_name()=="A pigeon") return 1;
}
