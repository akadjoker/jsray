#pragma once

JSValue js_isKeyPressed(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int key;
    JS_ToInt32(ctx, &key,argv[0]);
   
    return JS_NewBool(ctx, IsKeyPressed(key));
}

JSValue js_isKeyDown(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
   int key;
    JS_ToInt32(ctx, &key,argv[0]);
   
    return JS_NewBool(ctx, IsKeyDown(key));
}

JSValue js_isKeyUp(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
   int key;
    JS_ToInt32(ctx, &key,argv[0]);
   
    return JS_NewBool(ctx, IsKeyUp(key));
}

JSValue js_isKeyReleased(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
   int key;
    JS_ToInt32(ctx, &key,argv[0]);
    
    return JS_NewBool(ctx, IsKeyReleased(key));
}

JSFunctionMap keysFunctions = {
    {"pressed", js_isKeyPressed},
    {"down", js_isKeyDown},
    {"up", js_isKeyUp},
    {"released", js_isKeyReleased},
};

inline void RegisterKeyboardFunctions(JSContext* ctx, JSValue global_obj) 
{
    JSValue core = JS_NewObject(ctx);
    for (const auto& func : coreFunctions) 
    {
        JS_SetPropertyStr(ctx, core, func.first.c_str(), JS_NewCFunction(ctx, func.second, func.first.c_str(), 1));
    }
    JS_SetPropertyStr(ctx, global_obj, "keyboard", core);
}

//mouse

JSValue js_isMouseButtonPressed(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int button;
    JS_ToInt32(ctx, &button,argv[0]);
    
    return JS_NewBool(ctx, IsMouseButtonPressed(button));
}

JSValue js_isMouseButtonDown(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int button;

    JS_ToInt32(ctx, &button,argv[0]);
    
    return JS_NewBool(ctx, IsMouseButtonDown(button));
}

JSValue js_isMouseButtonReleased(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int button;
    JS_ToInt32(ctx, &button,argv[0]);
    
    return JS_NewBool(ctx, IsMouseButtonReleased(button));
}

JSValue js_isMouseButtonUp(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    int button;
    JS_ToInt32(ctx, &button,argv[0]);
    return JS_NewBool(ctx, IsMouseButtonUp(button));
}


JSFunctionMap mouseFunctions = {
    {"pressed", js_isMouseButtonPressed},
    {"down", js_isMouseButtonDown},
    {"up", js_isMouseButtonUp},
    {"released", js_isMouseButtonReleased},
};

inline void RegisterMouseFunctions(JSContext* ctx, JSValue global_obj) 
{
    JSValue core = JS_NewObject(ctx);
    for (const auto& func : mouseFunctions) 
    {
        JS_SetPropertyStr(ctx, core, func.first.c_str(), JS_NewCFunction(ctx, func.second, func.first.c_str(), 1));
    }
    JS_SetPropertyStr(ctx, global_obj, "mouse", core);
}