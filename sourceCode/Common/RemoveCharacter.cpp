/*
 * =====================================================================================
 *
 *       Filename:  remove_character.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/10/15 07:01:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "RemoveCharacter.h"

RemoveCharacter::RemoveCharacter(char specialChar, unsigned int location)
:specialChar_(specialChar)
,location_(location)
{
}
/*
 * Input: a string.
 * Output: a string that reduced the special character by request.
 * */
std::string RemoveCharacter::operator()(const std::string & str) 
{
    std::string ret;
    size_t begin = 0;
    size_t end = str.size() - 1;
    /*
     * Remove the special character in the front 
     * */
    if (location_ & LOCATION_FRONT)
    {
        while(begin <= end)
        {
            if (str[begin] == specialChar_)
            {
                ++begin;
            }
            else
            {
                break;
            }
        }
    }
    
    /*
     * Remove the special character in the end 
     * */
    if (location_ & LOCATION_END)
    {
        while(begin <= end)
        {
            if (str[end] == specialChar_)
            {
                --end;
            }
            else
            {
                break;
            }
        }
    }
    
    /*
     * str[begin] == specialChar_ means:
     * (1) begin = end.
     * (2) all the character are specialChar_.
     * */
    if (str[begin] != specialChar_)
    {
        ret = str.substr(begin, end - begin + 1);
    }
    /*
     * Remove the special character in the middle 
     * */
    if (location_ & LOCATION_MIDDLE)
    {
       size_t pos = 0;
       for (size_t i = begin; i <= end; ++i)
       {
           if (str[i] != specialChar_)
           {
               ret[pos++] = str[i];
           }
       }
       /*
        * Here, the pos value is equal the number os no- specialChar 
        * */
       ret = ret.substr(0, pos);
    }
    return ret;
}

std::string RemoveCharacter::removeMultiCh(const std::string& originalStr, const std::string& Chs)
{
    std::string result = originalStr;
    for (auto ch : Chs)
    {
        setCharacter(ch);
        result = operator()(result);
    }

    return result;
}
