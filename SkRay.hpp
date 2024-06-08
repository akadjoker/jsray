#pragma once



//core functions
JSValue js_setTargetFPS(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
    int fps;
    JS_ToInt32(ctx, &fps, argv[0]);
    SetTargetFPS(fps);
    return JS_UNDEFINED;
}

JSValue js_getFrameTime(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
    return JS_NewFloat64(ctx, GetFrameTime());
}

JSValue js_getElapsedTime(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
    return JS_NewFloat64(ctx, GetTime());
}

JSValue js_getFPS(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
    return JS_NewInt32(ctx, GetFPS());
}
JSValue js_random(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    int min, max;
    JS_ToInt32(ctx, &min, argv[0]);
    JS_ToInt32(ctx, &max, argv[1]);
    return JS_NewFloat64(ctx, GetRandomValue(min, max));
}

// Initialize the function map
JSFunctionMap coreFunctions = {
    {"setTargetFPS", js_setTargetFPS},
    {"getFrameTime", js_getFrameTime},
    {"getElapsedTime", js_getElapsedTime},
    {"getFPS", js_getFPS},
    {"random", js_random},
};

inline void RegisterCoreFunctions(JSContext* ctx, JSValue global_obj) 
{
    JSValue core = JS_NewObject(ctx);
    for (const auto& func : coreFunctions) 
    {
        JS_SetPropertyStr(ctx, core, func.first.c_str(), JS_NewCFunction(ctx, func.second, func.first.c_str(), 1));
    }
    JS_SetPropertyStr(ctx, global_obj, "core", core);
}

//window functions




JSValue js_setWindowTitle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    const char* title=JS_ToCString(ctx,  argv[0]);
    SetWindowTitle(title);
    JS_FreeCString(ctx, title);
    return JS_UNDEFINED;
}

JSValue js_Init(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (IsReady ) return JS_UNDEFINED;
    int width, height;
    JS_ToInt32(ctx, &width, argv[0]);
    JS_ToInt32(ctx, &height, argv[1]);
    const char* title=JS_ToCString(ctx, argv[2]);    

    
    InitWindow(width, height, title);

    JS_FreeCString(ctx, title);


    IsReady = true;
    return JS_UNDEFINED;
}

JSValue js_CloseWindow(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    CloseWindow();
    IsReady = false;
    return JS_UNDEFINED;
}

JSValue js_shouldClose(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    return JS_NewBool(ctx, WindowShouldClose());
}

JSValue js_get_width(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    return JS_NewInt32(ctx, GetScreenWidth());
}

JSValue js_get_height(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    return JS_NewInt32(ctx, GetScreenHeight());
}







JSFunctionMap windowFunctions = {
    {"setWindowTitle", js_setWindowTitle},
    {"init", js_Init},
    {"close", js_CloseWindow},
    {"shouldClose", js_shouldClose},
    {"getWidth", js_get_width},
    {"getHeight", js_get_height},
};  

inline void RegisterWindowFunctions(JSContext* ctx, JSValue global_obj) 
{
    JSValue core = JS_NewObject(ctx);
    for (const auto& func : windowFunctions) 
    {
        JS_SetPropertyStr(ctx, core, func.first.c_str(), JS_NewCFunction(ctx, func.second, func.first.c_str(), 1));
    }
    JS_SetPropertyStr(ctx, global_obj, "window", core);
}