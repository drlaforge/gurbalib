string path;
set_name(str){ path = str; }
short(){ return "a small pole"; }
long(){
if(!path) path = ""; 
  if(!cat(path)){ 
  write("The message on the pole is gone.\n"); 
  return 1; 
}
write("\n");
}
id(str){ if(str=="pole"||str=="small pole") return 1; }

init(){
add_action("read","read");
}
read(str){
  if(!id(str)) return 0;
  long();
  return 1;
}
