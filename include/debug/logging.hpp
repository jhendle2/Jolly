#include <string>

#include "debug.hpp"

#define LOGLEVELNONE 0
#define LOGLEVELNOTE 1
#define LOGLEVELERROR 2
#define LOGLEVELWARNING 3
#define LOGLEVELDEBUG 4
extern int LOGLEVEL;

void LOGNOTE(std::string);
void LOGERROR(std::string);
void LOGWARNING(std::string);
void LOGDEBUG(std::string);