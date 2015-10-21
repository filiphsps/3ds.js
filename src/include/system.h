//   3DS.js
//   © 2015-Present filfat Studios AB
//   Please see the LICENSE for more info!
#pragma once
#include <3ds.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "duktape/duktape.h"

using namespace std;


void systemInit(duk_context *ctx);

void unicodeToChar(char* dst, u16* src);
void charToUnicode(u16* dst, char* src);