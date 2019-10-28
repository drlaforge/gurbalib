
#include "local.h"

inherit STD_OBJ;

static int *vals;

void setup(){
    
    
   set_name("ticket");
   set_id("lottery ticket");
   set_weight(1);
   set_short("lottery ticket");
}

void long(){
int i;
   ::long();
   if(!vals){ destruct(this_object()); }
   else {
      writef("A simple piece of paper - which could be worth a lot of money! It is your ticket to the Abacus Lottery, the "+
         "lottery is drawn every Monday. Your numbers are: "+
         "\n");
      for(i=0; i<sizeof(vals); i++) write(vals[i]+"\t");
      write("\n");
   }
   return;
}

void setVals(int *in){ vals = in; }

