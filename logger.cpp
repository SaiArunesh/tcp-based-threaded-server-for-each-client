/*    Include Files    */

#include "logger.h"

/*************************************************************************
    Name: Logger()
    Function: Constructor fn opens the sample.txt 
    Args: nil
    Returns: nil
*************************************************************************/
Logger::Logger()
{
    fio.open("log.txt", ios::trunc | ios::out | ios::in);
}

/*************************************************************************
    Name: get_instance()
    Function: Creates and returns an object in singleton implementation
    Args: nil
    Returns: Logger pointer
*************************************************************************/
Logger *Logger::get_instance()
{
    if (!logger)
        logger = new Logger();

    return logger;
}

/*************************************************************************
    Name: file_print()
    Function: prints the string argument onto sample.txt 
    Args: string to be written on file
    Returns: nil
*************************************************************************/

void Logger::file_print(string line)
{
    fio << line << endl;
}

/*************************************************************************
    Name: ~Logger()
    Function: Desstructor fn closes fstream object 
    Args: nil
    Returns: nil
*************************************************************************/

Logger::~Logger()
{
    fio.close();
}