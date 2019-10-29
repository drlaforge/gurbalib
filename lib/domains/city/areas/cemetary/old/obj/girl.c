inherit "obj/monster";
reset(arg)          {
          ::reset(arg);
          if(arg) return;
          set_level(2);
          set_name("nightbreeder girl");
          set_alias("nightbreeder");
          set_alt_name("girl");
          set_short("a nightbreeder girl");
          set_long(
          "This is a very ugly looking mutant girl. She is one of the nightbreeders \n"+
          "living in the cemetary. She is weak of the sun.\n");
          set_wc(1);
          set_ac(1);
	set_gender(2);
}
