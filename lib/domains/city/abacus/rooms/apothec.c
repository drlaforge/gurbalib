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

