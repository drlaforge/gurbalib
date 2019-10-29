/* Wishbone Dec04 - updating mutant */

inherit "/std/room";
#include "../area.h"
object beggar, weapon, mark;
int booties;

/*
 * Make these arrays global, so they only have to be initialized once.
 */
mixed chat_str, a_chat_str, func, type, match;

void setup() {
    /*set_outdoors(1); */
    booties = 0;
/*will port it later - Exash
    if (!beggar) {
	beggar = clone_object("/domains/required/monsters/monster");
	call_other(beggar, "set_name", "mutant");
	call_other(beggar, "set_level", 3);
	call_other(beggar, "set_al", 200);
	call_other(beggar, "set_race", "mutant");
        call_other(beggar, "set_short", "A horrible looking mutant");
	call_other(beggar, "set_long",
                   "A horrible looking mutant, begging for money.\n");
	call_other(beggar, "set_hp", 30);
	move_object(beggar, this_object());
	if (!func) {
	    func = allocate(1);
	    type = allocate(1);
	    match = allocate(1);
	    func[0] = "give_beggar";
	    type[0] = "gives";
	}
	call_other(beggar, "set_match", this_object(), func, type, match);
	if (!chat_str) {
	    chat_str = allocate(3);
	    chat_str[0] =
		"Mutant says: Please, give money to a poor mutant!\n";
	    chat_str[1] =
		"Mutant says: Why can't I find any money ?\n";
	    chat_str[2] =
		"Mutant says: two dollars please !\n";
	}
	if (!a_chat_str) {
	    a_chat_str = allocate(1);
	    a_chat_str[0] = "Mutant says: Why do you do this to me ?\n";
	}
	call_other(beggar, "load_chat", 1, chat_str);
	call_other(beggar, "load_a_chat", 20, a_chat_str);
    }
*the new lib supports more modern solution for this -- will fix later
*/
    add_item("central square","square","It is to the south");
         add_item("pub","The pub looks open and inviting");
         add_item("eve street","street","Yes, this is Eve street");
     add_item("lights","flashing lights","casino","Could be a casino or something, better go take a look");
     add_item("smell","bacon","It definitely smells like bacon");

      set_exits((["south" : ROOMS+"west_square1",
	          "west" : ROOMS+"pub",
              "north" : ROOMS+"eve_street1"]));
	 set_short("Dark alley");
	 set_long("You stand at the end of Eve Street. The western side of Central Square\nis just to the south. There is a pub to the west. To the north you can\nmake out flashing lights and a faint smell of bacon.");
}

/* will be in-game after beggar is working
give_beggar(string str) {
    int money;
    string who;

    say("Mutant says: Thank you.\n");
    if (sscanf(str, "%s gives you %d dollars.", who, money) != 2)
	return;
    
    if (call_other(beggar, "query_money") >= 20 &&
	    environment(beggar) == this_object()) {
	call_other(beggar, "init_command", "west");

	call_other(beggar, "init_command", "buy beer");
	call_other (beggar, "init_command", "buy beer");
	call_other(beggar, "init_command", "east");
	call_other(beggar, "init_command", "drink beer");
    }

    if (call_other(beggar, "query_money") >= 1000 &&
	    environment(beggar) == this_object() && !booties) {

        say("Mutant says: You are so generous... Please take these!\n");
        say("The mutant pulls off his boots and throws them towards you.\n");

        weapon = clone_object("std/object/mark1");
        move_object(weapon, this_object());
        booties = 1;

    }

}
*/

