inherit "obj/obj";
#include "../area.h"

reset(arg)
{
::reset(arg);
if(arg)
  return;
set_name("sign");
set_short("A Warning Sign");
set_long_f(
  "A wooden sign pounded firmly into the ground. "+
  "Text has been burned into it. Try reading it.",FORMAT);
set_read_mess(
  "\t\t\tWarning!\n"+
  "\t Though the Cemetary is a newbie area, it\n"+
  "\t can get very dark at night. Be sure you\n"+
  "\t have a flashlight if it is dusk or night\n"+
  "\t time! Remember that you can examine the\n"+
  "\t weather to see what the time of day is.\n"+
  "\n"+
  "\t* Your trusty TourGuide Committee\n",
  "text");
}

id(str)
{
return 
str=="sign" ||
str=="warning sign" ||
str=="wooden sign";
}
