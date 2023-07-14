#pragma once
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
//Obtido de https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring, pq a stl n tem
// trim de string por default e eu quero trimar a string.
//  
// trim from start
std::string& ltrim(std::string& s);

// trim from end
std::string& rtrim(std::string& s);

// trim from both ends
std::string& trim(std::string& s);