inherit ROOM+"std_new_shop";

init () {
   ::init();
   add_action ("help","help");
}
void
reset (int arg) {
  ::reset (arg);
    if (arg)
      return;
    set_light(1);
    set_outdoors(0);
    short_desc = "A hi-tech wonder store.";
    long_desc = 
      "etc\n";
    dest_dir = (["south":({ROOM+"central_square",0}),
		 "west":({ROOM+"phone_room",0}) ]);
    items_arr = ({
      ({"window","glass"}), "The glass on the window is covered by iron bars.",
      "racks", 
        "The look as if something used to be on them, but they are empty now.",
      "merchant",
        "He looks like a hardy person and worked hard to open this store.",
      ({"walls","walls"}), "They have been repainted a pale beige colour.",
    });
    move_object (clone_object ("std/object/trashcan"),this_object());
    move_object (clone_object ("obj/r2"),this_object());

    set_reply_mess ("New words appear on the VDU: ");
    set_store_exit ("north");
    set_store_type("armour");

}

help (str) {
   if (str == "shop") {
      write ("Welcome to the shop.\n");
      write ("Commands are:\n");
      write (" list (armours|weapons|shootweapons|misc)\n");
      write ("       'armours' will show only armours.\n");
      write ("       'shootweapons' will show only shootweapons.\n");
      write ("       'weapons' will show shoot- and ordinary weapons.\n");
      write ("       'misc' will show everything but armours and weapons.\n");
      write (" sell <item>\n");
      write (" buy <item>\n");
      write (" value <item>\n");
      write (" browse <item>\n");
      return 1;
   }
}
