/* Plague changed this file.. make it flow better. */

inherit "room/room";

reset(arg) {
  if (arg) return;
  set_outdoors(0);
  set_light(0);
  short_desc = "a cellar in the house at the cemetary";
  long_desc = 
    "You are standing is the cellar of the house, except that it now looks\n"+
    "more like a cave. The walls are covered with dirt, and the floor has\n"+
    "a layer of grime on it as well. The air is so humid you can feel it\n"+
    "cling onto your exposed face like a wet mask. The cellar continues to\n"+
    "the north, where you can barely see the outline of some furniture.\n";
  items = ({
    ({"walls","wall","floor"}), 
      "They are covered with a foul smelling grime.",
      "@You almost gag at the smell...",
    "furniture","Their outlines are too fuzzy to see from here.",
  });
  dest_dir = 
    ({
      "/domains/areas/city/cemetary/room/house", "up",
      "/domains/areas/city/cemetary/room/housecell2", "north",
    });
}

