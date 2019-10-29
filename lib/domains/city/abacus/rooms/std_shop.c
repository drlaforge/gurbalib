/* A generic shop to inherit.
* Remember that you'll better ask for permission before you start
* coding a shop. It's only in very special cases you are allowed
* open a regular shop in your area.
*
* Functions to call except for the ordinary room settings:
*
*   set_store_exit (string direction)  -  Which way to the store room.
*   set_reply_mess (string mess)     -  Ex: "The shopkeeper says: "
*   set_show_inventory_values (status show) -  Show values when checking 'i'.
*/

inherit "std/room";
#include "../area.h"

#define MAX_IN_STORE 2
#define MAX_LIST 30            /* show n items in list */
#define HIDE_VALUE 50000        /* hide away valueable items at value n */
/* Limit raised on hide to $10k - player vote of 14 for to 1 against
for valueable items (esp uniques) not to vanish, but to be there
at full cost - Wishbone 13Aug00  */
#include <tune.h>
#include <free_kill.h>

/*-=-=-=- Variables.. -=-=-=-*/
static string reason;
static int closed;
static object store;
static string store_room_exit;
static string reply_mess;
static status show_values;

/*-=-=-=- Prototypes. -=-=-=-*/
int check_value (object item, status silent);
int calc_sell_value (int value);
void collect_bottles (object who);
void reset_clean();
void clean_up_store (string desc);
status nfail (string str);
status display_inventory (object *inventory, int multiple);
status reply (string str, status ret);
status sell_item (object item);
status sell_all (object *items);
status move (object from, object to, status silent);
status browse (string bitem);
string dollar (int amount);
object * find_item_list(string str, object* list );
object find_item (string str, object where);
object make_store();

void
reset (int arg)
{
   string filename;
    
   if (arg)
      return;
   make_store();
   /*      dest_dir =  (["store":({file_name(store),"#store"})]); */
   hide_obvious = ({"store"});
   show_values = 1;
}

void
init() {
   ::init();
   
   add_action ("sell","sell");
   add_action ("value","value");
   add_action ("buy","buy");
   add_action ("list",({"list", "show"}));
   add_action ("inventory","i");
   add_action ("browse",           "browse");
   add_action ("restrict", ({ "sell", "value", "buy", "list", "show", "browse" }) );
   
   call_out ("collect_bottles", 2, this_player());
}

set_closed(i){ closed = i; }
query_closed(){ return closed; }
set_reason(str){ reason = str; }
string
query_reason(){ return reason; }

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
/* Wishbone Sep04 - removed so this can be used for other shops
   move_object( clone_object("std/object/flashlight"), store);
   move_object(clone_object("std/object/citymap"), store);
*/
   return store;
}

int
restrict()
{
   if( query_closed() )
      {
      write( query_reason() );
      return 1;
   }
   else
      return 0;
}

status
sell (mixed item)
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
   sell_item (item);
   return 1;
}

status
sell_item (object ob)
{
   int value;
   string item;

/* Wishbone 30April06 - to stop accidental selling of worn/wielded items */
   if (ob->query_wielded())
    {
     write("You need to stop wielding that first!\n");
     return 1;
    }
   
   if (ob->query_worn())
    {
     write("You need to stop wearing that first!\n");
     return 1;
    }
/* Etc */
   
   if (!(value = check_value (ob, 0)))
      return 0;
   if (!move (ob, make_store(), 0))
      return 0;
   if (!creator(this_object()))
      add_worth (value, ob);

   item = (string) ob -> short();

   if( present("shut", find_object(ROOM+"church.c")) )
    {
     destruct(ob);
    } 

   else if ((value >= HIDE_VALUE) || (ob->query_hide_away()))
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
   if(value >= HIDE_VALUE)
      log_file("SHOP", ctime(time())+"  "+this_player()->query_real_name()+" sold "+item+" for "+value+" dollars.\n");
   this_player()->add_money (value);
   return 1;
}

