#ifndef __INTERFACE_INFO_H__
#define __INTERFACE_INFO_H__

#include "class_file.hpp"

struct Class_File;

typedef struct Interface_Info{
	u2 interface_table;
} Interface_Info;

/* INTERFACE_INFO */
void read_interface_info(FILE *file, Class_File *class_file);
Interface_Info get_interface_info(FILE *file, Class_File *class_file, Interface_Info interface_info);

#endif
