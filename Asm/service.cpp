//
// Created by Yngeborga on 17.12.2019.
//

#include "service.h"

char* Strtok(char* source, const char* delim)
{
    static char* cursor;

    if (source != nullptr)
        cursor = source;

    if (cursor == nullptr)
        return nullptr;

    char* token_head = nullptr;
    int delim_num = Strlen(delim);

    token_head = SkipDelims(cursor, delim, delim_num);

    if (*token_head == '\0')
        return nullptr;

    cursor = SkipLiters(token_head, delim, delim_num);

    if (*cursor != '\0')
        *(cursor++) = '\0';

    return token_head;
}

char* SkipDelims(char* source, const char* delim, int delim_num)
{
    unsigned long long i = 0;

    for (i = 0; (ChrCmp(source[i], delim, delim_num)) && (source[i] != '\0'); i++)
        ;

    return source + i;
}

char* SkipLiters(char* source, const char* delim, int delim_num)
{
    unsigned long long i = 0;

    for (i = 0; (!ChrCmp(source[i], delim, delim_num)) && (source[i] != '\0'); i++)
        ;

    return source + i;
}

char ChrCmp(char subj, const char* test, int test_num)
{
    for (int i = 0; i < test_num; i++)
        if (subj == test[i])
            return 1;

    return 0;
}

size_t Strlen(const char* str)
{
    if (str == nullptr)
        return 0;

    size_t i = 0;

    while (*(str + i) != '\0')
        i++;

    return i;
}

int StrCmp (const char* str1, const char* str2)
{
    size_t len1 = Strlen(str1);
    size_t len2 = Strlen(str2);

    if (len1 - len2)
        return ((int) (len1 - len2));

    for (size_t i = 0; i < len1; i++)
        if (str1[i] - str2[i])
            return (str1[i] - str2[i]);

    return 0;
}