//
// Created by Yngeborga on 17.12.2019.
//

#include "prepare.h"

size_t Fsize(std::fstream& streymur)
{
    size_t current = streymur.tellg();

    streymur.seekg(0, std::fstream::end);

    size_t Size = streymur.tellg();

    streymur.seekg(current, std::fstream::beg);

    return Size;
}

size_t CountLines(const char* text, size_t txt_size)
{
    size_t str_count = 1;

    for (size_t i = 0; i < txt_size; i++)
        if (text[i] == '\n')
            str_count++;

    return str_count;
}

char** SplitToLines(char* text, size_t lines_count)
{
    char** lines = new char* [lines_count];

    lines[0] = Strtok(text, "\n");

    for (size_t i = 1; i < lines_count; i++)
        lines[i] = Strtok(nullptr, "\n");

    return lines;
}

size_t Read(const char* name, char** target)
{
    std::fstream input (name, std::fstream::in | std::fstream::binary);

    if (input.rdstate() == std::fstream::failbit)
    {
        *target = nullptr;
        return 0;
    }

    size_t input_size = Fsize(input);

    *target = new char[input_size + 1];
    input.read(*target, input_size);
    *(*target + input_size) = '\0';

    input.close();

    return input_size;
}

char* ReName (char* name, const char* addition)
{
    size_t length = 0 ;
    for(; name[length] != '.' ; length++)
        ;
    *(name + length) = '\0';

    return strcat(name, addition);
}