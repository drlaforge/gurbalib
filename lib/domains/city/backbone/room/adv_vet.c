#include <def.h>
#include <tune.h>
inherit "std/room";
#include "../area.h"

#define CUR_EXP this_player()->query_exp()
#define LEVEL_EXP ROOM+"guildroom"->query_experience(this_player()->query_level())
#define REP_COST ROOM+"guildroom"->query_stat_experience(this_player()->query_Rep()+1)

#include <tune.h>

void setup(void)
{
    object board;

    if (arg)  return;

    board = clone_object("/obj/board");
    board -> set_save_path("boards/vet");
    board -> set_short("A small DBBS.");
    board -> set_delete_level(RET_LEVEL);
    board -> set_max_notes(50);
    move_object(board, this_object());

    outdoors = 0;
    no_clean_up = 0;
    set_light(1);
    short_desc = "The veterans place";
    set_long_f("You have entered the home of the veterans. "+
 	       "The walls are made from ancient, solid oak, upon "+
 	       "which small lights flicker irregularly. You notice "+
 	       "a small bulletin board in the northwest corner of "+
 	       "the room, barely visible among the shadows. The whole "+
 	       "atmosphere makes you feel very cozy and secure. "+
	       "You can 'advance rep' here as well as checking its 'cost'.\n");
    items_arr = ({
              ({"oak walls","oak wall","wall","walls"}),
 "The walls are made from solid oak, darkened by the passage\n"+
 "of time to a colour resembling ash grey. You marvel at the\n"+
 "history that must be embodied in these walls, and can't help\n"+
 "but think that buildings were made to last in ancient times.",

              ({"lights","light"}),
 "As you examine the lights more closely you notice that they\n"+
 "are small lanterns attached to the wall. They burn brightly\n"+
 "with a soft orange glow, casting shadows as they flicker,\n"+
 "struggling to remain alight with every rush of air.",


 "corner","A shadowy corner of the room, which is barely visable\n"+
          "from where you stand.",
 "shadows","The shadows obscure the bulletin board.",
 ({"glow","lantern","lanterns"}),"The lanterns glow softly.",
 ({"oak","wood"}),"The walls are made of oak.",

	    });
    smell_desc = "The smell of old cigarette smoke fills your nose.";
    sound_desc = "Only the sound of your own\n" +
                 "breathing reaches your ears.";
    smells = ({
               ({"oak walls","oak wall","wall","walls"}),
               "The walls smell of old cigarette smoke.",

             });
    dest_dir = (["down":({ROOM+"adv_guild",0}),]);
}

init()
{
  ::init();
  if (this_player()->query_level() >= VET_LEVEL)
  {
    add_action ("advance","advance");
    add_action ("cost","cost");
    return;
  }
  write("Only veterans are allowed to be here. You're move_objected away.\n");
  say(this_player()->query_name()+" tried to enter but failed miserably.\n");
  move_object(this_player(), ROOM+"adv_guild");
}

advance(s) {
  if (!s || (s!="rep" && s!="repair")) return 0;
  if (this_player()->query_level() < VET_LEVEL) {
    write ("You must be a veteran or legend.\n");
    return 1;
  }
  if (this_player()->query_Rep() <1) {
    write ("You must learn how to repair weapons first.\n");
    return 1;
  }
  if(CUR_EXP<REP_COST) {
    write("You don't have the experience.\n");
    return 1;
  }
  this_player()->add_exp(-REP_COST);
  this_player()->add_Rep(1);
  write ("Ok. You are now better at repairing weapons.\n");
  return 1;
}

cost() {
  int i,i2;
  if (this_player()->query_level() < VET_LEVEL) {
    return 0;
  }
  if (this_player()->query_Rep() < 1) {
    write ("You have not learned how to repair weapons.\n");
    return 1;
  }
  i=ROOM+"guildroom"->query_stat_experience(this_player()->query_Rep()+1);
  write ("Repair weapon skill: "+i+" xp.\n");
  return 1;
}

query_peace() { return 1; }


