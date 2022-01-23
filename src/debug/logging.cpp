#include <iostream>

#include "logging.hpp"
#include "color_text.hpp"

#define LOGHEADERLESS false

int LOGLEVEL = LOGLEVELWARNING;

void LOGNOTE(std::string note){
    if(LOGLEVEL>=LOGLEVELNOTE){
        if(LOGHEADERLESS) std::cout<<_fgBrightMagenta<<note<<_reset"\n";
        else std::cout<<_fgBrightMagenta<<"[ NOTE :>] "<<_reset<<note<<"\n";
    }
}
void LOGERROR(std::string error){
    if(LOGLEVEL>=LOGLEVELERROR){
        if(LOGHEADERLESS) std::cout<<_fgBrightRed<<error<<_reset"\n";
        else std::cout<<_fgBrightRed<<"[ ERROR :>] "<<_reset<<error<<"\n";
    }
}
void LOGWARNING(std::string warning){
    if(LOGLEVEL>=LOGLEVELWARNING){
        if(LOGHEADERLESS) std::cout<<_fgBrightGreen<<warning<<_reset"\n";
        else std::cout<<_fgBrightGreen<<"[ WARNING :>] "<<_reset<<warning<<"\n";
    }
}
void LOGDEBUG(std::string debug){
    if(LOGLEVEL>=LOGLEVELDEBUG){
        if(LOGHEADERLESS) std::cout<<_fgBrightCyan<<debug<<_reset"\n";
        else std::cout<<_fgBrightCyan<<"[ DEBUG :>] "<<_reset<<debug<<"\n";
    }
}