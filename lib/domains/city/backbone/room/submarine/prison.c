inherit "/std/room";
init() {
   ::init();
   add_action("read", "read");
}

void setup(void) {
      set_light(1);
      set_outdoors(1);
      short_desc = "prison jetty";
      set_long_f("This is a small jetty. A large building stands here. It is a prison. "+
	"There does not seem to be a door, so you wonder how the prisoners get in. There "+
        "is a sign stuck in the ground.");
      skip_obvious=1;
      items_arr=({
	    "door","There is no door!",
	    "ground","There is a sign stuck in the ground",
            "sign", "You might want to read it.",
            "prison","The prison looks like it is in disrepair.",
            "ground","The thing you are standing on.",
            "building","It is a prison.",
            "jetty", "A small prison jetty.",});
   }

read(str) {
   if(str!="sign"){
      write("Read what?\n");
      return 1;
   }
   if(str="sign")
      {
      writef("Welcome to prison island. The war has prevented the city of Abacus from "+
         "adequately maintaining the security and structure of the prison. It "+
         "is strongly suggested that you not enter the prison since your "+
         "security can no longer be ensured.\n");
      return 1;
   }
}
