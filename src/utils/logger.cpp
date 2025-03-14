/*----------------------------------------------------------------------*
 *                             LOGGER                                   *
 *----------------------------------------------------------------------*/

/*-----------------------------------------------------------------------

    Manages logging and logging levels.

------------------------------------------------------------------------*/

#include <iostream>
#include "../inc/utils/logger.h"

void log_info(const std::string& message)
{
    std::cout << "[INFO] " << message << std::endl;
}

void log_warning(const std::string& message)
{
    std::cout << "[WARNING] " << message << std::endl;
}

void log_error(const std::string& message)
{
    std::cout << "[ERROR] " << message << std::endl;
}