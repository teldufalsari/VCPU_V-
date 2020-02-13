//
// Created by Yngeborga on 17.12.2019.
//
#define _CRT_SECURE_NO_WARNINGS

#ifndef ZION_ASSEMBLY_BUILD_H
#define ZION_ASSEMBLY_BUILD_H

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include "service.h"

enum Exceptions {NOT_STK = -5, NOT_MEM = -4, NOARG = -3, NOTADDR = -2, NOTREG = -1, UCMD = 1, EXARG, EXNL, EXREG, EXLBL, ULBL, DLBL, UFUNC, DFUNC, EXFUNC};

enum Commands {PUSH1 = 1, POP0, POP1,  MOV2, CMP2, ADD0, SUB0, MUL0, DIV0, IN0, IN1, OUT0, OUT1, JA, JB, JE, JMP, HLT, CALL, RET};

enum Unit_types {CMD = 1, REG, INT, LBL, REG_MEM, INT_MEM, FUNC, REG_STK, INT_STK};

const char DELIMS[] = " \t\r\n";

struct Code_Unit
{
    char type;
    short int value;

    Code_Unit();
    ~Code_Unit();
};

class Build
{
private:
    char** lines;
    size_t total_lines;
    size_t cur_line;
    size_t err_count;
    std::vector <Code_Unit> *code;

    std::map <std::string, unsigned short> labels_dic;
    unsigned short int* labels_addr_list;

    std::map <std::string, unsigned short> functions_dic;
    unsigned short int* functions_addr_list;

    inline void write_push();
    inline void write_pop();
    inline void check_str();
    inline void write_cmp();
    inline void write_in();
    inline void write_out();
    inline void write_add();
    inline void write_sub();
    inline void write_mul();
    inline void write_div();
    inline void write_mov();
    inline void write_jump(short int jump_cond);
    inline void write_hlt();
    inline void write_call();
    inline void write_ret();

    inline void def_label(char *lbl_string);
    inline void def_function(char *string);

    inline void write(char type, short value);
    void translate_str(char* str);
    char add_label (char* string);
    char add_function(char* string);
    void fill_dictionary();
    void link_jumps();


    void cast(char err, size_t line);

    char get_reg_num(const char* str);
    char is_num(const char* str);
    char is_comment(const char* str);
    char get_addr(const char* str, unsigned short* addr_ptr);
    char get_value(const char* str, short* val_ptr);
    char is_mem(const char* str);
    char is_stk(const char* str);


public:
    Build() = delete;
    Build(char** lines, size_t lines_count);
    ~Build();
    size_t compile (std::vector <Code_Unit> *target);
};

void WriteInFile(std::vector <Code_Unit> &code, const char* filename);

#endif //ZION_ASSEMBLY_BUILD_H
