/* Wishbone September 2004 - converted to standard shop */

#include <tune.h>
inherit ROOM+"std_shop";

void setup(void) 
{
   
   

  set_light(1);
  set_outdoors(0);
  short_desc = "Dark Alley weapon shop";
  set_long_f(
    "The local weapon comparement and supply shop. "+
    "To compare your weapons type: 'compare <weapon 1> and <weapon 2>. "+
    "It costs 150 dollars to compare them. "+
    "Type 'list' to see available weapons to buy. "+
    "You can also sell your weapons here.\n");
  dest_dir =
    ({
      ROOM+"south_alley5","east",
    });
   set_reply_mess("The shopkeeper says: ");
   set_store_exit("north");
}

init()
{
 ::init();
 add_action("sell_it","sell");
 add_action("compare","compare");
}

compare(str) 
{
  object w1,w2;
  int wc1,wc2;
  string wname1,wname2;
  string cr1,cr2;

  if(str && sscanf(str,"%s and %s",wname1,wname2) != 2 &&
     sscanf(str,"%s with %s",wname1,wname2) != 2 &&
     sscanf(str,"%s to %s",wname1,wname2) != 2) {
    write("Usage: compare <weapon 1> and <weapon 2>.\n");
    return 1;
  }
  if(this_player()->query_money() < 150) {
    write("The comparement costs 150 dollars, which you don't have.\n");
    return 1;
  }
  if(!(w1 = present(lowercase(wname1),this_player()))) {
    write("You don't have a " + capitalize(wname1) + ".\n");
    return 1;
  }
  if(!(w2 = present(lowercase(wname2),this_player()))) {
    write("You don't have a " + capitalize(wname2) + ".\n");
    return 1;
  }
  if(!w1->weapon_class()) {
    write(capitalize(wname1) + " is not a weapon.\n");
    return 1;
  }
  if(!w2->weapon_class()) {
    write(capitalize(wname2) + " is not a weapon.\n");
    return 1;
  }
  wc1 = w1->weapon_class();
  wc2 = w2->weapon_class();

  if(w1->query_two_handed())
    wc1 = wc1/2;
  if(w2->query_two_handed())
    wc2 = wc2/2;

  if(wc1 > wc2) 
    write(w1->short() + " seems to be the best.\n");
  else if(wc1 == wc2) 
    write("They seem to be equally good.\n");
  else
    write(w2->short() + " seems to be the best.\n");
  cr1 = creator(w1);
  if(!cr1)
    cr1 = "Some factory";
  cr2 = creator(w2);
  if(!cr2)
    cr2 = "Some factory";
  write(" - "+capitalize(cr1) + " created " + w1->short() + ", and\n");
  write(" - "+capitalize(cr2) + " created " + w2->short() + ".\n");
  this_player()->add_money(-150);
  return 1;
}

sell_it(mixed item)
{
   string bag;
   object container;
   
   if (!item)
      return nfail ("Sell what ?\n");
   if (item == "all")
      {
      sell_all (deep_inventory(this_player()));
      return 1;
   }
   if (sscanf(item,"all from %s",bag)==1) 
      {
      if (!(container = find_item(bag,this_player())))
         return !notify_fail("There is no "+bag+" in your possession.\n");
      sell_all(deep_inventory(container));
      return 1;
   }
   if (!(item = find_item (item, this_player())))
      return reply ("You don't have that.\n", 1);
   if( item->no_sell() )
      return !notify_fail("You can't sell that!\n");
  if(!item->weapon_class()) 
   {
    write("The shopkeeper says: We only trade weapons here.\n");
    return 1;
   }
  return 0;
}

sell_all (object *inventory)
{
   int i;
   inventory = filter_array (inventory, "filter_fun", this_object());
   for (i=0; i < sizeof (inventory); i++)
   {
      int sell_value, value;
      if( inventory[i]->no_sell() )
	continue;
      if( !inventory[i]->weapon_class() )
        continue;
      value = (int) inventory[i]->query_value();
      sell_value = calc_sell_value (value);
      write ((string) inventory[i]->short()+":\t"+
         sell_value + " " + dollar(value) + ".\n");
      move (inventory[i], make_store(), 1);
      this_player()->add_money(sell_value);
      if (!creator(this_object()))
         add_worth (value, inventory[i]);
   }
   write ("The shopkeeper says: Ok!\n");
}