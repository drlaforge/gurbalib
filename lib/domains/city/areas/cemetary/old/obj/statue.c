init(){
	add_action("meditate","meditate");
}
int medi;
meditate(){
if(this_player()->query_level() > 2){ write("Nothing happens.\n"); return 1; }
	if(medi > 2){ write("Nothing happens.\n"); return 1; }
write("You sit down on the ground and focus your eyes on the statue.\n");
write("You feel your strength increase.\n");
say(this_player()->query_name()+" sits down on the ground.\n");
this_player()->heal_self((this_player()->query_max_hp()-this_player()->query_hp())*3/4);
medi++;
return 1;
}
short(){
        return "a buddha statue";
}
id(str){ if(str=="statue"||str=="buddha statue") return 1; }
long(){ write("Its a statue of buddha.\n"); return 1; }
query_weight(){ return 1; }
query_value(){ return 40; }
get(){ return 1; }
