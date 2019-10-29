
inherit "obj/monster";
reset(arg){
  ::reset(arg);
    if(arg) return;
    set_level(1);
    set_name("butterfly");
    set_alias("butterfly");
    set_alt_name("fly");
    set_short("a colorful butterfly");
    set_long(
	     "A small butterfly in the rainbows all colours.\n"+
	     "It looks very harmless.\n");
    set_wc(1);
    set_ac(0);
    set_hp(7+random(8));
    set_kill_shout(0);
}
second_life(){
  object butt;
  int where;
  ::second_life();
  where = 1+random(12);
    butt = clone_object("/obj/cemetary/butterfly");
  move_object(butt,"/room/cemetary/cem"+where);
/*  say("A new buttefly in cem"+where+".\n"); */
}
