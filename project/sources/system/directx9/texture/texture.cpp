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

	for(u32 i = TEXTURE_ID_DOT;i < TEXTURE_ID_MAX;++i)
	{
		if(FAILED(D3DXCreateTextureFromResource(device_,NULL,MAKEINTRESOURCE(i),&texture_container_[i - TEXTURE_ID_DOT])))
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
	for(u32 i = 0;i < TEXTURE_ID_MAX - TEXTURE_ID_DOT;++i)
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

	return texture_container_[texture_id - TEXTURE_ID_DOT];
}

//---------------------------------- EOF --------------------------------------
