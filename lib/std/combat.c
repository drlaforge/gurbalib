static object *targets;
static int fighting;
static object target;
int kills;
mapping killed_by;
object killer;
int wimpy;
int wimpy_hp;
string wimpy_dir;

#define FIGHTING_TIMEOUT 300
/* Amount of Endurance required to Attack */
#define ATTACK_COST 1

/* Uncomment this to get extra info in combat */
#define DEBUG_COMBAT 1

void create(void) {
   targets = ({ });
   fighting = 0;
   wimpy = 0;
   wimpy_hp = 0;
   wimpy_dir = "";
}

int is_fighting(void) {
   return fighting;
}

object query_killer(void) {
   return killer;
}

mapping query_killed_by(void) {
   if (!mappingp(killed_by)) {
      killed_by = ([]);
   }
   return killed_by;
}

void increment_kills(void) {
   kills++;
}

int query_kills(void) {
   return kills;
}

void add_killed_by(object who, int t) {
   string str;

   if (!mappingp(killed_by)) {
      killed_by = ([]);
   }

   killed_by[t] = who->file_name();
#ifdef DO_STATS
   str = "killed: " + this_object()->file_name() + " by " +
   who->query_Name() + "(" + who->file_name() + "):" + t + "\n";
   LOG_D->write_log("stats.raw", str);
#endif
}

int query_killed(void) {
   if (!mappingp(killed_by)) {
      killed_by = ([]);
   }
   return sizeof(map_indices(killed_by));
}

void set_wimpy(int w) {
   wimpy = w;
}

int query_wimpy() {
   return wimpy;
}

void set_wimpy_dir(string where) {
   wimpy_dir = where;
}

string query_wimpy_dir() {
   return wimpy_dir;
}

void set_wimpy_hp(int w) {
   wimpy_hp = w;
}

int query_wimpy_hp() {
   return wimpy_hp;
}

void halt_fight(void) {
   fighting = 0;
   targets = ({ });
}

int run_away(void) {
   string dir, error;
   string *exits;
   int x, y;

   if (!empty_str(wimpy_dir) &&
      this_object()->query_environment()->query_exit(wimpy_dir)) {

      write("You attempt to run " + wimpy_dir + ".\n");
      error = this_object()->this_environment()->body_exit(this_object(),
         wimpy_dir);
      if (error) {
         write(error);
      } else {
         return 1;
      }
   } else if (!empty_str(wimpy_dir) &&
      this_object()->query_environment()->query_hidden_exit(wimpy_dir)) {

      write("You attempt to run " + wimpy_dir + ".\n");
      error = this_object()->this_environment()->body_exit(this_object(),
         wimpy_dir);
      if (error) {
         write(error);
      } else {
         return 1;
      }
   } else {
      exits = this_object()->query_environment()->query_exit_indices();

      if (exits) {
         x = sizeof(exits);
         if (x < 1) {
            write("You attempt to run away but can not find " + "an exit.\n");
         } else {
            if (x > 1) {
               y = random(x);
            } else {
               y = 0;
            }
            this_object()->message("RUNAWAY : " + exits[y] + "\n");
            write("You attempt to run " + exits[y] + ".\n");
            error = this_object()->this_environment()->body_exit(this_object(),
               exits[y]);
            if (error) {
               write(error);
            } else {
               return 1;
            }
         }
      } else {
         write("You attempt to run away but can not find " + "an exit.\n");
      }
   }
   return 0;
}

void receive_damage(object who, int dam) {
   int x, when;

   this_object()->message("%^RED%^You took " + dam + " damage from " +
      who->query_id() + ".%^RESET%^");

   if (this_object()->query_hp() <= dam) {
      x = this_object()->query_max_hp();
      killer = who;
      when = time();
      this_object()->add_killed_by(killer, when);
      this_object()->halt_fight();
      who->halt_fight();
      who->increment_kills();
      who->increase_expr(x);
      /* make sure they are dead */
      this_object()->decrease_hp(x);
   }
   this_object()->decrease_hp(dam);
}

void damage_target(int dam, object who) {
   int target_hp;

   target_hp = who->query_hp();

   /* award expr for damage inflicted to target */
   if (dam > target_hp) {
      this_object()->increase_expr(target_hp);
   } else {
      this_object()->increase_expr(dam);
   }

   /* damage target */
   who->receive_damage(this_object(), dam);
}

int query_defense(void) {
   int me, i, max;
   object *armor;

   me = this_object()->query_skill("combat/defense") / 50;
   me+=1;
   me += this_object()->query_statbonus("dex");
   armor = this_object()->query_equipment();

   max = sizeof(armor);
   for (i = 0; i < max; i++) {
      if (armor[i]->is_armor()) {
         me += armor[i]->query_ac();
      }
   }

   armor = this_object()->query_wielded();
   max = sizeof(armor);
   for (i = 0; i < max; i++) {
      if (armor[i]->is_armor()) {
         me += armor[i]->query_ac();
      }
   }

   return me;
}

int do_swing(int me) {
   int opponent, me_roll, opponent_roll;

   if (me < 3) {
      me = 3;
   }

   me_roll = random(me + 1);

   opponent = target->query_defense();
   opponent_roll = random(opponent + 1);

#ifdef DEBUG_COMBAT
   this_object()->message("Roll [%^RED%^" + me_roll + "%^RESET%^/%^GREEN%^" +
      me + "%^RESET%^  vs %^RED%^" + opponent_roll + "%^RESET%^/%^GREEN%^" +
      opponent + "%^RESET%^]");
#endif

   if (me_roll > opponent_roll) {
      return 1;
   }
   return 0;
}

object get_target(object targ) {
   int i, max;

   if (targ) {
      if (targ->is_dead()) {
         targets -= ({ targ });
         if (sizeof(targets) == 0) {
            fighting = 0;
         }
      } else if (targ->query_environment() ==
         this_object()->query_environment()) {

         fighting = FIGHTING_TIMEOUT;
         return targ;
      }
   }
   max = sizeof(targets);
   for (i = 0; i < max; i++) {
      if (targets[i] && targets[i]->is_dead()) {
         targets -= ({targets[i]});
         i--;
         max--;                 /* shorten up our array.... */

         if (sizeof(targets) == 0) {
            fighting = 0;
            i = max;
         }
      }
      if (i < sizeof(targets) &&
         targets[i] && (targets[i]->query_environment() ==
         this_object()->query_environment())) {

         fighting = FIGHTING_TIMEOUT;
         return targets[i];
      }
   }
   fighting = fighting - 1;
   if (fighting < 1) {
      targets = ({ });
   }
   return nil;
}

int damage_hook(object victim, object weapon, int damage) {
   int extra_damage;

   extra_damage = damage;
   if (!nilp(weapon) && victim->is_vulnerable(weapon->query_materials())) {
      extra_damage += (damage / 3);
   }

   return extra_damage;
}

int after_damage_hook(object aggressor, object weapon, int damage) {
   return damage;
}

private void handle_performance_enhancement_expires() {
   if (this_object()->has_performance_enhancement()) {
      this_object()->decrease_performance_enhancement(1);
      if (!this_object()->has_performance_enhancement()) {
         this_object()->message("You no longer feel like you could " +
            "fight forever.");
      }
   }
}

