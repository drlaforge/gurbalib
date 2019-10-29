inherit "obj/monster";
reset(arg)          {
          ::reset(arg);
          if(arg) return;
          set_level(2);
          set_name("Cat");
          set_alias("cat");
          set_alt_name("cat");
          set_short("a small cute cat");
          set_long(
          "It's a small cute cat. He looks perfectly normal. He purrs at you\n"+
          "when you look at him.\n");
          set_wc(3);
          set_ac(2);
          set_al(500);
          load_chat(10,({
          "The cute little cat purrs.\n",
          }));
}
