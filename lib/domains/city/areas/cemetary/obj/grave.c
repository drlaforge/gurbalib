init(){
	add_action("dig","dig");
	add_action("unlock","unlock");
	add_action("open","open");
	remove_call_out("bonk");
	call_out("bonk",5);
}
int digged;
short(){
if(!digged) return "a grave";
if(digged==1) return "a recently dug grave revealing a coffin";
if(digged==2) return "a recently dug up grave revealing an opened coffin";
}
id(str){
if(!digged) { if(str=="grave") return 1; else return 0; }
if(digged==1){ if(str=="blargh"||str=="coffin") return 1; else return 0; }
if(digged==2) { if(str=="coffin"||str=="opened coffin") return 1; }
}
long(){
if(!digged) { write("The ground looks very fresh. This grave is not very old.\n"); return 1; }
if(digged==1){
write("You notice a locked lock on the coffin.\n");
return 1;
}
if(digged==2){
write("The coffin is open.\n");
return 1;
}
}
dig(str){
if(!present("shovel",this_player())) { write("You need a shovel to dig.\n");
					return 1;
					}
	if(str!="grave") { write("Dig what?\n"); return 1; }
	if(!digged){
	write("You dig for a long while... You find a coffin!\n");
say(this_player()->query_name()+" digs for a while... and finds a coffin.\n");
	digged = 1;
	return 1;
	}
	write("No need to dig anymore.\n");
	return 1;
}
unlock(str){
object bye;
	if(str=="coffin"||str=="lock"){
	if(digged!=1){
			write("unlock what?\n");
			return 1;
			}
	if(!present("bloodstained key",this_player())){
		write("You dont have the right key.\n");
		return 1;
		}
	write("You unlock the coffin.\n");
        write("A man jumps from the coffin and hugs you!\n");
        write("The man says: I'm free! Now I must help the others!\n");
        writef("After reciting a quick tale of how he and his "+
	"friends were captured by evil morticians, who used them "+
	"as practice for their art, how he was imprisoned for "+
	"trying to escape, and how the others are still "+
	"trapped somewhere... he runs away!\n");
	write("(AND he says all that in one breath!)\n");
	write("You notice a crystal fall from his pocket as he leaves.\n");
	move_object(clone_object("/domains/areas/city/cemetary/obj/shard"),environment(this_object()));
	digged = 2;
	return 1;
}
}
open(str){
	if(str!="coffin") return 0;
	if(digged!=1) return 0;
	write("You must unlock the lock first.\n");
	return 1;
}
