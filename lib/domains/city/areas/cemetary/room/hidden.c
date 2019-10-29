
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
    dest_dir = ({
        "/domains/areas/city/cemetary/room/n3_1", "up",
        });
    items = ({
          });
}
