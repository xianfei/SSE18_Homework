#pragma once

#include <graphics.h>
#include "rect.h"
#include "tria.h"
#include "Circle.h"
#include "controlEge.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>


void error(int,int);

int readFile(const std::filesystem::path& p);

int newShape(char* s);

void save(const std::filesystem::path& p,std::string& str);
