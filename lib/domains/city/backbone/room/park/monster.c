inherit "std/monster";
void setup(void){
    
   if(arg)return;
   set_level(20);
   set_race("mutant");
   set_name("water mutant");
   set_gender(0);
   set_aggressive(1);     
   set_alias("mutant");
   set_short("water mutant");
   set_long("The water mutant lives in the water. This one is an adult and\n"+
      "looks quite fearsome.\n"); 
}
