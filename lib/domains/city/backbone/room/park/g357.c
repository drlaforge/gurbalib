inherit "/obj/shootweapon.c";

void setup(void){
     
     set_name("magnum");
     set_alias("gun");
     set_short(".357-Magnum");
     set_long_f(
"This is a mother of a fucker MAGNUM. It will blow your whole head off in\n"+
"one shot. If people see you carring it they know to respect you and not to\n"+
"mess with you.\n"+"This gun handles like a baby\n");
    set_gun_type("handgun");
    set_bweight(20);
    set_burst(0);
    set_automatic(0);
    set_mag(6);
    set_ammo(6);                
    set_velocity(450);               
    set_calibre("900");          
    set_weight(3);
    set_wc(4);
    set_value(1250);
    set_two_handed(1);
    set_shooter_msg("*BA-DOOM*  I guess they weren't so lucky after all.\n");
    set_shooting_msg("says, 'You feel lucky, punk?' as the .357-Magnum blasts away!\n");
    set_victim_msg("says, 'You feel lucky, punk?' as the .357-Magnum takes off your head.\n");
    set_missmess1("I guess they were lucky after all.\n");
    set_missmess2("isn't very lucky after all.\n");
   }
