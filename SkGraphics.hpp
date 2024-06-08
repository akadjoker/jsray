#pragma once

class Graphics
{
public:
    static Graphics &Instance()
    {
        static Graphics instance;
        return instance;
    }

    void SetColor(unsigned int r, unsigned int g, unsigned int b)
    {
        mDefaultColor.r = r;
        mDefaultColor.g = g;
        mDefaultColor.b = b;
    }

    void SetAlpha(unsigned int a)
    {
        mDefaultColor.a = a;
    }

    void SetFont(unsigned int id)
    {
        mDefaultFont = AssetManager::Instance().GetFont(id);
    }

    void Circle(float x, float y, float radius, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            DrawCircleLines(x, y, radius, mDefaultColor);
        }
        else
        {
            DrawCircle(x, y, radius, mDefaultColor);
        }
    }

    void Line(float x1, float y1, float x2, float y2)
    {
        if (!IsReady)
            return;
        DrawLine(x1, y1, x2, y2, mDefaultColor);
    }

    void Rect(float x, float y, float width, float height, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            Rectangle r;
            r.x = x;
            r.y = y;
            r.width = width;
            r.height = height;
            DrawRectangleLinesEx(r, mlineThickness, mDefaultColor);
        }
        else
        {
            DrawRectangle(x, y, width, height, mDefaultColor);
        }
    }

    void Ring(float x, float y, float innerRadius, float outerRadius, float startAngle, float endAngle, bool mIsLine)
    {
        if (!IsReady)
            return;
        Vector2 center;
        center.x = x;
        center.y = y;

        if (mIsLine)
        {
            DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, mSegments, mDefaultColor);
        }
        else
        {
            DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, mSegments, mDefaultColor);
        }
    }
    void RectangleRounded(float x, float y, float width, float height, float rounding, bool mIsLine)
    {
        if (!IsReady)
            return;
        Rectangle r;
        r.x = x;
        r.y = y;
        r.width = width;
        r.height = height;

        if (mIsLine)
        {
            DrawRectangleRoundedLines(r, rounding, mSegments, mlineThickness, mDefaultColor);
        }
        else
        {
            DrawRectangleRounded(r, rounding, mSegments, mDefaultColor);
        }
    }

    // DrawEllipse

    void Ellipse(float x, float y, float radiusx, float radiusy, bool mIsLine)
    {
        if (!IsReady)
            return;
        if (mIsLine)
        {
            DrawEllipseLines(x, y, radiusx, radiusy, mDefaultColor);
        }
        else
        {
            DrawEllipse(x, y, radiusx, radiusy, mDefaultColor);
        }
    }
    void Point(float x, float y)
    {
        if (!IsReady)
            return;
        DrawPixel(x, y, mDefaultColor);
    }

    void Text(float x, float y, const char *text)
    {
        if (!IsReady)
            return;
        DrawText(text, x, y, mTextSize, mDefaultColor);
    }

    void SetLineThickness(float thickness)
    {
        if (!IsReady)
            return;
        mlineThickness = thickness;
    }

    void SetTextSize(int size)
    {
        if (!IsReady)
            return;
        mTextSize = size;
    }

    void SetSegments(int segments)
    {
        mSegments = segments;
    }

    void Begin()
    {
        if (!IsReady)
            return;
        BeginMode2D(mCamera);
    }

    void End()
    {
        if (!IsReady)
            return;
        EndMode2D();
    }
    void SetViewPosition(float x, float y)
    {
        mCamera.target.x = x;
        mCamera.target.y = y;
    }

    void SetViewZoom(float value)
    {
        mCamera.zoom = value;
    }

    void SetViewRotation(float value)
    {
        mCamera.rotation = value;
    }

    void SetViewCenter(float x, float y)
    {
        mCamera.offset.x = x;
        mCamera.offset.y = y;
    }

    void Render(unsigned int id, float x, float y)
    {
        if (!IsReady)
            return;
        Texture2D texture = AssetManager::Instance().GetTexture(id);
        DrawTexture(texture, x, y, mDefaultColor);
    }
    void Render(unsigned int id, float x, float y, float scale, float rotation)
    {
        if (!IsReady)
            return;
        Texture2D texture = AssetManager::Instance().GetTexture(id);
        Vector2 center;
        center.x = x;
        center.y = y;
        DrawTextureEx(texture, center, rotation, scale, mDefaultColor);
    }

    void ShowFPS(int x,int y)
    {
        if (!IsReady)
            return;
        DrawFPS(x,y);
    }

    void Clear(int r, int g, int b)
    {
        if (!IsReady)
            return;
        mBackgroundColor.r = r;
        mBackgroundColor.g = g;
        mBackgroundColor.b = b;

        ClearBackground(mBackgroundColor);
    }

