inherit "obj/monster";
reset(arg)          {
          ::reset(arg);
          if(arg) return;
          set_level(3);
          set_name("man");
          set_alias("man");
          set_alt_name("nightbreeder");
          set_short("a weak nightbreeder man");
          set_long(
          "This nightbreeder is quite weak of the sun, but can still give you a evil\n"+
          "grin as you look at him.\n");
          set_wc(3);
          set_ac(1);
          set_hp(30+random(5));
move_object(clone_object("/obj/cemetary/machete"),this_object());
init_command("wield machete");
}
