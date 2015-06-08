//*****************************************************************************
//
// option config menu
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "option_config_menu.h"
#include "render/sprite.h"
#include "system/system.h"
#include "option.h"

//=============================================================================
// constructor
//=============================================================================
OptionConfigMenu::OptionConfigMenu(void)
{
}

//=============================================================================
// destructor
//=============================================================================
OptionConfigMenu::~OptionConfigMenu(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool OptionConfigMenu::Initialize(void)
{
	select_button_ = new Sprite();
	select_button_->Initialize();
	select_button_->__size(Option::DEFAULT_MENU_SIZE);
	select_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,100.0f));
	select_button_->__texture_id(Texture::TEXTURE_ID_OK_BUTTON);
	select_button_->__point(Sprite::POINT_CENTER);
	select_button_->SetParameter();

	cancel_button_ = new Sprite();
	cancel_button_->Initialize();
	cancel_button_->__size(Option::DEFAULT_MENU_SIZE);
	cancel_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,200.0f));
	cancel_button_->__texture_id(Texture::TEXTURE_ID_CANCEL_BUTTON);
	cancel_button_->__point(Sprite::POINT_CENTER);
	cancel_button_->SetParameter();

	light_button_ = new Sprite();
	light_button_->Initialize();
	light_button_->__size(Option::DEFAULT_MENU_SIZE);
	light_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,300.0f));
	light_button_->__texture_id(Texture::TEXTURE_ID_LIGHT_BUTTON);
	light_button_->__point(Sprite::POINT_CENTER);
	light_button_->SetParameter();

	jump_button_ = new Sprite();
	jump_button_->Initialize();
	jump_button_->__size(Option::DEFAULT_MENU_SIZE);
	jump_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2,400.0f));
	jump_button_->__texture_id(Texture::TEXTURE_ID_JUMP_BUTTON);
	jump_button_->__point(Sprite::POINT_CENTER);
	jump_button_->SetParameter();

	/*key_1_ = new Sprite();
	key_1_->Initialize();
	key_1_->__size(Option::DEFAULT_MENU_SIZE);
	key_1_->__position(D3DXVECTOR2(0.0f,0.0f));
	key_1_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
	key_1_->__point(Sprite::POINT_CENTER);
	key_1_->SetParameter();

	key_2_ = new Sprite();
	key_2_->Initialize();
	key_2_->__size(Option::DEFAULT_MENU_SIZE);
	key_2_->__position(D3DXVECTOR2(0.0f,0.0f));
	key_2_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
	key_2_->__point(Sprite::POINT_CENTER);
	key_2_->SetParameter();

	key_3_ = new Sprite();
	key_3_->Initialize();
	key_3_->__size(Option::DEFAULT_MENU_SIZE);
	key_3_->__position(D3DXVECTOR2(0.0f,0.0f));
	key_3_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
	key_3_->__point(Sprite::POINT_CENTER);
	key_3_->SetParameter();

	key_4_ = new Sprite();
	key_4_->Initialize();
	key_4_->__size(Option::DEFAULT_MENU_SIZE);
	key_4_->__position(D3DXVECTOR2(0.0f,0.0f));
	key_4_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
	key_4_->__point(Sprite::POINT_CENTER);
	key_4_->SetParameter();

	key_5_ = new Sprite();
	key_5_->Initialize();
	key_5_->__size(Option::DEFAULT_MENU_SIZE);
	key_5_->__position(D3DXVECTOR2(0.0f,0.0f));
	key_5_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
	key_5_->__point(Sprite::POINT_CENTER);
	key_5_->SetParameter();

	key_6_ = new Sprite();
	key_6_->Initialize();
	key_6_->__size(Option::DEFAULT_MENU_SIZE);
	key_6_->__position(D3DXVECTOR2(0.0f,0.0f));
	key_6_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
	key_6_->__point(Sprite::POINT_CENTER);
	key_6_->SetParameter();*/
	
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void OptionConfigMenu::Uninitialize(void)
{
	SafeRelease(select_button_);
	SafeRelease(cancel_button_);
	SafeRelease(light_button_);
	SafeRelease(jump_button_);

	/*SafeRelease(key_1_);
	SafeRelease(key_2_);
	SafeRelease(key_3_);
	SafeRelease(key_4_);
	SafeRelease(key_5_);
	SafeRelease(key_6_);*/

}

//=============================================================================
// update
//=============================================================================
void OptionConfigMenu::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void OptionConfigMenu::Draw(void)
{
	select_button_->Draw();
	cancel_button_->Draw();
	light_button_->Draw();
	jump_button_->Draw();

	/*
	ボタンの横に設定してるキーのアイコンを出す(かもしれない)
	key_1_->Draw();
	key_2_->Draw();
	key_3_->Draw();
	key_4_->Draw();
	key_5_->Draw();
	key_6_->Draw();
	*/
}

//=============================================================================
// select
//=============================================================================
void OptionConfigMenu::Select(u32 menu)
{
	switch(menu)
	{
		case SELECT_BUTTON:
			select_button_->__size(Option::EXPAND_MENU_SIZE);
			cancel_button_->__size(Option::DEFAULT_MENU_SIZE);
			light_button_->__size(Option::DEFAULT_MENU_SIZE);
			jump_button_->__size(Option::DEFAULT_MENU_SIZE);

			select_button_->SetParameter();
			cancel_button_->SetParameter();
			light_button_->SetParameter();
			jump_button_->SetParameter();
		break;

		case CANCEL_BUTTON:
			cancel_button_->__size(Option::EXPAND_MENU_SIZE);
			select_button_->__size(Option::DEFAULT_MENU_SIZE);
			light_button_->__size(Option::DEFAULT_MENU_SIZE);
			jump_button_->__size(Option::DEFAULT_MENU_SIZE);

			select_button_->SetParameter();
			cancel_button_->SetParameter();
			light_button_->SetParameter();
			jump_button_->SetParameter();
		break;

		case LIGHT_BUTTON:
			light_button_->__size(Option::EXPAND_MENU_SIZE);
			select_button_->__size(Option::DEFAULT_MENU_SIZE);
			cancel_button_->__size(Option::DEFAULT_MENU_SIZE);
			jump_button_->__size(Option::DEFAULT_MENU_SIZE);

			select_button_->SetParameter();
			cancel_button_->SetParameter();
			light_button_->SetParameter();
			jump_button_->SetParameter();
		break;

		case JUMP_BUTTON:
			jump_button_->__size(Option::EXPAND_MENU_SIZE);
			select_button_->__size(Option::DEFAULT_MENU_SIZE);
			light_button_->__size(Option::DEFAULT_MENU_SIZE);
			cancel_button_->__size(Option::DEFAULT_MENU_SIZE);

			select_button_->SetParameter();
			cancel_button_->SetParameter();
			light_button_->SetParameter();
			jump_button_->SetParameter();
		break;

		default:
			break;
	}
}

//---------------------------------- EOF --------------------------------------
