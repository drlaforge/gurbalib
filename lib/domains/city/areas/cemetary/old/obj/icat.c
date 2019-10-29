inherit "obj/monster";
reset(arg)          {
          ::reset(arg);
          if(arg) return;
          set_level(5);
          set_name("Cat");
          set_alias("cat");
          set_alt_name("cat");
          set_short("a wierd looking cat");
          set_long(
          "This cat doesnt look sweet at all. It looks at you with evil dark eyes,\n"+
          "making you shiver alittle.\n");
          set_wc(3);
          set_ac(2);
          set_al(-500);
          load_chat(8,({
          "The cat barks.\n",
          "The cat looks at you with evil dark eyes.\n",
          "The cat says something with a deep dark voice.\n",
          }));
          load_a_chat(5,({
          "The cat smiles happily as you hit it.\n",
          "The cat barks at you.\n",
          }));
}
