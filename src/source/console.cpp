//   3DS.js
//   © 2015-Present filfat Studios AB
//   Please see the LICENSE for more info!
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"
#include "duktape/duktape.h"

using namespace std;

duk_function_list_entry console_funcs[] = {
	{ "flushBuffers", console_flushBuffers, 5 },
	{ "clear", console_clear, 4 },
	//{ "printAt", console_print, 3 },
	{ "print", console_print, 2 },
	{ "init", console_init, 1 },
	{ NULL, NULL, 0 }
};

int console_flushBuffers(duk_context *ctx) {
	gfxFlushBuffers();
	gfxSwapBuffers();
	gspWaitForVBlank();
	return 0;
}

int console_clear(duk_context *ctx) {
	consoleClear();
	return 0;
}

/*int console_printAt(duk_context *ctx){
	char *tx = (char*)duk_to_string(ctx, 0);
	int x = duk_to_number(ctx, 1);
	int y = duk_to_number(ctx, 2);
	printf("\x1b[%d;%dH%s", x, y, tx);
	return 0;
}*/
int console_print(duk_context *ctx) {
	char *tx = (char*)duk_to_string(ctx, 0);
	printf(tx);
	log("[Console] Print: \"%s\"", tx);
	return 0;
}

int console_init(duk_context *ctx) {
	//TODO: Check if we're using 3DS_UI
	
	string scr = (char*)duk_to_string(ctx, 0);
	if(scr == "bottom")
		consoleInit(GFX_BOTTOM, NULL);
	else
		consoleInit(GFX_TOP, NULL);
	printf("\x1b[0;0H"); //Reset position
	
	return 0;
}

void jsConsoleInit(duk_context *ctx) {
	duk_push_global_object(ctx);
	duk_push_object(ctx);
	duk_put_function_list(ctx, -1, console_funcs);
	duk_put_prop_string(ctx, -2, "Console");
	duk_pop(ctx);
	log("[Init] jsConsoleInit: Done!");
}

void die(string msg){
	gfxExit();
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	
	printf(msg.c_str());
	printf("\n\n\nPress \"A\" to exit...");
	while (aptMainLoop()) {
		hidScanInput();
		u32 kDown = hidKeysDown();
		if (kDown & KEY_A) break;
		
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
}