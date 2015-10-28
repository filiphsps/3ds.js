//   3DS.js
//   © 2015-Present filfat Studios AB
//   Please see the LICENSE for more info!

//Comment the next line to disable logging (it will result in a speedup)
#define LOGGING

#include <3ds.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "duktape/duktape.h"
#include "console.h"
#include "system.h"
#include "input.h"
#include "fileIO.h"
#include "network.h"

using namespace std;


duk_context *ctx = NULL;

int main(int argc, const char** argv) {
	
	//Based on https://github.com/Rinnegatamante/lpp-3ds/blob/master/source/main.cpp#L86
	if (argc > 0) {
		char path[256];
		int latest_slash = 0,
			i=5;
		while (argv[0][i]  != '\0'){
			if (argv[0][i] == '/') latest_slash = i;
			i++;
		}
		strcpy(path,&argv[0][5]);
		path[latest_slash-5] = 0;
		
		execPath = string(path) + "/";
		scriptPath = execPath + "app.js";
	} else {
		execPath = "/";
		scriptPath = execPath + "app.js";
	}
	//-----------
	initialize();
	
	//Create HEAP
	log("[JavaScript] Heap: Creating...");
	ctx = duk_create_heap_default();
	if(!ctx) {
		log("[ERROR] Failed to create a Duktape HEAP!");
        die("Failed to create a Duktape HEAP!");
        while (1) { }
    }
	log("[JavaScript] Heap: Done!");
	
	//Register Helpers
	jsConsoleInit(ctx);
	systemInit(ctx);
	inputInit(ctx);
	fileIOInit(ctx);
	networkInit(ctx);
		
	//Handle module loading
	//TODO: Load 'em from the same directory as the 3dsx file
	duk_eval_string(ctx, "Duktape.modSearch=function(id){return FileIO.read((id.charAt(0) == '/' ? '' : FileIO.getExecPath()) + id + '.js').toString();}");

	//Load "app.js"
	log("[JavaScript] Runtime: Running %s...", scriptPath.c_str());
	if (duk_peval_file(ctx, (char*)scriptPath.c_str()) != 0) {
		log("[ERROR] %s", duk_safe_to_string(ctx, -1));
        die(duk_safe_to_string(ctx, -1));
    }
	
	//Destory the HEAP
	duk_destroy_heap(ctx);
	log("[JavaScript] Heap: Destroyed!");
	
	deInitialize();
}

void initialize(void) {
	srvInit();
	aptInit();
	ptmInit();
	amInit();
	nsInit();
	initCfgu();
	hidInit();
	fsInit();
	sdmcInit();
	gfxInitDefault();
	httpcInit();
	logInit();
	osSetSpeedupEnable(true);
}

void deInitialize(void) {
	logExit();
	httpcExit();
	gfxExit();
	fsExit();
	sdmcExit();
	hidExit();
	exitCfgu();
	nsExit();
	amExit();
	ptmExit();
	aptExit();
	srvExit();
	exit(1);
}

#ifdef LOGGING
static FILE * fdebug = NULL;
#endif

int logInit() {
#ifdef LOGGING
	char logPath[256];
	sprintf(logPath, "%sdebug.log", execPath.c_str());
   	fdebug = fopen(/*logPath*/"/3dsjs.log", "wb");
	if (fdebug) {
		log("3ds.js v%i", __FRAMEWORK_VERSION__);
		log("Copyright (c) 2015-Present filfat Studios AB & Filiph Sandström");
		log("===============================================================");
		log("[JavaScript] Runtime: execPath is \"%s\"", execPath.c_str());
		return 0;
	}
#endif
   	return -1;
}
int logExit() {
#ifdef LOGGING
	if (fdebug) fclose (fdebug);
   	fdebug = NULL;
	return 0;
#endif
   	return -1;
}
int log(const char *text, ...) {
#ifdef LOGGING
	if (text == NULL) return -1;
	va_list argp;
	va_start(argp, text);
	if (fdebug) {
		vfprintf(fdebug, text, argp);
		fprintf(fdebug, "\r\n");
		fflush(fdebug);
	}
	va_end(argp);
	return 0;
#endif
	return -1;
}
