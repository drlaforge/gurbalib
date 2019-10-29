inherit "std/room";
#include "../area.h"

object worker, boots;
string chat;

void setup(void) {

  if(!worker) {
    if(!chat) {
      chat = allocate(3);
      chat[0] = "The worker gives up a very deep sigh.\n";
      chat[1] = "The worker says: Why? Why can't we find some oil?!\n";
      chat[2] = "The worker starts to kick the sand on the ground.\n";
    }
    worker = clone_object("/std/monster");
    move_object(worker,this_object());
    worker->set_name("an oilfield worker");
    worker->set_alt_name("oilfield worker");
    worker->set_alias("worker");
    worker->set_short("an oilfield worker");
    worker->set_long_f("The worker looks busy trying to find oil. "+
        "You notice that his clothes are rather clean. "+
        "Maybe that's because they haven't found much oil here.\n");
    worker->set_level(5);
    worker->set_aggressive(0);
    worker->load_chat(15,chat);
    boots = clone_object("/std/armor");
    boots->set_name("rubber boots");
    boots->set_alias("boots");
    boots->set_short("a pair of rubber boots");
    boots->set_plural_short("pairs of rubber boots");
    boots->set_type("boot");
    boots->set_ac(5);
    boots->set_weight(1);
    boots->set_value(45);
    move_object(boots,worker);
    command("wear boots",worker);
  }

   
   
  set_light(1);
  set_outdoors(1);
  short_desc = "large desolate wasteland by an oil rig";
  set_long_f(
	"This is the northeastern corner of a large desolate wasteland. "+
	"There are high cliff walls to the north and east. Only a few scraggly "+
	"weeds grow in the dry, rocky soil. Completely out of place in this "+
	"landscape, an oil rig sits here rising above you.\n");
  dest_dir = ({
	ROOM+"waste/land33","south",
	ROOM+"waste/land42","west",
       });
  items_arr = ({
	"corner","You are at the northeastern corner of the wasteland",
	({"wasteland","large wasteland","desolate wasteland","large desolate wasteland"}),
	"Yes, that's where you are",
	({"wall","walls","cliff","cliffs"}),"The cliff walls are to the south",
	({"rig","oil rig"}),"It's a rig with which they pump up oil",
    	({"weeds","weed","scraggly weeds","dry weeds",}),
    	"Dry weeds, failing in their vain attempt to grow in the rocky soil",
    	({"soil","ground","rocky soil","dry soil",}),
    	"The soil is dry and full of rocks",
    	({"rock","rocks"}),
    	"There are rocks of all sizes laying all around",
       });
 }
