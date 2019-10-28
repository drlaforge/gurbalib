#include "../backbone.h"
inherit STD_M_MONSTER;

void setup(void){
    
    
   add_object("/obj/monsters/droidgun.c",1,"wield gun");
   set_name("broken droid");
   set_alias(({"the droid","droid"}));
   set_short("a broken droid");
   set_long_f("This is a small broken droid. It's a defender, model VI-E. "+
      "The droid is still alive, but most functions have been destroyed. "+
      "watch out, it might go berserk.\n");
   set_level(17);
   set_gender(0);
   set_race("robot");
   load_chat(10,({
      "The droid makes a buzzing sound.\n",
      "The droid says: To prote*bzzzz* and serve *bzzz*\n",
   }));
   load_a_chat(10,({ 
      "The droid foolishly tries to attack itself.\n",
      "The droid says: I'm warning you! *bzzzz*\n",
   }));
   set_spell_chance (6);
   set_spell_dam (20);
   set_spell_mess1 ("The droid fires its lasergun!\n");
   set_spell_mess2 ("The droid fires its lasergun at you!\n");
}