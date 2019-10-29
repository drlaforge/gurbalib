#include "../backbone.h"
inherit STD_MONSTER;

void setup(void){
    
    
   set_name("robot cleaner");
   set_race("robot");
   set_alias(({"robot cleaner","cleaner","robot"}));
   set_short("a metallic robot cleaner");
   set_long("The robot cleaner is driven by a silent nuclear engine, fully capable "+
      "of running for two hundred years. The robot is designed to keep the city clean, "+
      "a task which is quite tough for such a small robot on it's own. Several "+
      "displays and light on the robot are flashing like a x-mas tree begging the "+
      "question of if it's malfunctioning or not.\n");
   set_level(10);
   set_chance(10);
   set_spell_mess1("The robot throws some trash around.\n");
   set_spell_mess2("The robot throws some trash at you.\n");
   set_spell_dam(random(10));
   load_a_chat(17,({
      "A synthetic voice from the robot says: Protect system actived.\n",
      "A voice from the robot says: Destroy human trash!\n",
      "A synthetic robot voice says: Stop or there will be trouble.\n",
   }));
   load_chat(10,({
      "A silent buzzing comes from the robot.\n",
      "The robot scans the area for trash.\n",
      "The robot stops and spins around unnecessarily.\n",
    }));
}
