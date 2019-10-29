inherit "obj/monster";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_level(1);
set_name("butterfly");
set_short("a colorful butterfly");
set_long_f("A small butterfly displaying all colors of the rainbow.\n",FORMAT);
set_id("colorful butterfly");
set_id("small butterfly");
set_hp(7+random(8));
set_kill_shout(0);
}

second_life()
{
object butterfly;
int where;
::second_life();
where=1+random(12);
butterfly=clone_object(CEMETARY+NPC+"butterfly");
move_object(butterfly,CEMETARY+ROOM+"cem"+where);
/* say("A new buttefly in cem"+where+".\n"); */
}
