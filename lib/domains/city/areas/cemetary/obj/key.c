init(){
}
short(){
        return "a small iron key";
}
id(str){
	if(str=="small iron key"||str=="iron key"||str=="key") return 1;
	else return 0;
}
long(){
	write("A small iron key.\n");
	return 1;
}
get(){
	return 1;
}
query_value(){
	return 25;
}
query_weight(){
	return 1;
}
