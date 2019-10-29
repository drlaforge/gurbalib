init(){
}
short(){
        return "a blood red crystal";
}
id(str){
	if(str=="crystal"||str=="red crystal"||str=="blood red crystal") return 1;
	else return 0;
}
long(){
	write("A blood red crystal, pointy at one end.\n");
	return 1;
}
get(){
	return 1;
}
query_value(){
	return 50;
}
query_weight(){
	return 1;
}
