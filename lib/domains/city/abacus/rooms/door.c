/* 
 * Door.c (27 Jun-93) /Drac
 */

/*
 *
 * Inherit this source to the rooms in which you wish 
 * to place doors. (Instead of the conventional 
 * inherit "/std/room"). Specify exits as per usual.  
 *   
 * In one room, you must have: 
 * add_door(string door_exit,
 *          mixed door_id,
 *          int door_status,
 *          int keyid);
 * 
 * In the adjoining room add a "copy_door" function,
 * with an exit direction, and everything from the first
 * room will be duplicated (including msg functions). 
 *
 * "door_exit" is a string with the exit command in that room.
 *
 * "door_id"   is a string containing the doors id. You can not
 *             have 2 doors with identical id's in the same room.
 *
 * "keyid"     is a code variable. Your key should have a function                          
 *             query_info() that returns an equal variable.
 *
 * "door_status" is a integer indicating the status of the door.
 *               bit 1 is set if the door is open    (else cleared)
 *               bit 2 is set if the door is locked  (else cleared)
 *               1 = door is open
 *               2 = door is locked
 *               3 = door is locked but open (it will lock when closed)
 *
 * set_enter_msg(string enter_msg,string enter_verbs,
 *		 string other_room);
 * "enter" standard
 * "#NA ## through the door.", "leave-leaves"
 * "#N enters the room." 
 *                       OBS! "other_room" is not a action string.
 *                       Name = #N not #NA.
 * 
 *
 * set_open_msg(string open_msg,
 *              string open_verbs,
 *              string other_room);
 *
 * "open_msg" standard
 * "#NA ## the door.","open-opens"
 * "The door opens."
 *
 * set_close_msg(string close_msg,
 *               string close_verbs,
 *               string other_room);
 *
 * "close_msg" standard
 * "#NA ## the door.","close-closes"
 * "The door closes."
 *
 * set_unlock_msg(string unlock_msg,
 *                string unlock_verbs,
 *                string other_room);
 *
 * "unlock_msg" standard
 * "#NA ## the door.","unlock-unlocks"
 * "You hear a faint click from the door."
 *
 * set_lock_msg(string lock_msg,
 *              string lock_verbs,
 *              string other_room);
 *
 * "lock_msg" standard
 * "#NA ## the door.","lock-locks"
 * "You hear a faint click from the door."
 *
 * set_fail_msg(string door_closed_msg,string door_closed_verb,
 *              string door_locked_msg,string door_locked_verb,
 *              string wrong_key);
 *
 * "door_locked" standard 
 * "#NA ## to open the door, but it is locked.","try-tries"
 *
 * "door_closed" standard
 * "#NA ## to leave through a closed door.","try-tries"
 *
 * "wrong_key" standard
 * "The key does not appear to fit."
 * set_but_msg(string door_is_closed,
 *             string door_is_open,
 *             string door_is_unlocked,
 *             string door_is_locked);
 *
 * "door_is_closed" standard
 * "The door is already closed."
 *
 * "door_is_open" standard
 * "The door is already open."
 *
 * "door_is_unlocked" standard
 * "The door is not locked."
 *
 * "door_is_locked" standard
 * "The door is already locked."
 *
 * All these msg functions change the last door created.
 *
 * copy_door(string door_exit,string door_id);
 *
 * You do not need to have a door in the adjoining room.
 * This obviously will look rather strange! 
 *
 */
#pragma strict_types
#include <newroom.h>
inherit "/std/room";

#define STANDARD\
	"#NA ## the door.","open-opens","The door opens.",\
	"#NA ## the door.","close-closes","The door closes.",\
	"#NA ## the door.","unlock-unlocks",\
	"You hear a faint click from the door.",\
	"#NA ## to open the door, but it is locked.","try-tries",\
	"#NA ## to leave through a closed door.","try-tries",\
	"The door is already closed.",\
	"The door is already open.",\
	"The door is not locked.",\
	"The door is already locked.",\
	"The key does not appear to fit.",\
	"#NA ## the door.","lock-locks",\
	"You hear a faint click from the door.",\
	"#NA ## through the door.", "leave-leaves",\
	"#N enters the room." 

#define DOOR_OPEN 1
#define DOOR_LOCKED 2

