inherit "/std/room"

short() {
    return "The void";
}

long() {
    write(short() + ".\n");
    write("-----------------------------------------------------------------"+
	  "--------------\n");
    writef("The void is that which stands in the middle of 'this' and 'that'"+
	   ". The void is all-inclusive, having no opposite - There is " +
	   "nothing it excludes or opposes. It is a living void, because no "+
	   "forms come out of it and whoever realizes the void is filled "+
	   "with life and power and the love of all things 	"+
	   "     /Bruce Lee\n", 79, 0);
    write("-----------------------------------------------------------------"+
	  "--------------\n");
    write("You come to the void if you fall out of a room and have nowhere to go.\n");
   write("Give the command 'cryo', and you will return to the cryogenic facility.\n");
}

filter_me(){
int i;
object *obs;

obs = all_inventory(this_object());
for(i=0; i<sizeof(obs); i++)
if(!userp(obs[i]))
{
destruct(obs[i]);
}
}

init() {
  filter_me();
    add_action("church", "cryo");
}

church() {
    call_other(this_player(), "move_player", "away#room/church");
    return 1;
}

void setup(void)
{
 
    if (arg)
	return;
    set_light(1);
}

id(str) { return str == "void"; }
