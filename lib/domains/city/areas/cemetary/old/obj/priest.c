init(){
	add_action("kill","kill");
}
short(){
        return "a priest standing on the tombstone";
}
id(str){
	if(str=="priest") return 1;
	else return 0;
}
get(){
	return 0;
}
long(){
write(
"There is an aoura of magic surrounding this priest. He eyes you carefully\n"+
"as you walk through the clearing. He holds his hands raised, over the hole\n"+
"and mumbles sacred spells.\n");
}
kill(str){
	if(str!="priest") return 0;
write(
"The priest raise his head looking at you, or rather, through you with an\n"+
"evil grin. Then he points at you with his right hand, raising his left\n"+
"towards the sky. Suddenly the sky is lit up by a lighting that strikes the\n"+
"priest, filling him with energy as he directs the lightning onto you.\n"+
"");
write("You are slunged out of the clearing.\n");
say(this_player()->query_name()+" suddenly get struck by the lightning.\n");
move_object(this_player(),"/room/cemetary/cem6");
say(this_player()->query_name()+" comes flying into the room.\n");
return 1;
}


