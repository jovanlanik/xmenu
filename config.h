#define OPTION_LIST \
	OPTION(const char *, font, "monospace:size=9", GET_STRING) \
	OPTION(const char *, background_color, "#FFFFFF", GET_STRING) \
	OPTION(const char *, foreground_color, "#000000", GET_STRING) \
	OPTION(const char *, selbackground_color, "#000000", GET_STRING) \
	OPTION(const char *, selforeground_color, "#FFFFFF", GET_STRING) \
	OPTION(const char *, separator_color, "#000000", GET_STRING) \
	OPTION(const char *, border_color, "#000000", GET_STRING) \
	OPTION(int, width_pixels, 124, GET_INT) \
	OPTION(int, height_pixels, 24, GET_INT) \
	OPTION(int, border_pixels, 1, GET_INT) \
	OPTION(int, separator_pixels, 1, GET_INT) \
	OPTION(int, gap_pixels, 0, GET_INT) \
	OPTION(int, alignment, LeftAlignment, GET_ALIGN) \
	OPTION(int, triangle_width, 4, GET_INT) \
	OPTION(int, triangle_height, 8, GET_INT) \
	OPTION(int, iconpadding, 4, GET_INT) \
	OPTION(int, horzpadding, 4, GET_INT)

/*
 * KEYBINDINGS
 *
 * Look at your /usr/include/X11/keysymdef.h  (or the equivalent file
 * in your system) for a list of key symbol constants, and change the
 * macros below accordingly.  All key symbol constants begin with the
 * prefix XK_.
 *
 * For example, to use vim-like key bindings, set KEYSYMLEFT to XK_h,
 * KEYSYMDOWN to XK_j, KEYSYMUP to XK_k, etc.
 *
 * Note that the regular keys like ArrowUp, ArrowDown, Tab, Home, etc
 * will ALWAYS work, so you do not need to set them.
 *
 * If you do not want to set a key binding, keep it with the value of
 * XK_VoidSymbol
 */
#define KSYMFIRST   XK_VoidSymbol       /* select first item */
#define KSYMLAST    XK_VoidSymbol       /* select last item */
#define KSYMUP      XK_VoidSymbol       /* select previous item */
#define KSYMDOWN    XK_VoidSymbol       /* select next item */
#define KSYMLEFT    XK_VoidSymbol       /* close current menu */
#define KSYMRIGHT   XK_VoidSymbol       /* enter selected item */
