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

int console_flushBuffers(duk_context *ctx);
int console_clear(duk_context *ctx);
//int console_printAt(duk_context *ctx);
int console_print(duk_context *ctx);
int console_init(duk_context *ctx);
void jsConsoleInit(duk_context *ctx);
void die(string msg);

static duk_function_list_entry console_funcs[] = {
	{ "flushBuffers", console_flushBuffers, 5 },
	{ "clear", console_clear, 4 },
	//{ "printAt", console_print, 3 },
	{ "print", console_print, 2 },
	{ "init", console_init, 1 },
	{ NULL, NULL, 0 }
};