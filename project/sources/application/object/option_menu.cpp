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

const D3DXVECTOR2 OptionMenu::DEFAULT_MENU_SIZE = D3DXVECTOR2(200.f, 50.f);
const D3DXVECTOR2 OptionMenu::EXPAND_MENU_SIZE = D3DXVECTOR2(300.f, 100.f);

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
	menu_config_->__size(DEFAULT_MENU_SIZE);
	menu_config_->__position(D3DXVECTOR2(0.0f,0.0f));
	menu_config_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
	menu_config_->SetParameter();

	menu_volume_ = new Sprite();
	menu_volume_->Initialize();
	menu_volume_->__size(DEFAULT_MENU_SIZE);
	menu_volume_->__position(D3DXVECTOR2(0.0f,0.0f));
	menu_volume_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
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
			menu_config_->__size(EXPAND_MENU_SIZE);
			menu_volume_->__size(DEFAULT_MENU_SIZE);

			menu_config_->SetParameter();
			menu_volume_->SetParameter();
		break;

		case OPTION_TYPE_VOLUME:
			menu_volume_->__size(EXPAND_MENU_SIZE);
			menu_config_->__size(DEFAULT_MENU_SIZE);

			menu_config_->SetParameter();
			menu_volume_->SetParameter();
		break;

		default:
			break;
	}
}

//---------------------------------- EOF --------------------------------------
