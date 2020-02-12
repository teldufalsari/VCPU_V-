//
// Created by Yngeborga on 17.12.2019.
//


#include "build.h"

Code_Unit::Code_Unit()
{
    type = 0;
    value = 0;
}

Code_Unit::~Code_Unit() = default;



Build::Build(char** Lines, size_t lines_count)
{
    this->lines = Lines;
    this->err_count = 0;
    this->cur_line = 0;
    this->total_lines = lines_count;
    labels_addr_list = nullptr;
    code = nullptr;
}

Build::~Build()
{
    this->lines = nullptr;
    this->code = nullptr;
    free(labels_addr_list);
}


void Build::translate_str(char *str)
{
    char* word = Strtok(str, DELIMS);

    if ((word == nullptr) || (is_comment(word)))
        return;

    else if (word[0] == ':')
        def_label(word);

    else if (StrCmp(word, "push") == 0)
        write_push();

    else if (StrCmp(word, "pop") == 0)
        write_pop();

    else if (StrCmp(word, "cmp") == 0)
        write_cmp();

    else if (StrCmp(word, "add") == 0)
        write_add();

    else if (StrCmp(word, "sub") == 0)
        write_sub();

    else if (StrCmp(word, "mul") == 0)
        write_mul();

    else if (StrCmp(word, "div") == 0)
        write_div();

    else if (StrCmp(word, "in") == 0)
        write_in();

    else if (StrCmp(word, "out") == 0)
        write_out();

    else if (StrCmp(word, "mov") == 0)
        write_mov();

    else if (StrCmp(word, "jmp") == 0)
        write_jump(JMP);

    else if (StrCmp(word, "je") == 0)
        write_jump(JE);

    else if (StrCmp(word, "ja") == 0)
        write_jump(JA);

    else if (StrCmp(word, "jb") == 0)
        write_jump(JB);

    else if (StrCmp(word, "hlt") == 0)
        write_hlt();

    else
    {
        cast(UCMD, cur_line + 1);
    }

}

void Build::write_pop()
{
    char* arg = Strtok(nullptr, DELIMS);
    if ((arg == nullptr) || (is_comment(arg)))
    {
        write(CMD, POP0);
        return;
    }

    write(CMD, POP1);

    char reg_num = get_reg_num(arg);

    if (reg_num != NOTREG)
        write(REG, reg_num);

    else if (is_num(arg))
        write(INT, (short int) strtol(arg, nullptr, 10));

    else
        cast(EXARG, cur_line + 1);

    check_str();
}

inline void Build::write(char type, short int value)
{
    Code_Unit tpl;
    tpl.type = type;
    tpl.value = value;
    code->push_back(tpl);
}

void Build::write_push()
{
    write(CMD, PUSH1);

    char* arg = Strtok(nullptr, DELIMS);

    if ((arg == nullptr) || (is_comment(arg)))
    {
        cast(EXARG, cur_line + 1);
        return;
    }

    char reg_num = get_reg_num(arg);

    if (reg_num != NOTREG)
        write(REG, reg_num);
    else if (is_num(arg))
        write(INT, (short int) strtol(arg, nullptr, 10));
    else
        cast(EXARG, cur_line + 1);

    check_str();
}

void Build::check_str()
{
    char* remainder = Strtok(nullptr, DELIMS);

    if ((remainder != nullptr) && (!is_comment(remainder)))
        cast(EXNL, cur_line + 1);
}

void Build::write_mov()
{
    write(CMD, MOV2);

    char* arg1 = Strtok(nullptr, DELIMS);

    char reg1_num = get_reg_num(arg1);

    if (reg1_num == NOTREG)
    {
        cast(EXREG, cur_line + 1);
        return;
    }

    write(REG, reg1_num);

    char* arg2 = Strtok(nullptr, DELIMS);

    char reg2_num = get_reg_num(arg2);

    if (reg2_num != NOTREG)
        write(REG, reg2_num);

    else if (is_num(arg2))
        write(INT, (short int) strtol(arg2, nullptr, 10));

    else
        cast(EXARG, cur_line + 1);

    check_str();
}

void Build::write_cmp()
{
    write(CMD, CMP2);

    char* arg1 = Strtok(nullptr, DELIMS);
    char* arg2 = Strtok(nullptr, DELIMS);

    char reg1_num = get_reg_num(arg1);

    if (reg1_num != NOTREG)
        write(REG, reg1_num);

    else if (is_num(arg2))
        write(INT, (short int) strtol(arg2, nullptr, 10));

    else
    {
        cast(EXARG, cur_line + 1);
        return;
    }

    char reg2_num = get_reg_num(arg2);

    if (reg2_num != NOTREG)
        write(REG, reg2_num);

    else if (is_num(arg2))
        write(INT, (short int) strtol(arg2, nullptr, 10));

    else
        cast(EXARG, cur_line + 1);

    check_str();
}

void Build::write_add()
{
    write(CMD, ADD0);
    check_str();
}

void Build::write_sub()
{
    write(CMD, SUB0);
    check_str();
}

void Build::write_div()
{
    write(CMD, DIV0);
    check_str();
}

void Build::write_mul()
{
    write(CMD, MUL0);
    check_str();
}

