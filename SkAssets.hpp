#pragma once



class AssetManager
{
public:
    static AssetManager &Instance()
    {
        static AssetManager instance;
        return instance;
    }

    bool ImageLoad(int id, const char *filename)
    {
        if (id == 0)
        {
            id = mLastImageId + 1;
        }
        if (images.find(id) != images.end())
        {
            Log(1,"Image ID already exists");
            return false;
        }

        Image image = LoadImage(filename);
        if (image.data == nullptr)
        {
           // Log(1,"Failed to load image");
            return false;
        }
        images[id] = image;

        mLastImageId++;

        return true;
    }

    bool ImageExists(int id) const
    {
        return images.find(id) != images.end();
    }

    Image &GetImage(int id)
    {
        if (images.find(id) == images.end())
        {
           Log(2,"Image ID not found");

           return mImageDefault;
        }
        return images[id];
    }

    void UnloadAllImages()
    {
        for (auto &pair : images)
        {
            UnloadImage(pair.second);
        }
        images.clear();
    }
    void FreeImage(int id)
    {
        if (images.find(id) == images.end())
        {
            Log(2,"Image ID not found");
            return;
        }
        UnloadImage(images[id]);
        images.erase(id);
    }

    bool TextureLoad(int id, const char *filename)
    {
        if (!IsReady) return false;
        if (id == 0)
        {
            id = mLastTextureId + 1;
        }
        if (textures.find(id) != textures.end())
        {
            Log(1,"Texture ID already exists");
            return false;
        }

        Texture2D texture = LoadTexture(filename);
        if (texture.id == 0)
        {
        //    Log(2,"Failed to load texture");
            return false;
        }
        textures[id] = texture;
        mLastTextureId++;
        

        return true;
    }

    bool TextureExists(int id) const
    {
        return textures.find(id) != textures.end();
    }

    Texture2D &GetTexture(int id)
    {
        if (textures.find(id) == textures.end())
        {
            Log(1,"Texture ID not found");
            return mTextureDefault;
        }
        return textures[id];
    }

    void UnloadAllTextures()
    {
        for (auto &pair : textures)
        {
            UnloadTexture(pair.second);
        }
        textures.clear();
    }
    void FreeTexture(int id)
    {
        if (!IsReady) return ;
        if (textures.find(id) == textures.end())
        {
            Log(2,"Texture ID not found");
            return;
        }
        UnloadTexture(textures[id]);
        textures.erase(id);
    }

    bool FontLoad(int id, const char *filename)
    {
        if (!IsReady) return false;
        if (id == 0)
        {
            id = mLastFontId + 1;
        }
        if (fonts.find(id) != fonts.end())
        {
            Log(1,"Font ID already exists");
            return false;
        }

        Font font = LoadFont(filename);
        if (font.baseSize == 0)
        {
         //   Log(2,"Failed to load font");
            return false;
        }
        fonts[id] = font;
        mLastFontId++;  

        return true;
    }

    bool FontExists(int id) const
    {
        return fonts.find(id) != fonts.end();
    }

    Font &GetFont(int id)
    {
        if (fonts.find(id) == fonts.end())
        {
            Log(1,"Font ID not found");
            return mFontDefault;
        }
        return fonts[id];
    }

    void UnloadAllFonts()
    {
        for (auto &pair : fonts)
        {
            UnloadFont(pair.second);
        }
        fonts.clear();
    }
    void FreeFont(int id)
    {
        if (fonts.find(id) == fonts.end())
        {
            Log(2,"Font ID not found");
            return;
        }
        UnloadFont(fonts[id]);
        fonts.erase(id);
    }

    void Clear()
    {
       Log(1,"Clearing all assets");
       UnloadAllImages();
       UnloadAllTextures();
       UnloadAllFonts();

    }

