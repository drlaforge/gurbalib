/* Newbie donation room, code stolen from Tenno/Hackers/UG */
/* Anyone can donate, only NEWBIE_LEVEL can retrieve */

#include <def.h>
#include <tune.h>
#define LOG "/log/newbie_donation"

static object book;
int write_file;
string log;
string chat_str;
inherit STD_ROOM; 
#include "../area.h"
object room;
mapping functions = (["list": 
                      (["all": "all", 
                        "s": "shootweapons",
                        "w": "weapons",
                        "h": "heals",
                        "a": "armour",
                        "b": "ammunition",
			"u": "uniques",
                        "m": "other objects"])
                      ]);

void setup(void) {
	if(!room) {
		room=clone_object("/std/room");
		room->add_exit("out",ROOM+"donation");
		room->fix_light(1);
		room->set_short("Newbie Donation");
		room->set_no_clean_up(1);
		room->set_no_boost(1);
	}
	 
	set_no_clean_up(1);
	set_outdoors(0);
	set_light(1);
	set_short("The Mob Gang Donation Room");
	set_long_f("This room is where anyone can donate items and equipment to "+
		"new citizens of Abacus. The room is fairly dirty and it has a stale "+
		"smell to it which comes from it not having any windows or sunlight. "+
		"The walls are covered in grafitti and the floor is covered in litter "+
		"and rubbish. Around the room are various shelves and boxes which are "+
		"used to store the equipment that is donated. For information on how "+
		"to use this room type 'help room'.\n");
	add_item(ROOM+"","You're in the donation room.");
	add_item(({"windows","sunlight"}),"Doh, read the description again fool.");
	add_item(({"wall","walls"}),"You've no idea what the natural colour of the walls are due to the\n"+
		"sheer amount of grafitti.");
	add_item("grafitti","Incomprehensible grafitti that is scrawed on just about every square\n"+
		"inch of the walls. The kids of today huh?");
	add_item("floor","The floor is covered in litter.");
	add_item(({"litter","rubbish"}),"It's hard to move without tredding on or kicking some of the litter.");
	add_item(({"shelf","shelves","boxes","box"}),"The shelves and boxes are used to store the equipment that is left here.\n");
	add_smell(({ROOM+"","air"}),"The air is stale and musky.");
	add_exit("west",ROOM+"school_entr");
}

init(){
	::init();
	if( this_player()->query_level() >= ROOKIE_LEVEL )
	print_warning();
	add_action("enter","enter");
	add_action("borrow","borrow");
	add_action("donate","donate");
	add_action("list","list");
	add_action("help_room","help");
}


print_warning(){
	write(
		"-->WARNING<---\n"+
		"DO NOT FRESH THIS ROOM WITHOUT ARCH APPROVAL\n"+
		"\n"+
		"Freshing this room will result in you deleting the entire contents\n"+
		"of the donation room.\n"+
		"Make sure you have arch approval before doing ANYTHING in here.\n\n");
	return ;
}


help_room(str){
	if(str!=ROOM+"")
		return 0;
	W("The massive stone platform reads:\n\n"+
		"- 'donate' <object/all> to donate a weapon or armour.\n"+
		"- 'borrow' <object> to borrow a weapon for temporary use.\n"+
		"- 'list (w/s/b/h/a/m)' to list the items which you can borrow.\n"+
		"        w: weapons\n"+
		"        s: shootweapons\n"+
		"        b: ammoboxes\n"+
		"        h: heals\n"+
		"        a: armour\n"+
		"        u: uniques\n"+
		"        m: everything else\n"+
		"Just 'list' to see them all.\n\n");
	return 1;
}

donate(str){
	object ob;
	int i,flag;
	if(!str) 
		return !notify_fail("What do you wish do donate?\n");
	if(str=="all"){
		ob=all_inventory(TP);
		for(i=0;i<sizeof(ob);i++) 
      			flag+=(!move_object(ob[i],room));
		if(flag){
			action("#NA ## all of #PO possessions.","donate-donates");
			write_file(LOG, ""+TP->QN+" donated all their stuff on "+ctime(time())+".\n");
		}
		return write("Ok!\n");
	}
  	if(!(ob=present(str,TP)))
		return W("But you don't have that.\n");
  
	if(!move_object(ob,room)){
		action("#NA ## "+ob->short()+".","donate-donates");
		if(TP->QL > NEWBIE_LEVEL && !random(5))
			W("The newbies of Abacus thank you.\n");
		if(!log){
			rotate_fun(LOG);
			write_file(LOG, ""+TP->QN+" donated "+ob->short()+" on "+ctime(time())+".\n");
		}
		else{
			rotate_fun(log);
			write_file(log, ""+TP->QN+" donated "+ob->short()+" on "+ctime(time())+".\n");
		}

		return 1;
	}
	else
		return write("You failed.\n");
}

