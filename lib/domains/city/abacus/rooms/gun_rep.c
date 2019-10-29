#include <def.h>
#include <tune.h>
#define IS_OPEN 1        /* If the shop is open or not */

/* repair.h - for repairing damaged weapons */

/* Price to raise one point of wc. From wc 7 to wc 8 makes (7 * 7) $49.
* From wc 12 to wc 15 makes (12*7 + 13*7 + 14*7) $273. Hope it's clear
* enough.
*/
#define WC_COST (wc * 7)

inherit "std/room";
#include "../area.h"

/* Some function declarations. Nesecery since I'm useing strict types.
*/
int query_open();
mixed find_weapon (string str);  /* Returns the weapon str if found. */
   int check_cost (string str);     /*If we give 'cost' as second arg to repair*/
int calculate_cost (int wc, int new_wc, object weapon, int level); /* Get the price. */
int reply (string str, int ret); /* Just a smooth way to write() and return */

void
reset (int arg)
{
   if (arg)
      return;
   
   set_light (1);
   set_outdoors (0);
   
   set_short("The Gun Repairment Shop");
   set_long_f("This is a newly opened gun repair shop. Denis' skills at weapon repairment are well known, "+
"but when it comes to shootweapons - he is clueless. This shop opened up not too long ago just for that "+
"need. The shop specializes in only gun repair - do 'repair cost <gun>' to check the cost and 'repair <gun>' "+
"to have it repairs.");
   
   dest_dir = ({ ROOM+"darkalley3", "south", 0 });
   add_object("/obj/monsters/spike.c", 1);
}

void
init ()
{
   ::init();
   
   add_action ("repair",           "repair");
}

int
repair (string str)
{
   int p;
   object weapon;
   
   if(!query_open()) return reply("Spike doesn't seem to be here - can't repair without him here!\n", 1);
   if (!str)
      return reply("Usage: repair <gun> or repair cost <gun>\n",1);
   if (str == "cost")
      return reply("Usage: repair cost <gun>\n",1);
   if (sscanf (str, "cost %s", str))
      return check_cost (str);
   if ( !(weapon = find_weapon (str)))
      return 1;
   p = calculate_cost ((int) weapon->weapon_class(),
      (int) weapon->new_weapon_class(), weapon, (int)TP->QL);
   if (!this_player()->add_money (-p))
      return reply("You can't afford that.\n",1);
   if (!weapon->query_gun())
      return reply("Heh. Try somewhere else!", 1);
   else
      weapon->unjam();
   this_player()->update_wc();
   return reply("Ok, the " + weapon->query_name () + " is repaired.\n",1);
}

int
check_cost (string str)
{
   int p;
   object weapon;
   
   if (!str)
      return reply("Check the price for which weapon ?\n",1);
   if ( !(weapon = find_weapon (str)))
      return 1;
   p = calculate_cost ((int) weapon->weapon_class(),
      (int) weapon->new_weapon_class(), weapon, (int)TP->QL);
   return reply("It would cost " + p + " to repair " + str + ".\n",1);
}

mixed
find_weapon (string str)
{
   object weapon;
   
   if ( !(weapon = present(str, this_player())))
      return reply("You don't have that.\n", 0);
   if (!weapon -> weapon_class ())
      return reply("That's not a weapon.\n", 0);
   if(!weapon->query_gun())
      return reply("That weapon cannot be repaired here, try Denis' shop - loser!\n", 0);
   if (weapon->query_gun() && !weapon->query_jammed())
      return reply("The " +weapon->query_name()+ " isn't jammed.\n", 0);
   return weapon;
}

int
calculate_cost (int wc, int new_wc, object weapon, int level)
{
   int cost; 
   if (weapon->query_gun())
      
   /* Price is adjusted so that it depends on player's level as well */
   /* This is a testing price formula. Aug. 10, 1997. Mindmaster Mastermind */
   return atoi(""+(((int)weapon->query_real_value()*60)/(180-(level)))+"");
   
   while (wc < new_wc)
   {
      cost = cost + WC_COST;
      wc++;
   }
   return cost;
}

int
reply (string str, int ret)
{
   write(str);
   return ret;
}

int
query_open ()
{
   return objectp(present("spike", this_object()));
}

