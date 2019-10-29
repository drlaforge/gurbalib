inherit "obj/monster";
reset(arg)          {
          ::reset(arg);
          if(arg) return;
          set_level(1);
          set_name("worm");
          set_alias("worm");
          set_alt_name("slimy worm");
          set_short("a slimy worm");
	add_money(10+random(5));
          set_long(
          "It's a slimy worm.\n");
         set_hp(25);
         set_kill_shout(0);
}
