//
// wip_conf
// Copyright (c) 2021 Jovan Lanik
//

char *wip_getConfPath(void);
void wip_initConf(void);
void wip_termConf(void);

#define WIP_CONF_TYPE_LIST \
	CONF_TYPE(const char *, Str, string, CONFIG_TYPE_STRING, NULL) \
	CONF_TYPE(int, Int, int, CONFIG_TYPE_INT, -1)

#define CONF_TYPE(type, name, lib, mac, def) \
type wip_getConf##name(const char *p);
WIP_CONF_TYPE_LIST
#undef CONF_TYPE

