//============================================================================
// @name        : iconManager.h
// @author      : Thomas Dooms
// @date        : 6/25/19
// @version     : 
// @copyright   : BA1 Informatica - Thomas Dooms - University of Antwerp
// @description : 
//============================================================================


#pragma once

#include <string>
#include <map>

struct IconManager
{
    static std::string getPath(const std::string& description)
    {
        return path + description + ".svg";
    }
    static inline const char* path = "res/icons/";
};
