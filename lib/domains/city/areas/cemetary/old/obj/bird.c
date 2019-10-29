inherit "obj/walkingmonster.c";

reset (arg) {
  ::reset();
    if (arg) return;
    set_name ("a pigeon");
    set_alias ("pigeon");
    set_alt_name ("bird");
    set_short ("a pigeon");
    set_long ("It's a beautiful pigeon.\nIt's the kind that lives on cemetarys.\n");
    set_level (1);
    set_wc (0);
    set_ac (0);
    set_walking(25);
    setmout ("A pigeon flies #D");
    setmin ("A pigeon flies in");

}
