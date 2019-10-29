inherit "std/room";
#include "../area.h"

object ob,ob2;

void setup(void) {
    if (!present ("mutant",this_object())) {
      ob=clone_object("/domains/required/monsters/monster");
      ob->set_name ("larry");
      ob->set_alias ("mutant");
      ob->set_short ("Larry the mutant");
      ob->set_long ("Larry has suffered bad toxic.\n"+
                    "his body is badly changed from\n"+
                    "nuclear radiation.\n"+
                    "");
      ob->set_level (12);
      ob->set_ac (6);
      ob->set_wc (10);
      ob->set_race ("mutant");
      ob->set_gender (1);
      ob->load_chat (5,({"Larry smokes his joint.\n",
                          "Larry adjusts his harness.\n",
			  "Larry says: I gUeSs YoU aRe qUiTe JeaLouS, Eh?\nLarry points at his harness.\n",
			  "Larry says: YoU ProBaBly wiSHed YoU hAd A HarNeSS LIke ThIs !\n",
			  }));
      ob->load_a_chat (5,({ "Larry screams!\n",
                             "Larry growls: Lay off!\n",
                             "Larry tries to bite you!\n",
			     }));
      ob2=clone_object ("obj/drug");
      ob2->set_name ("joint");
      ob2->set_short ("a joint");
      ob2->set_take (2);   /* smoke */
      ob2->set_long ("It's a marijuana joint.\n");
      ob2->set_heal (5);
      ob2->set_strength (5);
      ob2->set_consumer_mess ("You inhale what's left of the joint");
      ob2->set_consuming_mess ("smokes a joint");
      move_object (ob2,ob);
      ob2=clone_object("/std/armor");
      ob2->set_name ("harness");
      ob2->set_short ("a metal harness");
      ob2->set_long ("It's a strong metal harness.\n");
      ob2->set_ac (18);
      ob2->set_value (3000);
      ob2->set_weight (6);
      ob2->set_type ("armour");
      ob2->set_value (2000);
      move_object (ob2,ob);
      move_object (ob,this_object());
      ob->init_command ("wear harness");
    }
     

    set_outdoors(1);
    set_light(1);
    short_desc = "in an alley";
    
    long_desc = 
        "You stand in a dark alley.\n"
        + "The alley continues north-south.\n";
    dest_dir = ({
        ROOM+"alley_01", "north",
        ROOM+"alley_03", "south",
	"obj/chopper/helicopter_base","up",
        });
    items_arr = ({
      "alley","It's dark and gloomy",
          });

}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

int query_roommaker_access() {  return 1;  }