#define OPEN_MSG 4
#define OPEN_VERB 5
#define OPEN_OTHER 6
#define CLOSE_MSG 7
#define CLOSE_VERB 8
#define CLOSE_OTHER 9
#define UNLOCK_MSG 10
#define UNLOCK_VERB 11
#define UNLOCK_OTHER 12
#define FAIL_LOCK_MSG 13
#define FAIL_LOCK_VERB 14
#define FAIL_OPEN_MSG 15
#define FAIL_OPEN_VERB 16
#define FAIL_ITS_CLOSED 17
#define FAIL_ITS_OPEN 18
#define FAIL_ITS_UNLOCKED 19
#define FAIL_ITS_LOCKED 20
#define FAIL_KEY_WONT_FIT 21
#define LOCK_MSG 22
#define LOCK_VERB 23
#define LOCK_OTHER 24
#define LEAVE_MSG 25
#define LEAVE_VERB 26
#define LEAVE_OTHER 27

#define DOOR doors[door_id]
#define LDOOR doors[last_door]

mapping doors;
string last_door;

void
init()
{
  add_action("door_open","open");
  add_action("door_close","close");
  add_action("door_lock","lock");
  add_action("door_unlock","unlock");
  ::init();
}
status
add_door(string door_exit,string door_id, int door_status, int keyid)
{
  if (pointerp(dest_dir))
    dest_dir = FIX_DEST_DIR(0, dest_dir);
  if(!dest_dir[door_exit])
    return 0;

  if(!doors)
    doors = ([]);

  DOOR = ({ door_status,keyid,door_exit,dest_dir[door_exit][0],
	    STANDARD });
  dest_dir[door_exit][0] = door_id;
  dest_dir[door_exit][1] = "door_qxxc_move";
  last_door = door_id;
}
void
set_enter_msg(string enter_msg,string enter_verbs,
	      string other_room)
{
  LDOOR[LEAVE_MSG] = enter_msg;
  LDOOR[LEAVE_VERB] = enter_verbs;
  LDOOR[LEAVE_OTHER] = other_room;
}
void
set_open_msg(string msg,string verbs,string other)
{
  LDOOR[OPEN_MSG] = msg;
  LDOOR[OPEN_VERB] = verbs;
  LDOOR[OPEN_OTHER] = other;
}
void
set_close_msg(string msg,string verbs,string other)
{
  LDOOR[CLOSE_MSG] = msg;
  LDOOR[CLOSE_VERB] = verbs;
  LDOOR[CLOSE_OTHER] = other;
}
void
set_unlock_msg(string msg,string verbs,string other)
{
  LDOOR[UNLOCK_MSG] = msg;
  LDOOR[UNLOCK_VERB] = verbs;
  LDOOR[UNLOCK_OTHER] = other;
}
void
set_lock_msg(string msg,string verbs,string other)
{
  LDOOR[LOCK_MSG] = msg;
  LDOOR[LOCK_VERB] = verbs;
  LDOOR[LOCK_OTHER] = other;
}
void
set_fail_msg(string closed_msg,string closed_verbs,
	     string locked_msg,string locked_verbs,string wrong_key)
{
  LDOOR[FAIL_LOCK_MSG] = closed_msg;
  LDOOR[FAIL_LOCK_VERB] = closed_verbs;
  LDOOR[FAIL_OPEN_MSG] = locked_msg;
  LDOOR[FAIL_OPEN_VERB] = locked_verbs;
  LDOOR[FAIL_KEY_WONT_FIT] = wrong_key;
}
void
set_but_msg(string door_is_closed,string door_is_open,
	    string door_is_unlocked,string door_is_locked)
{
  LDOOR[FAIL_ITS_CLOSED] = door_is_closed;
  LDOOR[FAIL_ITS_OPEN] = door_is_open;
  LDOOR[FAIL_ITS_UNLOCKED] = door_is_unlocked;
  LDOOR[FAIL_ITS_LOCKED] = door_is_locked;
}

