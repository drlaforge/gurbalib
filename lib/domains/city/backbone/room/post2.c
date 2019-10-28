#include <def.h>
#include <tune.h>

inherit "std/room";
#include "../area.h"
string messages;
int new_mail;

void setup(void) {
   room 
   query_reset_mail();
   if (arg)	return;
   set_light(1);
   add_exit("north", ROOM+"west_square1");
   add_exit("up",ROOM+"postbox1");
   set_short("The post office");
   long_func = "long_func";
}

init() {
    if (!this_player())
	return;
    room::init();
    if(this_player()->query_listen_shout() < SCI_LEVEL)
	this_player()->listen_shout(SCI_LEVEL);
    move_object(clone_object("obj/mail_reader"), this_player());
    add_action("nope",({"lsay","say","whisper","emote"}));
    add_action("nope","'", 1);
}

exit() {
    object ob;

    if (!this_player())
	return;
    ob = present("mailread",this_player());
    if (ob)
	destruct(ob);
    this_player()->listen_shout(0);
}

nope() {
    write("Go outside the post office if you wanna talk.\n");
    return 1;
}

query_messages() {
    string name;
    string new;
 
    new_mail = messages = 0;
    name = this_player()->query_real_name();
    if (!restore_object(ROOM+"post_dir/" + name) || messages == "")
        return "You have no mail.";
    new = "";
    if (new_mail)
        new = " NEW";
    return "There is" + new +" mail for you in the Abacus post office.";
    return 1;
}

query_mail(silent) {
    string name;
    string new;

    new_mail = messages = 0;
    name = this_player()->query_real_name();
    if (!restore_object(ROOM+"post_dir/" + name) || messages == "") return 0;
    if (silent) return 1;
    new = "";
    if (new_mail)
        new = " NEW";
    write("\nThere is" + new + " mail for you in the Abacus Post Office\n"+
          "located (south, east, east, south) from the Cryogenic Facility.\n\n");
    return 1;
}

query_reset_mail(){
   int x;
   object who;
   who=users();
   for(x=0;x<sizeof(who);x++){
      if(query_new_mail(who[x]->QRN)){
         tell_object(who[x],colour_string("There is new mail for you in the Abacus Post Office.\n","CYAN"));
      }
   }
}

query_new_mail (name) {
    new_mail = messages = 0;
    if (!name) return 0;
    if (!restore_object(ROOM+"post_dir/" + name) || messages == "") return 0;
    if (new_mail) return 1;
    return 0;
}

long_func ()
{
    write(" -----------------------------------\n"+
	  "     Abacus Central Post Office     \n"+
	  " -----------------------------------\n"+
	  "You stand in the post office.\n"+
	  "You can:\n"+
	  " read          Read from the mailbox.\n" +
          " read <name>   Read your alt character mail, supply their name to read the mail.\n" + 
	  " mail <name>   Mail to player 'name'.\n" +
	  " from          Quick printout of your mail.\n");
    if (this_player()->query_level() >= SCI_LEVEL)
	write("As a scientist you can save them under your directory "+
		  "with the 's' option.\n");
}

enter_func(ob) {
    return 1;
}

exit_func(ob) 
{
}
 
query_peace() { return 1; }
query_snoop_protected() { return 1; }


