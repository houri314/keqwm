static const char col_ikoralime_active[]   = "#a2f2a2";
static const char col_ikoralime_inactive[] = "#334f38";
static const char col_ikoralime_bar[]	   = "#28663f";

static const char col_arch_inactive[]="#363076";
static const char col_bar_text[]="#a0a0a0";
static const char col_arch_active[]="#78a1cf";
static const char col_bar[]="#384f8b";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_arch_active, col_arch_inactive, col_arch_inactive },
	[SchemeSel]  = { col_ikoralime_inactive, col_arch_active,  col_arch_active  }
};