status
door_qxxc_move(string door_id)
{
  if(!(DOOR[0] & DOOR_OPEN))
    {
      action(DOOR[FAIL_OPEN_MSG],
	     DOOR[FAIL_OPEN_VERB]);
      return 1;
    }
  action(DOOR[LEAVE_MSG],DOOR[LEAVE_VERB]);
  this_player()->special_move("FOO",DOOR[3],0,0,DOOR[LEAVE_OTHER]);
  return 1;
}
status
door_open(string door_id)
{
  notify_fail("Open what?\n");
  if(!DOOR)
    return 0;
  if(DOOR[0] & DOOR_OPEN)
    {
      notify_fail(DOOR[FAIL_ITS_OPEN]+"\n");
      return 0;
    }
  if(DOOR[0] & DOOR_LOCKED)
    {
      action(DOOR[FAIL_LOCK_MSG],DOOR[FAIL_LOCK_VERB]);
      return 1;
    }
  DOOR[0] ^= DOOR_OPEN;
  action(DOOR[OPEN_MSG],DOOR[OPEN_VERB]);
  DOOR[3]->open_door(door_id);
  return 1;
}
status
door_close(string door_id)
{
  notify_fail("Close what?\n");
  if(!DOOR)
    return 0;
  if(!(DOOR[0] & DOOR_OPEN))
    {
      notify_fail(DOOR[FAIL_ITS_CLOSED]+"\n");
      return 0;
    }
  DOOR[0] ^= DOOR_OPEN;
  action(DOOR[CLOSE_MSG],DOOR[CLOSE_VERB]);
  DOOR[3]->close_door(door_id);
  return 1;
}
status
door_unlock(string door_id)
{
  string foo;
  if(!stringp(door_id))
    return 0;
  notify_fail("Unlock what with what?\n");
  if(sscanf(door_id,"%s with %s",door_id,foo) != 2)
    return 0;
  if(!DOOR || !DOOR[1])
    return 0;
  if(!(DOOR[0] & DOOR_LOCKED))
    {
      notify_fail(DOOR[FAIL_ITS_UNLOCKED]+"\n");
      return 0;
    }
  if(!present(foo,this_player()))
    {
      notify_fail("Unlock the "+door_id+" with what?\n");
      return 0;
    }
  if(present(foo,this_player())->query_info() != DOOR[1])
    {
      notify_fail(DOOR[FAIL_KEY_WONT_FIT]+"\n");
      return 0;
    }
  DOOR[0] ^= DOOR_LOCKED;
  action(DOOR[UNLOCK_MSG],DOOR[UNLOCK_VERB]);
  DOOR[3]->unlock_door(door_id);
  return 1;
}
status
door_lock(string door_id)
{
  string foo;
  if(!stringp(door_id))
    return 0;
  notify_fail("Lock what with what?\n");
  if(sscanf(door_id,"%s with %s",door_id,foo) != 2)
    return 0;
  if(!DOOR || !DOOR[1])
    return 0;
  if(DOOR[0] & DOOR_LOCKED)
    {
      notify_fail(DOOR[FAIL_ITS_LOCKED]+"\n");
      return 0;
    }
  if(!present(foo,this_player()))
    {
      notify_fail("Lock the "+door_id+" with what?\n");
      return 0;
    }
  if(present(foo,this_player())->query_info() != DOOR[1])
    {
      notify_fail(DOOR[FAIL_KEY_WONT_FIT]+"\n");
      return 0;
    }
  DOOR[0] ^= DOOR_LOCKED;
  action(DOOR[LOCK_MSG],DOOR[LOCK_VERB]);
  DOOR[3]->lock_door(door_id);
  return 1;
}
void
lock_door(string door_id)
{
  if(!DOOR)
    return;
  DOOR[0] |= DOOR_LOCKED;
  tell_room(this_object(),DOOR[LOCK_OTHER]+"\n");
}
void
unlock_door(string door_id)
{
  if(!DOOR)
    return;
  DOOR[0] &= ~DOOR_LOCKED;
  tell_room(this_object(),DOOR[UNLOCK_OTHER]+"\n");
}
void
open_door(string door_id)
{
  if(!DOOR)
    return;
  DOOR[0] |= DOOR_OPEN;
  tell_room(this_object(),DOOR[OPEN_OTHER]+"\n");
}
void
close_door(string door_id)
{
  if(!DOOR)
    return;
  DOOR[0] &= ~DOOR_OPEN;
  tell_room(this_object(),DOOR[CLOSE_OTHER]+"\n");
}
mixed *
get_door(string door_id)
{
  return DOOR;
}
status
copy_door(string dir,string door_id)
{
  mixed *tmp;
  int i;
  if (pointerp(dest_dir))
    dest_dir = FIX_DEST_DIR(0, dest_dir);

  if(!dest_dir[dir])
    return 0;

  tmp = (mixed *)dest_dir[dir][0]->get_door(door_id);

  add_door(dir,door_id,tmp[0],tmp[1]);
  for(i=4;i<sizeof(tmp);i++)
    DOOR[i] = tmp[i];
}
string
status_open(string door_id,string open,string closed)
{
  return DOOR[0] & DOOR_OPEN ? open:closed;
}
string
status_locked(string door_id,string locked,string unlocked)
{
  return DOOR[0] & DOOR_LOCKED ? unlocked:locked;
}

