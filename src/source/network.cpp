//   3DS.js
//   © 2015-Present filfat Studios AB
//   Please see the LICENSE for more info!
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "duktape/duktape.h"

using namespace std;


httpcContext context;

int network_isOnline(duk_context *ctx){
	bool status = true;
	Result result = httpcOpenContext(&context, (char*)"http://www.nintendo.com", 0);
	if (result != 0) {
		httpcCloseContext(&context);
		status = false;
	}
	result = httpcBeginRequest(&context);
	if (result != 0) {
		httpcCloseContext(&context);
		status = false;
	}
	httpcCloseContext(&context);
	duk_push_boolean(ctx, status);
	return 1;
}

int network_get(duk_context *ctx) {
	//TODO
	log("Warning: Called Network.get stub");
	return 1;
}

int network_post(duk_context *ctx) {
	//TODO
	log("Warning: Called Network.post stub");
	return 1;
}

void networkInit(duk_context *ctx) {
	duk_push_global_object(ctx);
	duk_idx_t obj_idx = duk_push_object(ctx);
	
	/* Functions */
	duk_push_c_function(ctx, network_post, 0);
	duk_put_prop_string(ctx, obj_idx, "post");
	duk_push_c_function(ctx, network_get, 0);
	duk_put_prop_string(ctx, obj_idx, "get");
	duk_push_c_function(ctx, network_isOnline, 0);
	duk_put_prop_string(ctx, obj_idx, "isOnline");
	
	duk_put_global_string(ctx, "Network");
	duk_pop(ctx);
}