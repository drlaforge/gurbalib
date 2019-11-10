#include "../area.h"
inherit "/std/sign";

private string get_sign_text(void){
	return "--------------------------\n"
           +"|   Muncher Industries   |\n"
           +"| New World Headquarters |\n"
           +"|     Opening Soon!!!    |\n"
           +"|         ----           |\n"
           +"|   Construction  Area   |\n"
           +"|   Hardhats  Required   |\n"
           +"--------------------------\n";
}

void setup(void){

	set_short("--sign--");
	set_message(get_sign_text());
	set_long("It's a business sign. Perhaps you should read it.");
}