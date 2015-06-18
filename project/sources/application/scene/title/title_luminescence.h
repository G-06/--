//*****************************************************************************
//
// title luminescence
//
// Author	: masato masuda
//
// ”­Œõ‚µ‚Ä‚é‚â‚Â
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TITLE_LUMINESCENCE_H_
#define _TITLE_LUMINESCENCE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class Titleluminescence : public Basic
{
public:
	// constructor
	Titleluminescence(void);

	// destructor
	virtual ~Titleluminescence(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// color
	void __color(const D3DXCOLOR& color);
	const D3DXCOLOR __color(void);

	// alpha_speed
	void __alpha_speed(const f32& alpha_speed){alpha_speed_ = alpha_speed;}
	const f32 __alpha_speed(void){return alpha_speed_;}
	void InverseAlphaSpeed(void){alpha_speed_ *= -1;}
	void ResetAlphaSpeed(void);

	// alpha
	void __alpha(const f32& alpha){alpha_ = alpha;}
	const f32 __alpha(void){return alpha_;}

	// texture
	void __texture_id(const Texture::TEXTURE_ID& texture_id);

private:
	static const D3DXVECTOR2 DEFAULT_POSITION;
	static const D3DXVECTOR2 DEFAULT_SIZE;

	Sprite* sprite_;

	f32 alpha_speed_;
	f32 alpha_;
};

#endif	// _TITLE_LUMINESCENCE_H_

//---------------------------------- EOF --------------------------------------
