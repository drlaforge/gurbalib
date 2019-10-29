inherit "obj/monster";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
add_object("/obj/obj/shovel",1,"wield shovel");
add_object(CEMETARY+OBJ+"bag");
add_object(CEMETARY+OBJ+"shorts",1,"wear pants");
set_level(3);
set_name("grave robber");
set_alias("robber");
set_short("a grave robber");
set_gender(1);
set_long_f(
  "An old man attempting to pillage this grave.\n",
  FORMAT);
load_chat(5,({"#chat_dirt"}));
}

chat_dirt()
{
int n;
n=random(5);
switch(n)
  {
  case 0:
    say("The grave robber huffs and puffs.\n");
    break;
  case 1:
    say("The grave robber says: This place has tons of riches. "+
      "You just gotta find a shovel and dig the graves.\n");
    break;
  case 2:
    say("The grave robber yells: Go away, you're making me nervous.\n");
    break;
  case 3..5:
    if(environment()->query_light()>0)
      say("The grave robber fills his shovel with dirt and tosses it upwards.\n");
    if(find_object(CEMETARY+ROOM+"cem1")->query_light()>0)
      tell_room(find_object(CEMETARY+ROOM+"cem1"),
        "A mass of dirt comes flying out of the hole and lands on the pile of dirt.\n");
    break;
  }
}
