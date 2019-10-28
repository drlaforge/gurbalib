/*  MILLIONAIRES COLLECTION BOX ADDED - Mycon 05-04-07 */
#include <def.h>
#include <tune.h>
#define StoreRoom   (ROOM+"casino/weapStorage.c")
inherit STD_ROOM; 
#include "../area.h"

void setup(){
    
    
   set_short("Andre's Casino");
   set_long_f("This newly opened casino hardly resembles anything you have heard about "+
      "the casinos of the old days. There are no flashy lights, cute waitresses, free drinks, "+
      "or anything like that. The only bright sign is the one outside! Just a dingy little room with a large door and a large "+
      "sign with little writing on it to the left of it. There seems to be a receptacle of some "+
      "sort to your left as well.\n", 80);
   add_item( ({ "recepticle", "weapon drop", "weapon slot" }), "This simple device takes your weapons and stores them till you leave the casino again");
   add_item( ({ "door", "wooden door", "large wooden door", "large door" }), "A large wooden door into the casion");
   set_light(1);
   set_outdoors(0);
   add_item("sign", "Try reading it");
   add_exit("east", ROOM+"eve_street1");
   add_exit("north", ROOM+"casino/sRoom.c", "#checkEntry");

}

int query_peace(){ return 1; }

void init(){
   ::init();
   add_action("push", "push");
   add_action("read", "read");
   add_action("check", "check");
}

int read(string str){
   if(!str || (str && str != "sign")) return 0;
   printf("%-:'='55s\n%|55s\n%-:'='55s\n%s\n%-:'='55s\n",
      "", "Welcome to Andre's Casino", "",
      "\n Welcome to my new casino. Follow these simple rules: \n"+
      " 1) No fighting.\n"+
      " 2) Spend Money.\n\n  -- Andre\n", "");
   return 1;
}

int weaps(object o){
   return (int)(o->weapon_class());
}
int check(string str){
   int i;
   object *objs;
   if(!str) return !notify_fail("Check what?\n");
   if(str != "weapons") return !notify_fail("Check what?\n");
   objs = filter_array( all_inventory(TP), "weaps", TO );
   if(!sizeof(objs)) return !notify_fail("You don't have any weapons!\n");
   for(i=0; i<sizeof(objs); i++)
   StoreRoom->store( objs[i], TP->QRN );
   write("You hand over your weapons.\n");
   write("A mechanical voice says: Thank you, you may enter now. To get them back, just: \"push button\".\n");
   return 1;
}

int push(string str){
   if(!str || (str && str != "button")) return !notify_fail("Push the button perhaps?\n");
   if(!StoreRoom->ret( this_player()->query_real_name() ))
      write("Error in getting your equipment. Sorry.\n");
   else
      write("Your equipment is returned to you.\n");
   return 1;
}

int checkEntry(){
/*
   object *objs;
   objs = filter_array( all_inventory(TP), "weaps", TO );
   if( sizeof( objs ) )
      {
      write("As you go to open the door, a grid of lasers form and a voice booms: \"check weapons\" first.\n");
      return 1;
   }
*/

   write("You enter through the door and climb up a flight of steps...\n");
   return 0;
}

