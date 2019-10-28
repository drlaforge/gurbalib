/*
ansi.h
borrowed from Genocide
--One
 */
 
#ifndef _ANSI_H

#define ESC " "
#define CLS ESC "[2J"
#define BELL " "

#define NORMAL ESC "[0m"
#define BOLD ESC "[1m"
#define UNDERLINE ESC "[4m"
#define BLINK ESC "[5m"
#define REVERSE ESC "[7m"
#define CONCEALED ESC "[8m"
 
#define BLACK ESC "[30m"
#define RED ESC "[31m"
#define GREEN ESC "[32m"
#define BROWN ESC "[33m"
#define YELLOW BROWN
#define BLUE ESC "[34m"
#define MAGENTA ESC "[35m"
#define CYAN ESC "[36m"
#define WHITE ESC "[37m"
 
#define B_BLACK ESC "[40m"
#define B_RED ESC "[41m"
#define B_GREEN ESC "[42m"
#define B_BROWN ESC "[43m"
#define B_YELLOW B_BROWN
#define B_BLUE ESC "[44m"
#define B_MAGENTA ESC "[45m"
#define B_CYAN ESC "[46m"
#define B_WHITE ESC "[47m"
 
#define SAVE_CURSOR ESC "[s"
#define RESTORE_CURSOR ESC "[u"
 
#define ROWCOL(x,y) sprintf(ESC "[%d;%dH", x, y)
#define TEXT_BOX(x,y) sprintf(ESC "[%d;%dr", x, y)

#define STANDARD_FOR(user) ((string)user->query_standard())
#define STANDARD STANDARD_FOR(this_player())
 
#define ANSI_FOR(user) (user->query_ansi())
#define ANSI ANSI_FOR(this_player())
 
#define _ANSI_H
 
#endif /* _ANSI_H */
