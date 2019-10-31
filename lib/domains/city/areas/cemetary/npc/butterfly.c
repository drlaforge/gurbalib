inherit "std/monster";
#include "../area.h"
void setup(void)
{
set_level(1);
set_id("butterfly");
set_short("a colorful butterfly");
set_long("A small butterfly displaying all colors of the rainbow.\n");
add_id("colorful butterfly");
add_id("small butterfly");
set_max_hp(7+random(8));
/*set_kill_shout(0); will have to implement*/
}

/*Hmm I'm not sure why do we do this? - Exash 19.10.31
second_life()
{
object butterfly;
int where;
::second_life();
where=1+random(12);
butterfly=clone_object(CEMETARY+NPC+"butterfly");
move_object(butterfly,CEMETARY+ROOM+"cem"+where);
say("A new buttefly in cem"+where+".\n");
}
*/