borrow(str){
	object next_ob;
	object ob;
	if(!str)
		return !notify_fail("Borrow what? See 'help room' for details on how to use the donation room.\n");
	if(TP->query_ghost())
		return !notify_fail("Try again, when you have a body!\n");
	if(TP->QL > NEWBIE_LEVEL && TP->QL < SCI_LEVEL)
		return !notify_fail("Only people of level "+NEWBIE_LEVEL+" or below can borrow equipment from here.\n");
	if(TP->query_guest())
		return !notify_fail("Only registered newbies can borrow from here.\n");
	if(str=="all"){
		ob = first_inventory(room);
		while( ob && !move_object(ob,TP) ) {
			action("#NA ## #VNA from the donation room.", "borrow-borrows", ob);
			ob = first_inventory(room);
		}
		write_file(LOG, ""+TP->QN+" borrowed all they could carry on "+ctime(time())+".\n");
		return 1;
	}

	if(!(ob=present(str,room)))
		return W("You can't find that item.\n");
    
	if(!move_object(ob,TP)){
		action("#NA ## #VNA.", "borrow-borrows", ob);
		if(!log){
			rotate_fun(LOG);
			write_file(LOG, ""+TP->QN+" borrowed "+ob->short()+" on "+ctime(time())+".\n");
		}
		else{
			rotate_fun(log);
			write_file(log, ""+TP->QN+" borrowed "+ob->short()+" on "+ctime(time())+".\n");
		}
		return 1;
	}
      	else 
		return write("You failed.\n");
}

string parse_argument(string func, string argument){
	mapping arg;
	arg = functions[func];
	return arg[argument];
}

list(arg){
	mapping what;
	string namn;
	string argument;
	int i;
	if(!arg)
		arg = "all";
	what = sorter(room, arg);
	argument = parse_argument("list", arg);
	if(!argument)
		return 0;
	if(m_sizeof(what) < 1){
		if (arg != "all") 
			return W("There are no " + argument + " in storage.\n");
		else
			return W("The donation room is empty at the moment.\n");
	}
	else{
		namn = m_indices(what);
		W("Items available:\n\n");
		printf(" Number of:          %s:\n", 
		(argument == "all" ? "Objects" : capitalize(argument)));
		for (i = 0; i < sizeof(namn); ++i) 
			printf(" [%3d]%15s%s\n", what[namn[i]],"", capitalize(namn[i]));
		W("\n");
	}
	return 1;
}

mapping sorter(object room, string arg){
	object *ob;
	int i;
	mapping map;               
	ob  = all_inventory(room);
	ob  = all_inventory(room);
	map = ([ ]);
	for (i = 0; i < sizeof(ob); ++i){
		switch (arg){
			case "s":
				if (ob[i]->query_velocity()) {
					if (map[ob[i]->short()]) 
						map[ob[i]->short()]++;
					else 
						map += ([ob[i]->short() : 1]);
				}
				break;
			case "a":
				if (ob[i]->armour_class()){
					if (map[ob[i]->short()]) 
						map[ob[i]->short()]++;
					else 
						map += ([ob[i]->short() : 1]);
				}
				break;
			case "w":
				if (ob[i]->weapon_class() && !ob[i]->query_velocity()){
					if (map[ob[i]->short()]) 
						map[ob[i]->short()]++;
					else 
						map += ([ob[i]->short() : 1]);
				}
				break;
			case "b":
				if (ob[i]->query_ammo() && !ob[i]->query_velocity()){
					if (map[ob[i]->short()]) 
						map[ob[i]->short()]++;
					else 
						map += ([ob[i]->short() : 1]);
				}
				break;
			case "u":
				if (("/obj/daemons/uniqued")->query_unique(ob[i])){
					if (map[ob[i]->short()]) 
						map[ob[i]->short()]++;
					else 
						map += ([ob[i]->short() : 1]);
				}
				break;
			case "h":
				if(ob[i]->query_heal()){
					if (map[ob[i]->short()]) 
						map[ob[i]->short()]++;
					else 
						map += ([ob[i]->short() : 1]);
				}
				break;
			case "m":
				if(!ob[i]->query_calibre() && !ob[i]->armour_class() && !ob[i]->query_ammo() && !ob[i]->weapon_class() && !ob[i]->query_heal()){
					if (map[ob[i]->short()]) 
						map[ob[i]->short()]++;
					else 
						map += ([ob[i]->short() : 1]);
				}
				break;
			case "all":
				if (map[ob[i]->short()]) 
					map[ob[i]->short()]++;
				else 
					map += ([ob[i]->short() : 1]);
				break;
			default:
				map = ([ ]);
		}
	}
	return map;
}

room_get(){
	if(TP->QL < SCI_LEVEL) return;
	move_object(room,TP);
	return 1;
}

enter(){
	if(TP->QL < SCI_LEVEL) return;
	move_object(TP,room);
	return 1;
}

query_peace(){ return "This is a peaceful place";}


rotate_fun(log_file){
	/* OK, if the file is Bigger than 100K, move it to .bak */
	/* If .bak exists get rid of it. Then start again fresh. And save some disk space.    */
	string tmp;
	int i;
	if(file_size(log_file) > 100000) {
		rm(log_file+".bak");
		for(i=1; tmp = read_file(log_file,i,100); i+=100)
		write_file(log_file+".bak",tmp);
		rm(log_file);
	}
  	return 1;
}
