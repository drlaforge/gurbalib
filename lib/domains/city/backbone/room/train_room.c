/* The train destination-files should be moved to this room */

object ob;
short () { return "In the train destinations room"; }

long () {
  write ("You stand in the train-destinations room.\nIf you want a "+
         "station in your area,\nYou should move an object in here.\n"+
         "This room works like the quest_room.\n");
}

reset (arg) {
object ob;
  
     
   set_light(1);
   ob = clone_object ("obj/train_object");  /* central station */
   ob->set_short ("Central Station");
   ob->set_dest (ROOM+"central_under2");
   move_object (ob,ROOM+"train_room");
  
   call_out ("place_trains",50);
}

/* place_trains .. We must wait until all
 * stations have been placed before starting
 * the trains!
 */
place_trains () {
   ob = clone_object ("obj/the_train");
   ob->set_percentage(0);
   ob = clone_object ("obj/the_train");
   ob->set_percentage(20);
   ob=clone_object ("obj/the_train");
   ob->set_percentage(40);
   ob=clone_object ("obj/the_train");
   ob->set_percentage(60);
   ob=clone_object ("obj/the_train");
   ob->set_percentage(80);
}

stations () {
object inv;
   write ("The SubWay Circular Schedule:\n");
   write ("\n");
   inv=first_inventory(this_object());
   while (inv) {
      if (inv->query_dest() && inv->short()) {
         write (capitalize(inv->short())+".\n");
         write ("    ||\n    \\/\n");
      }
      inv=next_inventory(inv);
   }
}
