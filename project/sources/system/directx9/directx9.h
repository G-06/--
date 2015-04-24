//*****************************************************************************
//
// directx9
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DIRECTX9_H_
#define _DIRECTX9_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Window;

//*****************************************************************************
// class definition
//*****************************************************************************
class Directx9 : public Basic
{
public:
	typedef struct VERTEX
	{
		D3DXVECTOR3 _position;
		D3DCOLOR _color;
		D3DXVECTOR2 _texcoord;
	}VERTEX;

	// constructor
	Directx9(Window* window);

	// destructor
	virtual ~Directx9(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// begin draw
	bool BeginDraw(void);

	// end draw
	void EndDraw(void);

	// screen shot
	void ScreenShot(void);

	// screen shot
	void ScreenShot(const s8* filename);

	// get texture
	LPDIRECT3DTEXTURE9 GetTexture(const Texture::TEXTURE_ID& texture_id);

	// accessor
	LPDIRECT3DDEVICE9 __direct3ddevice(void) { return direct3ddevice_; }
private:
	static const D3DVERTEXELEMENT9 VERTEXELEMENT_[];

	Window* window_;
	LPDIRECT3DDEVICE9 direct3ddevice_;
	LPDIRECT3D9 direct3d_;
	D3DPRESENT_PARAMETERS d3dpresent_parameters_;
	D3DDISPLAYMODE d3ddisplaymode_;
	LPDIRECT3DVERTEXDECLARATION9 direct3dvertexdeclaration_;
	Texture* texture_;

	// デフォルトレンダーステートの設定
	void SetDefaultRenderState(void);

	// デフォルトサンプラーステートの設定
	void SetDefaultSamplerState(void);

	// デフォルトテクスチャステージステートの設定
	void SetDefaultTextureStageState(void);
};

#endif // _DIRECTX9_H_

//---------------------------------- EOF --------------------------------------
