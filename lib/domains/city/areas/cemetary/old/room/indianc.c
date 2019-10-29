

inherit "room/room";

reset(arg) {
    if (arg) return;
if(!present("stone",this_object()))
move_object(clone_object("/obj/cemetary/stone"),this_object());

    set_light(1);
    set_outdoors(1);
    short_desc = "Indian cemetary";
    
    long_desc = 
        "You stand on an old indian cemetary. There are stones lying on the ground\n"
        + "making a perfect five edged pentagram on the ground.\n"
        + "There is a sign beside the pentagram.\n";
items = ({
	"cemetary","It's an old forgotten indian cemetary",
	"pentagram","It's a pentagram formed by stones on the ground",
	"stones","The stones formes a pentagram on the ground",
	"sign","Maybe you should read it",
	});
    dest_dir = 
        ({
        "/room/cemetary/petc", "east",
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
	::init();
	add_action("read","read");
	add_action("dig","dig");
}
read(str){
	if(str != "sign") return 0;
	write("You read on the sign: Varning! The ground is sour.\n");
	return 1;
	}
dig(){
write("The ground is full of rocks. Its impossible to dig here.\n");
return 1;
}