    void Free()
    {
            
         if (IsReady) 
        {
       
            UnloadTexture(mTextureDefault);
        }
    }

private:
    AssetManager() 
    {
        mImageDefault = GenImageColor(32, 32, MAGENTA);
        if (IsReady) 
        {
        mFontDefault = GetFontDefault();
        mTextureDefault = LoadTextureFromImage(mImageDefault);
        }
    }
    ~AssetManager()    
    { UnloadImage(mImageDefault);          }

    AssetManager(const AssetManager &) = delete;
    AssetManager &operator=(const AssetManager &) = delete;

    std::map<int, Image> images;
    std::map<int, Texture2D> textures;
    std::map<int, Font> fonts;


    long mLastImageId = 0;
    long mLastTextureId = 0;
    long mLastFontId = 0;
    Image mImageDefault;
    Texture2D mTextureDefault;
    Font mFontDefault;
};

JSValue js_LoadImage(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int id;
   
    JS_ToInt32(ctx, &id,argv[0]);
    const char *filename = JS_ToCString(ctx, argv[1]);


    if (!AssetManager::Instance().ImageLoad(id, filename))
    {
        JS_ThrowReferenceError(ctx, "Failed to load image");
    }
    
    JS_FreeCString(ctx, filename);
    return JS_UNDEFINED;
}

JSValue js_FreeImage(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int id;
    JS_ToInt32(ctx, &id, argv[0]);
    AssetManager::Instance().FreeImage(id);
    return JS_UNDEFINED;
}

JSValue js_UnloadAllImages(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    AssetManager::Instance().UnloadAllImages();
    return JS_UNDEFINED;
}

JSValue js_LoadTexture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int id;
    JS_ToInt32(ctx,&id, argv[0]);
    const char *filename = JS_ToCString(ctx, argv[1]);
    if (!AssetManager::Instance().TextureLoad(id, filename))
    {
        JS_ThrowReferenceError(ctx, "Failed to load texture");
    }
    
    JS_FreeCString(ctx, filename);
    return JS_UNDEFINED;
}



JSValue js_FreeTexture(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int id;
    JS_ToInt32(ctx, &id,argv[0]);
    AssetManager::Instance().FreeTexture(id);
    return JS_UNDEFINED;
}


JSValue js_UnloadAllTextures(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    AssetManager::Instance().UnloadAllTextures();
    return JS_UNDEFINED;
}


JSValue js_LoadFont(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    int id;
    JS_ToInt32(ctx, &id,argv[0]);
    const char *filename = JS_ToCString(ctx, argv[1]);
    if (!AssetManager::Instance().FontLoad(id, filename))
    {
        JS_ThrowReferenceError(ctx, "Failed to load font");
    }
    
    JS_FreeCString(ctx, filename);
    return JS_UNDEFINED;
}

JSValue js_FreeFont(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    int id;
    JS_ToInt32(ctx,&id, argv[0]);
    AssetManager::Instance().FreeFont(id);
    return JS_UNDEFINED;
}

JSValue js_UnloadAllFonts(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) 
{
    AssetManager::Instance().UnloadAllFonts();
    return JS_UNDEFINED;
}

JSValue js_Clear(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    AssetManager::Instance().Clear();
    return JS_UNDEFINED;
}

JSFunctionMap assetsFunctions = {
    {"loadImage", js_LoadImage},
  
    {"freeImage", js_FreeImage},

    {"loadTexture", js_LoadTexture},

    {"freeTexture", js_FreeTexture},
  
    {"loadFont", js_LoadFont},

    {"freeFont", js_FreeFont},

    {"clear", js_Clear},    

};

inline void RegisterAssetsFunctions(JSContext* ctx, JSValue global_obj) 
{
    JSValue core = JS_NewObject(ctx);
    for (const auto& func : assetsFunctions) 
    {
        JS_SetPropertyStr(ctx, core, func.first.c_str(), JS_NewCFunction(ctx, func.second, func.first.c_str(), 1));
    }
    JS_SetPropertyStr(ctx, global_obj, "assets", core);
}

