#ifndef TUNE_H
#define TUNE_H

/*
 * This file is used to tune the game
 * The game should be "easy" in the beginning, because there are not
 * enough monsters and puzzles.
 * When wizards start to create new rooms, an inflation will be noted
 * (it is easier to become wizard).
 */

/*
 * From what level you are a special rang. Used in who/finger etc.
 */ 
#define HIGH_ARCH_LEVEL         99
#define LOW_ARCH_LEVEL          98
#define DIR_LEVEL               95
#define ARCH_LEVEL              90
#define RET_LEVEL               89
#define GOV_LEVEL2              88
#define GOV_LEVEL		87
#define SPONSOR_LEVEL           86
#if 0
#define SCI_LEVEL4              85
#endif
#define SCI_LEVEL3              83
#define SCI_LEVEL4              84
#define SCI_LEVEL5              85
#define SCI_LEVEL               83
#define APP_LEVEL               82
#define ROOKIE_LEVEL            81
#define GEN_LEVEL               80
#define LTGEN_LEVEL             75
#define MAJGEN_LEVEL            70
#define BRIGGEN_LEVEL           65
#define COL_LEVEL               60
#define MAJ_LEVEL               55
#define CAPT_LEVEL              50
#define LT_LEVEL                45
#define MAST_LEVEL              40
#define STAFF_LEVEL             35
#define SERG_LEVEL              30
#define CORP_LEVEL              25
#define VET_LEVEL               20
#define NEWBIE_LEVEL		6


/*
 * This value is used to tune the cost to advance a stat in a player.
 */

#define STAT_COST 16
#define MAX_STAT 100
#define MAX_ADV_STAT 110

/*
 *
 * If you change this value, remove adv_guild.i (if you have it), so that
 * the new value will be used at restart of the game.
 *
 * EXP_COST: How many experience points you get for 100 gold coins in
 * avdenturers guild.
 *	200: For an easy start.
 *	100: Normal.
 *	50:  Extremly inflated game.
 *
 * Big LPmuds usually have several guilds made by other wizards. It is
 * very important that they call query_cost() in adv_guild.c to determine
 * what the cost is to advance a player. All guilds should have the same
 * cost for advancing.
 */
# define EXP_COST	60

/*
 * Define the level limits here. The players level-limits
 * will automatically be calculated from the limit to make
 * scientist.
 */
#define SCIENTIST_EXPERIENCE   500000
#define VETERAN_EXPERIENCE     2000000
#define LEGEND_EXPERIENCE      5000000

/* WIZ_COST is the cost in money when a player
 * advance to scientist
 */
#define WIZ_COST        1000000

/* OL_RANGE determines the legal range for outlaws.
   Plus or minus OL_RANGE is considered a within
   legal range.
 *  used from /obj/player 
 */
#define OL_RANGE       5

/* QUESTS_PERCENTAGE is how many percent quest points that must be collected
 *  used from /room/quest_room 
 */
#define QUESTS_PERCENTAGE	67

/*
 * File where the sponsored sci's are logged.
 */
#define SPONSORED	"/etc/sponsored"

/*
 * When does this mud reboot?
  see shut.h
 */


/* Use MUD Time? */
#define USE_NTIME

/* NTIME RATE */
#define NTIME_RATE 4
#define BASE_AGE 25


/* the max_int allowed on the mud */
#define MAX_DRIVER_INT 2147483647

#endif /** TUNE_H **/

