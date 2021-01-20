/*    Include Files    */

#include <iostream>
#include <fstream>

using namespace std;

/*    Class Template    */

class Logger
{

private:
    static Logger *logger;
    fstream fio;

public:
    Logger();

    static Logger *get_instance();

    void file_print(string);

    ~Logger();
};

/*    Static Variable Initialisation    */ 

Logger *Logger::logger = 0;