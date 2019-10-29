inherit "obj/armour";
#include "../area.h"

#define MAX_POWER 10000
#define POWER_COST 425

int threshold_level,power,max_power;

reset(arg)
{
::reset(arg);
if(arg)
  return;
threshold_level=5+random(5);
set_name("helmet");
set_short("heal helmet");
set_long_f(
  "A helmet with a complex system of circuitry lining the inside dome. "+
  "It is fairly small.",FORMAT);
set_type("helmet");
set_ac(6);
set_value(1000+random(500));
set_weight(2);
set_wear_func(this_object());
set_max_electricity(MAX_POWER);
set_electricity(MAX_POWER);
}

id(str)
{
return 
  str=="helmet" || 
  str=="heal helmet";
}

wear_function()
{
if(this_player()->query_level()<threshold_level)
  {
  call_out("slow_heal",5+random(10));
  return 1;
  }
writef("You try to squeeze it on your head, but it's too small.\n");
return 0;
}

slow_heal()
{
if(environment()!=worn_by)
  return;
if(power<POWER_COST)
  return write("Your helmet is out of power.\n");
environment()->heal_self(5+random(5));
write("You feel your head tingle delightfully beneath the heal helmet.\n");
power-=POWER_COST;
call_out("slow_heal",20+random(10));
}

query_max_electricity(){ return max_power; }
query_electricity(){ return power; }
set_electricity(x){ power=x; }
set_max_electricity(x){ max_power=x; }
