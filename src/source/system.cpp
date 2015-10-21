//   3DS.js
//   © 2015-Present filfat Studios AB
//   Please see the LICENSE for more info!
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "duktape/duktape.h"

using namespace std;

int system_exit(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_reboot(duk_context *ctx) {
	aptOpenSession();
	APT_HardwareResetAsync(NULL);
	aptCloseSession();
	return 0;
}

int system_getAppStatus(duk_context *ctx) {
	APP_STATUS status = aptGetStatus();
	duk_push_number(ctx, (int)status);
	return 1;
}


int system_getBattery(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_getBatteryCharging(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_getEstBatteryLife(duk_context *ctx) {
	//Placeholder
	return 0;
}

int system_getLanguage(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_getRegion(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_getProfile(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_getFirmwareVersion(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_getKernelVersion(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_getModel(duk_context *ctx) {
	//Placeholder
	return 0;
}

int system_launch3DSX(duk_context *ctx) {
	//Placeholder
	return 0;
}
int system_launchCartridge(duk_context *ctx) {
	//Placeholder
	return 0;
}

int system_createNotification(duk_context *ctx) {
	//Placeholder
	return 0;
}

void systemInit(duk_context *ctx) {
	duk_push_global_object(ctx);
	duk_idx_t obj_idx = duk_push_object(ctx);
	
	/* Properties */
	duk_push_number(ctx, __FRAMEWORK_VERSION__);
	duk_put_prop_string(ctx, obj_idx, "version");
	
	/* Functions */
	duk_push_c_function(ctx, system_exit, 0);
	duk_put_prop_string(ctx, obj_idx, "exit");
	duk_push_c_function(ctx, system_reboot, 0);
	duk_put_prop_string(ctx, obj_idx, "reboot");
	
	duk_push_c_function(ctx, system_getBattery, 0);
	duk_put_prop_string(ctx, obj_idx, "getBattery");
	duk_push_c_function(ctx, system_getBatteryCharging, 0);
	duk_put_prop_string(ctx, obj_idx, "getBatteryCharging");
	duk_push_c_function(ctx, system_getEstBatteryLife, 0);
	duk_put_prop_string(ctx, obj_idx, "getEstBatteryLife");
	
	duk_push_c_function(ctx, system_getLanguage, 0);
	duk_put_prop_string(ctx, obj_idx, "getLanguage");
	duk_push_c_function(ctx, system_getRegion, 0);
	duk_put_prop_string(ctx, obj_idx, "getRegion");
	duk_push_c_function(ctx, system_getProfile, 0);
	duk_put_prop_string(ctx, obj_idx, "getProfile");
	duk_push_c_function(ctx, system_getModel, 0);
	duk_put_prop_string(ctx, obj_idx, "getModel");
	duk_push_c_function(ctx, system_getKernelVersion, 0);
	duk_put_prop_string(ctx, obj_idx, "getKernelVersion");
	duk_push_c_function(ctx, system_getFirmwareVersion, 0);
	duk_put_prop_string(ctx, obj_idx, "getFirmwareVersion");
	
	duk_push_c_function(ctx, system_launch3DSX, 0);
	duk_put_prop_string(ctx, obj_idx, "launch3DSX");
	duk_push_c_function(ctx, system_launchCartridge, 0);
	duk_put_prop_string(ctx, obj_idx, "launchCartridge");
	
	duk_push_c_function(ctx, system_createNotification, 0);
	duk_put_prop_string(ctx, obj_idx, "createNotification");
	duk_push_c_function(ctx, system_getAppStatus, 0);
	duk_put_prop_string(ctx, obj_idx, "getAppStatus");
	
	duk_put_global_string(ctx, "System");
	duk_pop(ctx);
}