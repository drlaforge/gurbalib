/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_outdoors(1);
    set_light(0);
    short_desc = "Cemetary house(s)";
    
    long_desc = 
"You stand inside the house. Nothing here.";
items = ({
	"door","It's a huge wooden door",
	});
    dest_dir = 
        ({
        "/room/cemetary/cem11", "south",
        });
}

init(){
	::init();
	add_action("south","south");
	add_action("south","s");
	add_action("open","open");
	add_action("unlock","unlock");
	add_action("close","close");
	add_action("lock","lock");
}
int fkey;
int dstat;
south(){
int stat;
stat = query_door();
if(stat==0){ write("The door is locked.\n"); return 1; }
if(stat==1){ write("The door is closed.\n"); return 1; }
say(this_player()->query_name()+" leaves south.\n");
move_object(this_player(),"/room/cemetary/cem11");
say(this_player()->query_name()+" arrives.\n");
return 1;
}
query_door(){
object rum;
rum = "/room/cemetary/cem11.c";
if(!rum) { write("error\n"); return 1; }
dstat = rum->query_door();
	return dstat;
}
open(str){
int stat;
stat = query_door();
	if(str != "door"){
	write("Open what?\n");
	return 1;
	}
	if(stat==0){
	write("The door is locked.\n");
	return 1;
	}
	if(stat==2){
	write("The door is opened already.\n");
	return 1;
	}
	write("Ok.\n");
	dstat = 2;
	query_d();
	return 1;
}
close(str){
int stat;
stat = query_door();
	if(str != "door"){ write("Close what?\n"); return 1; }
	if(stat==0){ write("The door is locked.\n"); return 1; }
	if(stat==1){ write("The door is closed already.\n"); return 1; }
	write("You close the door.\n"); 
	dstat = 1;
	query_d();
	return 1;
}
unlock(str){
int stat;
stat = query_door();
	if(str != "door"){ write("Unlock what?\n"); return 1; }
	if(!present("small iron key",this_player())){
	write("You havent got the key.\n");
	return 1;
	}
	if(stat==1){ write("The door is already unlocked.\n"); return 1; }
	if(stat==2){ write("The door is open.\n"); return 1;
}
	write("You unlock the door.\n");
	dstat = 1;
	query_d();
	return 1;
}
lock(str){
int stat;
stat = query_door();
	if(str != "door"){ write("Lock what?\n"); return 1; }
	if(!present("small iron key",this_player())){
	write("You havent got the key.\n");
	return 1;
	}
	if(stat==0){ write("It's already locked.\n"); return 1; }
	if(stat==2){ write("Close the door first.\n"); return 1; }
	write("You lock the door.\n");
	dstat = 0;
	query_d();
	return 1;
}
query_d(){
object rum;rum = "/room/cemetary/cem11.c";
rum->query_d(dstat);
return 1;
}