void Build::write_in()
{
    char* arg = Strtok(nullptr, DELIMS);
    if ((arg == nullptr) || (is_comment(arg)))
    {
        write(CMD, IN0);
        return;
    }

    write(CMD, IN1);

    char reg_num = get_reg_num(arg);

    if (reg_num != NOTREG)
    {
        write(REG, reg_num);
        return;
    }

    if (is_num(arg))
        write(INT, (short) strtol(arg, nullptr, 10));
    else
        cast(EXARG, cur_line + 1);

    check_str();
}

void Build::write_out()
{
    char* arg = Strtok(nullptr, DELIMS);
    if ((arg == nullptr) || (is_comment(arg)))
    {
        write(CMD, OUT0);
        return;
    }

    write(CMD, OUT1);

    char reg_num = get_reg_num(arg);

    if (reg_num != NOTREG)
    {
        write(REG, reg_num);
        return;
    }

    if (is_num(arg))
        write(INT, (short) strtol(arg, nullptr, 10));
    else
        cast(EXARG, cur_line + 1);

    check_str();
}

void Build::write_jump(short int jump_cond)
{
    write(CMD, jump_cond);

    char* arg = Strtok(nullptr, DELIMS);

    if ((arg == nullptr) || (is_comment(arg)))
    {
        cast(EXARG, cur_line + 1);
        return;
    }

    std::string lbl_name (arg);

    auto lbl = labels_dic.find(lbl_name);

    if (lbl == labels_dic.end())
    {
        cast(ULBL, cur_line + 1);
        return;
    }

    write(LBL, lbl->second);         //I know it's implementation-defined, but my cpu recognises LBL arguments as unsigned, so it's ok to be gay.

    check_str();
}

void Build::write_hlt()
{
    write(CMD, HLT);
    check_str();
}

void Build::def_label(char* lbl_string)
{
    std::string name (lbl_string + 1);

    labels_addr_list[labels_dic[name]] = code->size() * 3;
}

char Build::get_reg_num(const char *str)
{
    if (StrCmp(str, "ax") == 0)
        return 1;

    if (StrCmp(str, "bx") == 0)
        return 2;

    if (StrCmp(str, "cx") == 0)
        return 3;

    if (StrCmp(str, "dx") == 0)
        return 4;

    return NOTREG;
}

char Build::is_num(const char *str)
{
    if (str == nullptr)
        return 0;

    int length = Strlen(str);

    if (length == 0)
        return 0;

    for (int j = 0; j < length; j++)
        if (!isdigit(str[j]) && (str[j] != '-'))
            return 0;

    return 1;
}

char Build::is_comment(const char *str)
{
    if (str == nullptr)
        return 0;

    if ((str[0] == '/') && (str[1] == '/'))
        return 1;

    return 0;
}

void Build::cast(char err, size_t line)
{
    switch (err)
    {
        case 0:
            return;

        case UCMD:
        {
            fprintf(stderr, "Error in line %zu: unknown command.\n", line);
            break;
        }

        case EXARG:
        {
            fprintf(stderr, "Error in line %zu: expected argument, got nonsense.\n", line);
            break;
        }

        case EXREG:
        {
            fprintf(stderr, "Error in line %zu: expected register as an argument.\n", line);
            break;
        }

        case EXNL:
        {
            fprintf(stderr, "Error in line %zu: expected new line.\n", line);
            break;
        }

        case EXLBL:
        {
            fprintf(stderr, "Error in line %zu: expected label name after \":\".\n", line);
            return;
        }

        case ULBL:
        {
            fprintf(stderr, "Error in line %zu: jump to undefined label.\n", line);
            break;
        }

        case DLBL:
        {
            fprintf(stderr, "Error in line %zu: duplicated label.\n", line);
            break;
        }

        default:
        {
            fprintf(stderr, "Error in line %zu: non-code symbols.\n", line);
            break;
        }
    }

    err_count++;
}

size_t Build::compile(std::vector<Code_Unit> *target)
{
    this->code = target;

    fill_dictionary();

    for (cur_line = 0; cur_line < total_lines; cur_line++)
        translate_str(lines[cur_line]);

    link_jumps();

    return err_count;
}

void Build::fill_dictionary()
{
    char* word = nullptr;

    for (size_t i = 0; i < total_lines; i++)
        if (*(word = SkipDelims(lines[i], DELIMS, Strlen(DELIMS))) == ':')
        {
            char state = add_label(word);
            cast(state, i + 1);
        }

    labels_addr_list = (unsigned short int*) std::calloc(labels_dic.size(), sizeof(unsigned short int));
}

char Build::add_label(char *string)
{
    char* name_tok = Strtok(string + 1, DELIMS);
    if ((name_tok == nullptr) || (is_comment(name_tok)))
        return EXLBL;

    std::string name(name_tok);

    auto new_label = labels_dic.find(name);

    if (new_label != labels_dic.end())
        return DLBL;

    labels_dic[name] = labels_dic.size();

    return 0;
}

void Build::link_jumps()
{
    for (auto& unit: *code) //add appropriate loop here!!
    {
        if (unit.type == LBL)
        {
            (unit.value = labels_addr_list[unit.value]);     //I know it's implementation-defined, but my cpu recognises LBL arguments as unsigned, so it's ok.
        }
    }
}

void WriteInFile(std::vector<Code_Unit> &code, const char* filename)
{
    std::fstream of (filename, std::fstream::out | std::fstream::binary);

    int tmp_value = 0;

    for (auto& unit : code)
    {
        of.put(unit.type);

        tmp_value = unit.value;

        of.put(((char*) &tmp_value)[0]);
        of.put(((char*) &tmp_value)[1]);
    }

    of.close();
}