inherit "obj/monster";
reset(arg)          {
          ::reset(arg);
          if(arg) return;
          set_level(2);
	  set_name("nightbreeder boy");
          set_alias("nightbreeder");
          set_alt_name("boy");
          set_short("a young nightbreeder boy");
          set_long(
          "This is a very ugly looking mutant boy. He is one of the nightbreeders living\n"+
          "on the cemetary. He is very weak of the sun and looks very afraid of you.\n");
          set_wc(1);
          set_ac(1);
}
