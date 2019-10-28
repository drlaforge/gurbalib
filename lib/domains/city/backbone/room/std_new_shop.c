/* A generic shop to inherit.
 * Remember that you'll better ask for permission before you start
 * coding a shop. It's only in very special cases you are allowed
 * open a regular shop in your area.
 *
 * Functions to call except for the ordinary room settings:
 *
 *   set_store_exit (string direction)  -  Which way to the store room.
 *   set_reply_mess (string mess)	     -  Ex: "The shopkeeper says: "
 *   set_show_inventory_values (status show) -  Show values when checking 'i'.
 *   set_store_type (string type) - Type can be 'weapon', 'armour', 'other'
 *                                 or 'all'. Default is 'all'.
 */

inherit "std/room";
#include "../area.h"

#define MAX_LIST 30            /* show n items in list */
#define HIDE_VALUE 3000        /* hide away valueable items at value n */
#include <tune.h>

/*-=-=-=- Variables.. -=-=-=-*/
static object store;
static string store_room_exit;
static string reply_mess;
static status show_values;
static string store_type;

/*-=-=-=- Prototypes. -=-=-=-*/
int check_value (object item, status silent);
int calc_sell_value (int value);
void collect_bottles (object who);
void clean_up_store (string desc);
status nfail (string str);
status display_inventory (object *inventory, int multiple);
status reply (string str, status ret);
status sell_item (object item);
status sell_all (object *items);
status move (object from, object to, status silent);
status browse (string bitem);
string dollar (int amount);
object find_item (string str, object where);
object make_store();
status correct_store(object ob);
string query_store_type();
void set_store_type(string type);

void
reset (status arg)
{
	string filename;
	if (arg)
		return;
	make_store();
	dest_dir =  (["store":({file_name(store),"#store"})]);
	hide_obvious = ({"store"});
        set_store_type("all");
	show_values = 1;
}

void
init() {
	::init();

	add_action ("sell",		"sell");
	add_action ("value",		"value");
	add_action ("buy",		"buy");
	add_action ("list",		({"list", "show"}));
	add_action ("inventory",	"i");
        add_action ("browse",           "browse");

	call_out ("collect_bottles", 2, this_player());
}

object
make_store ()
{
	string filename;

	if (objectp (store))
		return store;
	filename = file_name (this_object());
	store = clone_object ("/std/room");
	store -> set_long("All objects from the shop (" + filename +
						") is stored here.\n");
	store -> set_short("A storage room for the shop (" +
						filename + ")");
	store -> fix_light (1);
	store -> set_outdoors (0);
	store -> add_exit ("out", filename, 0);
	move_object(clone_object("std/object/flashlight"), store);
	move_object(clone_object("obj/citymap"), store);
	return store;
}

status
sell (mixed item)
{
	if (!item)
		return nfail ("Sell what ?\n");
	if (item == "all")
	{
		sell_all (all_inventory(this_player()));
		return 1;
	}
	if (!(item = find_item (item, this_player())))
		return reply ("You don't have that.\n", 1);
	if(!correct_store(item))
	  return reply ("You can't sell that here.\n", 1);
	sell_item (item);
	return 1;
}

status
correct_store (object ob)
{
  if(query_store_type() == "all") 
    return 1;
  if(query_store_type() == "other" && !ob->weapon_class() && !ob->armour_class()) 
    return 1;
  if(query_store_type() == "weapon" && ob->weapon_class())
    return 1;
  if(query_store_type() == "armour" && ob->armour_class())
    return 1;
  return 0;
}

status
sell_item (object ob)
{
	int value;
	string item;
	
	if (!(value = check_value (ob, 0)))
		return 0;
	if (!move (ob, make_store(), 0))
		return 0;
	if (!creator(this_object()))
		add_worth (value, ob);
	item = (string) ob -> short();
	if ((value >= HIDE_VALUE) || (ob->query_hide_away()))
	{
		write("The valuable item is hidden away.\n");
		destruct(ob);
	}
	else
	        clean_up_store ((string) ob->short());
	value = calc_sell_value (value);
	reply("I give you " + value + " " + dollar(value) +
			" for " + item + ".\n",0); 
	say (this_player()->query_name() + " sells " + item + ".\n");
	this_player()->add_money (value);
	return 1;
}

