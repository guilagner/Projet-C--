#ifndef AUTOCLASS_H_
#define AUTOCLASS_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <fstream>
#include <map>
#include <utility>

using namespace std;

void dispAttr();
void menu(string className);
void headerfilegenerator(std::string className, std::map<std::string, std::string> attributs);
void sourcefilegenerator(std::string className, std::vector<std::string> attributs);
void mainfilegenerator(std::string className, std::vector<std::string> attributs);
void makefilegenerator(std::string className);
bool validateEntry(const std::string blabla);
bool isValidFileName(const string &fileName);
bool validateEntryAttribut(const std::string blabla);

#endif