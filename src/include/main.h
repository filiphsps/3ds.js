//   3DS.js
//   © 2015-Present filfat Studios AB
//   Please see the LICENSE for more info!
#pragma once

#define __FRAMEWORK_VERSION__ 10000

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize(void);
void deInitialize(void);
int logInit();
int logExit();
int log(const char *text, ...);

static std::string execPath,
			  scriptPath;