void
sell_all (object *inventory)
{
	int i;
	inventory = filter_array (inventory, "filter_fun", this_object());
	inventory = filter_array (inventory, "correct_store", this_object());
	for (i=0; i < sizeof (inventory); i++)
	{
		int sell_value, value;
		value = (int) inventory[i]->query_value();
		sell_value = calc_sell_value (value);
		write ((string) inventory[i]->short()+":\t"+
			sell_value + " " + dollar(value) + ".\n");
		move (inventory[i], make_store(), 1);
		this_player()->add_money(sell_value);
		if (!creator(this_object()))
		         add_worth (value, inventory[i]);
		if (value >= 2000 || inventory[i]->query_hide_away())
		          destruct(inventory[i]);
		else
		          clean_up_store ((string) inventory[i]->short());
	}
	write ("Ok.\n");
}

int
calc_sell_value (int value)
{
	if (value >= 1100)
	{
	        reply ("I'm a little low on money.\n",0);
		value = 1000+((int)this_player()->query_int() / (random(3)+1) +
			(int) this_player()->query_cha() / (random (4) +1));
	}
	return value;
}

void
clean_up_store (string desc){
  int i, cnt;
  object *ob;
  
  i = sizeof(ob = all_inventory (make_store()));
  while(i--){
    if ((string) ob[i]->short() == desc)
      if (cnt >= 3) 
	destruct (ob[i]);
      else 
	cnt++;
  }
}
  
int
check_value (object item, status silent)
{
	int value;

	if (!(value = (int) item->query_value()))
	{
		if (!silent)
			 reply (capitalize ((string) item->short()) +
					" has no value.\n",0);
		return 0;
	}
	return value;
}

status
move (object from, object to, status silent)
{
	int ret;

	if (!(ret = move_object (from, to)))
		return 1;
	if (silent)
		return 0;
	if (ret == 1)
		return reply ("You can't carry anymore.\n", 0);
	return reply ("You can't drop that.\n", 0);
}

status
value (string item)
{
	int value;
	object ob;

	if (!item)
		return nfail("Value what ?\n"); 
	if ( !(ob = find_item (item, this_player())))
		if ( !(ob = find_item (item, make_store())))
			return reply ("Neither you nor me has such item.\n",1);
		else value = (int) ob->query_value()*2;
	else value = (int) ob->query_value();
	if(!correct_store(ob)) return reply(capitalize((string)ob->short())+" has no worth here.\n",1);
	if (!value)
	    return reply(capitalize((string)ob->short())+" has no value.\n",1);
	return reply (capitalize ((string) ob->short()) + " is worth " +
			value + " " + dollar(value) + ".\n",1);
}

status
buy (string item)
{
	object ob;
	int value;

	if (!item)
		return nfail ("Buy what ?\n");
	if ( !(ob = find_item (item, make_store())))
		return reply ("Sorry, I don't have that.\n", 1);
	if (!(value = check_value (ob, 0)))
		return 1;
	if ((int) this_player()->query_money() < value*2)
		return reply ("Sorry, but you can't afford that.\n", 1);
	if (!move (ob, this_player(), 0))
		return 1;
	this_player()->add_money (- (value*2));
	say (this_player()->query_name() + " buys " + ob->short() + ".\n");
	return reply("That'll be "+(value*2)+" "+dollar(value*2)+
						", thank you.\n", 1);
}

string
dollar (int value)
{
	if (value == 1)
		return "dollar";
	return "dollars";
}

object
find_item (string str, object where)
{
	object *inventory, item;
	int i;

	if (item = present (str, where))
		return item;
	for (inventory=all_inventory(where), i=0; i < sizeof (inventory); i++)
		if ((string) inventory[i] -> short() == str) 
			return inventory[i];
	return 0;
}

