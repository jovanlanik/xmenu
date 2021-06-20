#include "config.h"

#define XMENU_STR(x) #x
#define XMENU_GETNAME(x) XMENU_STR(x)
#define PROGNAME XMENU_GETNAME(NAME)

/* Actions for the main loop */
#define ACTION_NOP    0
#define ACTION_CLEAR  1<<0      /* clear text */
#define ACTION_SELECT 1<<1      /* select item */
#define ACTION_MAP    1<<2      /* remap menu windows */
#define ACTION_DRAW   1<<3      /* redraw menu windows */
#define ACTION_WARP   1<<4      /* warp the pointer */

/* enum for keyboard menu navigation */
enum { ITEMPREV, ITEMNEXT, ITEMFIRST, ITEMLAST };

/* enum for text alignment */
enum {LeftAlignment, CenterAlignment, RightAlignment};

/* macros */
#define LEN(x)              (sizeof (x) / sizeof (x[0]))
#define MAX(x,y)            ((x)>(y)?(x):(y))
#define MIN(x,y)            ((x)<(y)?(x):(y))
#define BETWEEN(x, a, b)    ((a) <= (x) && (x) <= (b))
#define GETNUM(n, s) { \
	unsigned long __TMP__; \
	if ((__TMP__ = strtoul((s), NULL, 10)) < INT_MAX) \
		(n) = __TMP__; \
	}

/* color enum */
enum {ColorFG, ColorBG, ColorLast};

/* EWMH atoms */
enum {NetWMName, NetWMWindowType, NetWMWindowTypePopupMenu, NetLast};

/* configuration structure */
#define OPTION(type, name, def, fn) type name;
struct Config {
	/*
	const char *font;
	const char *background_color;
	const char *foreground_color;
	const char *selbackground_color;
	const char *selforeground_color;
	const char *separator_color;
	const char *border_color;
	int width_pixels;
	int height_pixels;
	int border_pixels;
	int separator_pixels;
	int gap_pixels;
	int triangle_width;
	int triangle_height;
	int iconpadding;
	int horzpadding;
	int alignment;
	*/
	OPTION_LIST

	// the values below are set by options 
	int monitor;
	int posx, posy;

	// the value below is computed by xmenu
	int iconsize;
};
#undef OPTION

#define OPTION(type, name, def, fn) .name = def,
static struct Config config = {
	/*
	.font = "monospace:size=9",

	.background_color = "#FFFFFF",
	.foreground_color = "#000000",
	.selbackground_color = "#000000",
	.selforeground_color = "#FFFFFF",
	.separator_color = "#000000",
	.border_color = "#000000",

	.width_pixels = 124,
	.height_pixels = 24, 
	.border_pixels = 1,
	.separator_pixels = 1,
	.gap_pixels = 0,

	.alignment = LeftAlignment,

	.triangle_width = 4,
	.triangle_height = 8,

	.iconpadding = 4,

	.horzpadding = 4,
	*/
	OPTION_LIST
};
#undef OPTION

/* draw context structure */
struct DC {
	XftColor normal[ColorLast];
	XftColor selected[ColorLast];
	XftColor border;
	XftColor separator;

	GC gc;

	FcPattern *pattern;
	XftFont **fonts;
	size_t nfonts;
};

/* menu item structure */
struct Item {
	char *label;            /* string to be drawed on menu */
	char *output;           /* string to be outputed when item is clicked */
	char *file;             /* filename of the icon */
	int y;                  /* item y position relative to menu */
	int h;                  /* item height */
	int textw;              /* text width */
	struct Item *prev;      /* previous item */
	struct Item *next;      /* next item */
	struct Menu *submenu;   /* submenu spawned by clicking on item */
	Drawable sel, unsel;    /* pixmap for selected and unselected item */
	Imlib_Image icon;
};

/* monitor geometry structure */
struct Monitor {
	int x, y, w, h;         /* monitor geometry */
};

/* menu structure */
struct Menu {
	struct Menu *parent;    /* parent menu */
	struct Item *caller;    /* item that spawned the menu */
	struct Item *list;      /* list of items contained by the menu */
	struct Item *selected;  /* item currently selected in the menu */
	int x, y, w, h;         /* menu geometry */
	int hasicon;            /* whether the menu has item with icons */
	int drawn;              /* whether the menu was already drawn */
	int maxtextw;           /* maximum text width */
	unsigned level;         /* menu level relative to root */
	Window win;             /* menu window to map on the screen */
	XIC xic;                /* input context */
};
