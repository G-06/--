//*****************************************************************************
//
// texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "texture.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const s8* Texture::TEXTURE_NAME[TEXTURE_ID_MAX] =
{
	"resources/texture/test.png",
	"resources/texture/anim_test.png",
	"resources/texture/title/title_bg.jpg",
	"resources/texture/stage_bg.png",
};

//=============================================================================
// constructor
//=============================================================================
Texture::Texture(void) :
device_(nullptr)
{
	memset(texture_container_,0,sizeof(texture_container_));
}

//=============================================================================
// destructor
//=============================================================================
Texture::~Texture(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Texture::Initialize(void)
{
	device_ = GET_DIRECTX9_DEVICE;

	for(u32 i = 0;i < TEXTURE_ID_MAX;++i)
	{
		if(FAILED(D3DXCreateTextureFromFile(device_,TEXTURE_NAME[i],&texture_container_[i])))
		{
			ASSERT("failed load texure");
			return false;
		}
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Texture::Uninitialize(void)
{
	for(u32 i = 0;i < TEXTURE_ID_MAX;++i)
	{
		SafeRelease(texture_container_[i]);
	}
}

//=============================================================================
// get texture
//=============================================================================
LPDIRECT3DTEXTURE9 Texture::GetTexture(const TEXTURE_ID& texture_id)const
{
	if(texture_id == TEXTURE_ID_NONE)
	{
		return nullptr;
	}

	return texture_container_[texture_id];
}

//---------------------------------- EOF --------------------------------------
