/*  This file includes some handy defines. Include it if you want to use them. 
 *  xxx: delete most of these someday
*/
#ifndef ___DEF___

#define ___DEF___
#define TP this_player()
#define TO this_object()
#define QN query_name()
#define QPO query_possessive()
#define QPR query_pronoun()
#define QO query_objective()
#define QRN query_real_name()
#define QL query_level()
#define QS query_str()
#define QD query_dex()
#define QC query_con()
#define QI query_int()
#define QA query_attack()
#define W write
#define WF writef
#define S say
#define C capitalize
#define D destruct
#define ENV environment
#define FN(x)      file_name(x)
#define T ctime(time())



#define STD_ROOM	"/std/room"
#define USTD_ROOM       "/domains/underworld/standard/room.c"
#define STD_SHOP	"/std/shop.c"
#define STD_POST	"/std/post.c"
#define STD_REST        "/std/restaurant.c"

#define STD_WEAPON	"/std/weapon"
#define STD_SHOOT       "/std/shootweapon.c"
#define STD_ARMOUR	"/std/armor.c"
#define STD_OBJ	        "/std/object.c"
#define STD_AUTO        "/std/auto_load.c"

#define STD_AMMO	"/std/ammobox.c"
#define STD_NEW_AMMO	"/std/new_ammobox.c"

#define STD_FOOD	"/std/food.c"
#define STD_SOFT	"/std/soft_drink.c"
#define STD_ALCO	"/std/drink.c"
#define STD_DRUG        "/std/drug.c"

#define STD_MONSTER	"/std/monster.c"
#define STD_M_MONSTER	"/std/mean_monster.c"
#define STD_C_MONSTER	"/std/slowchat_monster.c"
#define STD_W_MONSTER	"/std/walkingmonster.c"
#define STD_S_MONSTER	"/std/smartmonster.c"
#define STD_SELL_MONSTER  "/std/shop_monster.c"
#define STD_SIGN	 "/std/sign"

/*corpses*/
#define STD_CORPSE       "/std/corpse/corpse.c"
#define METAL_CORPSE    "/std/corpse/metal.c"

/* vator */
#define STD_VATOR        "/std/elevator.c"
#define PANEL         "/std/vatorpanel.c"

#endif

