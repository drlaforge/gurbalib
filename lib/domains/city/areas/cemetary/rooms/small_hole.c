inherit "room/room";
#include "../area.h"

int grave_raided;
int treasure_stolen;

reset(arg)
{
if(grave_raided)
  {
  tell_room(this_object(),"Some dirt piles into the hole.\n");
  grave_raided=0;
  }
if(!present("robber",this_object()))
  tell_room(this_object(),"A grave robber arrives and starts diggin' away.\n");
::reset(arg);
if(arg)
  return;
add_local_unique(CEMETARY+NPC+"digger");
set_outdoors(1);
set_light(1);
set_short("A hole");
add_exit("out",CEMETARY+ROOM+"cem1");
}

id(str)
{
if(grave_raided && str=="skeleton")
  return 1;
if(grave_raided && !treasure_stolen && (str=="bracelet" || str=="gold bracelet"))
  return 1;
}

long(str)
{
switch(str)
  {
  case 0:
    if(!grave_raided)
      writef("The hole is about 150cm deep.",FORMAT);
    else
      writef("The hole is nearly two metres deep. "+
        "A skeleton is mostly buried at the bottom.",FORMAT);
    break;
  case "skeleton":
    write("A partially exposed skeleton.");
    if(!treasure_stolen)
      write(" Around the wrist bone is a gold bracelet.");
    write("\n");
    break;
  case "bracelet": case "gold bracelet":
    write("A gold bracelet. It could be stolen.\n");
    break;
  }
::long(str);
}

init()
{
::init();
add_action("cmd_dig","dig");
add_action("cmd_steal","steal");
}

cmd_dig(str)
{
if(!present("shovel",this_player()))
  return 0;
if(present("robber",this_object()))
  {
  write("The grave robber shoves you and says: This grave is mine, ya pansy!\n");
  say("The grave robber shoves "+this_player()->query_name()+" and says: "+
    "This grave is mine, ya pansy!\n");
  return 1;
  }
if(str!="grave")
  return 0;
if(!grave_raided)
  {
  write("You begin digging deeper into the hole.\n");
  say(this_player()->query_name()+" begins digging deeper into the hole.\n");
  call_out("digging",5);
  return 1;
  }
return 0;
}

cmd_steal(str)
{
object bracelet;
if(str!="bracelet" && str!= "gold bracelet")
  return 0;
if(!grave_raided || treasure_stolen)
  return 0;
bracelet=clone_object(CEMETARY+OBJ+"bracelet");
if(!transfer(bracelet,this_player()))
  {
  write("You steal the "+str+" from the wrist of the skeleton.\n");
  say(this_player()->query_name()+" steals the "+str+" from the wrist of the skeleton.\n");
  treasure_stolen=1;
  return 1;
  }
if(bracelet)
  destruct(bracelet);
write("You fail to steal the "+str+".\n");
return 1;
}

digging()
{
if(!present(this_player(),this_object()))
  return;
write("You come across a skeleton!\n");
say(this_player()->query_name()+" comes across a skeleton!\n");
grave_raided=1;
}