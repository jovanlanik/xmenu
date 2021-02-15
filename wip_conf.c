//
// wip_conf
// Copyright (c) 2021 Jovan Lanik
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <libconfig.h>

#include "wip_fn.h"
#include "wip_conf.h"

config_t wip_globalConf;

#define CONF_TYPE(type, name, lib, mac, def) \
type wip_getConf##name(const char *path) { \
	type x = def; \
	config_lookup_##lib(&wip_globalConf, path, &x); \
	return x; \
}
WIP_CONF_TYPE_LIST
#undef CONF_TYPE

char *wip_getConfPath(void) {
	char *config = getenv("XDG_CONFIG_HOME");
	if(config != NULL && *config != '\0') {
		char *c = wip_alloc(strlen(config)+1);
		if(!c) return NULL;
		strcpy(c, config);
		config = c;

	}
	else {
		config = getenv("HOME");
		if(config == NULL || *config == '\0') {
			struct passwd *pwd = getpwuid(getuid());
			if(!pwd) {
				return NULL;
			}
			char *c = wip_alloc(strlen(pwd->pw_dir)+1);
			if(!c) return NULL;
			strcpy(c, pwd->pw_dir);
			config = c;
		}
		else {
			char *c = wip_alloc(strlen(config)+1);
			if(!c) return NULL;
			strcpy(c, config);
			config = c;
		}
		char dirname[] = "/.config";
		int ret;
		char *c = wip_realloc(config, strlen(config)+sizeof(dirname), &ret);
		if(!ret) return NULL;
		strcat(c, dirname);
		config = c;
	}
#define STR(x) #x
#define GETNAME(x) STR(x)
	char filename[] = "/"GETNAME(NAME)".conf";
#undef STR
#undef GETNAME
	int ret;
	char *c = wip_realloc(config, strlen(config)+sizeof(filename), &ret);
	if(!ret) return NULL;
	if(!c) exit(1);
	strcat(c, filename);
	config = c;
	return config;
}

void wip_initConf(void) {
	config_init(&wip_globalConf);
	char *confPath = wip_getConfPath();
	FILE *confFile = wip_openFile(confPath);
	free(confPath);
	int ret;
	if(!confFile) {
		return;
	}
	else ret = config_read(&wip_globalConf, confFile);
	if(!ret) {
		fprintf(stderr, "%s: Config error:\n%s:%d - %s\n", __func__,
			config_error_file(&wip_globalConf),
			config_error_line(&wip_globalConf),
			config_error_text(&wip_globalConf)
		);
		config_destroy(&wip_globalConf);
		return;
	}
	return;
}

void wip_termConf(void) {
	config_destroy(&wip_globalConf);
	return;
}

