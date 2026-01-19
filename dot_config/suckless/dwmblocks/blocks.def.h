//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/    /*Command*/                                                    /*Update Interval*/   /*Update Signal*/
	{"",        "~/.config/suckless/dwmblocks/blocks_scripts/keyboard_layout",                 60,                 4},
	{"",        "~/.config/suckless/dwmblocks/blocks_scripts/volume",                           0,                10},
	{"",        "~/.config/suckless/dwmblocks/blocks_scripts/battery",                         60,                 0},
	{"",        "~/.config/suckless/dwmblocks/blocks_scripts/time",                             1,                 0},
	{"",        "echo '[ DWM ]'",                                                               0,                 0},
};

// signal is being emmited withusage of kill -N $(pidof dwmblocks)
// where N = US + 34
// *US - Update Signal

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = "  ";
static unsigned int delimLen = sizeof(delim);
