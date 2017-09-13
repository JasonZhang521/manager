/*
 * =====================================================================================
 *
 *       Filename:  replace_character.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/09/15 10:27:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef _REPLACE_CHARACTER_H_
#define _REPLACE_CHARACTER_H_
#include <string>
class ReplaceCharacter : public std::binary_function<const std::string&, char, std::string >
{
    char replacedCh_;
public:
    ReplaceCharacter(char ch = ' ');
    std::string operator()(const std::string&, char);
    void setCharacter(char replaceCh) {replacedCh_ = replaceCh;};
};

#endif
