inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;
#define DIR "/domains/2.4.5"

void setup() {
   object obj;

   set_name("frog");
   add_adj("cute");
   set_in_room_desc("A cute little frog");
   set_long("It looks a little slimey.");
   set_race("frog");
   set_max_hp(50);
   set_level(2);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/crown");
   obj->setup();
   obj->move(this_object());
   do_wear(obj);
}
