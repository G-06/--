//*****************************************************************************
//
// option menu
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "option_menu.h"
#include "render/sprite.h"
#include "system/system.h"
#include "option.h"

//=============================================================================
// constructor
//=============================================================================
OptionMenu::OptionMenu(void)
{
}

//=============================================================================
// destructor
//=============================================================================
OptionMenu::~OptionMenu(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool OptionMenu::Initialize(void)
{
	menu_config_ = new Sprite();
	menu_config_->Initialize();
	menu_config_->__size(Option::DEFAULT_MENU_SIZE);
	menu_config_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,200.0f));
	menu_config_->__texture_id(Texture::TEXTURE_ID_CONFIG_BUTTON);
	menu_config_->__point(Sprite::POINT_CENTER);
	menu_config_->SetParameter();

	menu_volume_ = new Sprite();
	menu_volume_->Initialize();
	menu_volume_->__size(Option::DEFAULT_MENU_SIZE);
	menu_volume_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,400.0f));
	menu_volume_->__texture_id(Texture::TEXTURE_ID_VOLUME_BUTTON);
	menu_volume_->__point(Sprite::POINT_CENTER);
	menu_volume_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void OptionMenu::Uninitialize(void)
{
	SafeRelease(menu_config_);
	SafeRelease(menu_volume_);
}

//=============================================================================
// update
//=============================================================================
void OptionMenu::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void OptionMenu::Draw(void)
{
	menu_config_->Draw();
	menu_volume_->Draw();
}

//=============================================================================
// select
//=============================================================================
void OptionMenu::Select(u32 menu)
{
	switch(menu)
	{
		case OPTION_TYPE_CONFIG:
			menu_config_->__size(Option::EXPAND_MENU_SIZE);
			menu_volume_->__size(Option::DEFAULT_MENU_SIZE);

			menu_config_->SetParameter();
			menu_volume_->SetParameter();
		break;

		case OPTION_TYPE_VOLUME:
			menu_volume_->__size(Option::EXPAND_MENU_SIZE);
			menu_config_->__size(Option::DEFAULT_MENU_SIZE);

			menu_config_->SetParameter();
			menu_volume_->SetParameter();
		break;

		default:
			break;
	}
}

//---------------------------------- EOF --------------------------------------