status
store ()
{
	if (this_player()->query_level() >= SCI_LEVEL)
	{
		write("You wriggle through the laser-field...\n");
		return 0;
	}
	write ("There is a strong laser-field in your way.\n");
	say(this_player()->query_name() +
		" tries to go through the laser-field, but fails.\n");
	return 1;
}

status
inventory ()
{
	return display_inventory (all_inventory (this_player()), 1);
}

status
list (string obj)
{
	object *inventory;
	string foo;
	string filter;
	
	inventory = all_inventory (make_store());
        if (!obj) obj="ALL";
        if (obj[0]=='m')
	        filter = "MISC";
	if (obj[0]=='w')
		filter = "weapon_class";
	if (obj[0]=='a')
		filter = "armour_class";
        if (obj[0]=='s')
	        filter = "query_calibre";
	inventory = filter_array (inventory, "filter_fun",
						this_object(), filter);
	if (!sizeof (inventory))
	{
	        return reply ("Sorry, I don't have that.\n",1);
	}
	display_inventory (inventory, 2);
	return 1;
}

status
filter_fun (object ob, string filter)
{
        if (filter == "MISC" &&
            !ob->weapon_class() &&
            !ob->armour_class())
	        return 1;
	if (!ob->query_value() || !ob->short())
		return 0;
	if (!filter)
	        return 1;
	if (!call_other (ob, filter,0))
	       return 0;
	return 1;
}

status
display_inventory (mixed inventory, int multiple)
{
	int i, j, value,maxs;
	string name;

	if (!show_values && multiple == 1)
		return 0;
	if (multiple == 1)
		write ("You are carrying:\n");
        maxs=sizeof (inventory);
	if (maxs > MAX_LIST) maxs = MAX_LIST;
	for (i=0, j=0; i < maxs; i++)
	        if (name = (string) inventory[i]->short())
		{
			string tmp;
			if (value=((int)inventory[i]->query_value()*multiple))
				write ("$" + value + "\t");
			else write ("  -\t");
			write (capitalize(name) + ".\n");
		}
	return 1;
}

status
reply (string str, status ret)
{
	if (!reply_mess)
		reply_mess = "";
	write (break_string (reply_mess + str, 79, 20));
	return ret;
}

status
nfail (string str)
{
	notify_fail (str);
	return 0;
}

void
set_store_type(string type)
{
  store_type = type;
}

string
query_store_type(){
  return store_type;
}

void
set_store_exit (string direction)
{
	if (!stringp (direction))
		return;
	add_exit(direction, file_name(make_store()), "#store");
	filter_array (all_inventory(), "update_init",this_object());
	hide_obvious = add_array (hide_obvious, direction);
}


status
qxxc_move ()
{
	int foo;

	if (sscanf (dest_dir[query_verb()][0], ROOM+"room#%d", foo)) 
			dest_dir[query_verb()][0] = file_name (make_store());
	return ::qxxc_move();
}

void
collect_bottles (object who)
{
	object bottle;
	int value;
	if (!(bottle = present ("empty_container", who)))
		return;
	while (bottle)
	{
		value += (int) bottle -> query_value();
		destruct (bottle);
		bottle = present ("empty_container", who);
	}
	if (!value)
		return;
	write ("The merchant comes and collects your empty bottles.\n"+
		"You get " + value + " " + dollar(value) + " for them.\n");
	this_player()->add_money (value);
}	

status
browse (string bitem) {
 object ob;
 int i;
   if (!bitem) { return reply ("Browse what item?\n",1); }
   ob = present (bitem , make_store());
   if (!ob) { return reply ("No such item here!\n",1); }
   write ("You take a close look at "+ob->short()+".\n");
   i=((int)ob->query_value()*2);
   reply ("Value "+i+" "+dollar(i)+".\n",1);
   move_object (ob,this_player());
   (int)this_player()->examine (bitem);
   move_object (ob,make_store());
   /* ob->long() */
   return 1;
}

void
set_reply_mess (string mess) { reply_mess = mess; }

void
set_show_inventory_values (status show) { show_values = show; }

status
query_peace ()  { return 1; }








