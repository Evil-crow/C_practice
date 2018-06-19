#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include "./list.h"

Node *read_from_file(const char *filename);

Node *file_from_list(FILE *fp, Node *file_list);

void write_to_file(const char *filename, Data *data);

#endif