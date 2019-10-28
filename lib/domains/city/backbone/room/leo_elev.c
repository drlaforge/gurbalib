inherit ROOM+"elevator";

reset (arg)
{
   
   
  dests = ({
            ROOM+"leo_room",
	    ROOM+"adv_inner",
           });
    set_enter ("down");
    set_hide (1);
    set_length (7);
    set_speed (3);
    set_start (2);
}