void
sell_all (object *inventory)
{
   int i;
   inventory = filter_array (inventory, "filter_fun", this_object());
   for (i=0; i < sizeof (inventory); i++)
   {
      int sell_value, value;
      if( inventory[i]->no_sell() )
	continue;

/* Wishbone 30April06 - to stop accidental selling of worn/wielded items */
   if (inventory[i]->query_wielded())
     continue;
   if (inventory[i]->query_worn())
     continue;
/* Etc */

      value = (int) inventory[i]->query_value();
      sell_value = calc_sell_value (value);
      write ((string) inventory[i]->short()+":\t"+
         sell_value + " " + dollar(value) + ".\n");
      move (inventory[i], make_store(), 1);
      if(sell_value >= HIDE_VALUE)
         log_file("SHOP", ctime(time())+"  "+this_player()->query_real_name()+" sold "+inventory[i]+" for "+sell_value+" dollars.\n");
      this_player()->add_money(sell_value);
      if (!creator(this_object()))
         add_worth (value, inventory[i]);
   if( present("shut", find_object(ROOM+"church.c")) ){
     destruct(inventory[i]);
   } else
      if (value >= HIDE_VALUE || inventory[i]->query_hide_away())
         destruct(inventory[i]);
      else
         clean_up_store ((string) inventory[i]->short());
   }
   write ("Ok.\n");
}

int
calc_sell_value (int value)
{
   if(FREE_KILL) return value;
   if (value >= 1100)
      {
      reply ("I'm a little low on money.\n",0);
      value = 1000+((int)this_player()->query_int() / (random(3)+1) +
         (int) this_player()->query_cha() / (random (4) +1));
      if(value > 1100) { value = 1100; }
      /* In case player has BS stats that set value to 50K */
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
         if (cnt >= MAX_IN_STORE)
         destruct (ob[i]);
      else 
         cnt++;
   }
}

void reset_clean(){
  int i, x;
  mixed *ob;
  ob = unique_array( all_inventory(make_store()), "short" );
  for(i=0; i<sizeof(ob); i++){
    x = sizeof(ob[i]);
    x -= MAX_IN_STORE;
    while(x>0){
      destruct(ob[i][x]);
      x--;
    }
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

object *
find_item_list(string str, object* list ) {
   object *inventory, *ret;
   int i;
   
   ret = ({ });
   
   for( i = 0; i < sizeof(list); i++ )
   if( list[i]->id(str) )
      ret += ({ list[i] });
   
   return ret;
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
inventory(string arg)
{
   if(arg) return 0;
   return display_inventory (all_inventory (this_player()), 1);
}

status
list (string obj)
{
   object *inventory;
   string foo;
   string filter;
   
   inventory = all_inventory (make_store());
   if (!obj) { obj = "ALL"; filter = 0; }
   
   if( strlen(obj) > 1 && obj != "ALL" ) inventory = find_item_list(obj, inventory);
   else {
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
   }
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
   if(ob->no_sell()) return 0;
   if (!filter)
      return 1;
   if(!call_other(ob, filter, 0))
      return 0;
   if( filter == "weapon_class" && call_other(ob, "query_calibre") )
      return 0;
   if( filter == "query_calibre" && ob->id("ammo") ) return 0;
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
   if( multiple == 2 ){
      inventory = unique_array( inventory, "short" );
   }
   maxs=sizeof (inventory);
   if (maxs > MAX_LIST) maxs = MAX_LIST;
   if( multiple == 2 ){
      for(i=0; i<maxs; i++){
         if (name = (string) inventory[i][0]->short()){
            if (value=((int)inventory[i][0]->query_value()*multiple))
               write ("$" + value + "\t");
            else write ("  -\t");
            write (capitalize(name) +""+(sizeof(inventory[i])>1?" ["+sizeof(inventory[i])+"]" : "") +".\n");
          }
      }
   }
   else
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
   if (!who || !(bottle = present ("empty_container", who))) return;
   while (bottle)
   {
      value += (int) bottle -> query_value();
      destruct (bottle);
      bottle = present ("empty_container", who);
    }
   if (!value)
      return;
   write ("The merchant comes and collects your empty drink containers.\n"+
      "You get " + value + " " + dollar(value) + " for them.\n");
   who->add_money (value);
}

status
browse (string bitem) {
   object ob;
   int i;
   if (!bitem) { return reply ("Browse what item?\n",1); }
   ob = present (bitem , make_store());
   if (!ob) { return reply ("No such item here!\n",1); }
   write ("You take a close look at "+ob->short()+".\n");
   ob->long();
   i=((int)ob->query_value()*2);
   if( ob->weapon_class() && (int)this_player()->test_wield(ob,1) == 7 )
      reply("You look to small to wield that anyway!\n", 1);
   reply ("Value "+i+" "+dollar(i)+".\n",1);
   return 1;
}

void
set_reply_mess (string mess) { reply_mess = mess; }

void
set_show_inventory_values (status show) { show_values = show; }

