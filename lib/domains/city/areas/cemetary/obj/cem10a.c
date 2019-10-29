/* This object exists only to ensure init() gets called
   in the room (cem10) after the init() in the door. */

init()
{
if(environment())
  environment()->init();
}
