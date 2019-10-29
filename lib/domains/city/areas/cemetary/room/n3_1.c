
inherit "room/room";
int digged;
reset(arg) {
  digged = 0;
  dest_dir = ({
    "/domains/areas/city/cemetary/room/n3", "south",
  });
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeder storage";
    
    long_desc = 
        "You stand in a storageroom of the nightbreeders.\n"
        + "The tunnel continues to the south.\n";
    items = ({
          });
}
init(){
  ::init();
    add_action("dig","dig");
  }
dig(){
  if(digged) return 0;
  if(!present("shovel",this_player())){
    write("You start to dig with your nails. Broke one, broke two, ouch!\n");
    write("You realise you need a shovel to dig here.\n");
    this_player()->reduce_hit_points(random(10));
    say(this_player()->query_name()+" breaks some nails against the floor.\n");
    return 1;
  }
  digged = 1;
  write("You dig and find an exit down.\n");
  say(this_player()->query_name()+" digs up an exit leading down.\n");
  add_exit("down", "/domains/areas/city/cemetary/room/hidden");
  filter_array(all_inventory(this_object()), "update_init", this_object());
  /* I did not come up with this line! Bigfoot did! ^ / Azatoth */
  return 1;
}

