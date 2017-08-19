//
// Created by itai on 6/30/17.
//

#ifndef DNS_UTIL_H
#define DNS_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include "logger.hpp"

#define DIE(MSG) {\
    Logger& logger = Logger::instance();\
    logger.error(MSG);\
    exit(1);\
}

#endif //DNS_UTIL_H
