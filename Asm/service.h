//
// Created by Yngeborga on 17.12.2019.
//

#ifndef ZION_ASSEMBLY_SERVICE_H
#define ZION_ASSEMBLY_SERVICE_H

#define _CRT_SECURE_NO_WARNINGS

#include <cctype>

char* Strtok(char* source, const char* delim);

char* SkipDelims(char* source, const char* delim, int delim_num);

char* SkipLiters(char* source, const char* delim, int delim_num);

char ChrCmp(char subj, const char* test, int test_num);

size_t Strlen(const char* str);

int StrCmp (const char* str1, const char* str2);


#endif //ZION_ASSEMBLY_SERVICE_H