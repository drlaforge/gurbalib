
inherit "std/room";
#include "../area.h"

object ob, ob2, sword;
int sword_present;

init() {
  ::init();
    add_action("search","search");
  }
     
void setup(void) {
    if(!present("ricky",this_object())) {
      ob=clone_object("/std/monster");
      ob->set_name("ricky");
      ob->set_alias("warrior");
      ob->set_short("Ricky the notorious gangleader");
      ob->set_long("Ricky is the notorious leader of the 'Devils'. He has\n"+
		   "a wide scar below his right eye. He stares at you with\n"+
		   "a evil smile on his face.\n");
      ob->set_level(10);
      ob->set_ac(1);
      ob->set_wc(10);
      ob->set_aggressive(1);
      ob->set_chance(20);
      ob->set_spell_mess1("Ricky kicks you right in your face.");
      ob->set_spell_mess2("Ricky kicks you right in your face.");
      ob->set_spell_dam(20);
      move_object(ob,this_object());
      
      ob2=clone_object("/std/weapon");
      ob2->set_name("iron bar");
      ob2->set_short("an iron bar");
      ob2->set_long("A long heavy bar of pure iron.\n");
      ob2->set_class(10);
      ob2->set_value(250);
      ob2->set_weight(2);
      ob2->set_alias("bar");
      move_object(ob2,ob);
      command("wield bar",ob);
      sword_present = 1;
    }

     
    set_light(1);
    set_outdoors(1);
    short_desc = "a gloomy backyard";
    set_long_f("You are in a very dark backyard. "+
      "The air is filled with the smell of rotten trash. "+
      "All around you see rusty trashbins spread out on the ground. "+
      "Big rats feast on some old food scraps. Pieces of the gray "+
      "walls have fallen to ground. In front of you the backyard "+
      "ends with a high wooden fence containing the old text 'The Devils "+
      "rule the world!'.\n");
    dest_dir=({
      ROOM+"alley3","east"
    });
    items_arr=({
      "rats","They seems to have lived well on leftovers","pieces",
      "small pieces of cement","walls","They look old and dusty",
      "fence","A high wooden fence with a lot of writing on it. The\n"+
      "biggest one reads: The Devil's rule the world!",
      ({ "bins", "trashbins", "bin" }), "#search",
      ({"text","writing","grafitti"}),
      "The largest of the grafitti reads: The Devil's rule the world!",
    });
}
    
search(){
    if(present("ricky",this_object())) {
      writef("A wicked blow from Ricky's iron bar takes your mind off "+
          "of that.\n");
      return 1;
    }
    if(sword_present) {
      write("A very rusty trashbin with a lot of bulges\n"+
	    "In it you find an antique sword.\n");
      say(this_player()->query_name()+" finds a antique sword.\n");
      sword = clone_object("obj/headcutter");
      move_object(sword,this_object());
      sword_present = 0;
      return 1;
    }
    write("A very rusty trashbin with a lot of bulges\n"+
	  "You don't find anything of interest in it.\n");
    return 1;
}
  

