/* ROOMMAKER..  Modified by Thorwald. */

inherit "room/room";
int fkey;

reset(arg) {
fkey = 0;
    if (arg) return;

    set_outdoors(1);
    set_light(1);
    short_desc = "a cemetary house";
    
    long_desc = 
        "You stand by a house on the cemetary. The house looks very old and got a huge\n"
        + "door at the front. There is a staircase leading up to the house.\n";
items = ({
	"house","You can see two windows on the frontside",
	"windows","Looking in through the window is pointless. It's to dark inside",
	"door","It's a huge wooden door",
	"staircase","There is a doormat on the staircase",
	({"doormat","mat"}),"#mat",
	});
    dest_dir = 
        ({
        "/domains/areas/city/cemetary/room/cem8", "south",
        "/domains/areas/city/cemetary/room/house1", "north",
        });
}

init(){
	::init();
	add_action("north","north");
	add_action("north","n");
	add_action("lift","lift");
	add_action("lift","move");
	add_action("lift","look");
	add_action("lift","get");
	add_action("open","open");
	add_action("unlock","unlock");
	add_action("close","close");
	add_action("lock","lock");
	add_action("clean","clean");
}
clean(str){
	if(str=="feet"||str=="your feet"){
	if(fkey==0){
	write("When you clean your feet you feel something under the doormat.\n");
        say(this_player()->query_name()+" cleans "+this_player()->query_possessive()+
            " feet on the doormat.\n");
	return 1;
	}
	write("You clean your feet on the doormat.\n");
        say(this_player()->query_name()+" cleans "+this_player()->query_possessive()+
            " feet on the doormat.\n");
	return 1;
	}
	write("Clean what?\n");
	return 1;
}
int dstat;
north(){
int stat;
stat = query_door();
if(stat==0){ write("The door is locked.\n"); return 1; }
if(stat==1){ write("The door is closed.\n"); return 1; }
say(this_player()->query_name()+" leaves north.\n");
move_object(this_player(),"/domains/areas/city/cemetary/room/house");
write("You walk through the door.\n");
command("look",this_player());
say(this_player()->query_name()+" arrives.\n");
return 1;
}

mat() {
 write ("It's a red doormat with the text: Clean your feet.\n");
 if (!fkey) { write ("There is something under the mat.\n"); return 1; }
}

lift(str){
	if(str=="doormat"||str=="under doormat"||str=="mat"||str=="under mat")
	{
	if(fkey==1) { write("You find nothing.\n"); return 1; }
	write("You found a key under the doormat.\n");
	say(this_player()->query_name()+" found a key under the doormat.\n");
	fkey = 1;
	move_object(clone_object("/domains/areas/city/cemetary/obj/key"),this_player());
	return 1;
}
}
query_door(){
	return dstat;
}
open(str){
int stat;
stat = dstat;
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
	return 1;
}
close(str){
int stat;
stat = dstat;
	if(str != "door"){ write("Close what?\n"); return 1; }
	if(stat==0){ write("The door is locked.\n"); return 1; }
	if(stat==1){ write("The door is closed already.\n"); return 1; }
	write("You close the door.\n"); 
	say(this_player()->query_name()+" closed the door.\n");
	dstat = 1;
	return 1;
}
unlock(str){
int stat;
stat = dstat;
	if(str != "door"){ write("Unlock what?\n"); return 1; }
	if(!present("small iron key",this_player())){
	write("You havent got the key.\n");
	return 1;
	}
	if(stat==1){ write("The door is already unlocked.\n"); return 1; }
	if(stat==2){ write("The door is open.\n"); return 1;
}
	write("You unlock the door.\n");
	say(this_player()->query_name()+" unlocks the door.\n");
	dstat = 1;
	return 1;
}
lock(str){
int stat;
stat = dstat;
	if(str != "door"){ write("Lock what?\n"); return 1; }
	if(!present("small iron key",this_player())){
	write("You havent got the key.\n");
	return 1;
	}
	if(stat==0){ write("It's already locked.\n"); return 1; }
	if(stat==2){ write("Close the door first.\n"); return 1; }
	write("You lock the door.\n");
	say(this_player()->query_name()+" locks the door.\n");
	dstat = 0;
	return 1;
}
query_d(in){
dstat = in;
}
