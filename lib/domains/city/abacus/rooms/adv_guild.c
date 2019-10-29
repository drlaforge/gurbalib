/* Modified for a little color, Cygnus (06/99) */
/* Fixed colour so it doesn't show for people with it off. Dman */
/* Removed colour in titles, bad idea. Ansi codes will show up */

inherit ROOM+"guildroom";

#include <tune.h>
 
#include <def.h>

#define CS(x,y) colour_string(x,y)

static string male_title_str,fem_title_str; /*get_new_title()*/
static object ob2, ob, board;


init() {
  ::init(); /* !important! */
  /* ----- called in ROOM+"guildroom": (Do this in your guild)----- */
    add_action("cost_for_level", "cost");
add_action("adv_advance", "raise");
    add_action("adv_advance", "advance");
    add_action("list_quests", "list");

  /* ----- called in this room: ----- */
    add_action("south", "south");
    add_action("register_second","register");
    add_action("deregister_second","dereg");
}

void setup(void) {
   
              /* if reboot: */
/*
  if (!present("box",this_object()))
    move_object(clone_object("std/object/area_voter"),this_object());
*/

  set_light (1);
  
  set_long_f(
    "You are standing in an old and dirty lecture room. Scattered around "+
    "this place are a couple of broken chairs and tables that no one has "+
    "bothered to clean up. A large unbroken window to the east lets in the "+
    "sunshine to lighten up this otherwise gloomy place. There is a large "+
    "sign on the eastern wall which explains how to raise your statistics "+
   "and/or level. A wooden staircase leads "+
    "down to the cellar. The opening in the southern wall has many lasers "+
    "criss crossing it, barring entry.\n"+
    "There is also a plaque nailed on the eastern wall.\n");
    dest_dir = ({ ROOM+"school_entr", "north",0,
		  ROOM+"adv_cellar", "down",0,
                  ROOM+"vote", "east", 0,
		  ROOM+"announce","west",0,
              ROOM+"jokesboard","up",0,
	        });
     items_arr = ({
       ({"broken chairs","broken chair","broken table","broken tables","chairs","tables"}), "They look broken and unusable.",
       "window","It is unbroken, unlike everything else in this room",
       ({"staircase","wooden staircase"}), "It is made from wood",
       ({"laser","laser beams","opening","south"}),
           "The laser beams block the way south.",
         "sign", "#show_sign",
        ({"new plaque","plaque"}),"#info",
	});
    add_readable("sign");

  /* --- book --- */
  move_object(clone_object("std/object/book"), this_object());

  /* --- voter --- */
  /* move_object(clone_object("std/object/voter"), this_object()); */

 /* --- board --- */
  board = clone_object("obj/board");
  move_object(board,  this_object());
  board -> set_save_path("boards/bulletin");
  board -> set_max_notes(60);
  board -> set_delete_level (ARCH_LEVEL-1);
  board -> set_show_levels(ROOKIE_LEVEL-1);
   board->set_archive(1);
   board->set_arch_path("boards/archive/main");
   board->set_new_level(3);
   board->set_new_fail("You're still a little too inexperienced for anyone to care what you have to say.\n");
  /* --- guild first quest --- */
  ob = clone_object("obj/quest_obj");
  ob->set_name("headcutter");
  ob->set_hint(
    "Dennis, the hooded man, is angry with the Devils because they killed\n"+
    "his family and burned down his home. Help him get revenge.\n");
  ob->set_qp(10);
  move_object(ob, ROOM+"quest_room");
  /* --- guild 2nd quest --- */
  ob2 = clone_object("obj/quest_obj");
  ob2->set_name("generosity");
  ob2->set_hint(
  "Show a little generosity around town.\n");
  ob2->set_qp(10);
  move_object(ob2, ROOM+"quest_room");
}

short() {
  return CS("The mob gang headquarters","HIBLUE");
}

adv_advance(str) 
{
  object ob;
  ob = present("gang_object",this_player());
  if(ob) 
  {
    write ("You should advance in the "+ob->query_gang()+".\n");
    return 1; 
  }
advance(str);
return 1;
}

south() 
{
  if(call_other(this_player(), "query_level", 0) < APP_LEVEL) 
  {
    write("The laser beams effectively stop you.\n");
    say(this_player()->query_name()+
	" tried to go through the laser beams, but failed.\n");
    return 1;
  }
  write(
    "As you approach the door, the lasers shut off and you walk through.\n"+
    "A mechanized voice announces: "+CS("'Welcome SPOK-member'","HIBLUE")+"\n");
    this_player()->move_player("south, to where all the greatest minds meet#room/adv_inner");
  return 1;
}

vet() 
{
  if (this_player()->query_level() >= VET_LEVEL)
    return 0;
  write("I am sorry, but that room is for veterans only.\n");
  say(this_player()->query_name()+
      " tries to enter the veterans room but fails.\n");
  return 1;
}
/* ---------- DEFINE SPECIFIC GUILD-TITLES -----------------
 * You must make this function in your guildroom and inherit
 * ROOM+"guildroom" and add_action() some functions (see this init())
 * get_new_title() should take gender,level as two arguments and
 * return the correct title. How you retrieve the title is
 * up to you. In this case we make three arrays.
 *
 *           Thorwald 920414
 */

