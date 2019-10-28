#include <def.h>
#include <tune.h>
#define IS_OPEN 1        /* If the shop is open or not */

/* repair.h - for repairing damaged weapons */

/* Price to raise one point of wc. From wc 7 to wc 8 makes (7 * 7) $49.
* From wc 12 to wc 15 makes (12*7 + 13*7 + 14*7) $273. Hope it's clear
* enough.
*/
#define WC_COST (wc * 9)

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
   
   short_desc = "the weapon repairment shop";
   add_item(({"acid rain coat", "rain coats", "raincoat", "raincoats"}), "You'll be able to buy them from Denis. They seem strong enough to protect you from the weather.");
   set_long_f("You stand in a large weapon repairment shop. Here you can repair your damaged "+
      "weapons, or even learn the art from the shop's proprietor. Do 'repair cost <weapon>' to see the "+
      "cost of repairing a weapon, then 'repair <weapon>' to have it repairs. Apart from weapons, you "+
      "also see numerous raincoats hanging on the walls - you have a feeling that these would protect you "+
      "from the acidic weather!\n");
   "get it done.\n";
   
   dest_dir = ({ ROOM+"darkalley2", "north", 0 });
   add_object("/obj/monsters/dennis.c", 1);
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
   
   if( !query_open() )
      return reply("Looks like Denis isn't here - there is no one to help you.\n", 1);
   if (!str)
      return reply("Usage: repair <weapon> or repair cost <weapon>\n",1);
   if (str == "cost")
      return reply("Usage: repair cost <weapon>\n",1);
   if (sscanf (str, "cost %s", str))
      return check_cost (str);
   if ( !(weapon = find_weapon (str)))
      return 1;
   p = calculate_cost ((int) weapon->weapon_class(),
      (int) weapon->new_weapon_class(), weapon, (int)TP->QL);
   if (!this_player()->add_money (-p))
      return reply("You can't afford that.\n",1);

   weapon->add_def_points ( -((int) weapon->query_def_points ()));

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
   return reply("It would cost $" + p + " to repair " + str + ".\n",1);
}

mixed
find_weapon (string str)
{
   object weapon;
   
   if ( !(weapon = present(str, this_player())))
      return reply("You don't have that.\n", 0);
   if (!weapon -> weapon_class ())
      return reply("That's not a weapon.\n", 0);
   if(weapon->query_gun() && weapon->query_jammed())
      return reply("I don't know how to unjam that, try Spike's shop to the west.\n", 0);
   if (!weapon -> query_def_points ())
      return reply("That weapon cannot be repaired more here.\n", 0);
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
   return objectp(present("denis", this_object()));
}

