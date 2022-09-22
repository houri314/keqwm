/* See LICENSE file for copyright and license details. */
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "exlayouts.h"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|", centeredmaster},	//centered master
	{ "<M<", centeredfloatingmaster},
	{ "(@)", spiral},
	{ "[\\]",dwindle},
	{ "|-|", NULL},	//tatami
};

static bool ikoraIsMute=false;
static const int ikoraVolumeDiff=2;		//volume difference in % when going up/down
static const char* ikoraSoundCardName="Master";	//default sound card name
static void ikoraVolume(const Arg* mode) {
	char commandVolume[50];
	if (mode->i==1) {
		if (ikoraIsMute)
			sprintf(commandVolume,"amixer set %s unmute",ikoraSoundCardName);
		else 
			sprintf(commandVolume,"amixer set %s mute",ikoraSoundCardName);
		ikoraIsMute=!ikoraIsMute;
	}
	else if (mode->i==2)
		sprintf(commandVolume,"amixer set %s %d%%-",ikoraSoundCardName,ikoraVolumeDiff);
	else if (mode->i==3)
		sprintf(commandVolume,"amixer set %s %d%%+",ikoraSoundCardName,ikoraVolumeDiff);
	system(commandVolume);
}
static void ikoraMR(const Arg* arg) {
	XEvent ev;
	Monitor* m=selmon;
	if (!(m->sel&&arg&&arg->v&&m->sel->isfloating))
		return;
	resize(m->sel,m->sel->x+((int*)arg->v)[0],
		m->sel->y+((int*)arg->v)[1],
		m->sel->w+((int*)arg->v)[2],
		m->sel->h+((int*)arg->v)[3],
		True);
	while (XCheckMaskEvent(dpy,EnterWindowMask,&ev));
}

/* appearance */

static const char conf_stext[]="hourin-keqwm";
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int gappx=3;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=10" };
static const char dmenufont[]       = "terminus:size=10";

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{"mpv",NULL,NULL,0,1,-1},
	{NULL,NULL,"Screenshot",0,1,-1},
	{NULL,NULL,"QEMU",0,1,-1},
	{NULL,NULL,"osu!",0,1,-1},
	{NULL,NULL,"Taisei Project v1.3.2",0,1,-1},
//	{"Godot_Engine",NULL,NULL,0,1,-1},
//	{"Godot_Editor",NULL,NULL,0,0,-1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */


/* key definitions */
#define MODKEY Mod1Mask
#define HOURIN Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *vim[]={"alacritty","-e","vim"};

static const char *browser[] = {"firefox",NULL};
static const char *screenshot[] = {"gnome-screenshot",NULL};

#include "color_mono_black.h"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{HOURIN,XK_Return,spawn,{.v=dmenucmd}},
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{HOURIN,XK_b,spawn,{.v=browser}},
	{HOURIN, XK_d, spawn, SHCMD("alacritty -e ranger")},
	{HOURIN|Mod1Mask,XK_d,spawn,SHCMD("alacritty -e vifm")},
	{HOURIN|ShiftMask,XK_d,spawn,SHCMD("nemo")},
	{ HOURIN,XK_Print,spawn,SHCMD("gnome-screenshot")},
	{ NULL,XK_Print,spawn,SHCMD("gnome-screenshot -c")},
	{ HOURIN|ShiftMask,XK_Print,spawn,SHCMD("gnome-screenshot -i")},
	{ HOURIN,XK_k,spawn,SHCMD("setxkbmap us")},
	{ HOURIN|ShiftMask,XK_k,spawn,SHCMD("setxkbmap dvorak")},
	{ HOURIN,XK_1,ikoraVolume,{1} },
	{ HOURIN,			XK_2,	   ikoraVolume,	   {2} },
	{ HOURIN,			XK_3,	   ikoraVolume,	   {3} },
	{ HOURIN|ShiftMask,XK_s,spawn,SHCMD("killall screenkey || screenkey -s small --opacity 0.6 -t 0.4")},
	{ HOURIN,XK_e,spawn,{.v=vim}},
	{ HOURIN|ShiftMask,XK_e,spawn,SHCMD("alacritty -e emacs")},
	{ HOURIN|Mod1Mask,XK_e,spawn,SHCMD("alacritty -e nano")},
	{ HOURIN,XK_v,spawn,SHCMD("alacritty -e alsamixer")},
	{ HOURIN,XK_s,spawn,SHCMD("alacritty -e htop")},
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ HOURIN,XK_x,killclient,{0}},
	{ MODKEY, XK_t, setlayout, {.v = &layouts[0]} },
	{ MODKEY, XK_f, setlayout, {.v = &layouts[1]} },
	{ MODKEY, XK_m, setlayout, {.v = &layouts[2]} },
	{ MODKEY, XK_u, setlayout, {.v = &layouts[3]} },
	{ MODKEY|ShiftMask, XK_u, setlayout, {.v=&layouts[4]}},
	{ HOURIN, XK_f, setlayout, {.v = &layouts[5]}},
	{ HOURIN|ShiftMask, XK_f, setlayout, {.v = &layouts[6]}},
	{HOURIN|ShiftMask,XK_Return,togglefloating,{0}},
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{HOURIN,XK_Down,ikoraMR,{.v=(int[]){0,20,0,0}}},
	{HOURIN,XK_Up,ikoraMR,{.v=(int[]){0,-20,0,0}}},
	{HOURIN,XK_Left,ikoraMR,{.v=(int[]){-20,0,0,0}}},
	{HOURIN,XK_Right,ikoraMR,{.v=(int[]){20,0,0,0}}},

	{HOURIN|ShiftMask,XK_Down,ikoraMR,{.v=(int[]){0,0,0,20}}},
	{HOURIN|ShiftMask,XK_Up,ikoraMR,{.v=(int[]){0,0,0,-20}}},
	{HOURIN|ShiftMask,XK_Right,ikoraMR,{.v=(int[]){0,0,20,0}}},
	{HOURIN|ShiftMask,XK_Left,ikoraMR,{.v=(int[]){0,0,-20,0}}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ClkClientWin,HOURIN,Button1,movemouse,{0}},
	{ClkClientWin,HOURIN|ShiftMask,Button1,resizemouse,{0}},
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkStatusText, 0, Button1, spawn, SHCMD("killall conky || conky")},
};

