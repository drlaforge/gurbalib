inherit "std/room";
#include "../area.h"

void setup(void) {
     
    set_light(1);
    short_desc = "an old stockroom";
    set_long_f("You stand in a converted stockroom. This was once the proud "+
        "storage facility of the hypermarket, but now is rarely used "+
        "and is currently completely empty.\n");
    add_exit("east", ROOM+"shop");
    items_arr = ({
        "converted stockroom","A small stockroom",
        "stockroom","A small stockroom",
        "port","A port in the wall that is used to dispense equipment.",
        "wall",
"The wall is plain, with the exception of a small port used to dispense\n"+
"equipment. There currently is nothing you can get from here",
    });
}
