//   3DS.js
//   © 2015-Present filfat Studios AB
//   Please see the LICENSE for more info!

#include <3ds.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "duktape/duktape.h"
#include "console.h"
#include "3dsjs.h"
#include "input.h"
#include "fileIO.h"

using namespace std;


duk_context *ctx = NULL;

int main(int argc, const char** argv) {
	initialize();
	
	//Create HEAP
	ctx = duk_create_heap_default();
	if(!ctx) {
        die("Failed to create a Duktape HEAP!");
        while (1) { }
    }
	
	//Register Helpers
	jsConsoleInit(ctx);
	dsJSInit(ctx);
	inputInit(ctx);
	fileIOInit(ctx);
	
	//Handle module loading
	//TODO: Load 'em from the same directory as the 3dsx file
	duk_eval_string(ctx, "Duktape.modSearch=function(id){return FileIO.read('/' + id + '.js').toString();}");

	//Load "app.js"
	//TODO: Load it from the same directory as the 3dsx file
	if (duk_peval_file(ctx, "/app.js") != 0) {
        die(duk_safe_to_string(ctx, -1));
		while (1) { }
    }
	
	//Destory the HEAP
	duk_destroy_heap(ctx);
	
	deInitialize();
}

void initialize(void){
	srvInit();
	aptInit();
	hidInit();
	fsInit();
	sdmcInit();
	gfxInitDefault();
	//uiInit();
	
	//Hacky way to improve n3ds performance
	aptOpenSession();
	Result ret = APT_SetAppCpuTimeLimit(NULL, 80);
	aptCloseSession();
}

void deInitialize(void){
	//uiExit();
	gfxExit();
	fsExit();
	sdmcExit();
	hidExit();
	aptExit();
	srvExit();
	exit(1);
}