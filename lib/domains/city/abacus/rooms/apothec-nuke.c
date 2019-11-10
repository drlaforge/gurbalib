/* Hiya Wish recognize your own code? --Naz */
/* This is an honest theft of Wishbones code */
/* Substantially altered by Lestat :) */
#include "../area.h"
#include <def.h>

inherit STD_ROOM;


#define KIT_PATH "/std/object/duoderm.c"
#define KIT_COST 200

int kitt;
object kit;

void setup(void)
{
  kitt = 40;
   
  set_light(1);
  /*set_outdoors(0);*/
  set_short("Inside an apothec");
  set_long("You are standing inside a brand new, clinically clean "+
	     "and fully automatic drug store. Here you can buy first-"+
	     "aid kits and perhaps even pain killers. On the wall "+
	     "there is a list that shows what is for sale in this "+
	     "drug store.\n");
  add_exit("west",ROOMS + "shop");
  add_item("wall","There is a list on the wall that seems " +
           "rather interesting");
  add_item("list","Maybe you should read it?");
  add_item("machine","drug store","store","In fact, this " +
           "drug store is a machine");
  add_item("stair","stairway","stairs","The stairway leads up");
  
  add_action("read_list","read");
  add_action("buy_first_aid","buy");
}

private int read_list(string str)
{
  notify_fail("Read what?\n");
  if(!str || str != "list") return 0;
  W("\n" + "The machine sells:\n" +
    "Duoderm First-aid Kit:    $" + KIT_COST + "\n\n");
  S(TP->QN +" reads the list.\n");
  return 1;
}

private int buy_first_aid(string str)
{
  notify_fail("Buy what?\n");
  if(!str || member_array(str,({
     "duoderm",
     "first aid",
     "first-aid",
     "kit",
     })) < 0) return 0;
  if(kitt < 1)
    {
      W("The machine is out of Duoderm First-aid Kits.\n" +
        "Why don't you come back later?\n");
      S("The machine appears to be out of Duoderm First-aid Kits.\n");
      return 1;
    }
  if(TP->query_money() < KIT_COST) 
    {
      W("You don't have enough money!\n");
      S(TP->QN+" is a bit low on money.\n");
      return 1;
    }
  kit = clone_object(KIT_PATH);
  if(obj->move(kit,TP)) 
    {
      W("The Duoderm First-aid Kit is too heavy for you!\n");
      S(TP->QN+" finds the Duoderm First-aid Kit too heavy.\n");
      destruct(kit);
      return 1;
    }
  W("You buy a Duoderm First-aid Kit from the machine.\n");
  S(TP->QN + " buys a Duoderm First aid kit from the machine.\n");
  TP->add_money(-KIT_COST);
  kitt--;
  return 1;
}
