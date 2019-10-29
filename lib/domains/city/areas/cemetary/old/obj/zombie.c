inherit "obj/monster";
reset(arg){
  ::reset(arg);
    if(arg) return;
    set_alt_name("zombie");
  }
second_life(){
  ::second_life();
  say("The corpse of "+query_name()+" rottens instantly.\n");
  destruct(present("corpse of "+query_name(),this_object()));
}
