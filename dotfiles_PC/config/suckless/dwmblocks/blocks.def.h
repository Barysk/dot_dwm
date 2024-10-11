//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/    /*Command*/		                                                /*Update Interval*/	/*Update Signal*/
    {"",        "/home/bk/.config/my_system_things/my_system_scripts/bk-KBL",   60,                  4},
	{"",        "/home/bk/.config/my_system_things/my_system_scripts/bk-VOL",   0,                  10},
	{"",        "/home/bk/.config/my_system_things/my_system_scripts/bk-time",	1,		            0},
};

// signal is being emmited withusage of kill -N $(pidof dwmblocks)
// where N = US + 34
// *US - Update Signal

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ";
static unsigned int delimLen = 5;
