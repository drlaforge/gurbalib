inherit ROOM+"restaurant";

#include <tune.h>

string vets;

init () {
   ::init();
   if (this_player()->query_level() < VET_LEVEL) {
     tell_room (this_object(),"The bartender points at "+this_player()->query_name()+" and laughs.\nThe bartender says: Where is your mom then?\n");
   }
   if (this_player()->query_level() >= VET_LEVEL) {
     add_vet(this_player()->query_name());
   }
   add_action ("my_order","order");
   add_action ("my_order","buy");
   add_action ("my_menu","menu");
}


reset (arg) {
    
    
     
    vets=([ ]);
    set_short("In the Veteran pub");
    set_long_f
        ("You stand in an exclusive pub decorated with dark wooden "+
        "furniture. You see photographs of famous veterans and legends "+
         "on the wall. "+
        "There is a stairway leading down to the local pub. "+
        "Do 'menu' to see what you can order.\n");

    set_light (1);
    set_outdoors (0);
    items_arr = ({ ({ "photographs","photos","pictures"}),"#photographs",
		 "stair","It's leading down to the pub",
	         ({"furnitures","furniture"}),"Dark wooden furnitures", });
    dest_dir = ({ 
      ROOM+"pub","down", 
/* - Removed, Wishbone 20Dec03
      ROOM+"tobshop","north", 
*/
    });
    dname = ({ "tequila","icetea","mixture","chili", });
    dalias = ({ "glass", "long island","barrel", "hot chili", });
    dshort = ({ 
      "A glass of strong Tequila",
      "A Long Island icetea",
       "A barrel of Doctor's Mixture",
       "Hot chili",
    });
    dmess = ({ 
      "Ough! You sweep the glass of tequila",
      "You drink the icetea. HOT!",
      "Ouh! You drink some from the mixture.",
      "You eat the chili.\nYou wipe the sweat from your forehead.",
    });
    dstrength = ({ 21, 22, 18, 22, });
    dheal = ({ 27, 30, 20, 25});
    dtype = ({ "obj/drink", "obj/drink", "obj/drink","obj/food",});
    dportable = ({ 1,1,1,1 });
    max_size = ({ 1,1,10,1 });
    set_reply ("The bartender says: ");
    set_order_what ("Order what?\n");
    set_menu_table ("___________________________: ");
    set_not_enough ("You don't have enough money.\n");
    set_enough_healing ("You've had enough in here for now.\n");
}

my_order (str) {

/*
   if(str == "mixture" || str == "barrel")
    {
      if(this_player()->query_money() < 2990)
        {
         writef("You don't have enough money!\n");
         return 1;
        }
      if(!mix)
        {
         writef("The bartender says: I'm sold out... Just can't get the supplies these days.\n");
         return 1;
        }
     if(!restaurant_order("mixture"))
        {
	writef("blah");
         return 1;
        }
      mix -= 1;
      return 1;
   }
*/

  restaurant_order (str);
  /* ^ this will return 1 if success 0 if not success */
  return 1;
}

my_menu () {
   write ("*-------** THE VETERAN MENU **-------*\n");
   query_menu();
   write ("*------------------------------------*\n");
   return 1;
}

add_vet(v) {
  if (!vets[v]) vets+=([ v:get_what() ]);
  return;
}

get_what() {
  int i;
  i=random (11);
  switch (i) {
  case 0:
    return "fighting an army of mutated gangwarriors"; break;
  case 1:
    return "fighting droids at the battle of Kendir"; break;
  case 2:
    return "fighting in the 5th gangwar"; break;
  case 3:
    return "drinking lots of beer in the local pub";break;
  case 4:
    return "shooting the model X laser cannon";break;
  case 5:
    return "going real fast on a jet motorbike";break;
  case 6:
    return "killing a whole army of battledroids";break;
  case 7:
    return "slaughtering a bunch of sewer warriors";break;
  case 8:
    return "recovering from a bad fight in the whorehouse";break;
  case 9:
    return "posing with a really large machinegun"; break;
  case 10:
    return "trying out a new jetpackage";break;
  }
}

photographs() {
  string m;
  int i,i2;
  m=m_indices(vets);
  if (sizeof(m)>0) {
    write ("You see pictures of among others..\n");
    while (i<sizeof(m)) {
      write (m[i]+" "+vets[m[i]]+".\n");
      i++;
    }
  }else {
    write ("You see pictures of great veterans fighting great wars.\n");
  }
  return;
}
