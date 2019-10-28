string kort,color;
int numbers;
short() {
   return kort;
}
long() {
   write (short()+".\n");
}
reset (arg) {
    
   numbers=0;
   kort = "An unvalid roulette token";
}
 
id(str) {
     return str == "token" || str == color || str == "roulettetoken" || str == "tokens";
}
 
query_weight() { return 0; }
get() { return 1; }
drop() { return 1; }
query_value() { return 0; }
 
set_color (str2) {
   color=str2;
   if (numbers==1) {
   kort = "A "+color+" roulette token";
   } else {
      kort = numbers+" "+color+" roulette tokens";
   }
   return color;
}
query_color () {
   return color;
}
add_tokens (str) {
   numbers=numbers+str;
}
query_tokens () {
   return numbers;
}
