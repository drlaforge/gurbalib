init(){
}
short(){
        return "a bloodstained key";
}
id(str){
	if(str=="key"||str=="bloodstained key"||str=="key") return 1;
	else return 0;
}
long(){
	write("A small key covered with blood.\n");
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
