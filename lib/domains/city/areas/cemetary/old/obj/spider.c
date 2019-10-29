inherit "obj/monster";
reset(arg){
  ::reset(arg);
    if(arg) return;
    set_level(1);
    set_name("spider");
    set_alias("spider");
    set_alt_name("spider");
    set_short("a spider");
    set_long(
	     "It's a small spider running around in the grave. Looking closer you notice\n"+
	     "that it has got nine legs. It has also a cross on it's back.\n");
    set_wc(1);
    add_money(10+random(5));
    set_ac(0);
    set_hp(10+random(10));
    set_kill_shout(0);
  }
