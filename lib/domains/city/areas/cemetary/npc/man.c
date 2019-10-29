inherit "obj/monster";
#include "../area.h"

reset(arg){
::reset(arg);
if(arg)
  return;
add_object(CEMETARY+OBJ+"fuel_tank");
add_object(CEMETARY+OBJ+"ironbar",1,"wield ironbar");
set_level(3);
set_name("man");
set_short("a ragged man");
set_long_f(
"A scrawny, ragged man.",FORMAT);
load_chat(5,({"#chat_stuff"}));
set_mass_defend(1);
}

id(str)
{
return str=="man" ||
str=="ragged man" ||
str=="scrawny ragged man";
}

chat_stuff()
{
int n;

n=random(2);
switch(n)
  {
  case 0:
    if(!random(2))
      say("The flames in the trashcan surge as the ragged man "+
        "pours something into it.\n");
    break;
  case 1:
    if(present("boy",environment()))
      say("The ragged man says: Stay close to the fire son.\n");
    break;
  }
}
