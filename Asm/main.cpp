#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include "service.h"
#include "prepare.h"
#include "build.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "No file name to compile." << std::endl;
        exit(0);
    }

    char name[MAXNAME] = {0};
    strcpy(name, argv[1]);

    char* code = nullptr;

    size_t input_size = Read(name, &code);

    if (code == nullptr)
    {
        std::cout << "File with given name not found." << std::endl;
        exit(0);
    }

    size_t n_lines = CountLines(code, input_size);

    char** lines = SplitToLines(code, n_lines);

    std::vector<Code_Unit> m_code;

    Build build (lines, n_lines);

    size_t errn = build.compile(&m_code);

    switch (errn)
    {
        case 1:
        {
            std::cout << "Compilation failed: an error found." << std::endl;
            break;
        }

        case 0:
        {

            WriteInFile(m_code, ReName(name, ".zcf"));
            std::cout << "Compilation successful." << std::endl;
            break;
        }

        default:
        {
            std::cout << "Compilation failed: " << errn << " errors found." << std::endl;
            break;
        }
    }

    delete lines;
    delete code;

    return 0;
}