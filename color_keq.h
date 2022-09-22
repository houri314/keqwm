static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";


static const char col_ikoralime_active[]   = "#a2f2a2";
static const char col_ikoralime_inactive[] = "#334f38";
static const char col_ikoralime_bar[]	   = "#28663f";

static const char col_purple_inactive[]="#231d3e";
static const char col_bar_text[]="#9966e4";
static const char col_purple_active[]="#cf9fdb";
static const char col_bar[]="#1c2348";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_purple_active, col_purple_inactive, col_purple_inactive },
	[SchemeSel]  = { col_ikoralime_inactive, col_purple_active,  col_purple_active  }
};
static const char *dmenucmd[] = { "dmenu_run","-b", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1,
	"-nf", col_gray3, "-sb", col_bar, "-sf", col_gray4, NULL };
