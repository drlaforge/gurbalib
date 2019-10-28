/*--- STANDARD gangroom.c  For use in all gangs. ---*/
/* Thorwald '93 */
 
#include <tune.h> /** Get the tuning values **/
 
#include <free_kill.h>
#include <skills.h>
inherit "std/room";
#include "../area.h"

#define TP this_player()
#define C capitalize
#define CON (this_player()->query_Con())
#define DEX (this_player()->query_Dex())
#define INT (this_player()->query_Int())
#define STR (this_player()->query_Str())
#define LEVEL (this_player()->query_level())
#define EXP (this_player()->query_exp())
#define TOTAL_STATS (CON+DEX+INT+STR)

int *lvl_experience;
int *tot_exps;
 
int 
query_experience(int level)
{
    int i;
    if(!lvl_experience)
    {
	lvl_experience=allocate(GEN_LEVEL);
	lvl_experience[VET_LEVEL-1]=SCIENTIST_EXPERIENCE;
	for(i=18;i>0;i--)
	    lvl_experience[i]=lvl_experience[i+1]*2/3;
	for(i=VET_LEVEL;i<GEN_LEVEL;i++)
	    lvl_experience[i]=lvl_experience[i-1]+100000;
	lvl_experience[0]=0;
    }
    if(level) level--;
    if(level>(GEN_LEVEL-1)) level=(GEN_LEVEL-1);
    return lvl_experience[level];
}

query_total_experience(int l)
{
  int i;
  l--;
  if (!tot_exps)
    {
      query_experience(0);
      tot_exps = allocate(GEN_LEVEL);
      tot_exps[0] = lvl_experience[0];
      for (i=1;i<GEN_LEVEL;i++)
	tot_exps[i] = tot_exps[i-1] + lvl_experience[i];
    }
  if (l<0) l = 0;
  if (l>(GEN_LEVEL-1)) l = (GEN_LEVEL-1);
  return tot_exps[l];
}

query_stat_experience(stat) 
{
   return (((stat*stat*stat)*STAT_COST)/2);
}

try_stat_advance(stat) 
{
    int cost;
    if(stat>MAX_STAT) 
	return !write("You have reached maximum.\n"); 
    
    cost=query_stat_experience(stat);
    if(EXP < cost) 
      return !write("You don't have enough experience.\n");
    if ((TOTAL_STATS/4>=LEVEL+3) && (LEVEL<=(GEN_LEVEL-1))) 
      return !write("You have a too high average stat already.\n");
    TP->add_exp(-cost, 1);
    return 1;
}

try_advance(exp) 
{
    int cost;
    if(TOTAL_STATS/4<=LEVEL-3)
	return !write("You have to raise your stats before"+
		      " you can raise your level.\n");
    if(EXP<exp) 
	return !write("You need "+(exp-EXP)+" more experience points to"+
		      " advance your level.\n");
    return 1;
}