get_new_title(gender, lvl) 
{
  if(!male_title_str) 
  {
    male_title_str = allocate(20);
    male_title_str[19]  ="apprentice veteran";
    male_title_str[18]	="the grand master slasher";
    male_title_str[17]	="the obvious winner";
    male_title_str[16]	="the dangerous streetlord";
    male_title_str[15]	="the master butcher";
    male_title_str[14]	="the licenced executioner";
    male_title_str[13]	="the silent executioner";
    male_title_str[12]	="the terrifying master of violence";
    male_title_str[11]	="the dangerous assassin";
    male_title_str[10]	="the beginner assassin";
    male_title_str[9]	="the experienced murderer";
    male_title_str[8]	="the promising murderer";
    male_title_str[7]	="the dangerous warrior";
    male_title_str[6]	="the experienced warrior";
    male_title_str[5]	="the warrior";
    male_title_str[4]	="the violent rebel";
    male_title_str[3]	="the experienced streetfighter";
    male_title_str[2]	="the promising streetfighter";
    male_title_str[1]	="the new streetfighter";
    male_title_str[0]	="the newcomer";
    
    fem_title_str = allocate(20);
    fem_title_str[19]   ="apprentice veteran";
    fem_title_str[18]	="the grand master slasherchick";
    fem_title_str[17]	="the obvious winner";
    fem_title_str[16]	="the dangerous streetchick";
    fem_title_str[15]	="the master butcher";
    fem_title_str[14]	="the licenced executioner";
    fem_title_str[13]	="the silent executioner";
    fem_title_str[12]	="the terrifying mistress of violence";
    fem_title_str[11]	="the dangerous assassin";
    fem_title_str[10]	="the beginner assassin";
    fem_title_str[9]	="the experienced murderer";
    fem_title_str[8]	="the promising murderer";
    fem_title_str[7]	="the dangerous warchick";
    fem_title_str[6]	="the experienced warchick";
    fem_title_str[5]	="the warchick";
    fem_title_str[4]	="the violent rebel";
    fem_title_str[3]	="the experienced streetfighter";
    fem_title_str[2]	="the promising streetfighter";
    fem_title_str[1]	="the new streetfighter";
    fem_title_str[0]	="the newcomer";
    
  }
  if (gender==1) return male_title_str[lvl];	/* -- male -- */
  if (gender==2) return fem_title_str[lvl];	/* -- female -- */
  return 0;    /* if failed */
}

query_peace() { return 1; }

/* Legal Seconds system - Nedo 970407  */

deregister_second(string arg)
{
  string sec,mainchar;
  if (TP->query_level()<ARCH_LEVEL) 
    return !notify_fail("Hahahahaha. You'd like that wouldn't you.\n");
  if (!arg || sscanf(arg,"%s %s",sec,mainchar)!=2) {
    return !notify_fail("Usage: "+CS("dereg","RED")+" <sec_name> <main_name>\n");
  }
  return SECOND_D->deregister_second(sec,mainchar);
}

register_second(string str) {
  object ob;
  string second,sec_pass;
  if(!str || sscanf(str,"%s %s",second,sec_pass)!=2) {
    notify_fail("Usage: "+CS("register","RED")+" <name_of_your_second_char> <password_of_your_second>\n");
    return 0;
  }

  second = lowercase(second);

  if( second == this_player()->query_real_name() ){ write("Register yourself as your own second? Wierd.\n"); return 1; }
  if(!(SECOND_D->register_second(second,sec_pass))) return;
  log_file("SECONDS",C(TP->QRN)+" ("+TP->query_level()+") registered "+
	   C(second)+" ("+find_player(second)->query_level()+
	   ") as a second character, "+ ctime(time())+".\n");
  ob = find_player(second);
  tell_object(ob,break_string(
	      "You have been registered as the secondary character to "+
	      C(TP->QRN)+". We can not allow both chars to be on "+
	      "during the same reboot. Therefore you have been forced "+
	      "to quit. We "+
	      "will be happy to see you in another reboot. Bye bye.",78,0));
  command("quit",ob);
  SECOND_D->add_entry(lowercase(TP->QRN));
  return write(CS("Ok. "+C(second)+" is now registered as your second character.","BLUE")+"\n");
}

info(string str) {
  return W(CS("Nuclearwar MUD announces that a Legal Seconds System is now\n","BLUE")
          +CS("in effect. The following rules apply:\n","BLUE")
          +"1) You must be of VET level to have a second character.\n"
          +"2) You must be of less than ROOKIE LEVEL to have a second character.\n"
          +"3) Both characters must connect from the same host while registrating.\n"
          +"4) Only ONE of the characters my be used each reboot (hardcoded).\n"
          +"5) You may register here with: "+CS("register","RED")+" <name of second char> \n"
          +"   <password_of_second_char>\n"
	  +"6) The second will be forced to quit immediately after\n"
	  +"   the registration. \n"
	  +"7) Type "+CS("'help seconds'","RED")+" for more info.\n"
          +CS("Note: Having unregistered seconds is just as illegal as before.\n","HIRED"));
}

show_sign() {
return W( CS("            Welcome to the Mob's gang headquarters!","BLUE")+"\n"+
        "This is where you come to gain statistics and levels if you are\n"+
        "not a member of a gang. If you are, then please go to your\n"+
        "gang's headquarters.\n"+
        "Commands:\n"+
        CS("    cost","HIRED")+" <to show you how much experience you have and what to spend it on.>\n"+
        CS("    advance","HIRED")+" [level, str, int, dex, con] <to raise them.>\n"+
          CS("    list","HIRED")+" (number)  <to see what the quests are.>\n");
}


