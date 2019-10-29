inherit "obj/container";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("trash bag");
set_short("a black trash bag");
set_long_f("A black trash bag.",FORMAT);
set_id("bag");
set_id("trash bag");
set_id("black trash bag");
set_weight(1);
set_max_local_weight(6);
set_value(50+random(44));
}
