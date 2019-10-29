inherit "/std/weapon";
void setup(void){
         
        if(arg)return;
        set_hit_func(this_object());
        set_name("handbag");
        set_alt_name("handbag");
        set_alias("bag");
        set_wc(5);
        set_weight(2);
        set_short("Handbag");
        set_long("A womans handbag.\n"+
                "You may be able to wield it.\n");
        set_value(50+random(100));
}

