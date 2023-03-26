/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 9;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 9;       /* vert inner gap between windows */
static const unsigned int gappoh    = 12;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 12;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int attachbelow	    = 1;	/* 1 means attach after the currently active window */
static const char *fonts[]          = { "monospace:size=10" };
/* COLOURS */
static const char background[]	    = "#1D213C";
static const char foreground[]	    = "#E5EBF7";
static const char black[]	    = "#15131D";
static const char red[] 	    = "#F56486";
static const char green[]	    = "#48E79A";
static const char yellow[]	    = "#E5C374";
static const char blue[]	    = "#2B81D2";
static const char magenta[]	    = "#E77AC1";
static const char cyan[]	    = "#97D6FF";
static const char grey[]	    = "#ADA3AD";
/* BRIGHT COLOURS */
static const char bright_black[]    = "#2E2F4C";
static const char bright_red[] 	    = "#E55381";
static const char bright_green[]    = "#2CDA9D";
static const char bright_yellow[]   = "#D4A96A";
static const char bright_blue[]	    = "#1674CE";
static const char birght_magenta[]  = "#C76DB4";
static const char bright_cyan[]	    = "#72B0D7";
static const char bright_grey[]	    = "#9C8F95";
static const char *colors[][3]      = {
	/*               fg          bg           border   */
	[SchemeNorm] = { foreground, black,       bright_grey },
	[SchemeSel]  = { foreground, blue,        magenta  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance title tagsmask  isfloating monitor */
	{ "Gimp",     NULL,    NULL, 0,        1,         -1 },
	{ "Firefox",  NULL,    NULL, 1 << 1,   0,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/", "-c", cmd, NULL } }

/* commands */
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *rofiemoji[] = { "rofi", "-show", "emoji", "-show-icons", NULL };
static const char *roficalc[] = { "rofi", "-show", "calc", "-show-icons", "no-show-match", "no-sort", NULL };
static const char *rofipass[] = { "rofi-pass", NULL };
static const char *rofibrowser[] = { "/home/nhe/.config/rofi/rofibrowser.sh", NULL };
static const char *rofipower[] = { "/home/nhe/.config/rofi/rofipower.sh", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *filemanager[]  = { "thunar", NULL };
static const char *brightnessup[] = { "brillo", "-q", "-u", "150000", "-A", "5", NULL };
static const char *brightnessdn[] = { "brillo", "-q", "-u", "150000", "-U", "5", NULL };
static const char *volumeup[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *volumedn[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *volumemt[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *mphonemt[] = { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };
static const char *arandr[] = { "arandr", NULL };
static const char *btop[] = { "alacritty", "-e", "btop", NULL };
static const char *rofifiles[] = { "rofi", "-show", "filebrowser", "-show-icons", NULL };
static const char *screenshot[] = { "flameshot", "gui", NULL };
#include "movestack.c"
#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_z,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = rofiemoji } },
	{ MODKEY,                       XK_p,      spawn,          {.v = rofipass } },
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,	                XK_x,      spawn,          {.v = rofibrowser } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = roficalc } },
	{ MODKEY,	                XK_c,      spawn,          {.v = filemanager } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = rofipower } },
//	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
//	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_m,      view,           {0} },
	{ MODKEY,   	                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setfullscreen,  {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {.v = &layouts[1]} },
	{ MODKEY,	                XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
//	THINKPAD KEYS
	{ 0, 		XK_Print, 	           spawn, 	   {.v = screenshot } },
	{ 0, 		XF86XK_AudioMute,          spawn, 	   {.v = volumemt } },
	{ 0,		XF86XK_AudioLowerVolume,   spawn,	   {.v = volumeup } },
	{ 0,		XF86XK_AudioRaiseVolume,   spawn,   	   {.v = volumedn } },
	{ 0,		XF86XK_AudioMicMute,       spawn,  	   {.v = mphonemt } },
	{ 0,		XF86XK_MonBrightnessUp,    spawn,      	   {.v = brightnessup } },
	{ 0,		XF86XK_MonBrightnessDown,  spawn,      	   {.v = brightnessdn } },
	{ 0,		XF86XK_Display,            spawn,      	   {.v = arandr } },
	{ 0,		XF86XK_Tools,              spawn,      	   {.v = btop } },
	{ 0,		XF86XK_Search,             spawn,      	   {.v = rofifiles } },
	{ 0,		XF86XK_LaunchA,            spawn,      	   {.v = roficmd } },
	{ 0,		XF86XK_Explorer,           spawn,      	   {.v = filemanager } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
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

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
/*	{ "incnmaster",     incnmaster }, */
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};
