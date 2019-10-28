inherit "std/room";
#include "../area.h"

object ob,ob2;

void setup(void) {
    if (!present ("droid",this_object())) {
      ob=clone_object ("obj/mean_monster");
      ob->set_race("robot");
      ob->set_name ("the droid");
      ob->set_alias ("droid");
      ob->set_alt_name ("broken droid");
      ob->set_short ("a broken droid");
      ob->set_long ("This is a small broken droid.\n"+
		    "It's a defender, model VI-E.\n"+
		    "The droid is still alive, but\n"+
		    "most functions have been destroyed.\n"+
		    "watch out, it might go berserk.\n"+
		    "");
      ob->set_level (17);
      ob->set_ac (2);
      ob->set_wc (15);
      ob->set_gender (0);
      ob->set_race("robot");
      ob->load_chat (10,({"The droid makes a buzzing sound.\n",
			  "The droid says: To prote*bzzzz* and serve *bzzz*\n",
			  }));
      ob->load_a_chat (10,({ 
			     "The droid foolishly tries to attack itself.\n",
			     "The droid says: I'm warning you! *bzzzz*\n",
			     }));
      ob2 = clone_object("/obj/monsters/droidgun.c");
      move_object (ob2,ob);
      ob->set_spell_chance (6);
      ob->set_spell_dam (20);
      ob->set_spell_mess1 ("The droid fires its lasergun!\n");
      ob->set_spell_mess2 ("The droid fires its lasergun at you!\n");
      move_object (ob,this_object());
      ob->init_command ("wield gun");
    }
     

    set_outdoors(1);
    set_light(1);
    short_desc = "in an alley";
    
    long_desc = 
	"You stand in a dark alley.\n"
	+ "The alley continues north-south.\n";
    dest_dir = ({
	ROOM+"alley_02", "north",
	ROOM+"alley_04", "south",
      });
    items_arr = ({
      "alley","It's dark and gloomy",
	  });
}

