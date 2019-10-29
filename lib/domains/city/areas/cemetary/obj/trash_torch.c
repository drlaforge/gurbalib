inherit "obj/obj";
#include "../area.h"

#define BURN_TIME (170+random(195))

int trash_type;

reset(arg)
{
::reset(arg);
if(arg)
  return;
trash_type=random(2);
set_weight(1);
set_get(1);
set_light(1);
call_out("end_the_burn",BURN_TIME);
set_characteristics(0);
}

set_characteristics(arg)
{
if(!arg)
  switch(trash_type)
    {
    case 0:
      set_name("newspaper");
      set_short("a clump of newspaper (burning)");
      set_long_f("A clump of newspaper. The end is on fire.",FORMAT);
      set_id(({"newspaper","clump of newspaper","clump"}));
      break;
    case 1:
      set_name("stick");
      set_short("a wooden stick (burning)");
      set_long_f("A wooden stick. The end is on fire.",FORMAT);
      set_id(({"stick","wooden stick"}));
      break;
    }
if(arg)
  switch(trash_type)
    {
    case 0:
      set_short("a smoldered clump of newspaper");
      set_long_f("A smoldered clump of newspaper.",FORMAT);
      set_id("smoldered clump of newspaper");
      break;
    case 1:
      set_short("a smoldered wooden stick");
      set_long_f("A smoldered wooden stick.",FORMAT);
      set_id("smoldered wooden stick");
      break;
    }
}

end_the_burn()
{
set_characteristics(1);
if(!environment(this_object()))
  return;
if(!living(environment(this_object())))
  {
  if(!set_light(-1))
    tell_room(environment(this_object()),"It becomes dark.\n");
  return;
  }
tell_object(environment(this_object()),"The "+query_name()+" stops burning.\n");
if(!set_light(-1))
  tell_object(environment(this_object()),"It becomes dark.\n");
}

message_fun(obj)
{
tell_object(obj,"You cautiously reach towards the flames "+
  "and pull out "+short()+".\n");
say(obj->query_name()+" pulls "+short()+" out of the "+
  "burning trashcan.\n");
}
