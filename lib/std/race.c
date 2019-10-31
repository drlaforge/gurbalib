inherit "/std/monster_race";

string language;

int is_monster_race(void) {
   return 0;
}

string query_language(void) {
   return language;
}

string set_language(string str) {
   language = str;
}

int has_darkvision(void) {
   return 0;
}

void create(void) {
   ::create();

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

