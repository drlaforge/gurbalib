/* I changed to the restaurant standard. Thorwald */

inherit ROOM+"restaurant";

void setup(void) {
       /* resets the max healing per reset */
   

  set_light(1);
  short_desc = "Bar in dark alley";
  long_desc =
    "Welcome to the BACKSIDE BAR.\n"+
    "You're standing in a run down, but still frequently used bar.\n"+
    "The bartender is standing behind the counter, ready to serve you.\n"+
    "You can see a menu on the wall behind the bartender.\n";
  dest_dir =
    ({ROOM+"south_alley3","east",
  });
  items_arr = ({
    "wall","A greasy wall",
    "bartender","#bartender",
    "menu","#menu",
    "counter","#counter",
  });
  dname = ({ "leg", "pork chop","chicken","bone", });
  dalias = ({ "horse leg","chop","fried chicken","meat bone", });
  dshort = ({"a huge horse leg","pork chop","a fried chicken","a meat bone",});
  dmess = ({
         "You eat the horse leg and feel like you could tear a house down.",
         "You almost choke on the huge pork chop when you eat it.",
         "You throw the chicken up in the air and catch it in your mouth.",
         "You break the meat bone into small pieces and eat them all up.",
  });
  dstrength = ({ 15,10,7,5 });
  dheal = ({ 20,15,10,5 });
  dportable = ({ 0,0,0,0 });
  dtype = ({ "obj/food","obj/food","obj/food","obj/food", });
  set_reply ("The bartender grunts: ");
  set_enough_healing ("Hey pal! You've had enough!!!\n");
  set_menu_table ("___________________________");
}

init() {
  ::init();
  add_action("read","read");
  add_action("restaurant_order","order");
  add_action("restaurant_order","buy");
  add_action ("my_menu","menu");  /* remove this if you want :) */
}

my_menu() {
  return menu();
}

bartender() {
    write("The bartender is a big fellow with huge side burns.\n");
    write("He looks at you impatiently.\n");
    write("He says: Well, boy! I ain't got all day you know...\n");
    return 1;
}

counter() {
    write("The bartender is fast at taking empty glasses off the counter.\n");
    write("Maybe he doesn't like people who \"accidentally\" take them home.\n");
    return 1;
}

menu() {
    write("/--============= * ==============---\\\n");
    write("             M  E  N  U\n");
    write("             ==========\n");      
    query_menu();
    write("\n\\--============= * ==============---\\\n");
    return 1;
}

read(str) {
  if(!str || str!="menu") return !notify_fail("Read what?\n");
  return menu();
}

restaurant_order(arg) {
  ::restaurant_order(arg);
  return 1;
}

