#pragma once
#include <map>

/** @file */

/**
 * @struct chr
 * @brief structure that is used for example to create vector used to store the frequency of the characters in the encrypted text
*/

struct chr{
    std::map<int, int> mapChrTable;
    int nChrTotal;
};