/* Now the shopkeeper in this shop will randomly choose a weapon
to protect himself. Mindmaster Mastermind 971012 */
/* Fixed shopkeeper weapon routines, and made him pick the best one - Darkman 011221 */
/* Shopkeeper timed, masked calc_val for night keeper, more colors - Darkman 020613 */

#include <tune.h>
inherit ROOM+"std_shop";

string get_rand_color() {
   string *colors;
   
   colors = ({"blue", "red", "violet", "pink", "yellow", "black", "white", 
         "light blue", "green", "light green", "purple", "beige", "grey",
         "navy blue", "cyan", "magenta", "orange", "aqua", "brown" });
   return colors[ random(sizeof(colors)) ];
}

void setup() 
{
   string color;
   color = get_rand_color();
   ::reset (arg);
   
   set_short("Central "+capitalize(color)+" Shop.");
   set_long_f("You have entered the shop. The floor is clean, "
      +"and the walls are a nice "+color+" colour. "
      +"There is a window in the northern wall and you can occasionally see "
      +"the shopkeeper behind it. He will buy your goods and also sell what he "
      +"has already. There are many empty shelves here, and you suspect that "
      +"the shopkeeper stores what he buys in the back somewhere safe. "
      +"If you type: 'list s/m/w/a', you can get a printout of the items for "
      +"sale. If you have further questions, type 'help shop' for more info.",78);
      add_help(({ROOM+"", "shop"}),
"This is the central Abacus Shop. The commands are simple:\n"+
"\n"+
"list w      - Lists Weapons for sale.\n"+
"list a      - Lists Armours for sale.\n"+
"list s      - Lists Shootweapons for sale.\n"+
"list m      - Lists Misc. objects (keys, ammo, etc) for sale.\n"+
"list foo    - Lists all \"foo\" for sale, for example: \"list sword\"\n"+
"              will list all swords for sale.\n\n"+
"sell item   - Will sell \"item\" from your inventory to the shopkeeper.\n"+
"buy item    - Buy \"item\" from the shopkeeper.\n"+
"value item  - Determine the current value of your item, eg: \"value sword\"\n"+
"browse item - Quickly look over an item for sale in the shop.\n\n"+
"The shop is staffed day and night, except for a few hours for the the\n"+
"shift change. Sorry for the inconvenience.\n\n           - Shopkeeper.\n");
   
   items_arr = ({
         ({"wall", "walls", color+" wall", color+" walls"}), 
         "They have been painted a nice "+color+" colour",
         ({"northern wall"}),
         "There is a window in the northern wall, through which you see the shopkeeper.",
         "floor",
         "The floor is very clean",
         ({"shelves","shelf", "empty shelves"}), 
         "The shelves are mostly empty",
         ({"window","glass"}), 
         "The glass on the window is covered by iron bars.",
         "racks", 
         "They look as if something used to be on them, but they are empty now.",
         ({"shop", color+" shop"}),
         "The shop is where you sell and buy items. When the shopkeeper is around,\n"+
         "you can get him to list the prices for you.",
         ({"bars", "iron bars"}),
         "The iron bars covers the window, that seperates the customers from the\n"+
         "shopkeeper."
          });
   
   if (arg)
      return;
   
   set_light(1);
   set_outdoors(0);
   
   add_exit("south",ROOM+"central_square",0);
   add_exit("west",ROOM+"sentel/cpshop",0);
   add_exit("east",ROOM+"apothec",0);  
   
   add_object("std/object/recharger", 1);
   add_object("std/object/trashcan", 1);
   if( !random(2) )
   add_object( "/obj/monsters/shopkeeper.c", 1 );
     else
    add_object( "/obj/monsters/shopkeep2.c", 1 );
   
   set_reply_mess("The shopkeeper says: ");
   set_store_exit("north");
}

init () 
{
   ::init();
   add_action("check_keeper", ({ "list", "show", "sell", "buy", "value", "browse" }) );
}


check_keeper(str)
{
   if(!present("shopkeeper") && !present("shopkeep2"))
      {
if( this_player()->query_level() <= NEWBIE_LEVEL && this_player()->query_gang() == 0 ){
write("A helper droid appears out of the back to assist you in your transaction.\n");
return 0;
}
      write("Unfortunately, there is no one here to help you. Try again later.\n");
      return 1;
   }
   return 0;
}

calc_sell_value(value) {
   object n_keep;
   int n_value, o_value;
   
   o_value = std_shop::calc_sell_value(value);
   if(!n_keep = present("shopkeep2", this_object()))
      return o_value;
   
   if(o_value <= 1000) n_value = 0;
   else
      n_value = random(value);
   if( n_value > 500 ) n_value = random(random(400));
   if( !random(3) ) n_keep -> add_money(n_value);
   
   return (o_value+n_value);
}

int list(string in){
   switch(in){
      case "armour" :
      case "armours" :
      return ::list("a");
      break;
      case "weapon" :
      case "weapons" :
      return ::list("w");
      break;
      case "shoot" :
      case "shootweapon" :
      case "guns" :
      case "shootweapons" :
      return ::list("s");
       case "misc" : return ::list("m"); 
      default : return ::list(in);
   }
   return 0;
}

