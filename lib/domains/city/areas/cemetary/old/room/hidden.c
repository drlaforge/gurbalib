
inherit "room/room";
int count;
reset(arg) {
  count = 0;
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "A small hidden room";
    
    long_desc = 
        "You stand in a small hidden room under a storage-room.\n";
  /*      + "There are three skulls on the north wall.\n"; */
    dest_dir = ({
        "/room/cemetary/n3_1", "up",
        });
    items = ({
/*      "skulls", "The white skulls looks like human skulls.\n"+
	        "It looks like you can press down the skulls abit.\n",
*/
          });
}
/* init(){
  ::init();
  add_action("press",({ "press", "push", "move", "hit" }));
  }
*/
