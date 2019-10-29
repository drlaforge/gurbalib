inherit "obj/shootweapon";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_short("a rifle");
set_name("rifle");
set_long_f("An old, rather dirty rifle.",FORMAT);
set_value(200+random(250));
set_wc(10);
set_weight(5);

set_gun_type("rifle");
set_two_handed(1);
set_automatic(0);
set_burst(0);
set_velocity(350);
set_bweight(5);
set_calibre("1700");
set_mag(4);
set_ammo(4);
modify_recoil(25);
  /* Newbie area, newbies should be able to control. */

set_shooter_msg(
"A loud banging noise is heard as you fire your rifle.\n");
set_shooting_msg(
"shoots his rifle with a loud bang.\n");
set_victim_msg(
"shoots at you with his rifle, making a loud banging noise.\n");
}

id(str)
{
return str=="rifle" ||
str=="dirty rifle" ||
str=="rather dirty rifle" ||
str=="old, rather dirty rifle";
}
