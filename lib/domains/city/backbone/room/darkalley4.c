inherit "std/room";
#include "../area.h"
object ob;
void setup(void) {
  if(!present("robot",this_object())) {
    ob=clone_object("/std/monster");
    ob->set_name("The Robot cleaner");
    ob->set_race("robot");
    ob->set_alias("robot");
    ob->set_alt_name("cleaner");
    ob->set_short("A metallic robot cleaner");
    ob->set_long("It is driven by a silent nuclear engine, loaded\n"+
		 "to keep running for two hundred years. The robot\n"+
		 "is made to keep clean among the places for garbage\n"+
		 "dumping. Several displays and lamps are flashing like\n"+
		 "a x-mas tree.\n");
    ob->set_level(10);
    ob->set_chance(10);
    ob->set_spell_mess1("The robot blows some trash at you.\n");
    ob->set_spell_mess2("The robot blows some trash at you.\n");
    ob->set_spell_dam(random(10));
    ob->set_ac(6);
    ob->set_wc(12);
    ob->set_al(200);
    ob->load_a_chat(17,({
      "A syntetic voice from the robot says: Protect system actived.\n"
    		      }));
  ob->load_chat(10,({
    "A silent buzzing comes from the robot.\n"
    }));
  move_object(ob,this_object());
  }
     

    set_outdoors(1);
    set_light(1);
    short_desc = "A corner of an alley";
    
    long_desc = 
        "You have come to the dead-end of this alley. This\n"
        + "is a sort of garbage dump for this neighbourhood.\n"
        + "Trash and garbage is spread out on the ground and the\n"
        + "trashbins are full to the top. The smell isn't very\n"
        + "nice around here.\n";
    dest_dir = 
        ({
        ROOM+"darkalley3", "east",
        });
    items_arr=({
      ({"bin","bins","trashbins"}),"A rusty trashbin full of crap.",
      "trash","Just some old trash",
      "garbage","You see nothing special about it."
      });
}

init() { ::init(); add_action("smell","smell"); }

smell(str) {
  if (str) return;
  write ("There is terrible rotten smell in the air.\n");
  return 1;
}
