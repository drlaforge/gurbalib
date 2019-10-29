/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";
int batt;

reset(arg) {
batt = 0;
    if (arg) return;

    set_outdoors(0);
    set_light(0);
    short_desc = "living room in a house in a cemetary";
    
    long_desc = 
        "You stand in the living room of the house. There are a sofa placed in\n"
        + "the middle of the room, strategically put heading towards a TV. There is\n"
        + "a bookcase standing towards the wall. In the bookcase you can see an\n"
        + "old stereo.\n";
items = ({
	"sofa","It looks comfortable",
	"tv","The TV has a broken screen, probably unfunctional",
	"bookcase","It's filled with books about evil powers",
	"stereo","It looks like one of the old stereo's driven by batteries",
	"screen","There is a crack running through the whole screen",
	});
    dest_dir = 
        ({
        "/room/cemetary/housekitch", "north",
        "/room/cemetary/house", "east",
        });
}

init(){
	::init();
	add_action("sit","sit");
	add_action("turn","turn");
	add_action("turn","start");
	add_action("get","get");
	add_action("get","take");
	add_action("tune","tune");
}
sit(str){
	if(str!="sofa") return 0;
	write("You sit down. Aww... You wish the TV was functional.\n");
        say(this_player()->query_name()+" sits down on the sofa.\n");
	return 1;
}

turn(str){
	if(str=="on stereo"||str=="stereo"){
	if(batt==1){
                write("Nothing happens.\n");
		return 1;
		}
	write("The stereo goes: Screeeeaaccchhh\n");
	say("The stereo goes: Screeeeaaccchhh\n");
	return 1;
	}
}
get(str){
	if(str=="batteries from stereo"){
	if(batt==1){
		write("Someone has taken them already.\n");
		return 1;
		}
	batt = 1;
move_object(clone_object("/obj/cemetary/batteries"),this_player());
	write("You remove the batteries from the stereo.\n");
	say(this_player()->query_name()+" takes some batteries from a stereo.\n");
	return 1;
	}
	if(str=="batteries"){
if(present("batteries",this_object())) return 0;
		write("from what?\n");
		return 1;
		}
}
tune(str){
	if(str!="stereo") return 0;
	write("You tune the stereo to the local gym-station.\n");
	write("The stereo goes: Stretch - Bend - ahhh - 1 - 2 and bend again.\n");
	say("The stereo goes: Stretch -Bend - ahhh - 1 - 2 and bend again.\n");
	return 1;
}

