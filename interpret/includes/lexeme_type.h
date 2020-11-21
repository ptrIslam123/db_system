#ifndef _LEXEME_TYPE_H
#define _LEXEME_TYPE_H


enum class LEXEME_TYPE 
{
    /* SYS_FUNC */
    GET,
    INSERT,
    ADD,
    CREATE_TABLE,
    DROP_TABLE,
    REMOVE,
    PRINT,
    UPDATE,
    SUM,
    HELP,

    /* TOKENS */
    WORD,
    DATA,
    TRIGGER,

    /* OPERATORS */
    LESS,
    EQ,
    TWO_POINT,
    L_SHAPE_BRACKET,    // {
    R_SHAPE_BRACKET,    // }
    L_BRACKET,  // (
    R_BRACKET,  // )

    /* ARGS_TYPE */
    DT,
    TI,
    DS,
    DT_TI,
    DT_DS,
    TI_DS,
    DT_TI_DS,

    VOID

};

#endif // !_LEXEME_TYPE_H
