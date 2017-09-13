/*
 * =====================================================================================
 *
 *       Filename:  remove_character.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/10/15 06:44:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef _REMOVE_CHARACTER_H_
#define _REMOVE_CHARACTER_H_

#include <string>
#include <functional>

enum RemovePlace
{
    LOCATION_FRONT = 1,
    LOCATION_END = 2,
    LOCATION_MIDDLE = 4
};

class RemoveCharacter : public std::unary_function<const std::string&, std::string>
{
    char specialChar_;
    unsigned int location_;
public:
    RemoveCharacter(char specialChar = ' ', unsigned int location = LOCATION_FRONT | LOCATION_END);
    std::string operator()(const std::string &);
    inline void setCharacter(char specialChar) {specialChar_ = specialChar;}
    std::string removeMultiCh(const std::string& originalStr, const std::string& Chs);
};

#endif
