inherit "obj/monster";

reset(arg)          
{
  ::reset(arg);
  if(arg) return;
    set_level(1);
    set_name("beetle");
    set_alias("beetle");
    set_alt_name("beetle");
    set_short("a beetle");
    set_long(
      "It's a small beetle running around in the bottom of this grave. If you are\n"+
      "fast enough you maybe can squeeze it.\n");
    set_wc(1);
    set_ac(0);
    set_hp(15+random(10));
    set_kill_shout(0);
    add_money(10+random(5));
}

init(){
	::init();
	add_action("squeeze","squeeze");
}

squeeze(str)
{
  object beetle;
  if(str == "beetle")
  {
    if(random(50)<25)
    {
      write("You missed the beetle.\n");
      return 1;
    }
    write("You put your foot on the bug squeezing it to pieces.\n");
    say(this_player()->query_name()+" puts a foot on the beetle squeezing it to peices.\n", this_player());
    this_player()->add_exp(25+random(25));
    beetle = clone_object("/obj/obj/corpse");
    beetle->set_name("beetle");
    move_object(beetle,environment(this_object()));
    destruct(this_object());
    return 1;
  }
}
