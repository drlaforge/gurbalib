inherit "std/room";
#include "../area.h"

void setup(void) {
  object ob, ob2;
  if (!present("dick",this_object())) {
    ob = clone_object("/std/monster");
    ob->set_name("dick");
    ob->set_alt_name("drunkard");
    ob->set_short("Dick the drunkard");
    ob->set_long("Dick is a poor sucker, who lost the link with reality.\n"+
		 "He spend most of his time and money on some sort of alcohol.\n"+
		 "His nose is extremely red and it looks like he doesn't know\n"+
		 "where he is, and not what's going on.\n");
     ob->set_level(16);
    ob->set_ac(5);
    ob->set_wc(16);
    ob->set_gender(1);
    ob->set_hp(230);
    ob->set_chance(18);
    ob->set_spell_mess1("Dick swings his broken bottle");
    ob->set_spell_mess2("Dick cuts you with his broken bottle");
    ob->set_spell_dam(15);
    ob->add_money(7);
    ob->load_chat(15,({
      "Dick says: Deboodie giadoodie *hic* blurgh!\n",
      "Dick doubles over and pukes at you.\n",
      "Dick mumbles something unhearable.\n",
      "Something drops from Dick's nose.\n",
      "Dick drinks from a dirty bottle of parfume.\n",
      "Dick hiccups.\n",
      "Dick spits on the ground.\n",
      "Dick sings: heell aand coore... chong up fall and allan...\n",
      }));
    ob->load_a_chat(18,({
      "Dick yells: Hey you.. Don't try to steal my drink!!!!\n",
      "Dick screams: Another drink will make all good.\n",
      "Dick pees on you.\n"
      }));
    move_object(ob,this_object());
    ob2 = clone_object("/std/weapon");
    ob2->set_name("bottle");
    ob2->set_short("a broken bottle");
    ob2->set_long("A huge broken bottle with two handles.\n");
    ob2->set_class(5);
    ob2->set_weight(2);
    ob2->set_value(50);
    move_object(ob2,ob);
    command("wield bottle",ob);
    ob2=clone_object ("obj/drink");
    ob2->set_name ("parfume");
    ob2->set_short ("A bottle of parfume");
    ob2->set_strength (4);
    ob2->set_heal (2);
    move_object (ob2,ob);
  }
   

    set_outdoors(1);
    set_light(1);
    short_desc = "an alley";
    
    long_desc = 
        "You are in the beginning of a narrow alley.\n"
        + "It gets a bit darker here among all the grey buildings.\n"
        + "Further west you can see a neon sign, flashing\n"
        + "in the dark. You spot an old market to the south.\n";
    dest_dir = 
        ({
        ROOM+"weigh", "south",
        ROOM+"darkalley2", "west",
        ROOM+"boul3", "east",
        });
  items_arr = ({"sign","It's makes the gloomy alley a little bit more light but\n"
	      + "you can't read is from here",
	    ({"building","buildings"}),"They are pretty boring. You wouldn't"+
	      " like to live here"});
}

