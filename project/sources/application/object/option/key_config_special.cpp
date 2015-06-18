//*****************************************************************************
//
// key config special
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_special.h"
#include "render/sprite.h"
#include "system/system.h"
#include "../option.h"

//=============================================================================
// constructor
//=============================================================================
KeyConfigSpecial::KeyConfigSpecial(void)
{
}

//=============================================================================
// destructor
//=============================================================================
KeyConfigSpecial::~KeyConfigSpecial(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool KeyConfigSpecial::Initialize(void)
{
	special_button_ = new Sprite();
	special_button_->Initialize();
	special_button_->__size(Option::DEFAULT_MENU_SIZE);
	special_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2 - 250,475.0f));
	special_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_SPECIAL);
	special_button_->__point(Sprite::POINT_CENTER);
	special_button_->SetParameter();

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigSpecial::Uninitialize(void)
{
	SafeRelease(special_button_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigSpecial::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigSpecial::Draw(void)
{
	special_button_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigSpecial::Select(bool is_select)
{
	if(is_select == true)
	{
		special_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		special_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
	
	special_button_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
