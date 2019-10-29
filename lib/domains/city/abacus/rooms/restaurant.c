/* This is a standard Restaurant/Pub/Inn use this when
* designing your own pubs. You may inherit this file
* and change the menu with these functions:
*
* dname = ({ "name1","name2", .... ,"namen" });
* dalt_name = ({ "alt_name1","alt_name2", .... ,"alt_namen" });  * Bigfoot *
* dalias = ({ "alias1","alias2",....,"aliasn" });                * 920509  *
* dshort = ({ "short1","short2", .... ,"shortn" });
* dmess = ({ "mess1","mess2", .... ,"messn" });
* dtype = ({ "type1","type2", .... ,"typen" });
* dstrength = ({ str1,str2, .... ,strn });
* dheal = ({ heal1,heal2, .... ,healn });
* dportable = ({ port1,port2, .... ,portn });
*
* set_reply ("The bartender says: ");
* set_order_what ("Order what?\n");
* set_menu_table ("............");   space between item and price.
* set_not_enough ("Sorry, you don't got enough money.\n");
* set_enough_healing ("You've had enough here. Please return later.\n");
*
* Remember ::init() and ::reset() if you inherit this file!
   *
* dheal = the healing the item does when consuming it.
* dstrength = the amount of intoxination/stuffing/soaking it does.
* dportable = 1: portable (more expensive)  /  0: not portable (cheaper)
* dtype = what to include. "obj/drink", "obj/food", "obj/soft_drink"
*
*   finished         Thorwald 920310
*/

/* Wishbone was here 16Nov03 - added dlong so that you can have */
/* a different long to short. No long will default it to short */
/* as it presently does. Woo.. backwards compatibility! */

 
inherit "std/room";
#include "../area.h"
inherit "obj/daemons/shop_cmds";
static string  dname, dalt_name, dalias, dshort, dmess, dtype, dlong;
static string  reply_string, order_what_string;
static string  menu_table_string, not_enough_string, enough_healing_string;
static int     value, dstrength, dheal, dportable, i, i2, total;
static int     max_size;   /* is it a barrel? */
object player, tp, ob, ob2, drink;
static int    closed;
static string reason;
static mapping  visitors;

/* Wishbone 21Dec03 - some defines to make balance easier! */
/* Historical values: player 200, shop 3000 */

#define	PLAYER_HEAL 220  /* total heal per player per reset */
#define SHOP_HEAL 1100   /* total heals available per reset */

set_closed(i){ closed = i; }
query_visitors(){ return visitors; }

query_closed(){ return closed; }
set_reason(str){ reason = str; }
query_reason(){ return reason; }

void setup(void) {
   visitors=([ ]);                /*  Visitors mapping. cleared each reset */
   total=SHOP_HEAL;               /*  Total healing sold per reset  */
                  /*  If reset */
   
   /* default room */
   reply_string = "";
   order_what_string = "Order what?\n";
   menu_table_string ="             ";
   not_enough_string = "You don't got enough money.\n";
   enough_healing_string = "You've had enough in here!\n";
}

init () {
   string dirs;
   room::init();
   shop_cmds::init();
   add_action("restrict", ({ "order", "buy", "menu" }));
   if (!m_sizeof (dest_dir)) 
      return;
   for (i=0; i<sizeof(dirs=m_indices(dest_dir));i++)
   dest_dir[dirs[i]][1]="rest_move";
}

restrict() {
   if( query_closed() )
      {
      write( query_reason() );
      return 1;
   }
   else
      return 0;
}

query_menu () {
   int tempmax;
   tempmax = 0;
   for(i=0;i<sizeof(dshort);i++) {
      if (strlen(dshort[i]) > tempmax) tempmax = strlen(dshort[i]);
   }
   i = 0;
   while (i<sizeof(dname)) {
      if (total >= dheal [i])
         printf("%45-s",extract(capitalize(dshort[i])+menu_table_string,0,(tempmax+3)));
      if (!max_size) max_size=dportable; /* ugly but works */
      write (" $"+price (dstrength[i],dheal[i],dportable[i],max_size[i])+".\n");
      i++;
   }
   return 1;
}


int add_visitor( string name, int h ){

   if(!name) return 0;
   if(!h) return 0;
   if(!visitors){
      visitors = ([ name : h ]);
      return 1;
   }
   if( undefinedp(visitors[name]) ){
      visitors[name] = h;
      return 1;
   }
   if( visitors[name] + h > PLAYER_HEAL ){
      return 0;
   }
   visitors[name] += h;
   return 1;
}

