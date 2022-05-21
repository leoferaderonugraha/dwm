/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

/* custom colours */
static const char window_fg[] = "#EEEEEE";
static const char window_bg[] = "#000000";
static const char window_border[] = "#EEEEEE";
static const char custom_palette0[][10] = {
    /* classic black-green palette*/
    "#000000",
    "#00FF00"
};
static const char custom_palette1[][10] = {
    "#2E0249", 
    "#570A57",
    "#A91079",
    "#F806CC",
};


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	//[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeNorm] = {
        custom_palette0[1], // Foreground
        custom_palette0[0], // Background
        custom_palette0[1], // Border colour
    },
	[SchemeSel]  = {
        window_fg,      // Foreground
        window_bg,      // Background
        window_border,  // Border colour
    },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
/* Mod1Mask is <alt>
 * Mod4Mask is <super-key>
 */
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
    "-nb", col_gray1,
    "-nf", col_gray3,
    "-sb", col_cyan,
    "-sf", col_gray4,
    NULL
};
static const char *termcmd[]  = { "st", NULL };

/* custom commands */
static const char *firefox[] = { "firefox", NULL };
static const char *chromium[] = { "chromium", NULL };
static const char *terminator[] = { "terminator", NULL };
static const char *file_manager[] = { "nemo", NULL };
static const char *bt_manager[] = { "blueman-manager", NULL };

static Key keys[] = {
	/* modifier            key        function        argument */
	{ MODKEY,              XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,              XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,              XK_b,      togglebar,      {0} },
	{ MODKEY,              XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,              XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,              XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,              XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,              XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,              XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,    XK_Return, zoom,           {0} },
	{ MODKEY,              XK_Tab,    view,           {0} },
	{ MODKEY,              XK_x,      killclient,     {0} },
	{ MODKEY|ShiftMask,    XK_a,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,    XK_s,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,    XK_d,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,              XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,    XK_space,  togglefloating, {0} },
	{ MODKEY,              XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,    XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,              XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,              XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,    XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,    XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(               XK_1,                      0)
	TAGKEYS(               XK_2,                      1)
	TAGKEYS(               XK_3,                      2)
	TAGKEYS(               XK_4,                      3)
	TAGKEYS(               XK_5,                      4)
	TAGKEYS(               XK_6,                      5)
	TAGKEYS(               XK_7,                      6)
	TAGKEYS(               XK_8,                      7)
	TAGKEYS(               XK_9,                      8)
	{ MODKEY|ShiftMask,    XK_q,      quit,           {0} },
    /* custom commands key binding */
    { MODKEY,              XK_w,      spawn,          {.v = firefox} },
    { MODKEY,              XK_e,      spawn,          {.v = chromium} },
    { MODKEY,              XK_t,      spawn,          {.v = terminator} },
    { MODKEY,              XK_q,      spawn,          {.v = file_manager} },
    { MODKEY|ShiftMask,    XK_b,      spawn,          {.v = bt_manager} },
};

/* button definitions */
/* 
 * click can be ClkTagBar, ClkLtSymbol, ClkStatusText,
 * ClkWinTitle, ClkClientWin, or ClkRootWin
 *
 */
static Button buttons[] = {
	/* click         event mask  button   function        argument */
	{ ClkLtSymbol,   0,          Button1, setlayout,      {0} },
	{ ClkLtSymbol,   0,          Button3, setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,   0,          Button2, zoom,           {0} },
	{ ClkStatusText, 0,          Button2, spawn,          {.v = termcmd } },
	{ ClkClientWin,  MODKEY,     Button1, movemouse,      {0} },
	{ ClkClientWin,  MODKEY,     Button2, togglefloating, {0} },
	{ ClkClientWin,  MODKEY,     Button3, resizemouse,    {0} },
	{ ClkTagBar,     0,          Button1, view,           {0} },
	{ ClkTagBar,     0,          Button3, toggleview,     {0} },
	{ ClkTagBar,     MODKEY,     Button1, tag,            {0} },
	{ ClkTagBar,     MODKEY,     Button3, toggletag,      {0} },
};

