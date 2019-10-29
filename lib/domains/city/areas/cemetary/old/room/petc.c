

inherit "room/room";

reset(arg) {
    if (arg) return;

    set_light(1);
    set_outdoors(1);
    short_desc = "a pet cemetary";
    
    long_desc = 
        "You are standing in the pet cemetary. This is the place where people bury\n"
        + "their loved deceased pets. The tombstones are not as well made as the ones\n"
        + "you can see in the ordinary cemetary. The whole cemetary is surrounded by\n"
        + "a fence. There are some bushes growing by the fence to the west.\n";
items = ({ "cemetary","You are standing in the pet cemetary",
	   "pets",
"You dig awhile and find an old rotten corpse of a cat. Yuck! You bury it again",
	     "fence","The fence is very high",
	     "bushes","You find a hole in the fence behind the bushes",
	     "bush","You find a hole in the fence behind the bushes",
	     "hole","The hole looks big enough to enter",
	     ({ "tombstone" , "tombstones" , "stones" , "graves" , "tombs" }),
	     "#tomb",
  
	});
    dest_dir = 
        ({
        "/room/cemetary/cem7", "east",
        });
}

query_light() {
    return 1;
}
query_room_maker() {
    return 101;
}

init(){
	::init();
	add_action("enter","enter");
	add_action("dig","dig");
	}
enter(str){
        if(str != "hole") return !notify_fail("Enter what?\n");
	say(this_player()->query_name()+" leaves into a hole.\n");
	write("You leave into the hole.\n");
	move_object(this_player(),"/room/cemetary/clearing");
	say(this_player()->query_name()+" enters from the path.\n");
	command("look",this_player());
	return 1;
	}
tomb(){
int i;
string text;
	text = allocate(8);
	i = random(3);
write("You look on");
if(i==0) write(" a gravemark made of wooden planks stuck in the ground.\n");
if(i==1) write(" a stone on the ground with some text on it.\n");
if(i==2) write(" a gravemark made by a plank lying on the ground.\n");
	i = random(8);
	text[0] = "It's and old anynomous grave with only the RIP letters";
	text[1] = "The words FIDO painted in red is on the gravemark";
	text[2] = "You notice the name FRITZ on the gravemark";
	text[3] = "You read the name EINSTEIN on the gravemark";
	text[4] = "The name THORSTEN is written on the gravemark. Odd name for a pet you think";
	text[5] = "This dog didnt get a nice funeral. Some bones beside a sign saying: DOOPY";
	text[6] = "The name FLUFFY is nicely written a sign";
	text[7] = "The text SNOOPY is written on the gravemark";
	write(text[i]+".\n");
	return 1;
	}
dig(){
	if(!present("shovel",this_player())) return 0;
        write("You dig for a while but don't find anything.\n");
	return 1;
}
