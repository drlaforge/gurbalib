
inherit "room/room";

int door_status;
reset(arg) {
object guard;
door_status = 0;
if(!present("guard",this_object()))
{
guard = clone_object("/obj/monster");
guard->set_name("guard");
guard->set_short("a nightbreeder guard");
guard->set_alias("nightbreeder");
guard->set_gender(1);
guard->set_race("nightbreeder");
guard->set_level(4);
guard->set_long("The guard seems to guard the door leading north.\n"+
                "The guard has a very misformed face, making him look very dangerous.\n"+
               "");
guard->add_money(40+random(25));
move_object(guard,this_object());
}
    if (arg) return;

    set_outdoors(0);
    set_light(1);
    short_desc = "Nightbreeders territory";
    
    long_desc = 
        "You stand in a tunnel leading north and south.\n"
        + "The place is lit up by torches on the walls.\n"
        + "The tunnel north is blocked by a door.\n";
    dest_dir = ({
        "/domains/areas/city/cemetary/room/n3_1", "north",
        "/domains/areas/city/cemetary/room/w3", "south",
        });
    items = ({
              "torches",
              "The torches are stuck in the mud on the walls",
              "door","#door",
          });
}

/* If you have modified or added something to this file,
 * change this function to return 0 instead of 1.
 */

query_roommaker_access() {  return 1;  }

door(){
if(door_status){ write("The door is open.\n"); return 1; }
write("The door is closed.\n");
return 1;
}
init(){
 ::init();
 add_action("north","north");
add_action("open","open");
add_action("close","close");
}
north(){
if(present("guard",this_object()))
{
write("The guard does all he can to keep you away from the door.\n");
say(this_player()->query_name()+" is stopped by the guard.\n");
if(door_status){
write("The guard closes the door infront of you.\n");
say("The guard closes the door.\n");
door_status = 0;
}
return 1;
}
if(door_status) return 0;
write("The door is closed.\n");
return 1;
}
open(str){
if(str!="door") return 0;
if(door_status){ write("The door is alredy open.\n"); return 1; }
write("Ok.\n");
say(this_player()->query_name()+" open the door.\n");
door_status = 1;
return 1; 
}
close(str){
if(str!="door") return 0;
if(!door_status){ write("The door is already closed.\n"); return 1; }
write("Ok.\n");
say(this_player()->query_name()+" close the door.\n");
door_status = 0;
return 1;
}
