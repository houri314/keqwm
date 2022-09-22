static const char col_gray1[]       = "#232323";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#b7b7b7";
static const char col_gray4[]       = "#1e1e1e";

static const char col_test[] = "#00ffff";

static const char col_ikoralime_active[]   = "#a2f2a2";
static const char col_ikoralime_inactive[] = "#334f38";

static const char col_purple_inactive[]="#1b1b1b";
static const char col_purple_active[]="#e0e0e0";
static const char col_bar[]="#e5e5e5";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_purple_active, col_purple_inactive, col_purple_inactive },
	[SchemeSel]  = { col_gray4, col_purple_active,  col_purple_active  }
};
static const char *dmenucmd[] = { "dmenu_run","-b", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1,
	"-nf", col_gray3, "-sb", col_bar, "-sf", col_gray4, NULL };
