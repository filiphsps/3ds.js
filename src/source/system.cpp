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


int system_reboot(duk_context *ctx) {
	aptOpenSession();
	APT_HardwareResetAsync(NULL);
	aptCloseSession();
	return 0;
}

int system_appStatus(duk_context *ctx) {
	APP_STATUS status = aptGetStatus();
	duk_push_number(ctx, (int)status);
	return 1;
}

void systemInit(duk_context *ctx) {
	duk_push_global_object(ctx);
	duk_idx_t obj_idx = duk_push_object(ctx);
	
	duk_push_number(ctx, __FRAMEWORK_VERSION__);
	duk_put_prop_string(ctx, obj_idx, "version");
	
	duk_push_c_function(ctx, system_reboot, 0);
	duk_put_prop_string(ctx, obj_idx, "reboot");
	
	duk_push_c_function(ctx, system_appStatus, 0);
	duk_put_prop_string(ctx, obj_idx, "appStatus");
	
	duk_put_global_string(ctx, "System");
	duk_pop(ctx);
}