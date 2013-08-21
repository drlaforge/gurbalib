/*
 * Gurbalib interface for using commands
 *
 * Aidil @ Way of the Force.
 *
 * This code is in the public domain
 *
 */

#define DEFAULT_PRIORITY 10

private mapping pathkey;

static void create() {
   pathkey = ([ ]);
}

/*
 * mask those functions in your object and call the inherited
 * versions to make this interface public.
 *
 */


/* intended for usage from regular lpc code */
static void add_pathkey(string path, varargs int prio) {
   if(!prio) prio = DEFAULT_PRIORITY;
   if(!pathkey[prio]) 
      pathkey[prio] = ({ path });
   else 
      pathkey[prio] |= ({ path });
}

static void remove_pathkey(string path) {
   int *priorities;
   int i,sz;

   priorities = map_indices(pathkey);
   for (i=0, sz=sizeof(priorities); i < sz; i++) {
      pathkey[priorities[i]] -= ({ path });
   }
}

/* 2 helper functions for the shell interface below */
private string map_to_path(mapping stuff) {
   string res;
   int i, sz;
   int *prio;

   res = "";
   prio = map_indices(stuff);

   for (i=0, sz=sizeof(prio); i<sz; i++) {
      /* will leave a trailing :, we don't care since the reverse function doesn't care either */
      res += implode( stuff[prio[i], ":" ) + ":";
   }
   return res;
}

private mapping path_to_map(string path, varargs int validate) {
   mapping result;
   string *keys;
   int i, prio;

   result = ([ ]);
   prio = DEFAULT_PRIORITY;
   keys = explode(path, ":");
   /* no empty path components wanted, throw them out */
   keys -= ({ "" });
   
   /* note, have to check against sizeof() for each iteration as the array may change */
   for (i=0; i<sizeof(keys); i++, prio+=10) {
      if (keys[i] == "$PATH") {
         string *tmp;
         string pstr;

         pstr = map_to_path(pathkey);
         /* explode, as we are not interested in leading/trailing : */
         keys = keys[..i-1] + explode(pstr, ":") + keys[i+1..];
      }
      if(!validate || COMMAND_D->validate_path(keys[i])) {
         result[prio] = ({ keys[i] });
      } else {
         /* we didn't use this 'priority' */
         prio -= 10;
      }
   }
   return result;
}

/* intended for 'shell' objects like the player object */
static string query_searchpath() {
   return map_to_path(pathkey);
}

static void set_searchpath(string str) {
   pathkey = path_to_map(str, 1);
}

private string *pathkey_to_array( mapping stuff ) {
   string *res;
   int i, sz;
   int *prio;

   /* if we did this before in this thread, don't do it again */
   if( res = get_otlvar("pathkey") ) {
     return res;
   }

   res = ({ });
   prio = map_indices(stuff);

   for (i=0, sz=sizeof(prio); i<sz; i++) {
      /* will leave a trailing :, we don't care since the reverse function doesn't care either */
      res += stuff[prio[i]];
   }
   /* store the result, just in case */
   set_otlvar("pathkey",res);
   return res;
}


/* for both regular lpc code and shells, execute the argument as a command */
static int command(string input) {
   return COMMAND_D->exec_command(input, res);
}
