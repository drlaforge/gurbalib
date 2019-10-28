#include "/domains/Gangs/JS/js.h"

inherit "std/room";
#include "../area.h"

object  me,jet;

void setup(void) {
   

  set_outdoors(1);
  set_light(1);
  short_desc = "the end of East Road";
  long_desc =
    "You're standing in front of an old, brown brick house with broken windows.\n"+
    "The gravelled road ends here. To the south lies the 5th Avenue which\n"+
    "continues eastwards through town. You think you can see some movement on\n"+
    "the top of the roof, and you are completely sure that you can hear loud\n"+
    "kick-ass music from within the building. Outside the building you see a\n"+
    "sign that says: VOTE FOR INTEGRATION.\n";
  dest_dir = 
    ({ROOM+"roof","up",
      ROOM+"east_road2","west",
      ROOM+"5th_avenue1.c","south",
      });
  items = 
    ({"staircase","Although it's partly broken it sure can hold you",
      "building","It's an old, brown brick house with broken windows",
      "sign","It says: VOTE FOR INTEGRATION",
      ({"movement","top of the roof"}),"You are not sure, but something interesting seems to be going on up there",
      ({"music","kick-ass music"}),"You are not sure what it is, you have to listen for a while to it",
      ({"roof","roof of building"}),"The roof is not so high. If you have the right equipment you\n"
                                   +"might be able to boost up there. If you don't, you would have\n"
                                   +"to 'beg' a sturdy Jetscreamer to help you get there"
      });
}

init() {
  room::init();
  add_action("beg","beg");
  add_action("boost","boost");
  add_action("up","up");
  add_action("listen","listen");
}

beg(string str) {
object ob;
  if(!str) {
    notify_fail("Beg whom to get you there?\n");
    return 0;
  }
  if(!(ob = find_player(str)) || !present(ob,ENV(TP))) {
    notify_fail("There is no one by that name here.\n");
    return 0;
  }
  if(!present("Jetscreamers",ob))
    return W("That person is not a Jetscreamer, and can not help you to get there.\n");
  if(ob->query_level() < ACCEPT_LEVEL)
    return W("That person is not sturdy enough to carry you there.\n");

  action("#NA ## #VNA to carry #OB up to the roof of the JS building.","beg-begs",ob);
  tell_object(ob,"You may now 'boost "+TP->QRN+" to roof' if you accept the plea.\n");
  me = TP;
  jet = ob;
  return 1;
}

boost(string str) {
mixed whom;
  if(!str) return !notify_fail("Where do you want to boost?\n");
  if(str == "to roof") return up();
  if(sscanf(str,"%s to roof",whom)!=1) return 0;
  if(!whom = find_player(whom) || !present(whom,ENV(TP)))
    return W("There is no player by that name who wants a ride here.\n");
  if(!SCREAMER)
    return W("You are not able to get there yourself, dood.\n");
  if(TP != jet)
    return W("No one has begged you for a ride.\n");

  write_file("/"+HEAD_PATH+ "log/js.join",
             whom->query_real_name()+" ("+
             whom->query_level()+")"+
             " was accepted by "+this_player()->query_real_name()+
             " ("+this_player()->query_level()+") "+
             " "+extract(ctime(time()), 4, 15)+".\n");

  (CMDS+"start")->main("screamer");
  action("#NA ## to the roof, carrying #VNA under a strong arm.","boost-boosts",whom);
  move_object(whom,ROOM+"roof");
  move_object(TP,ROOM+"roof");
  tell_room(ENV(TP),TP->QN+" arrives.\n"+whom->QN+" arrives.\n");
  command("look",TP);
  command("look",whom);
  (CMDS+"stop")->main("screamer");
  return 1;
}

up() {
  if(!SCREAMER)
    return W("You are not able to climb to the roof. Someone had better help you up\n"
            +"if you want to go there.\n");
  if(!SCREAMER->query("started"))
    (CMDS+"start")->main("screamer");
    call_out("post_down",1);
}

listen(string str) {
string *tunes;
  if(str && str != "music" && str != "kick-ass music") {
    notify_fail("Listen to what?\n");
    return 0;
  }
  tunes = ({
    "Misery Loves Co.","Pantera","Faith no more","Sisters of Mercy","Helmet",
    "Machines of loving grace","Nine inch nails","Rage against the machine",
    "Offspring","Entombed","Danzig","Peace, love and pitbulls","Biohazard",
    "Skinny puppy","Marilyn manson","Silverchair","Soundgarden","K.C. and the Sunshine Band","The Main Street Singers","ABBA"
  });
  return W("You can hear a tune by "+
           tunes[random(sizeof(tunes))]
         +" being played on VERY high volume from\ninside the building.\n");
}

post_down()
{
  (CMDS+"stop")->main("screamer");
}
