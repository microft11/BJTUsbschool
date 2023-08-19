#pragma once
#include "Lab3_data.h"
void read_conf(CONF* c);
void recourcount(CONF* c);
int checkFilePath(char* path);
void splitFilePath(CONF* conf, char* path);
void recourpath(CONF* c);
void function(CONF* c);
int is_number(char* str);