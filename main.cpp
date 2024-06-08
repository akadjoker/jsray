#include "pch.hpp"
#include "quickjs-libc.h"
#include "quickjs.h"

static bool IsReady = false;
  
using JSFunctionMap = std::map<std::string, JSValue(*)(JSContext*, JSValueConst, int, JSValueConst*)>;

#include "SkUtils.hpp"
#include "SkRay.hpp"
#include "SkAssets.hpp"
#include "SkInput.hpp"
#include "SkGraphics.hpp"


std::string readFile(const std::string& filePath) 
{
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void execute(JSContext* ctx, const char* script, const char* filename) 
{
    JSValue result = JS_Eval(ctx, script, TextLength(script), filename, JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(result)) 
    {
        JSValue exception = JS_GetException(ctx);
        const char* errorMessage = JS_ToCString(ctx, exception);
        Log(2, errorMessage);
        JS_FreeCString(ctx, errorMessage);
        JS_FreeValue(ctx, exception);
    }
    JS_FreeValue(ctx, result);
}


int main(int cv, char *argv[])
{
  




    JSRuntime* rt = JS_NewRuntime();
    JSContext* ctx = JS_NewContext(rt);
    js_std_add_helpers(ctx, -1, NULL); // Adiciona suporte a console.log e outras funções padrão do QuickJS


    JSValue global_obj = JS_GetGlobalObject(ctx);

    RegisterCoreFunctions(ctx, global_obj);
    RegisterWindowFunctions(ctx, global_obj);
    RegisterMouseFunctions(ctx, global_obj);
    RegisterKeyboardFunctions(ctx, global_obj);
    RegisterAssetsFunctions(ctx, global_obj);
    RegisterGraphicsFunctions(ctx, global_obj);
 
 
    if (cv > 1) 
    {
        if (FileExists(argv[1]))
        {
            std::string script = readFile(argv[1]);
            execute(ctx, script.c_str(), GetFileName(argv[1]));
        }
            
    } else 
    {
            std::string script = readFile("main.js");
            execute(ctx, script.c_str(), "main.js");
    }



    JS_FreeValue(ctx, global_obj);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);


    return 0;


}
