#pragma once
#ifndef ENGINE_UTILS_
#define ENGINE_UTILS_



#include "Glib\Glib.h"
#include <assert.h>
class EngineUtils
{
public:
	static void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
	static GLib::Sprite* CreateSprite(const char* i_pFilename);
};
#endif // !ENGINE_UTILS

