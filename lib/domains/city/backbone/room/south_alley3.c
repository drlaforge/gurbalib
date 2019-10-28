/* Wishbone Dec04 - beggar changes */

#include ROOM+".h"

string chat_str, a_chat_str, func, type, match;
object beg, stick, robe;
int cloakie;

setup() 
{
  cloakie = 0;
  set_outdoors(1);
  
  if(!beg) 
   {
    beg = clone_object("/std/monster");
    call_other(beg, "set_name", "beggar");
    call_other(beg, "set_level", 8);
    call_other(beg, "set_short", "a blind beggar");
    call_other(beg, "set_long", "The beggar has a long robe, covering his eyes.\n"+
		  "He is down on his luck and in desperate need of some money.\n");
    move_object(beg,this_object());
  
    if (!func) 
      {
	func = allocate(1);
	type = allocate(1);
	match = allocate(1);
	func[0] = "give_beggar";
	type[0] = "gives";
      }

    call_other(beg, "set_match", this_object(), func, type, match);
	if (!chat_str) 
          {
	    chat_str = allocate(3);
	    chat_str[0] =
		"Beggar says: Please, give some money!\n";
	    chat_str[1] =
		"Beggar says: I just need a little money...\n";
	    chat_str[2] =
		"Beggar says: Can't you help me?\n";
	  }
	if (!a_chat_str) 
          {
	    a_chat_str = allocate(1);
	    a_chat_str[0] = "Beggar says: Please leave me alone!\n";
	  }
	call_other(beg, "load_chat", 1, chat_str);
	call_other(beg, "load_a_chat", 20, a_chat_str);
      }
    items_arr = ({
         ({"alley","dark alley"}),"The alley is very dark",
	 "bar","The bar is to the west",
	});

      dest_dir = ({
      ROOM+"south_alley4","south",
      ROOM+"south_alley2","north",
      ROOM+"bar","west"});
      set_short("a dark and narrow alley");
      set_long(
    "This is a shabby, dark alley that continues north and south. There is a "+
"run down bar to the west, but you cannot tell whether it is open or not.");
}

give_beggar(str) {
    int money;
    string who;
    object weapon;

    say("Beggar says: Thank you so much.\n");
    if (sscanf(str, "%s gives you %d dollars.", who, money) != 2)
	return;
    
    if (call_other(beg, "query_money") >= 1000 &&
	    environment(beg) == this_object() && !cloakie) {

        say("Beggar says: You are so kind. I must repay you!\n");
        say("The beggar pulls off his dark glasses and throws them towards you.\n");
       
        robe = clone_object("std/object/mark2");
        move_object(robe, this_object());
        cloakie = 1;
    }
}

init()
{
  ::init();
  add_action("time","west");
}

time()
{
 if("/obj/daemons/timed"->query_hour() < 12)
  {
   writef("Backside Bar is closed - opening hours are from midday to midnight.\n");
   return 1;
  }
 return 0;
}
