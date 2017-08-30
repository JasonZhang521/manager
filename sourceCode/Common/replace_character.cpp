/*
 * =====================================================================================
 *
 *       Filename:  replace_character.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/09/15 10:33:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "replace_character.h"

ReplaceCharacter::ReplaceCharacter(char ch)
:replacedCh_(ch)
{
}

std::string ReplaceCharacter::operator()(const std::string& original, char ch)
{
    std::string str = original;
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == replacedCh_)
        {
            str[i] = ch;
        }
    }
    return str;
}
