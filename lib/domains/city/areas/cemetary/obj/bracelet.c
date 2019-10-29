inherit "obj/armour";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("bracelet");
set_short("gold bracelet");
set_long_f("A beautiful gold bracelet.",FORMAT);
set_type("glove");
set_ac(2);
set_value(750+random(250));
set_weight(1);
}

id(str)
{
return 
  str=="bracelet" || 
  str=="gold bracelet" || 
  str=="beautiful gold bracelet";
}
