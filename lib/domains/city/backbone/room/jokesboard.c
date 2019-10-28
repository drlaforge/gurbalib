#include <def.h>
#include <tune.h>
#include <ansi2.h>
#define RED ESC+ANSICODES[COLOURS["RED"]]
#define BLUE ESC+ANSICODES[COLOURS["BLUE"]]
#define GREEN ESC+ANSICODES[COLOURS["GREEN"]]
#define RE ESC+ANSICODES[COLOURS["RESET"]]
#define CYAN ESC+ANSICODES[COLOURS["CYAN"]]
#define MAG ESC+ANSICODES[COLOURS["MAGENTA"]]
#define BOLD ESC+ANSICODES[COLOURS["BOLD"]]
#define ITALIC ESC+ANSICODES[COLOURS["ITALIC"]]
#define UNDERL ESC+ANSICODES[COLOURS["UNDERLINE"]]
#define FLASH ESC+ANSICODES[COLOURS["FLASH"]]

/*  -*- LPC -*-  */
inherit "std/room";
#include "../area.h"

object ob;

void setup(void) 
{
   
    ob = clone_object("obj/board");
    ob->set_name("jokes_board");
    ob->set_alias("board");
    ob->set_short("Jacky's Joke Board");
    ob->set_long("It's a really fucked-up board. It's so funny that you just can't \n"+
                 "resist posting your flappy jokes on it.\n");
    ob->set_save_path("boards/jokes");
    ob->set_delete_level (RET_LEVEL);
    ob->set_max_notes(100);
    ob->set_delete_message(this_player()->query_name()+" screwed up "+this_player()->query_possessive()+" message and aborts it.\n");
    move_object(ob, this_object());
  set_light(1);
  set_outdoors(0);
  set_short("The Comedy Lounge");
  set_long_f("You walk into a high class Comedy Lounge. "
      "As you look around you see a stage with "+
      "Jacky the Joke Man "+
      "sitting on it looking depressed. "+
      "To your left you see a sexy waitress "+
      "bending over a table, and in front you see a "+
      "sign you could read.\n");

add_exit("down",ROOM+"adv_guild");
add_exit("west",ROOM+"archive");

   add_item(({"hot waitress","waitress","skinny waitress","blonde","blonde waitress","very skinny waitress","very skinny blonde waitress","skinny blonde waitress","skinny blonde","very skinny blonde"}),
      	      "A very skinny blonde waitress. OUCH! She is bending over the table,\n"+
	      "nasty thoughts begin to run through your mind");

   add_item(({"stage","comedians stage","comedian's stage"}),
	      "A comedian's stage. Jacky is sitting on it, he seems to be depressed.\n"+
	      "Hard to tell what is wrong with him");

   add_item(({"jacky","jacky the joke man","man","comedian"}),
  	      "Jacky the joke man stands about 5 feet and weighs about 165lbs.\n"+
	      "He looks like the type of person that would make you laugh all night\n"+
   	      "long. As he is setting down right now, you can't really tell\n"+
              "much about him. He looks kinda muscular, under a few inches of flab");
	      
   add_item(({"table"}),
               "There is one HOT waitress bending over it. You are about to fall over.\n"+
	       "You only wish you could get her attention, as your throat's kind of dry\n"+
	       "and the service apparently sucks around here");
    
   add_item(({"high class lounge","comedy lounge","high class comedy lounge","lounge","striking's lounge","strikings lounge","hell"}),
               "This is the lounge that Striking built. Fear not, someone else took care\n"+
	       "of all the typos and bugs before it was in for too long");    
   
   add_item(({"sign"}),
               "Perhaps you could read it");
         
}


init()
{

  ::init();
  add_action("sign_desc","read");
  add_action("ooh_baby",({"pinch","grab","fondle"}));

}

sign_desc(str)
{
  if(!str || (str != "sign")) 
  {
    notify_fail("Read what?\n");
    return 0;
  }

  tell_object(this_player(),("\n"+RED+"  POST YOUR FLAPPY JOKES HERE"+RE+"\n"+
  "\n"+                             "(Jacky the joke man courtesy of\n"+
				    " some crazy idea Striking had)\n"));
  tell_room(TO,(TP->QN+" reads the sign.\n"),({TP}));
  return 1;
}

ooh_baby(str) 
{
  if(!str || (str != "waitress" && str != "waitress' ass" && str != "ass" && str != "blonde ass"))
  {
    notify_fail(C(query_verb())+" what?\n");
    return 0;
  }

  tell_object(TP,break_string("You go to "+query_verb()+" some blonde waitress ass, but get a hard "+
			      "smack instead. For trailer-trash, she has pretty good reflexes.\n",78));
  tell_room(TO,(TP->QN+" tries to get fresh with the waitress and fails like any dork would.\n"),({TP}));
  return 1;
}

query_peace()
{
write("This toom is for making people laugh. Not killing, asshole.\n");
 return 1;
}
