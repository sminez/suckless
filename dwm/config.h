/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int gappx          = 6;  /* gap pixel between windows */
static const unsigned int snap           = 12;  /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const char *fonts[]               = {
	"ProFont For Powerline:size=10"
};
static const char dmenufont[]            = "ProFont For Powerline:size=12";
static const char col_gray1[]            = "#282828";
static const char col_gray2[]            = "#3c3836";
static const char col_gray3[]            = "#a89984";
static const char col_gray4[]            = "#f2e5bc";
/* static const char col_highlight[]        = "#b16286"; */
/* static const char col_highlight[]        = "#458588"; */
/* static const char col_highlight[]        = "#076678"; */
/* static const char col_highlight[]        = "#75507B"; */
/* static const char col_highlight[]        = "#8ec07c"; */
static const char col_highlight[]        = "#40af61";

#define baralpha    0xd0
#define borderalpha OPAQUE

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_highlight, col_highlight },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
/* static const char *tags[] = { "1 ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 λ", "9 " }; */
/* static const char *tags[] = { "", "", "", "", "", "", "", "λ", "" }; */
/* static const char *tags[] = { "term", "note", "doc", "web1", "web2", "code", "edit", "repl", "media" }; */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class               instance    title       tags mask     isfloating   monitor */
	{ "Gimp",              NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",           NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Spotify",           NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Skype",             NULL,       NULL,       1 << 8,       0,           -1 },
	{ "drawn-term",        NULL,       NULL,       0,            1,           -1 },
	{ "jupyter-qtconsole", NULL,       NULL,       0,            1,           -1 },
	{ "mpv",               NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

/* Additional layouts */
#include "centeredmaster.c"
#include "bottomstack.c"
#include "fibonacci.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[side]", tile },    /* first entry is default */
	{ "[botm]", bstack },
	{ "[cent]", centeredmaster },
	{ "[fibo]", dwindle },
	{ "[mono]", monocle },
	{ "[    ]", NULL },    /* no layout function means floating behavior */
	{ NULL, NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-p", "./ ",
    "-sb", col_highlight, "-nb", col_gray1, "-nf", col_gray4,
    "-l", "10", NULL
};
/* static const char *dmenucmd[] = { "/home/innes/bin/rofi-apps", NULL }; */
static const char *acmeopencmd[]  = { "/home/innes/Personal/acme-corp/scripts/afindfile.sh", NULL };
static const char *acmesearchcmd[]  = { "/home/innes/Personal/acme-corp/scripts/acme-fuzzy-window-search.sh", NULL };
static const char *drawtermcmd[]  = { "draw-term", NULL };
static const char *lockcmd[]  = { "/home/innes/bin/lock-screen", NULL };
static const char *mutecmd[]  = { "amixer", "sset", "'Master'", "unmute", NULL };
static const char *playyoutubecmd[]  = { "play-youtube", NULL };
static const char *logoutcmd[]  = { "/home/innes/bin/scripts/dwm/logout.sh", NULL };
static const char *pythonconsolecmd[]  = { "python3.7", "-m", "qtconsole", NULL };
/* static const char *termcmd[]  = { "tilix", NULL }; */
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *screenshotcmd[]  = { "screenshot", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *togglekbcmd[]  = { "toggle-keyboard-layout", NULL };
static const char *voldowncmd[]  = { "amixer", "sset", "'Master'", "5%-", NULL };
static const char *volupcmd[]  = { "amixer", "sset", "'Master'", "5%+", NULL };
static const char *wifimenucmd[]  = { "rofi-wifi-menu", NULL };
static const char *windowselectcmd[]  = { "rofi", "-show", "window", NULL };

#include "keepfloatingposition.c"

/* see /usr/include/X11/keysymdef.h for available keys */
static Key keys[] = {
	/* modifier             key              function        argument */
	{ MODKEY,               XK_semicolon,    spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_Return,       spawn,          {.v = termcmd } },
	{ MODKEY|Mod1Mask,      XK_l,            spawn,          {.v = lockcmd } },
	{ MODKEY|Mod1Mask,      XK_r,            quit,           {0} }, /* This actually reloads dwm due to my wrapper script */
	{ MODKEY|Mod1Mask,      XK_b,            togglebar,      {0} },
	{ MODKEY|Mod1Mask,      XK_Escape,       spawn,          {.v = logoutcmd } },
	{ MODKEY|Mod1Mask,      XK_k,            spawn,          {.v = togglekbcmd } },
	{ MODKEY,               XK_n,            spawn,          {.v = wifimenucmd } },
	{ MODKEY,               XK_w,            spawn,          {.v = windowselectcmd } },
	{ MODKEY,               XK_o,            spawn,          {.v = acmeopencmd } },
	{ MODKEY,               XK_s,            spawn,          {.v = acmesearchcmd } },
	{ MODKEY|ShiftMask,     XK_s,            spawn,          {.v = screenshotcmd } },
	{ MODKEY|ShiftMask,     XK_p,            spawn,          {.v = pythonconsolecmd } },
	{ MODKEY,               XK_p,            togglepinned,   {0} },
	{ MODKEY,               XK_slash,        togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,     XK_y,            spawn,	         {.v = playyoutubecmd } },

    /* Audio control */
	{ MODKEY,               XK_F1,           spawn,          {.v = mutecmd } },
	{ MODKEY,               XK_F2,           spawn,          {.v = voldowncmd } },
	{ MODKEY,               XK_F3,           spawn,          {.v = volupcmd } },

    /* Cycle between windows on the stack */
	{ MODKEY,               XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,            focusstack,     {.i = -1 } },

    /* Add/Remove windows to the master area */
	{ MODKEY,               XK_i,            incnmaster,     {.i = +1 } },
	{ MODKEY,               XK_d,            incnmaster,     {.i = -1 } },

    /* Increase/decrease the size of the master area */
	{ MODKEY,               XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,            setmfact,       {.f = +0.05} },

    /* Drag the focused window through the client stack */
	{ MODKEY|ShiftMask,     XK_j,            movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_k,            movestack,      {.i = -1 } },

    /* Pop the focused window to the master area of the stack */
	{ MODKEY,               XK_backslash,    zoom,           {0} },

    /* Toggle back to the last tag that was focused */
	{ MODKEY,               XK_Tab,          view,           {0} },
	{ MODKEY|ShiftMask,     XK_q,            killclient,     {0} },

    /* cycle layouts rather than binding an individual hotkey for each one */
	{ MODKEY,	        	XK_grave,        cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_grave,        cyclelayout,    {.i = -1 } },

    /* Set monocle layout: (fullscreen deck). Need to use MOD+space to get back to prev layout */
	{ MODKEY,               XK_f,            setlayout,      {.v = &layouts[4]} },

    /* manage floating windows */
	{ MODKEY,               XK_space,        setlayout,      {0} },
	{ MODKEY|ShiftMask,     XK_space,        togglefloating, {0} },

    /* Display all tags on the current display */
	{ MODKEY,               XK_0,            view,           {.ui = ~0 } },

    /* Pin the focused window to all tags */
	{ MODKEY|ShiftMask,     XK_0,            tag,            {.ui = ~0 } },

    /* Jump to the prev/next screen */
	{ MODKEY,               XK_bracketleft,  focusmon,       {.i = -1 } },
	{ MODKEY,               XK_bracketright, focusmon,       {.i = +1 } },

    /* Throw to the prev/next screen */
	{ MODKEY|ShiftMask,     XK_bracketleft,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_bracketright, tagmon,         {.i = +1 } },

    /* Bind the various actions needed for managing each tag */
	TAGKEYS(XK_1, 0), TAGKEYS(XK_2, 1), TAGKEYS(XK_3, 2),
	TAGKEYS(XK_4, 3), TAGKEYS(XK_5, 4), TAGKEYS(XK_6, 5),
	TAGKEYS(XK_7, 6), TAGKEYS(XK_8, 7), TAGKEYS(XK_9, 8),
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
/* Buttons are: */
/*   1 - left */
/*   2 - middle */
/*   3 - right */
/*   4 - scroll up */
/*   5 - scroll down */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },

    /* Toggle keyboard layout with middle click on status */
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = togglekbcmd } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = volupcmd } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = voldowncmd } },

    /* Window movement */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },


    /* Draw terminals with the mouse */
	{ ClkRootWin,        MODKEY|ShiftMask,  Button3,        spawn,          {.v = drawtermcmd } },
	{ ClkClientWin,      MODKEY|ShiftMask,  Button3,        spawn,          {.v = drawtermcmd } },

    /* Swap to tag */
	{ ClkTagBar,            0,              Button1,        view,           {0} },
    /* Add tag to this monitor */
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
    /* Send focused window to tag */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    /* Add focused window to tag (now on both) */
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
