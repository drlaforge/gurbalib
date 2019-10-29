inherit "obj/weapon.c";
#include "../area.h"

reset(arg) {
	::reset(arg);
	if(arg) return;
set_name("machete");
set_alias("rusty machete");
set_short("a rusty machete");
set_long_f("A rusty machete.",FORMAT);
set_wc(11);
set_weight(2);
set_value(65+random(20));
}
