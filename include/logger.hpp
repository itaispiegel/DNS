/**
 * This is a singleton class used for logging messages.
 * For now this logs everything to STDOUT, but later this will change and log everything to a file.
 * @author Itai Spiegel
**/

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger {
    public:

        /**
         * Static method used for getting the single logger instance.
        **/
        static Logger& instance();

        void debug(const std::string& msg);

    private:
        Logger() = default;
        static Logger* s_instance;
};

#endif
