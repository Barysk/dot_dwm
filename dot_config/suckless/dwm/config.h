/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "IBM 3270:size=10:bold" };
static const char dmenufont[]       = "IBM 3270:size=10:bold";

static const char col_black[]		= "#111111";
static const char col_red[]			= "#4d0000";
static const char col_white[]       = "#ffffff";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_white, col_black, col_black },
    [SchemeSel]  = { col_white, col_red,  col_red  },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "タイル",        tile },    /* first entry is default */
    { "フロート",      NULL },    /* no layout function means floating behavior */
    { "メガネ",        monocle },
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
static const char *dmenucmd[] = {
    "dmenu_run",
    "-m", dmenumon,
    "-fn", dmenufont,
    "-nb", col_black,
    "-nf", col_white,
    "-sb", col_red,
    "-sf", col_white,
    NULL
};
static const char *termcmd[]  = { "kitty", NULL };
static const char *explrcmd[]  = { "pcmanfm", NULL };
static const char *browsercmd[]  = { "brave", NULL };
static const char *telegramcmd[]  = { "Telegram", NULL };

/* volume commands */
static const char *volup[] = { "sh", "-c", "pactl set-sink-volume @DEFAULT_SINK@ +10% && kill -44 $(pidof dwmblocks)", NULL };
static const char *voldown[] = { "sh", "-c", "pactl set-sink-volume @DEFAULT_SINK@ -10% && kill -44 $(pidof dwmblocks)", NULL };
static const char *mute_audio[] = { "sh", "-c", "pactl set-sink-mute @DEFAULT_SINK@ toggle && kill -44 $(pidof dwmblocks)", NULL };
static const char *toggle_mic[] = { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };

/* brightness commands */
static const char *brightness_down[] = { "brightnessctl", "set", "10%-", NULL };
static const char *brightness_up[] = { "brightnessctl", "set", "+10%", NULL };

/* multimedia */
static const char *multimedia_pause[] = { "playerctl", "play-pause", NULL };
static const char *multimedia_next[] = { "playerctl", "next", NULL };
static const char *multimedia_previous[] = { "playerctl", "previous", NULL };

/* multi monitor */
static const char *connect_second_screen[] = { "/home/bk/.config/suckless/dwm/dwm_scripts/change_monitors", NULL };

/* lockscreen command */
static const char *lock_screen[] = { "/home/bk/.config/suckless/dwm/dwm_scripts/lockscreen", NULL };

/* screenshot */
static const char *make_screenshot[] = { "flameshot", "gui", NULL };

/* shutdown script | Uncoment if needed */
//static const char *logout_cmd[] = { "~/.config/suckless/dwm/dwm_scripts/logout", NULL };

/* change layout script */
static const char *change_layout[] = { "/home/bk/.config/suckless/dwm/dwm_scripts/change_keyboard_layout", NULL };

static const Key keys[] = {
    /* modifier                     key         function        argument */
    { MODKEY,                       XK_p,       spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return,  spawn,          {.v = termcmd } },
    { MODKEY,                       XK_e,       spawn,          {.v = explrcmd } },
    { MODKEY,                       XK_t,       spawn,          {.v = telegramcmd } },
    { MODKEY,                       XK_b,       spawn,          {.v = browsercmd } },
    { MODKEY|ShiftMask,             XK_b,       togglebar,      {0} },
    { MODKEY,                       XK_j,       focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,       focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,       incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,       incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return,  zoom,           {0} },
    { MODKEY,                       XK_Tab,     view,           {0} },
    { MODKEY,                       XK_q,       killclient,     {0} },
    { MODKEY|ShiftMask,             XK_q,       setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_w,       setlayout,      {.v = &layouts[1]} },
    { MODKEY|ShiftMask,             XK_e,       setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_f,       togglefullscr,  {0} },
//  { MODKEY,                       XK_space,   setlayout,      {0} }, // I don't use it
    { MODKEY,                       XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_f,       togglefloating, {0} },
    { MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
    { MODKEY,                       XK_minus,   setgaps,        {.i = -1 } },
    { MODKEY,                       XK_equal,   setgaps,        {.i = +1 } },
    { MODKEY|ShiftMask,             XK_equal,   setgaps,        {.i = 0  } },
    { MODKEY,                       XK_space,   spawn,          {.v = multimedia_pause  } },
    { MODKEY,                       XK_Down,    spawn,          {.v = multimedia_pause  } },
    { MODKEY,                       XK_Right,   spawn,          {.v = multimedia_next  } },
    { MODKEY,                       XK_Left,    spawn,          {.v = multimedia_previous  } },
    { 0,                            0x1008ff02, spawn,          {.v = brightness_up } },    // brightness up
    { 0,                            0x1008ff03, spawn,          {.v = brightness_down } },  // brightness down
    { MODKEY,                       XK_Escape,  spawn,          {.v = lock_screen } },      // screen lock
    { MODKEY|ShiftMask,             XK_s,       spawn,          {.v = make_screenshot} },   // screenshot
    { 0,                            0x1008ff59, spawn,          {.v = connect_second_screen } },    // second screen
    { 0,                            0x1008ff13, spawn,          {.v = volup } },        // volume up
    { 0,                            0x1008ff11, spawn,          {.v = voldown } },      // volume down
    { 0,                            0x1008ff12, spawn,          {.v = mute_audio } },   // mute button
    { 0,                            0x1008ffb2, spawn,          {.v = toggle_mic } },   // mute source
    { Mod1Mask,                     XK_Shift_L, spawn,          {.v = change_layout } },// Alt + Shift, Keyboard layout change
//  { 0,                            0x1008ff2a, spawn,          {.v = logout_cmd } },   // power off button // Add if needed
    TAGKEYS(                        XK_1,                       0)
    TAGKEYS(                        XK_2,                       1)
    TAGKEYS(                        XK_3,                       2)
    TAGKEYS(                        XK_4,                       3)
    TAGKEYS(                        XK_5,                       4)
    TAGKEYS(                        XK_6,                       5)
    TAGKEYS(                        XK_7,                       6)
    TAGKEYS(                        XK_8,                       7)
    TAGKEYS(                        XK_9,                       8)
    { MODKEY|ShiftMask,             XK_Escape,  quit,           {0} },
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