private:
    Graphics()
    {
        mDefaultFont = GetFontDefault();
        mTextSize = mDefaultFont.baseSize;

        mCamera.target.x = 0.0f;
        mCamera.target.y = 0.0f;

        mCamera.offset.y = 0.0f;
        mCamera.offset.x = 0.0f;

        mCamera.rotation = 0.0f;
        mCamera.zoom = 1.0f;

        mDefaultColor = {255, 255, 255, 255};
    }
    ~Graphics() {}

    Graphics(const Graphics &) = delete;
    Graphics &operator=(const Graphics &) = delete;

    Color mDefaultColor;
    Font mDefaultFont;
    int mSegments = 32;
    float mlineThickness = 1.0f;
    int mTextSize;
    Camera2D mCamera;
    Color mBackgroundColor = {0, 0, 0, 255};
};

JSValue js_begin(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    BeginDrawing();
    return JS_UNDEFINED;
}

JSValue js_end(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    EndDrawing();
    return JS_UNDEFINED;
}

JSValue js_clear(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    int r,g,b;
    JS_ToInt32(ctx, &r,argv[0]);
    JS_ToInt32(ctx, &g,argv[1]);
    JS_ToInt32(ctx, &b,argv[2]);
    Graphics::Instance().Clear(r, g, b);
    
    return JS_UNDEFINED;
}

JSValue js_setLineThickness(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    double thickness;
    JS_ToFloat64(ctx, &thickness, argv[0]);
    Graphics::Instance().SetLineThickness(thickness);
    return JS_UNDEFINED;
}

JSValue js_setTextSize(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    int size;
    JS_ToInt32(ctx, &size, argv[0]);
    Graphics::Instance().SetTextSize(size);
    return JS_UNDEFINED;
}

JSValue js_setSegments(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    int segments;
    JS_ToInt32(ctx, &segments, argv[0]);
    Graphics::Instance().SetSegments(segments);
    return JS_UNDEFINED;
}


JSValue js_setViewPosition(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    double x,y;
    JS_ToFloat64(ctx, &x, argv[0]);
    JS_ToFloat64(ctx, &y, argv[1]);
    Graphics::Instance().SetViewPosition(x, y);
    return JS_UNDEFINED;
}


JSValue js_setViewZoom(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    double zoom;
    JS_ToFloat64(ctx, &zoom, argv[0]);
    Graphics::Instance().SetViewZoom(zoom);
    return JS_UNDEFINED;
}


JSValue js_setViewRotation(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    double rotation;
    JS_ToFloat64(ctx, &rotation, argv[0]);
    Graphics::Instance().SetViewRotation(rotation);
    return JS_UNDEFINED;
}


JSValue js_setViewCenter(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    double x,y;
    JS_ToFloat64(ctx, &x, argv[0]);
    JS_ToFloat64(ctx, &y, argv[1]);
    Graphics::Instance().SetViewCenter(x, y);
    return JS_UNDEFINED;
}


JSValue js_render_rotate_scale(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    int id;
    double x,y,scale,rotation;
    JS_ToInt32(ctx, &id, argv[0]);
    JS_ToFloat64(ctx, &x, argv[1]);
    JS_ToFloat64(ctx, &y, argv[2]);
    JS_ToFloat64(ctx, &scale, argv[3]);
    JS_ToFloat64(ctx, &rotation, argv[4]);
    Graphics::Instance().Render(id, x, y, scale, rotation);
    return JS_UNDEFINED;
}

JSValue js_draw(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    int id;
    double x,y;
    JS_ToInt32(ctx, &id, argv[0]);
    JS_ToFloat64(ctx, &x, argv[1]);
    JS_ToFloat64(ctx, &y, argv[2]);
    Graphics::Instance().Render(id, x, y);
    return JS_UNDEFINED;
}

JSValue js_showFPS(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    if (!IsReady) return JS_UNDEFINED;
    int x,y;
    JS_ToInt32(ctx, &x, argv[0]);
    JS_ToInt32(ctx, &y, argv[1]);

    Graphics::Instance().ShowFPS(x,y);
    return JS_UNDEFINED;
}

JSValue js_circle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    double x,y,r;
    bool mIsLine;
    JS_ToFloat64(ctx, &x, argv[0]);
    JS_ToFloat64(ctx, &y, argv[1]);
    JS_ToFloat64(ctx, &r, argv[2]);
    mIsLine = JS_ToBool(ctx,  argv[3]);;
    Graphics::Instance().Circle(x, y, r, mIsLine);
    return JS_UNDEFINED;
}

