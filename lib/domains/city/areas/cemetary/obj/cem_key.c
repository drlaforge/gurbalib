inherit "obj/obj";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_short("dirty key");
set_long_f("A dirty key.",FORMAT);
set_value(150);
set_weight(1);
set_get(1);
}

id(str)
{
return 
 str=="key" ||
 str=="dirty key" ||
 str=="cemetary_key";
}
