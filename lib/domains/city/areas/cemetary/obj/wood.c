inherit "obj/weapon.c";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("splinter");
set_short("a thick splinter of wood");
set_long_f("A rusty machete.",FORMAT);
set_wc(6);
set_weight(2);
set_value(5+random(10));
set_wield_func(this_object());
}

id(str)
{
return 
 str=="splinter" || 
 str=="thick splinter" || 
 str=="splinter of wood" || 
 str=="thick splinter of wood";
}

wield_function(arg)
{
tell_object(find_player("mystiq"),"Blah\n");
tell_object(find_player("mystiq"),source_file_name(previous_object()));
}
