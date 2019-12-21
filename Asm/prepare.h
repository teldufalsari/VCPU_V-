//
// Created by Yngeborga on 17.12.2019.
//

#ifndef ZION_ASSEMBLY_PREPARE_H
#define ZION_ASSEMBLY_PREPARE_H

#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "service.h"
#include <cstring>

#define MAXNAME 1024

size_t Fsize(std::fstream & streymur);

size_t CountLines(const char* text, size_t txt_size);

char** SplitToLines(char* text, size_t lines_count);

size_t Read(const char* name, char** target);

char* ReName (char* name, const char* addition);


#endif //ZION_ASSEMBLY_PREPARE_H
