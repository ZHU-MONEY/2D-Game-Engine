#pragma once
#include "Glib\Glib.h"
#include <assert.h>
class EngineUtils
{
public:
	void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
	GLib::Sprite* CreateSprite(const char* i_pFilename);



};

