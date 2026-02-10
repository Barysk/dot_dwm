#include "movestack.c"

// DWM 6.8

#define FONT          "serif:size=12"
#define COL_BLACK     "#000000"
#define COL_WHITE     "#ffffff"
#define COL_ACCENT    "#646464"
#define COL_SECONDARY "#323232"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 1;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { FONT };
static const char dmenufont[]       = FONT;

static const char *colors[][3]      = {
	/*               fg         bg             border   */
	[SchemeNorm] = { COL_WHITE, COL_BLACK,     COL_BLACK  },
	[SchemeSel]  = { COL_WHITE, COL_SECONDARY, COL_ACCENT },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九", "十" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title           tags mask     isfloating   monitor */
	{ "Telegram",     NULL,       "Media viewer", 0,            1,           -1 },
	{ "Gimp",         NULL,       NULL,           0,            1,           -1 },
	{ "Firefox",      NULL,       NULL,           1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact        = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 1;  /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0;  /* 1 will force focus on the fullscreen window */
static const int refreshrate    = 60; /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "タイル",   tile },    /* first entry is default */
	{ "フロート", NULL },    /* no layout function means floating behavior */
	{ "メガネ",   monocle },
	{ "センター", centeredmaster },
	{ "トップ",   bstack },
	{ "デッキ",   deck },
	// { ">M>",      centeredfloatingmaster },
	// { "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = { "/home/bk/.config/suckless/dwm/scripts/dmenu_wrapper", dmenumon, FONT, COL_BLACK, COL_WHITE, COL_SECONDARY, COL_WHITE, NULL };
static const char *termcmd[]      = { "kitty",    NULL };
static const char *explrcmd[]     = { "pcmanfm",  NULL };
static const char *browsercmd[]   = { "brave",    NULL };
static const char *telegramcmd[]  = { "Telegram", NULL };

/* volume commands */
static const char *volup[]      = { "sh", "-c", "pactl set-sink-volume @DEFAULT_SINK@ +10% && kill -44 $(pidof dwmblocks)", NULL };
static const char *voldown[]    = { "sh", "-c", "pactl set-sink-volume @DEFAULT_SINK@ -10% && kill -44 $(pidof dwmblocks)", NULL };
static const char *mute_audio[] = { "sh", "-c", "pactl set-sink-mute @DEFAULT_SINK@ toggle && kill -44 $(pidof dwmblocks)", NULL };
static const char *toggle_mic[] = { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };

/* brightness commands */
static const char *brightness_down[] = { "brightnessctl", "set", "10%-", NULL };
static const char *brightness_up[]   = { "brightnessctl", "set", "+10%", NULL };

/* multimedia */
static const char *multimedia_pause[]    = { "playerctl", "play-pause", NULL };
static const char *multimedia_next[]     = { "playerctl", "next", NULL };
static const char *multimedia_previous[] = { "playerctl", "previous", NULL };

/* multi monitor */
static const char *connect_second_screen[] = { "/home/bk/.config/suckless/dwm/scripts/change_monitors", dmenufont, COL_BLACK, COL_WHITE, COL_SECONDARY, COL_WHITE, NULL };

/* lockscreen command */
static const char *lock_screen[] = { "/home/bk/.config/suckless/dwm/scripts/lockscreen", NULL };

/* screenshot */
static const char *make_screenshot[] = { "flameshot", "gui", NULL };

/* change layout script */
static const char *change_layout[] = { "/home/bk/.config/suckless/dwm/scripts/change_keyboard_layout", NULL };

static const Key keys[] = {
	/* modifier                     key          function          argument */
	{ MODKEY,                       XK_p,        spawn,            {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,   spawn,            {.v = termcmd } },
	{ MODKEY,                       XK_e,        spawn,            {.v = explrcmd } },
	{ MODKEY,                       XK_t,        spawn,            {.v = telegramcmd } },
	{ MODKEY,                       XK_b,        spawn,            {.v = browsercmd } },
	// 5
	{ MODKEY|ShiftMask,             XK_b,        togglebar,        {0} },
	{ MODKEY,                       XK_j,        focusstack,       {.i = +1 } },
	{ MODKEY,                       XK_k,        focusstack,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,        movestack,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,        movestack,        {.i = -1 } },
	{ MODKEY,                       XK_i,        incnmaster,       {.i = +1 } },
	{ MODKEY,                       XK_d,        incnmaster,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,        setcfact,         {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,        setcfact,         {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,        setcfact,         {.f =  0.00} },
	// 10
	{ MODKEY,                       XK_h,        setmfact,         {.f = -0.05} },
	{ MODKEY,                       XK_l,        setmfact,         {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,   zoom,             {0} },
	{ MODKEY,                       XK_Tab,      view,             {0} },
	{ MODKEY,                       XK_q,        killclient,       {0} },
	// 5
	{ MODKEY|ControlMask,           XK_h,        setlayout,        {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_f,        setlayout,        {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_m,        setlayout,        {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_c,        setlayout,        {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_k,        setlayout,        {.v = &layouts[4]} },
	{ MODKEY|ControlMask,           XK_d,        setlayout,        {.v = &layouts[5]} },
	// 5
	{ MODKEY,                       XK_space,    spawn,            {.v = multimedia_pause  } },
	{ MODKEY,                       XK_Down,     spawn,            {.v = multimedia_pause  } },
	{ MODKEY,                       XK_Right,    spawn,            {.v = multimedia_next  } },
	{ MODKEY,                       XK_Left,     spawn,            {.v = multimedia_previous  } },
	{ 0,                            0x1008ff02,  spawn,            {.v = brightness_up } },
	{ 0,                            0x1008ff03,  spawn,            {.v = brightness_down } },
	{ MODKEY,                       XK_Escape,   spawn,            {.v = lock_screen } },
	{ MODKEY|ShiftMask,             XK_s,        spawn,            {.v = make_screenshot} },
	{ 0,                            0x1008ff59,  spawn,            {.v = connect_second_screen } },
	{ 0,                            0x1008ff13,  spawn,            {.v = volup } },
	{ 0,                            0x1008ff11,  spawn,            {.v = voldown } },
	{ 0,                            0x1008ff12,  spawn,            {.v = mute_audio } },
	{ 0,                            0x1008ffb2,  spawn,            {.v = toggle_mic } },
	{ Mod1Mask,                     XK_Shift_L,  spawn,            {.v = change_layout } },
	// 14
	{ MODKEY|ShiftMask,             XK_f,        togglefloating,   {0} },
	{ MODKEY,                       XK_f,        togglefullscreen, {0} },
	{ MODKEY,                       XK_percent,  view,             {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_percent,  tag,              {.ui = ~0 } },
	{ MODKEY,                       XK_comma,    focusmon,         {.i = -1 } },
	{ MODKEY,                       XK_period,   focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,    tagmon,           {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,   tagmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,      swapmon,          {0} },
	// 9
	TAGKEYS(                        XK_plus,                       0)
	TAGKEYS(                        XK_bracketleft,                1)
	TAGKEYS(                        XK_braceleft,                  2)
	TAGKEYS(                        XK_parenleft,                  3)
	TAGKEYS(                        XK_ampersand,                  4)
	TAGKEYS(                        XK_asciicircum,                5)
	TAGKEYS(                        XK_parenright,                 6)
	TAGKEYS(                        XK_braceright,                 7)
	TAGKEYS(                        XK_bracketright,               8)
	TAGKEYS(                        XK_asterisk,                   9)
	{ MODKEY|ShiftMask,             XK_Escape,  quit,              {0} },
	// 10
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

