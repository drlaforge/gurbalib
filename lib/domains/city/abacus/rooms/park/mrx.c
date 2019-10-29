/*  -*- LPC -*-  */
/* Mugg ( December 1993 part of the new backbone ) */

inherit "obj/mean_monster";

object ob;
mapping mymap  = (["lsd": ({"obj/drugs/lsd",43}),
      "crack": ({"obj/drugs/crack",70}),
      "ice": ({"obj/drugs/ice",80}),
      "adrenalin": ({"obj/drugs/adrenalin",155}),]);
void setup(void){
   mean_monster 
    
   set_name("Mr X");
   set_alt_name("mrx");
   set_alias(({"mr x", "x", "mr", "Mr",}));
   set_short("Mr X");
   set_long ("Clad in a long dark overcoat, Mr X glances furtively about\n"+
      "him. Drugs are his business, and his business is drugs. If\n"+
      "you need dope, he can supply it:\n"+
      "\n"+
      "lsd       43 dollars\n"+
      "crack     70 dollars\n"+
      "ice       80 dollars\n"+
      "adrenalin 155 dollars\n\n");                   
   set_level(28);
   add_money(random(200));
   add_object("/std/object/overcoat", 1, "wear overcoat");
   load_chat (10, ({"Mr X looks around.\n",
            "Mr X says: lsd?\n",
            "Mr X says: crack?\n",
            "Mr X says: ice? \n",
            "Mr X says: adrenalin?\n",
            "Mr X says: looking for a high?\n",  
             }));
   load_a_chat (10, ({"Mr X says: You're dead! you insignificant little shit.\n",
            "Mr X says: Get out of my face! Ass wipe.\n",
             }));
   set_kill_shout("#N has just been Xecuted");
   
}

monster_died(){
int i, x;
for(i=0; i<random(3); i++)
{
if( i == 1 ){ write("Some drugs fall out of Mr X's overcoat as he falls to the ground, dead.\n"); }
x = random( m_sizeof(mymap) );
move_object( clone_object( mymap[m_indices(mymap)[x]][0] ), environment(this_object()) );
}
}

void init(){ ::init(); add_action("buy", "buy"); }

buy(str) {
   if( query_attack() )
      {
      notify_fail("Mr X shouts: I'm a little busy!!\n");
      return 0;
   }
   if(!mymap[str]) {
      notify_fail("Mr X says: I don't deal that stuff!\n");
      return 0;
   }
   else 
      if(this_player()->query_money() < mymap[str][1]) {
      notify_fail("Mr X says: hey shitface you don't have the collateral!\n");
      return 0;
   }
   else
      if(mymap[str] != 0){
      if(move_object(ob=clone_object(mymap[str][0]),this_player())){
         notify_fail("Mr X says: You can't carry anymore fool!\n");
         destruct(ob);
         return 0;
         }
      write("You give Mr X "+mymap[str][1]+" dollars, nervously watching as he\n"+
         "counts the notes. A sly grin appears on his face\n"+
         "as he hands you the goods, and bids you good day.\n");
      this_player()->add_money(-mymap[str][1]);
      return 1;
   }
}
