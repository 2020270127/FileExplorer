#pragma once
#include <string>

int strstr(char text[], char pattern[]);
bool kmp(char text[], char pattern[]);

//string type 오버로딩
int strstr(std::string text, std::string pattern);
bool kmp(std::string text, std::string pattern);