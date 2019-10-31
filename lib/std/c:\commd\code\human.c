/* Definition of the human race */
inherit "/std/race";

void create(void) {
   ::create();

   set_race_short_desc("Humans are cursed with being average " +
      "in all aspects.");
   set_race_long_desc("Humans are predominant in the lands. They, as a " +
      "race, have most of\nthe power in the realm. Since they are so, all " +
      "the other races are compared \n to them. They get along with all " +
      "the other races fairly well, and a human has\na wide range of " +
      "adventuring options available to him or her. The downside is \n" +
      "that they do not excel in any particular fields.");
   set_language("english");
/* no need to do this: set_skill("language/engilsh",100); */
   base_stat_minimum["str"] = 1;
   base_stat_minimum["con"] = 1;
   base_stat_minimum["dex"] = 1;
   base_stat_minimum["int"] = 1;
   base_stat_minimum["wis"] = 1;
   base_stat_minimum["cha"] = 1;

   base_stat_maximum["str"] = 50;
   base_stat_maximum["con"] = 50;
   base_stat_maximum["dex"] = 50;
   base_stat_maximum["int"] = 50;
   base_stat_maximum["wis"] = 50;
   base_stat_maximum["cha"] = 50;
}

