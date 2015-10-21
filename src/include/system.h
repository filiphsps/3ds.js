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

//Taken from https://github.com/Rinnegatamante/lpp-3ds/blob/77712c9bbaa86f70aeae664f69ab88e66783bfc7/source/luaSystem.cpp#L54
void unicodeToChar(char* dst, u16* src){
	if(!src || !dst)return;
	while(*src)*(dst++)=(*(src++))&0xFF;
	*dst=0x00;
}
void charToUnicode(u16* dst, char* src){
	if(!src || !dst)return;
	while(*src)*(dst++)=(*src++);
	*dst=0x00;
}