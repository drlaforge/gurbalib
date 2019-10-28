
inherit ROOM+"casino/stdroom.c";

void setup(){
    
    
   set_short("Andre's Casino");
   set_light(1);
   set_outdoors(0);
   set_long_f("This is the largest, cleanest, and most packed room of this small casino. Since "+
      "this room is the most visited by the patrons the management has seen fit to actually "+
      "clean the spit and dirt off the floor every now and then. There is only one reason to be "+
      "in here - to play Roulette. There is a large sign you may want to look at nailed to the wall.", 80);
   add_exit("west", ROOM+"casino/baRoom", "#cashIn");
   add_exit("south", ROOM+"casino/sRoom", "#cashIn");
   add_readable(({"large sign", "sign"}),
      "STANDARD PRODUCTS GAMING nor ANDRE'S CASINO accept any responsibility for any losses.\n"+
      "A maximum of eight players can be accommodated at any one time on\n"+
      "our roulette table.\n"+
      "                       -- The Gaming Commission");
   add_object(ROOM+"casino/roulette.c", 1);
}

int cashIn(){
   if( present("roulettetoken", this_player()) )
      command("cash", this_player());
   return 0;
}

