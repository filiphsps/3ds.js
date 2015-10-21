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
	deInitialize();
	return 0;
}
int system_reboot(duk_context *ctx) {
	aptOpenSession();
	APT_HardwareResetAsync(NULL);
	aptCloseSession();
	return 0;
}

int system_getBatteryLevel(duk_context *ctx) {
	u8 b;
	PTMU_GetBatteryLevel(NULL, &b);
	duk_push_number(ctx, (int)b);
	return 1;
}
int system_getBatteryCharging(duk_context *ctx) {
	u8 b;
	PTMU_GetBatteryChargeState(NULL, &b);
	duk_push_boolean(ctx, (bool)b);
	return 1;
}

int system_getLanguage(duk_context *ctx) {
	u8 x;
	CFGU_GetSystemLanguage(&x);
	duk_push_number(ctx, (int)x);
	return 1;
}
int system_getRegion(duk_context *ctx) {
	u8 x;
	CFGU_SecureInfoGetRegion(&x);
	duk_push_number(ctx, (int)x);
	return 1;
}
int system_getProfile(duk_context *ctx) {
	//Placeholder
	return 1;
}
int system_getFirmwareVersion(duk_context *ctx) {
	duk_push_number(ctx, (int)osGetFirmVersion());
	return 1;
}
int system_getKernelVersion(duk_context *ctx) {
	duk_push_number(ctx, (int)osGetKernelVersion());
	return 1;
}
int system_getModel(duk_context *ctx) {
	u8 x;
	CFGU_GetSystemModel(&x);
	duk_push_number(ctx, (int)x);
	return 1;
}

int system_launch3DSX(duk_context *ctx) {
	//Placeholder
	return 0;
}

//Based on https://github.com/Rinnegatamante/lpp-3ds/blob/master/source/luaSystem.cpp#L1238
int system_launchCartridge(duk_context *ctx) {
	char product_id[16];
	AM_GetTitleProductCode(mediatype_GAMECARD, 0, product_id);
	if (product_id[0] == 'C' and product_id[1] == 'T' and product_id[2] == 'R') {
		u8 buf0[0x300];
		u8 buf1[0x20];
		memset(buf0, 0, 0x300);
		memset(buf1, 0, 0x20);
		aptOpenSession();
		APT_PrepareToDoAppJump(NULL, 0, 0, mediatype_GAMECARD);
		APT_DoAppJump(NULL, 0x300, 0x20, buf0, buf1);
		aptCloseSession();
	} else {
		NS_RebootToTitle(mediatype_GAMECARD,0);
	}
	return 0;
}

int system_getTotalSteps(duk_context *ctx) {
	u32 b;
	PTMU_GetTotalStepCount(NULL, &b);
	duk_push_number(ctx, (int)b);
	return 1;
}
int system_createNotification(duk_context *ctx) {
	char *title = (char*)duk_to_string(ctx, 0),
		 *msg = (char*)duk_to_string(ctx, 1);
	
	u16* t = (u16*)malloc(strlen(title) * sizeof(u16));
	u16* m = (u16*)malloc(strlen(msg) * sizeof(u16));
	newsInit();
	NEWSU_AddNotification(t, strlen(title), m, strlen(msg), NULL, 0, false);
	newsExit();
	return 0;
}
int system_getAppStatus(duk_context *ctx) {
	APP_STATUS status = aptGetStatus();
	duk_push_number(ctx, (int)status);
	return 1;
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
	
	duk_push_c_function(ctx, system_getBatteryLevel, 0);
	duk_put_prop_string(ctx, obj_idx, "getBatteryLevel");
	duk_push_c_function(ctx, system_getBatteryCharging, 0);
	duk_put_prop_string(ctx, obj_idx, "getBatteryCharging");
	
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
	
	duk_push_c_function(ctx, system_launch3DSX, 1);
	duk_put_prop_string(ctx, obj_idx, "launch3DSX");
	duk_push_c_function(ctx, system_launchCartridge, 0);
	duk_put_prop_string(ctx, obj_idx, "launchCartridge");
	
	duk_push_c_function(ctx, system_getTotalSteps, 0);
	duk_put_prop_string(ctx, obj_idx, "getTotalSteps");
	duk_push_c_function(ctx, system_createNotification, 2);
	duk_put_prop_string(ctx, obj_idx, "createNotification");
	duk_push_c_function(ctx, system_getAppStatus, 0);
	duk_put_prop_string(ctx, obj_idx, "getAppStatus");
	
	duk_put_global_string(ctx, "System");
	duk_pop(ctx);
}

//Based on https://github.com/Rinnegatamante/lpp-3ds/blob/77712c9bbaa86f70aeae664f69ab88e66783bfc7/source/luaSystem.cpp#L54
inline void unicodeToChar(char* dst, u16* src){
	if(!src || !dst)return;
	while(*src)*(dst++)=(*(src++))&0xFF;
	*dst=0x00;
}
inline void charToUnicode(u16* dst, char* src){
	if(!src || !dst)return;
	while(*src)*(dst++)=(*src++);
	*dst=0x00;
}