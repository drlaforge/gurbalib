inherit "std/room";
#include "../area.h"

int rubbish;
object key;
object lady;
object we;

void setup(void) {
  if (!present ("streetlady",this_object())) {
    lady=clone_object ("obj/mean_monster");
    lady->set_name ("lady");
    lady->set_alias ("streetlady");
    lady->set_short ("a streetlady");
    lady->set_gender (2);
    lady->set_long ("She's a beauty, and she knows how to fight.\n"+
		    "She has painted war symbols in her face.\n");
    lady->set_level (14);
    lady->set_hp (200);
    lady->set_wc (15);
    lady->set_ac (5);
    lady->load_a_chat ( 20,({
      "Streetlady says: Come on, you can do better!\n",
      "Streetlady says: You're nothing but a whimp!\n",
      "Streetlady says: Ouuuhh!\n",
      "Streetlady says: I'll get you!\n",
    }));
    we=clone_object("/std/weapon");
    we->set_name ("whip");
    we->set_short ("a leather whip");
    we->set_long ("A nice leather whip.\n");
    we->set_wc (11);
    we->set_value (300);
    we->set_weight (2);
    move_object (we,lady);
    lady->init_command ("wield whip");
    move_object (lady, this_object());
  }
     

    rubbish = 1;
    set_outdoors(0);
    set_light(1);
    short_desc = "in a building";
    
    long_desc = 
        "You stand in a building.\n"
        + "You see some rubbish on the ground.\n";
    dest_dir = ({
        ROOM+"building1", "west",
        });
    items_arr = ({
          "rubbish","#rubbish",
          });
}

rubbish () {
  if (!rubbish) { write ("Nothing but dust and concrete.\n"); return 1; }
  write ("You look through the rubbish and find a key.\n");
  say (this_player()->query_name()+" finds a key.\n");
  key=clone_object("/std/object");
  key->set_name ("key");
  key->set_alias ("sewer_key");
  key->set_weight (1);
  key->set_value (4);
  key->set_short ("a filthy key");
  key->set_long ("It's a really filthy key.\n");
  if (move_object (key,this_player())) move_object (key,this_object());
  rubbish=0;
  return 1;
}