advance(str) 
{
    object scroll;
    int level;
    int i; int cost;
    string blah;

    if( TP->query_guest() )
    {
	write("Sorry guests can't advance.\n");
	say("Guest trys to advance but fails.\n");
	return 1;
    }
    level=LEVEL;
    
    if(!str || str=="level")
    {
	if(level>=ROOKIE_LEVEL) 
	    return !write("Scientists can't advance here.\n");

	if(level==GEN_LEVEL)
	    return !write("You can't advance your level more.\n");
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
		TP->set_vet_new(1);
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
	    TP->add_exp(-cost, 1);
	    write(TP->short()+".\n");
	}
	TP->save_me(1);
	return 1;
    }
    switch(lowercase(str))
    {
    case "sci":
    {
        string sec,tmp;
	if(FREE_KILL)
	    return write("You cannot advance to sci during free kill.\n");
	if(level>=ROOKIE_LEVEL) 
	    return write("But you are a scientist already!\n");
	if(ROOM+"quest_room"->count(1) > 0)  /* have qp% left? */
	    return write("You have not solved enough quests for a scientist.\n");
      if( level < CAPT_LEVEL )
	    return write("You must be level "+CAPT_LEVEL+" or higher to advance to scientist.\n");
        if( ("/obj/daemons/player_info")->query_level( TP->query("app_sponsor") ) >= DIR_LEVEL )
            return write ("You need a sponsor to become a scientist!\n");
	if(TP->query_money()<WIZ_COST)
	    return write ("You need the extra $"+WIZ_COST+" to become a scientist!\n");
	TP->add_money(-WIZ_COST);
	write("WELCOME SCIENTIST!\n");
	shout("We have a new scientist!\n");
	TP->set_level(APP_LEVEL);
	TP->set_title("the Apprentice");
	if(scroll=clone_object("/doc/examples/init_scroll"))
	    move_object(scroll,TP);
	TP->save_me(1);
	if (sec = SECOND_D->check_second(lowercase(TP->query_real_name()))) {
	  writef("Your second character "+C(sec)+
		 " has been disallowed login temporarily. "+
		 "You will not be able to play this character until "+
		 "you have proven yourself worthy.");
	}
	return 1;
    }
    case "dex":
    case "dexterity":
	if(try_stat_advance(DEX+1)) 
	{
	    TP->set_dex(DEX+1);
	    write("You are now a more skillful fighter.\n");
        if(TP->query_Dex()==MAX_STAT){
           write("D E X T E R I T Y\n");
           blah=("/std/object/digital_numbers")->digital_numbers(MAX_STAT);
           write("  "+blah[0]+"\n");
           write("  "+blah[1]+"\n");
           write("  "+blah[2]+"\n\n");
        }
	}
	break;
    case "con":
    case "constitution":
	if(try_stat_advance(CON+1)) 
	{
	    TP->set_con(CON+1);
	    write("You have an improved constitution.\n");
        if(TP->query_Con()==MAX_STAT){
           write("C O N S T I T U T I O N\n");
           blah=("/std/object/digital_numbers")->digital_numbers(MAX_STAT);
           write("    "+blah[0]+"\n");
           write("    "+blah[1]+"\n");
           write("    "+blah[2]+"\n\n");
        }
	}
	break;
    case "str":
    case "strength":
	if(try_stat_advance(STR+1)) 
	{
	    TP->set_str(STR+1);
	    write("You are now stronger.\n");
        if(TP->query_Str()==MAX_STAT){
           write("S T R E N G T H\n");
           blah=("/std/object/digital_numbers")->digital_numbers(MAX_STAT);
           write(" "+blah[0]+"\n");
           write(" "+blah[1]+"\n");
           write(" "+blah[2]+"\n\n");
        }
	}
	break;
    case "int":
    case "intelligence":
	if(try_stat_advance(INT+1)) 
	{
	    TP->set_int(INT+1);
	    write("You are now wiser.\n");
        if(TP->query_Int()==MAX_STAT){
           write("I N T E L I G E N C E\n");
           blah=("/std/object/digital_numbers")->digital_numbers(MAX_STAT);
           write("    "+blah[0]+"\n");
           write("    "+blah[1]+"\n");
           write("    "+blah[2]+"\n\n");
        }
	}
	break;
    default:
	write("You can't advance that here.\n");
    }
    TP->save_me(1);
}

cost_for_level()
{
    int i;

    if(LEVEL<SCI_LEVEL)
	write("You have "+EXP+
	      " experience points to spend on stats and level.\n");
    
    if(STR>=100) 
	write ("You are as strong as you can be.\n");
    else 
	write ("Strength      :"+query_stat_experience(STR+1)+" xp.\n");
    if(INT>=100)
        write("You are as wise as you can be.\n");
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
  {
  if(4*LEVEL+12-TOTAL_STATS<=0)
    writef("Your stats are maxed out for this level.\n");
  if(4*LEVEL+12-TOTAL_STATS==1)
    writef("You have 1 more stat to raise this level.\n");
  if(4*LEVEL+12-TOTAL_STATS>1)
    writef("You have "+(4*LEVEL+12-TOTAL_STATS)+" more stats to raise this level.\n");
  }

    if(LEVEL == (ROOKIE_LEVEL-1))
     return write("You have achieved the highest level.\n");

     if(LEVEL >= (ROOKIE_LEVEL) )
	return write ("Scientists can't advance their levels so easily.\n");

    if(query_experience(LEVEL+1) < EXP)
	write("You are ready for level "+(LEVEL+1)+".\n");
    else
	write("You need "+(query_experience(LEVEL+1)-EXP)+
	      " more experience points to advance to level "+
	      (LEVEL+1)+ ".\n");
    
    if(LEVEL>=CAPT_LEVEL && ROOM+"quest_room"->count(1)<=0)
	write("You are ready to become a scientist.\n");

    return 1;
}