restaurant_order(str) 
{
   int tmp;
   if (!str) 
      {
      reply (order_what_string);
      return 0;
   }
   
   /* Invasion embargo stuff */
   if( restrict() ) return 0;
   /* Changed due to the adding of dalias and dalt_name. /Bigfoot 920509 */
   if (dname && (tmp = member_array (str, dname)) >= 0 ) i=tmp;
   else if (dalias && (tmp = member_array (str, dalias)) >= 0) i=tmp;
   else if (dalt_name && (tmp = member_array (str, dalt_name)) >= 0) i=tmp;
   else {  reply (order_what_string);  return 1; }
   
   if (!max_size) max_size=dportable; /* ugly but works */
   value = price (dstrength[i],dheal[i],dportable[i],max_size[i]);
   tp=this_player();
   if (call_other(this_player(), "query_money", 0) < value) 
      {
      reply(not_enough_string);
      say (tp->query_name()+" tries to order, but hasn't got enough money.\n");
      return 0;
   }
     if( call_other(this_player(), "query_overdue", 1) ){
        reply("We've been \"asked\" not to sell to you. Sorry.\n");
         return 0;
      }
   drink =  clone_object(dtype[i]);
   if (dname && sizeof (dname) > i) drink -> set_name (dname[i]);
   if (dalias && sizeof (dalias) > i) drink -> set_alias (dalias[i]);
   if (dalt_name && sizeof (dalt_name) > i) drink->set_alt_name (dalt_name[i]);
   drink -> set_short (dshort[i]);
   if( dlong && sizeof(dlong) > i ) drink->set_long(dlong[i]);
   else drink -> set_long (dshort[i]);
   drink -> set_weight (1);
   drink -> set_strength (dstrength[i]);
   drink -> set_heal (dheal[i]);
   drink -> set_consumer_mess (dmess[i]);
   if (dportable[i]!=1) drink -> set_portable (this_object());
   drink -> set_value (10);          /* value for empty bottle */
   if (value < 10 && value > 0) drink->set_value (value-1);
   drink -> set_full_value (0);      /* worth nothing when full */
   
   if (max_size && sizeof(max_size) > i) 
      {
      drink->set_max_size(max_size[i]);
      if (max_size[i] > 1) drink->set_empty_container ("barrel");
   }
   
   if( move_object(drink,tp) ){
     reply("Seems you can't carry it, it's too heavy for you!\n");
     destruct(drink);
     return 1;
   }

/* Wishbone 4Sep04 - fix barrels re: buying limits */
/* It's an ugly fix, something freaky in max_size as 10/2 was 6... */

   if(drink->query_max_size() && max_size[i] > 1)
    {
     if(!add_visitor(tp->query_real_name(),dheal[i]*(max_size[i]/2-1)))
      {
       reply(enough_healing_string);
       destruct(drink);
       return 1;
      }
    }
   if(!add_visitor(tp->query_real_name(),dheal[i]))
    {
     reply(enough_healing_string);
     destruct(drink);
     return 1;
    }

/* End of fix, leaving the shop total sales as is */

   if (total-dheal[i] <0) 
      {
      reply (enough_healing_string);
      destruct (drink);
      return 1;
   }
   total=total-dheal[i];
   
      write ("You order a "+dname[i]+" for "+value+" dollars.\n");
      say(tp->query_name() + " orders a " + dname[i] + ".\n");
      SHOP_D->logBuy( drink, value, this_object() );
   
   tp->add_money(-value);
   return 1;
}

reply (str) {
   write (reply_string + str);
   return 1;
}

/* Calculate price */
/* On Dalis behalf I fixed a bug that gave negative prices
* ie gave players money when buying heals...
* 961202 - Aladdin
*/
price(str,hl,prtbl,siz)       /* str=strength hl=heal prtbl=portable(0,1) */
{
   int pengar;
   if(!siz) 
      siz=1;
   if(hl) 
      {
      if(prtbl) 
         pengar=siz*((10*hl)+(hl*hl)/5 -(4*str));
      else
         pengar=siz*( (8* hl) + (hl * hl)/5  -(4 * str));
   }
   else if(prtbl) 
      pengar=siz*(str*4 +4);
   else
      pengar=siz*str*4;
   
   if(pengar < 1)
      pengar=5;
   
   return pengar;
}

rest_move(str) {      /* This is called when player leaves room */
   if ( !(ob = find_notportable (this_player())))
      return 0;
   reply ("You can't leave with "+lowercase (ob->short())+".\n");
   return 1;
}

find_notportable(str) {      /* search for portable stuff in player */
   object npo;
   if (!sizeof(npo=deep_inventory (str)))
      return;
   if (!sizeof(npo=filter_array(npo,"filter_npo",this_object())))
      return 0;
   return npo[0];
}

filter_npo(ob) {
   return ob->id("notprtbl");
}

query_restaurant(){ return 1; }

/* -------- settings: -------- */
set_reply (str) { reply_string = str; }
set_order_what (str) { order_what_string = str; }
set_menu_table (str) { menu_table_string = str; }
set_not_enough (str) { not_enough_string = str; }
set_enough_healing (str) { enough_healing_string = str; }
