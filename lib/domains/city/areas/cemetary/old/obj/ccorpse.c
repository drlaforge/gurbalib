init(){
}
short(){
        return "corpse of a white cat";
}
id(str){
	if(str=="corpse"||str=="corpse of a white cat") return 1;
	else return 0;
}
long(){
write(
"It's a corpse of a cat. It looks quite fresh. The poor kitten has\n"+
"obviously been hit by a vehicle of some kind.\n");
}
get(){
	return 1;
}
query_value(){
	return 4;
}
query_wieght(){
	return 1;
}
