/*--- STANDARD gangroom.c  For use in all gangs. ---*/
/* Thorwald '93 */
 
#include <tune.h> /** Get the tuning values **/
 
inherit "std/room";
#include "../area.h"

#define TP this_player()
#define C capitalize
#define CON (this_player()->query_stat("con"))
#define DEX (this_player()->query_stat("dex"))
#define INT (this_player()->query_stat("int"))
#define STR (this_player()->query_stat("str"))
#define LEVEL (this_player()->query_level())
#define EXP (this_player()->query_expr())
#define TOTAL_STATS (CON+DEX+INT+STR)

int *lvl_experience;
int *tot_exps;
string **titles;

int cost_for_level(string str);
int advance(string str);


void setup(void)
{
titles = ({({"has no level", "has no level"}),
({"the newbie", "the newbie"}),
({"the student", "the student"}),
({"the student", "the student"}),
({"the student", "the student"}),
({"the student", "the student"}),
({"the student", "the student"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"}),
({"the player", "the player"})});
set_short("Standard guild room.");
set_long("Standard guild room, send a bug report if you see this message.");
add_action("cost_for_level", "cost");
add_action("advance", "advance");
}


string get_new_title(string gender, int level)
{
if (gender == "male") return titles[level][0];
if (gender == "female") return titles[level][1];
if (gender == "neuter") return titles[level][0];
}


int query_experience(int level)
{
    int i;
    if(!lvl_experience)
    {
	lvl_experience=allocate(VET_LEVEL);
	lvl_experience[VET_LEVEL-1]=SCIENTIST_EXPERIENCE;
	for(i=18;i>0;i--)
	    lvl_experience[i]=lvl_experience[i+1]*2/3;
	lvl_experience[0]=0;
    }
    if(level) level--;
    if(level>(VET_LEVEL-1)) level=(VET_LEVEL-1);
    return lvl_experience[level];
}

int query_total_experience(int l)
{
  int i;
  l--;
  if (!tot_exps)
    {
      query_experience(0);
      tot_exps = allocate(VET_LEVEL);
      tot_exps[0] = lvl_experience[0];
      for (i=1;i<VET_LEVEL;i++)
	tot_exps[i] = tot_exps[i-1] + lvl_experience[i];
    }
  if (l<0) l = 0;
  if (l>(VET_LEVEL-1)) l = (VET_LEVEL-1);
  return tot_exps[l];
}

int query_stat_experience(int stat) 
{
   return (((stat*stat*stat)*STAT_COST)/2);
}

int try_stat_advance(int stat) 
{
    int cost;
    if(stat>MAX_STAT) {
	write("You have reached maximum.\n"); 
	return 0;
    }

    cost=query_stat_experience(stat);
    if(EXP < cost) {
      write("You don't have enough experience.\n");
      return 0;
}
    /*if ((TOTAL_STATS/4>=LEVEL+3) && (LEVEL<=(GEN_LEVEL-1))) return !write("You have a too high average stat already.\n"); we don't need this right now - Exash 19.11.02 */
    if(TP->query_stat_points() == 0) {
      write ("You have no stat points.");
      return 0;
    }
    TP->decrease_expr(cost);
    return 1;
}

int try_advance(int exp) 
{
    int cost;
    if(TOTAL_STATS/4<=LEVEL-3) {
	write("You have to raise your stats before"+
		      " you can raise your level.\n");
	return 0;
}
    if(EXP<exp) {
	write("You need "+(exp-EXP)+" more experience points to"+
		      " advance your level.\n");
	return 0;
}
    return 1;
}

int advance(string str) 
{
    object scroll;
    int level;
    int i; int cost;
    string blah;

    if (empty_str(str))
    {
      write ("Advance what?");
      return 1;
    }
    if( query_guest(TP) )
    {
	write("Sorry guests can't advance.\n");
	TP->query_environment()->tell_room(TP, "Guest trys to advance but fails.\n");
	return 1;
    }
    level=LEVEL;
    
    if(str=="level")
    {
	if(level>=ROOKIE_LEVEL) 
{
	    write("Scientists can't advance here.\n");
	    return 1;
}
	if(level==VET_LEVEL)
{
	    write("You can't advance your level more.\n");
	    return 1;
}
	if(try_advance(cost = query_experience(level+1))) 
	{
	    write("Welcome to level "+(level+1)+"\n");
	    TP->set_level(level+1);
	    if(level+1<VET_LEVEL)
		TP->set_title(get_new_title(TP->query_gender(),level));
	    switch(level+1)
	    {
	    case VET_LEVEL :
		TP->set_title("the Veteran");
		/*TP->set_vet_new(1); will be implemented later */
		write("You are now a Veteran!\n");
		break;
	    case CORP_LEVEL :
		write("You are now a Veteran Corporal!\n");
		break;
	    case SERG_LEVEL :
		write("You are now a Veteran Sergeant!\n");
		break;
	    case STAFF_LEVEL :
		write("You are now a Veteran Staff Sergeant!\n");
		break;
	    case MAST_LEVEL :
		write("You are now a Veteran Master Sergeant!\n");
		break;
	    case LT_LEVEL :
		write("You are now a Veteran Lieutenant!\n");
		break;
	    case CAPT_LEVEL :
		write("You are now a Veteran Captain!\n");
		break;
	    case MAJ_LEVEL :
		write("You are now a Veteran Major!\n");
		break;
	    case COL_LEVEL :
		write("You are now a Veteran Colonel!\n");
		break;
	    case BRIGGEN_LEVEL :
		write("You are now a Veteran Brigadear General!\n");
		break;
	    case MAJGEN_LEVEL :
		write("You are now a Veteran Major General!\n");
		break;
	    case LTGEN_LEVEL :
		write("You are now a Veteran Lieutenant General!\n");
		break;
	    case GEN_LEVEL :
		write("You are now a Veteran General!\n");
	    }
	    TP->decrease_expr(cost);
	    write(TP->query_short()+".\n");
	}
	TP->save_me();
	return 1;
    }
    switch(lowercase(str))
    {
    case "dex":
    case "dexterity":
	if(try_stat_advance(DEX+1)) 
	{
	    TP->set_base_stat("dex", DEX+1);
	    TP->set_stat_points(TP->query_stat_points()-1);
	    write("You are now a more skillful fighter.\n");
        if(TP->query_Dex()==MAX_STAT){
           write("D E X T E R I T Y   M A X E D\n");
        }
	}
	break;
    case "con":
    case "constitution":
	if(try_stat_advance(CON+1)) 
	{
	    TP->set_base_stat("con", CON+1);
	    TP->set_stat_points(TP->query_stat_points()-1);
	    write("You have an improved constitution.\n");
        if(TP->query_Con()==MAX_STAT){
           write("C O N S T I T U T I O N   M A X E D\n");
        }
	}
	break;
    case "str":
    case "strength":
	if(try_stat_advance(STR+1)) 
	{
	    TP->set_base_stat("str", STR+1);
	    TP->set_stat_points(TP->query_stat_points()-1);
	    write("You are now stronger.\n");
        if(TP->query_Str()==MAX_STAT){
           write("S T R E N G T H   M A X E D\n");
        }
	}
	break;
    case "int":
    case "intelligence":
	if(try_stat_advance(INT+1)) 
	{
	    TP->set_base_stat("int", INT+1);
	    TP->set_stat_points(TP->query_stat_points()-1);
	    write("You are now wiser.\n");
        if(TP->query_Int()==MAX_STAT){
           write("I N T E L I G E N C E   M A X E D\n");
        }
	}
	break;
    default:
	write("You can't advance that here.\n");
	return 1;
    }
return 1; /*bug in lib? If returns with 0 it gets called twice - Exash 19.11.09*/
    TP->save_me();
}

int cost_for_level(string str) /*it just ignores parameter, not needed, just because of command*/
{
    int i, statpoints;
    statpoints = TP->query_stat_points();

    if(LEVEL<SCI_LEVEL)
	write("You have "+EXP+
	      " experience points to spend on stats and level.\n");
    
    if(STR>=100) 
	write ("You are as strong as you can be.\n");
    else 
	write ("Strength      :"+query_stat_experience(STR+1)+" xp.\n");
    if(INT>=100)
        write("You are as intelligent as you can be.\n");
    else
        write("Intelligence  :"+query_stat_experience(INT+1)+" xp.\n");
    if(DEX>=100) 
	write ("You are as skilled as you can be.\n");
    else 
	write ("Dexterity     :"+query_stat_experience(DEX+1)+" xp.\n");
    if(CON>=100) 
	write("You are as hard as you can be.\n");
    else
	write("Constitution  :"+query_stat_experience(CON+1)+" xp.\n");

if(LEVEL<=(GEN_LEVEL-1))
  { /*Refactoring -- don't calculate 4 times with the same formula, using new point system */
  /*Old formula was 4*level+12*/
  if(statpoints==0) 
    write("Your stats are maxed out for this level.\n");
  if(statpoints==1)
    write("You have 1 more stat to raise this level.\n");
  if(statpoints>1)
    write("You have "+statpoints+" more stats to raise this level.\n");
  }

    if(LEVEL == (VET_LEVEL)) {
     write("You have achieved the highest level.\n");
     return 0;
}

    if(query_experience(LEVEL+1) < EXP)
	write("You are ready for level "+(LEVEL+1)+".\n");
    else
	write("You need "+(query_experience(LEVEL+1)-EXP)+
	      " more experience points to advance to level "+
	      (LEVEL+1)+ ".\n");
    return 1;
}

