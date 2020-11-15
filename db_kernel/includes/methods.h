#ifndef _METHODS_H_
#define _METHODS_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <string>



#define F_PATH_DB_KERNEL_DEGUB_INF "../debug/db_kernel_debag_inf.report"
#define F_PATH_MALLOC_OBJECTS_DINF "../debug/memory_alloc_deb_inf.report"


void malloc_deb_inf(const std::string& msg);

template<typename T>
void error_report(const std::string& , T&& );



template<typename T>
void error_report(const std::string& file_name, T&& msg)
{
    std::ofstream ofile(file_name, std::ios::app);
    if (ofile.is_open())
    {
        ofile << msg;
        ofile.close();
    }
    else
    {
        ofile.close();
       // std::cout << "methods : method : error_report | file not found\n";
    }
    
}

#endif // !_METHODS_H_