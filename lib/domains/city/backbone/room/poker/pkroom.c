inherit "/std/room";
object pkd;

void setup(void){
   
   
if(!pkd)
  pkd=clone_object(ROOM+"poker/pk");
  move_object(pkd,this_object());
  set_light(1);
  set_short("a poker room");
  set_long_f("You are standing in a small smoke filled room.  "+
     "There is a small table in the corner, with room for six "+
     "people to gather around it, and a poker dealer to stand "+
     "behind, and there he is.  Take a look at him and you "+
     "might get a grasp at this fine game of cards.  There is a "+
     "plaque on the wall. "+
     "NOTE: SCI's are NOT to play against players. All transactions "+
     "are logged.");
  add_item(({"wall"}),"There is a plaque on it.");
  add_item(({"plaque","plaque on wall","plaque on the wall"}),
     "Infinitive thanks to Shalafi@Genocide, creator of this code.\n"+
    "Report any problems to One.");
  add_item(({"smoke","smoke filled room",
   "small smoke filled room","small room"}),
     "The room is filled with smoke, from many smokers most likely.");
  add_item(({"table","small table","small table in the corner",
     "poker table","small poker table"}),
     "A poker table my friend.");
  add_item(({"corner","corner of the room"}),
     "There resides a small poker table, perhaps play a game?");
  add_exit("east",ROOM+"casino");
}
query_peace(){
  return "The dealer asks you to do take fights elsewhere.\n";
}
query_escape_proof(){return 1;}
init(){
  ::init();
  add_action("woah",({"quit","east","e"}));
}
woah(){
  if(pkd->is_playing(this_player())){
  write("Not in a hand!\n");
  return 1;
  }
  return 0;
}