list_quests(i) 
{
    int l;
    if(i && sscanf(i, "%d", l)==1)
	call_other(ROOM+"quest_room","list", l);
    else
	call_other(ROOM+"quest_room","count", 0);
   return 1;
}


/*****************************************************
 * Add some functions to help players use skills     *
 * Need to calculate the cost of the skill, and      *
 * to advance skills                                 *
 *                                                   *
 *****************************************************/


query_skill_cost(string skill_value)
{
    if(skill_value < 0) return 0;

    return ((skill_value * skill_value) * SKILL_TUNE_VAL);

}
         


/* we need a function to filter the skill and see if it is acceptable *

int discard_invisible_skills(mapping _single_skill)
{
	return (_single_skill["visible"]);
}

/* following function returns 1 if skill is at it's maximum, or maximum for level */
int check_skill_max(mapping _single_skill)
{
    return ((_single_skill["value"] >= _single_skill["max_value"])
          || (_single_skill["value"] >= GUILD_SKILL_MAX) );
}

/* function to display costs of skill */

int show_cost_of_skills()
{
int sz;
mapping myskills;
string *mylist;
int i;
int myprinted;

    myskills = TP->query_all_skills();
    if (!myskills)
    {
        write("You have no skills to advance.\n");
        return 1;
    }
    myprinted = 0;
    for (i = 0, sz = sizeof(mylist); i < sz; i++)
    {
        if (TP->query_skill_visible(mylist[i]))
        {
            if (!myprinted)
            {
                write("You have "+EXP+
                " experience points to spend.\n\n");
                myprinted = 1;
            }
            if (check_skill_max(myskills[mylist[i]]))
            {
                printf("%-50s : At Maximum\n",
                      TP->query_skill_description(mylist[i])
                      );
            }
            else
            {
                printf("%-50s : %10d XP\n",
                       TP->query_skill_description(mylist[i]),
              query_skill_cost(TP->query_skill_real_value(mylist[i])));
            }
        }
    }
    if (!myprinted)
    {
        write("You have no skills to advance.\n");
    }
    return 1;
}

/* this function checks skill, and advances the skill value  */

int advance_skill(string _skill_name)
{
mapping _single_skill;
int skill_cost;

_single_skill = (TP->query_skill(_skill_name));

    /* check skill exists */

    if (!_single_skill)
    {
       write("You do not possess that skill.\n");
       return 1;        
    }        

    /* check skill is visible/advanceable */
 
    if (!TP->query_skill_visible(_skill_name))
    {
       write("You do not possess that skill.\n");
       return 1;        
    }

   /* ensure player has not overreached his/her max for skill */

    if (check_skill_max(_single_skill))
    {
        write("That skill cannot be advanced further here.\n");
        return 1;
    }

   /* ensure the player has enough experience to advance the skill */

    if (EXP < 
       query_skill_cost(TP->query_skill_real_value(_skill_name)) )
    {
        write("You do not have enough experience to advance that.\n");
        return 1;
    }

    /* here we can advance the skill, 
       it is not maxed and they have the exp */

    skill_cost = 
         query_skill_cost(TP->query_skill_real_value(_skill_name));
    TP->set_skill(_skill_name,
          (TP->query_skill_real_value(_skill_name) + 1));
    TP->add_exp(-skill_cost, 1);
     write("You have improved your skills.\n");
    TP->save_me(1);
    return 1;
}

