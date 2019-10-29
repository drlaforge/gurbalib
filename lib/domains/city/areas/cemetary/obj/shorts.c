inherit "obj/armour";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("pants");
set_plural_short("Torn-up pants");
set_short("Torn-up pants");
set_long_f("These pants are so torn up they barely even look like shorts.",FORMAT);
set_type("pants");
set_ac(2);
set_value(5+random(5));
set_weight(1);
}

id(str)
{
return str=="pants" ||
str=="torn-up pants";
}
