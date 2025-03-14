/*----------------------------------------------------------------------*
 *                            LOGGER HEADER                             *
 *----------------------------------------------------------------------*/

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

using namespace std;

void log_info(const string& message);
void log_warning(const string& message);
void log_error(const string& message);

#endif