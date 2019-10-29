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
say(this_player()->query_name()+" unlocks the coffin.\n");
        write("Someone jumps up from the coffin. You realize it is Cliff!\n");
	write("Cliff says: Thanks!! How can I ever repay you?\n");
say("Someone jumps up from the coffin.\n");
	write("Cliff hugs you.\n");
	write("Cliff runs into the house. He returns stright afterwards.\n");
	write("Cliff says: Take this money! It's all I got!\n");
	write("Cliff gives you 346 dollars.\n");
say("Someone gives "+this_player()->query_name()+" some money.\n");
	this_player()->add_money(346);
	write("Cliff runs happily in the house again.\n");
	digged = 2;
bye = present("bloodstained key",this_player());
destruct(bye);
this_player()->set_quest("cemetary");
	return 1;
}
}
open(str){
	if(str!="coffin") return 0;
	if(digged!=1) return 0;
	write("You must unlock the lock first.\n");
	return 1;
}
bonk(){
object ob;
int a;
	if(!digged){
	tell_room("/room/cemetary/houseyard","You hear damp bonks from the grave.\n");
	}
	if(digged==1){
	a = random(3);
	if(a==0)
	tell_room("/room/cemetary/houseyard","You hear a damp voice from the coffin screaming: Help!! I am buried alive!!\n");
	if(a==1)
	tell_room("/room/cemetary/houseyard","You hear a damp voice from the coffin screaming: The demon locked me in here!\n");
	if(a==2)
	tell_room("/room/cemetary/houseyard","You hear someone pounding on the coffinlid from inside.\n");
	}
	if(digged==2){
	return 1;
	}
ob = first_inventory(environment(this_object()));
while(ob){
if(living(ob)){ call_out("bonk",10); return 1; }
ob = next_inventory(ob);
}
}


