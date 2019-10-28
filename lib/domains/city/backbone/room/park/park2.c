inherit "std/room";
#include "../../area.h"
object wimp;
object bully;

void setup(void){
   
    
   add_object(ROOM+"park/wimp");
   add_object(ROOM+"park/bully");
  set_light(1);
  set_outdoors(1);
  set_short("Nuclear Winter Park");
  set_long_f(
"The ground is all trampled, with much blood lying around "+
"There is one dead body already on the ground in a state of "+ 
"decomposition. Various mutated animals best described as rats "+
"are scurrying in and out of this corner of the park. "+
"This place looks very threatening.");


   add_exit("south",ROOM+"park/park3");
   add_exit("east",ROOM+"park/park1");

   add_item(({"ground","trampled ground"}),"The ground is all trampled, covered with blood and a dead body");
   add_item("nuclear winter park","You're stood in the park");
   add_item(({"blood","drop","drops","drop of blood","drops of blood"}),"Drops of blood from a previous fight");
   add_item("corner","This is the corner of the park");
   add_item(({"dead body","body","decomposing dead body","decomposing body"}),"A decomposing body");
   add_item(({"mutated animals","mutated animal","animal","rat","mutated rat","mutated rats","animals","rats"}),"These mutated animals are dashing about consuming the dead body that got\n"+"wasted");
   add_item("park","A threating area of the park");

}

init(){
  ::init();
if(present("wimp",this_object()) && present("bully",this_object()) && present(this_player(),this_object())){
    call_out("fight_here1",15);
}
   }

fight_here1(){
if(present("wimp",this_object()) && present("bully",this_object()) && present(this_player(),this_object())){
    tell_object(this_player(),"Bully says: Just give me your money wimp.\n");
    call_out("fight_here2",8);
    return;
}
}

fight_here2(){
if(present("wimp",this_object()) && present("bully",this_object()) && present(this_player(),this_object())){
    tell_object(this_player(),"Wimp replys: n nnnn no.\n");
    call_out("fight_here3",6);
    return;
}

}

fight_here3(){
if(present("wimp",this_object()) && present("bully",this_object()) && present(this_player(),this_object())){
    tell_object(this_player(),"Bully shouts: Just give me the money.\n"+
          "Wimp cries: Leave me alone.\n"+
          "Wimp says: I dont have any money.\n");
    call_out("fight_here4",9);
    return;
}
}

fight_here4(){
if(present("wimp",this_object()) && present("bully",this_object()) && present(this_player(),this_object())){
    tell_object(this_player(),"Bully says: Give me your coat then.\n"+
          "Wimp says: Its mine!\n"+
           "'Give me your coat now' screams the Bully\n");
    call_out("fight_here5",10);
    return;
}
}

fight_here5(){
if(present("wimp",this_object()) && present("bully",this_object()) && present(this_player(),this_object())){
    tell_object(this_player(),"Wimp says: Its all I have.\n"+
        "Bully says: I am going to kill you if you dont give me your coat.\n"+
           "Wimp stutters: I dont want to die.\n"+
           "The bully cocks his gun.\n");
    call_out("fight_here1",100);
    return;
}
}

