
inherit "std/room";
#include "../area.h"

void setup(void) {
  set_outdoors(1);
  set_light(1);
  short_desc = "a dark alley";
  long_desc="You are walking along a very dark alley.\n"+
            "Your mind screams of fear and tells you to leave.\n"+
            "Some wierd disgusting smell of rotten meat reaches your\n"+
	    "nose and makes you wanna puke. The alley splits up in four\n"+
	    "directions here.\n";
  dest_dir=({
             ROOM+"alley3","north","#Move",
	     ROOM+"alley4","west",0,
	     ROOM+"alley5","east",0,
	     ROOM+"alley1","south",0,
	     });
    add_smell("meat","The smell of rotten meat makes you want to puke.");
    add_smell("rotten meat","The smell of rotten meat makes you want to puke.");
  }

Move() {
  if(!present("warrior", this_object()))
    return 0;
  write("A warrior bars your way.\n");
  return 1;
}

extra_reset(how_many,room) {
    object orc, weapon, ob;
    int n,i,class,value,weight;
    string w_name, alt_name, s_name, alias, name;

    alias=allocate(8);
    alias[0]="rob";
    alias[1]="ken";
    alias[2]="trash";
    alias[3]="bull";
    alias[4]="chip";
    alias[5]="bran";
    alias[6]="killroy";
    alias[7]="lennie";
    name=allocate(8);
    name[0]="Rob";
    name[1]="Ken";
    name[2]="Trash";
    name[3]="Bull";
    name[4]="Chip";
    name[5]="Bran";
    name[6]="Killroy";
    name[7]="Lennie";

     i = 0;
    if (!present("warrior",room)) {
while(i<how_many) {
	    i += 1;
    ob = clone_object("/std/monster");
    ob->set_alias(alias[i-1]);
    ob->set_name(name[i-1]);
    ob->set_alt_name("warrior");
    ob->set_short(name[i-1]+" the warrior of the Devils");
    ob->set_long("He's a warrior of the streetgang the Devils. He's\n"+
	       "about 15 years old.\n");
    ob->set_level(random(2) + 1);
    ob->set_hp(30);
    ob->set_aggressive(1);
 	    n = random(4);
	    weapon = clone_object("/std/weapon");
	    if (n == 0) {
		w_name = "chain";
                s_name = "a chain";
		class = 5;
		value = 8;
		weight = 1;
	      }
	    if (n == 1) {
                w_name = "small wooden bar";
                s_name = "a small wooden bar";
		class = 7;
		value = 15;
		weight = 1;
		alt_name = "bar";
	    }
	    if(n == 3) {
                w_name = "crowbar";
                s_name = "a crowbar";
		class = 8;
		value = 20;
		weight = 3;
		alt_name = "bar";
	    }
	    if (n == 2) {
                w_name = "rambo knife";
                s_name = "a Rambo knife";
		class = 9;
		value = 25;
		weight = 2;
		alt_name = "knife";
	    }
            weapon->set_name(w_name);
            weapon->set_short(s_name);
            weapon->set_class(class);
            weapon->set_value(value);
            weapon->set_weight(weight);
            weapon->set_alt_name(alt_name);
	    move_object(weapon, ob);
	    command("wield " + w_name, ob);
	    move_object(ob, room);
	}
    }
}
