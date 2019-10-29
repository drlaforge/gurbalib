inherit "obj/weapon.c";
reset(arg) {
	::reset(arg);
	if(arg) return;
set_name("rusty machete");
set_alias("machete");
set_short("a rusty machete");
set_long("The machete must have been lying in dirt for a long time.\n");
set_class(6);
set_weight(1);
set_value(75);
}
