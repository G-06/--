//*****************************************************************************
//
// message_window
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "tutorial_back.h"
#include "system/system.h"
#include "object/message_sprite_smooth.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 TutorialBack::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.6f);
const D3DXVECTOR2 TutorialBack::DEFAULT_SIZE = D3DXVECTOR2(0.0f, 0.0f);

const u32 DEST_FRAME_COUNT = 30;
const s32 DEFAULT_SELECT = 1;
const D3DXCOLOR CLEAR_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
const D3DXCOLOR SHOW_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

const D3DXVECTOR2 WINDOW_SCALE = D3DXVECTOR2(1.4f, 0.5f);
//const D3DXVECTOR2 WINDOW_SCALE = D3DXVECTOR2(1.4f, 1.0f);

const D3DXVECTOR2 WINDOW_SIZE = D3DXVECTOR2(512.f * WINDOW_SCALE.x, 512.0f * WINDOW_SCALE.y);

// string texture_id
const Texture::TEXTURE_ID SELECT_STRING_TEXTURE[] = {
	Texture::TEXTURE_ID_GENERAL_STRING_YES,
	Texture::TEXTURE_ID_GENERAL_STRING_NO };

//=============================================================================
// constructor
//=============================================================================
TutorialBack::TutorialBack(void)
	:window_(nullptr)
	,dest_frame_count_(DEST_FRAME_COUNT)
	,is_show_(false)
	,is_move_(false)
	,window_position_(DEFAULT_POSITION)
	,window_size_(WINDOW_SIZE)
{
}

//=============================================================================
// destructor
//=============================================================================
TutorialBack::~TutorialBack(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool TutorialBack::Initialize(void)
{
	// window
	window_ = new MessageSpriteSmooth();
	window_->Initialize();
	window_->__texture_id(Texture::TEXTURE_ID_GENERAL_WINDOW);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void TutorialBack::Uninitialize(void)
{
	SafeRelease(window_);
}

//=============================================================================
// update
//=============================================================================
void TutorialBack::Update(void)
{
	window_->Update();

	const bool is_move = window_->__move_flag_();

	if(is_move_ == true && is_move == false){
		is_move_ = false;
	}
}

//=============================================================================
// draw
//=============================================================================
void TutorialBack::Draw(void)
{
	window_->Draw();
}

//=============================================================================
// show
//-----------------------------------------------------------------------------
// —Ç‚¢Š´‚¶‚ÉŠJ‚­
//=============================================================================
void TutorialBack::Show(void)
{
	is_show_ = true;
	is_move_ = true;

	// window
	window_->__position(window_position_);
	window_->__size(DEFAULT_SIZE);
	window_->__color(CLEAR_COLOR);
	window_->__dest_position(window_position_);
	window_->__dest_size(window_size_);
	window_->__dest_color(SHOW_COLOR);
	window_->__dest_frame(dest_frame_count_);
	window_->StartMove();
}

//=============================================================================
// close
//-----------------------------------------------------------------------------
// —Ç‚¢Š´‚¶‚É•Â‚¶‚é
//=============================================================================
void TutorialBack::Close(void)
{
	is_show_ = false;
	is_move_ = true;

	// window
	window_->__position(window_->__position());
	window_->__size(window_->__size());
	window_->__color(SHOW_COLOR);
	window_->__dest_position(window_position_);
	window_->__dest_size(DEFAULT_SIZE);
	window_->__dest_color(CLEAR_COLOR);
	window_->__dest_frame(dest_frame_count_);
	window_->StartMove();
}

//---------------------------------- EOF --------------------------------------
