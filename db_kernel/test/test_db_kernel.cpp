#include "test_db_kernel.h"
#include "../../interpret/includes/sys_error.h"
#include <iostream>

namespace test_db_kerenel
{



void test_remove(db_ptr db , size_t index)
{
    printRed("\t###########|| TEST_REMOVE ||###########");
    try
    {
        test_print_table(db);

        printBlue("\t****|| REMOVE:    ||****");
        db->remove(index);
        printBlue("\t****|| END_REMOVE ||****");

        test_print_table(db);
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}


void test_insert(db_ptr db , size_t pos, token_t&& val)
{
    printRed("\t###########|| TEST_INSERT ||###########");
    try
    {
        test_print_table(db);
        printBlue("\t****|| INSERT:    ||****");
        db->insert(pos, std::move(val));
        printBlue("\t****|| END_INSERT ||****");
        test_print_table(db);
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}

void test_print_table(db_ptr db)
{
    printRed("\t###########|| PRINT_TABLE ||###########");
    try
    {
        printBlue("\t****|| PRINT_TABLE:    ||****");
        db->print_table();
        printBlue("\t****|| END_PRINT_TABLE ||****");
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}

void test_add(db_ptr db, token_t&& val)
{
    printRed("\t###########|| TEST_ADD ||###########");
    try
    {
        test_print_table(db);
        printBlue("\t****|| ADD:    ||****");
        db->add(std::move(val));
        printBlue("\t****|| END_ADD ||****");
        test_print_table(db);
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}

void test_update(db_ptr db,
                 size_t pos,
                 std::string&& dt,
                 std::string&& ti, 
                 std::string&& ds)
{

    printRed("\t###########|| TEST_UPDATE ||###########");
    try
    {
        test_print_table(db);
        printBlue("\t****|| UPDATE:    ||****");
        db->update_dt_ti_ds(pos, 
                        std::move(dt) , 
                        std::move(ti) , 
                        std::move(ds) );
        printBlue("\t****|| END_UPDATE ||****");
        test_print_table(db);
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}

token_ptr test_get(db_ptr db, size_t pos)
{
    printRed("\t###########|| TEST_GET ||###########");
    try
    {
        return db->get(pos);
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}

void test_create_table(db_ptr db)
{   
    printRed("\t###########|| TEST_CREATE_TABLE ||###########");
    try
    {
        printBlue("\t****|| CREATE_TABLE:    ||****");
        db->create_table();
        printBlue("\t****|| END_CREATE_ATBLE ||****");
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}

void test_drop_table(db_ptr db)
{
    printRed("\t###########|| TEST_DROP_TABLE ||###########");
    try
    {
        printBlue("\t****|| DROP_TABLE:    ||****");
        db->drop_table();
        printBlue("\t****|| END_DROP_TABLE ||****");
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}

void test_open_file(db_ptr db)
{
    printRed("\t###########|| TEST_OPEN_FILE ||###########");
    try
    {
        printBlue("\t****|| OPEN_FILE:    ||****");
        db->open_file();
        printBlue("\t****|| END_OPEN_FILE ||****");
    }
    catch(sys_error& e)
    {
        e.what();
        exit(-1);
    }
}


void printRed(const std::string& msg)
{
    auto m = msg.c_str();
    printf("\033[31m%s\033[0m\n", m);
}

void printBlue(const std::string& msg)
{
    auto m = msg.c_str();
    printf("\033[34m%s\033[0m\n", m);
}

}
