#pragma once
#pragma once
#include <string>
#include <filesystem>

#define KMP 0
#define STRSTR 1

namespace fs = std::filesystem;

int strstr(char text[], char pattern[]);
bool kmp(char text[], char pattern[]);

//string type 오버로딩
int strstr(std::string text, std::string pattern);
bool kmp(std::string text, std::string pattern);

// 하위 폴더 전체 검색
void dfs(const fs::path& p, const std::string& target, int method);
void bfs(const fs::path& p, const std::string& target, int method);
