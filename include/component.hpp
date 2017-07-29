/**
 * This abstract class defines a base component of the server.
 * Every component must have access to the logger.
 *
 * @author Itai Spiegel
**/


#ifndef COMPONENT_H
#define COMPONENT_H

#include "logger.hpp"

class Component {
    public:
        /**
         * Debug a message with the logger.
        **/
        void debug(const std::string& msg) const;

    private:
        /**
        * Access to the single logger instance.
        **/
        Logger& logger() const;
};

#endif