JSValue js_line(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    if (!IsReady) return JS_UNDEFINED;
    double x1,y1,x2,y2;
    JS_ToFloat64(ctx, &x1, argv[0]);
    JS_ToFloat64(ctx, &y1, argv[1]);
    JS_ToFloat64(ctx, &x2, argv[2]);
    JS_ToFloat64(ctx, &y2, argv[3]);
    Graphics::Instance().Line(x1, y1, x2, y2);
    return JS_UNDEFINED;
}


JSValue js_rectangle(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    if (!IsReady) return JS_UNDEFINED;
    double x,y,w,h;
    bool mIsLine;
    JS_ToFloat64(ctx, &x, argv[0]);
    JS_ToFloat64(ctx, &y, argv[1]);
    JS_ToFloat64(ctx, &w, argv[2]);
    JS_ToFloat64(ctx, &h, argv[3]);
    mIsLine = JS_ToBool(ctx,  argv[4]);
    Graphics::Instance().Rect(x, y, w, h, mIsLine);
    return JS_UNDEFINED;
}


JSValue js_rectangle_rounded(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    if (!IsReady) return JS_UNDEFINED;
    double x,y,w,h,r;
    bool mIsLine;
    JS_ToFloat64(ctx, &x, argv[0]);
    JS_ToFloat64(ctx, &y, argv[1]);
    JS_ToFloat64(ctx, &w, argv[2]);
    JS_ToFloat64(ctx, &h, argv[3]);
    JS_ToFloat64(ctx, &r, argv[4]);
    mIsLine = JS_ToBool(ctx,  argv[5]);
    Graphics::Instance().RectangleRounded(x, y, w, h, r, mIsLine);
    return JS_UNDEFINED;
}

JSValue js_set_color(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    if (!IsReady) return JS_UNDEFINED;
    int r,g,b;
    JS_ToInt32(ctx, &r, argv[0]);
    JS_ToInt32(ctx, &g, argv[1]);
    JS_ToInt32(ctx, &b, argv[2]);
    Graphics::Instance().SetColor(r,g,b);
    return JS_UNDEFINED;
}


JSValue js_set_alpha(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    if (!IsReady) return JS_UNDEFINED;
    int a;
    JS_ToInt32(ctx, &a, argv[0]);
    Graphics::Instance().SetAlpha(a);
    return JS_UNDEFINED;
}

JSValue js_set_text_size(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    if (!IsReady) return JS_UNDEFINED;
    int size;
    JS_ToInt32(ctx, &size, argv[0]);
    Graphics::Instance().SetTextSize(size);
    return JS_UNDEFINED;
}

JSValue js_text(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    if (!IsReady) return JS_UNDEFINED;
    const char* text=JS_ToCString(ctx, argv[2]);
    int x,y;

    JS_ToInt32(ctx, &x, argv[0]);
    JS_ToInt32(ctx, &y, argv[1]);

    Graphics::Instance().Text(x,y ,text);
    JS_FreeCString(ctx, text);
    return JS_UNDEFINED;
}

JSFunctionMap graphicsFunctions = {
    {"begin", js_begin},
    {"end", js_end},
    {"clear", js_clear},
    {"setLineThickness", js_setLineThickness},
    {"setTextSize", js_setTextSize},
    {"setSegments", js_setSegments},
    {"setViewPosition", js_setViewPosition},
    {"setViewZoom", js_setViewZoom},
    {"setViewRotation", js_setViewRotation},
    {"setViewCenter", js_setViewCenter},
    {"showFPS", js_showFPS},
    {"draw", js_draw},
    {"drawRotateScale", js_render_rotate_scale},
    {"circle", js_circle},
    {"line", js_line},
    {"rectangle", js_rectangle},
    {"roundRect", js_rectangle_rounded},
    {"setColor", js_set_color},
    {"setAlpha", js_set_alpha},
    {"text", js_text}


    
};


inline void RegisterGraphicsFunctions(JSContext* ctx, JSValue global_obj) 
{
    JSValue core = JS_NewObject(ctx);
    for (const auto& func : graphicsFunctions) 
    {
        JS_SetPropertyStr(ctx, core, func.first.c_str(), JS_NewCFunction(ctx, func.second, func.first.c_str(), 1));
    }
    JS_SetPropertyStr(ctx, global_obj, "graphics", core);
}


