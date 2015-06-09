//*****************************************************************************
//
// key config ok
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_ok.h"
#include "render/sprite.h"
#include "system/system.h"
#include "option.h"

//=============================================================================
// constructor
//=============================================================================
KeyConfigOk::KeyConfigOk(void)
{
}

//=============================================================================
// destructor
//=============================================================================
KeyConfigOk::~KeyConfigOk(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool KeyConfigOk::Initialize(void)
{
	select_button_ = new Sprite();
	select_button_->Initialize();
	select_button_->__size(Option::DEFAULT_MENU_SIZE);
	select_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,100.0f));
	select_button_->__texture_id(Texture::TEXTURE_ID_OK_BUTTON);
	select_button_->__point(Sprite::POINT_CENTER);
	select_button_->SetParameter();

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigOk::Uninitialize(void)
{
	SafeRelease(select_button_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigOk::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigOk::Draw(void)
{
	select_button_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigOk::Select(bool is_select)
{
	if(is_select == true)
	{
		select_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		select_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
	
	select_button_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
