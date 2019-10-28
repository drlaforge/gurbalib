/* Wishbone September 2004 - converted to standard shop */

#include <tune.h>
inherit ROOM+"std_shop";

void setup(void) 
{
   

  set_light(1);
  set_outdoors(0);
  short_desc = "Dark Alley armour shop";
  set_long_f(
    "The local armour comparement and supply shop. "+
    "To compare your armours type: 'compare <armour 1> and <armour 2>'. "+
    "It costs 150 dollars to compare them. "+
    "Type 'list' to see available armour to buy. "+
    "You can also sell your armour here.\n");
  dest_dir =
    ({
      ROOM+"south_alley5","west",
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

compare(str) {
  object a1,a2;
  int ac1,ac2;
  string aname1,aname2;
  string cr1,cr2;

  if(sscanf(str,"%s and %s",aname1,aname2) != 2 &&
     sscanf(str,"%s with %s",aname1,aname2) != 2 &&
     sscanf(str,"%s to %s",aname1,aname2) != 2) {
    write("Usage: compare <armour 1> and <armour 2>.\n");
    return 1;
  }
  if(this_player()->query_money() < 150) {
    write("The comparement costs 150 dollars, which you don't have.\n");
    return 1;
  }
  if(!(a1 = present(lowercase(aname1),this_player()))) {
    write("You don't have a " + capitalize(aname1) + ".\n");
    return 1;
  }
  if(!(a2 = present(lowercase(aname2),this_player()))) {
    write("You don't have a " + capitalize(aname2) + ".\n");
    return 1;
  }
  if(!a1->armour_class()) {
    write(capitalize(aname1) + " is not an armour.\n");
    return 1;
  }
  if(!a2->armour_class()) {
    write(capitalize(aname2) + " is not an armour.\n");
    return 1;
  }
  ac1 = a1->armour_class();
  ac2 = a2->armour_class();

  if(ac1 > ac2) 
    write(a1->short() + " seems to be the best.\n");
  else if(ac1 == ac2) 
    write("They seem to be equally good.\n");
  else
    write(a2->short() + " seems to be the best.\n");

  cr1 = creator(a1);
  cr2 = creator(a2);
  if(!cr1)
    cr1 = "some factory";
  if(!cr2)
    cr2 = "some factory";

  write(" - "+capitalize(cr1) + " created " + a1->short() + ", and\n");
  write(" - "+capitalize(cr2) + " created " + a2->short() + ".\n");
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
  if(!item->armour_class()) 
   {
    write("The shopkeeper says: We only trade armour here.\n");
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
      if( !inventory[i]->armour_class() )
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