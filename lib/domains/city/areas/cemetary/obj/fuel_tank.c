inherit "obj/fuel_container";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("tank");
set_short("a fuel tank");
set_long_f("A fuel tank. It could hold roughly 15 litres.",FORMAT);
set_id("fuel tank");
set_weight(2);
set_value(50+random(150));
set_get(1);

set_tank(15);
set_fuel(10);
}
