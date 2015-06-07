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
#include "message_window.h"
#include "system/system.h"
#include "object/message_sprite_smooth.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 MessageWindow::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 MessageWindow::DEFAULT_SIZE = D3DXVECTOR2(0.0f, 0.0f);

const u32 DEST_FRAME_COUNT = 30;
const s32 DEFAULT_SELECT = 1;
const D3DXCOLOR CLEAR_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
const D3DXCOLOR SHOW_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXVECTOR2 WINDOW_SIZE = D3DXVECTOR2(700.0f, 300.0f);
const D3DXVECTOR2 TITLE_SIZE = D3DXVECTOR2(500.0f, 60.0f);
const D3DXVECTOR2 SELECT_SIZE = D3DXVECTOR2(270.0f, 80.0f);

const D3DXVECTOR2 SELECT_POSITION_OFFSET = D3DXVECTOR2(170.0f, 60.0f);
const D3DXVECTOR2 TITLE_POSITION_OFFSET = D3DXVECTOR2(0.0f, -80.0f);

// string texture_id
const Texture::TEXTURE_ID SELECT_STRING_TEXTURE[] = {
	Texture::TEXTURE_ID_TITLE_STRING_TEST_A,
	Texture::TEXTURE_ID_TITLE_STRING_TEST_A };

//=============================================================================
// constructor
//=============================================================================
MessageWindow::MessageWindow(void)
	:window_(nullptr)
	,title_(nullptr)
	,dest_frame_count_(DEST_FRAME_COUNT)
	,is_show_(false)
	,is_move_(false)
	,window_position_(DEFAULT_POSITION)
	,window_size_(WINDOW_SIZE)
	,title_size_(TITLE_SIZE)
	,select_size_(SELECT_SIZE)
	,is_select_(DEFAULT_SELECT)
{
	memset(frame_, NULL, sizeof(frame_));
	memset(select_, NULL, sizeof(select_));
}

//=============================================================================
// destructor
//=============================================================================
MessageWindow::~MessageWindow(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool MessageWindow::Initialize(void)
{
	// window
	window_ = new MessageSpriteSmooth();
	window_->Initialize();

	// title
	title_ = new MessageSpriteSmooth();
	title_->Initialize();
	title_->__texture_id(Texture::TEXTURE_ID_TITLE_STRING_TEST_A);

	for(int i = 0 ; i < SELECT_MAX ; i++){

		// frame
		frame_[i] = new MessageSpriteSmooth();
		frame_[i]->Initialize();
		if(i != is_select_){
			frame_[i]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
		}else{
			frame_[i]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
		}

		// select
		select_[i] = new MessageSpriteSmooth();
		select_[i]->Initialize();
		select_[i]->__texture_id(SELECT_STRING_TEXTURE[i]);
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void MessageWindow::Uninitialize(void)
{
	SafeRelease(window_);
	SafeRelease(title_);
	
	for(int i = 0 ; i < SELECT_MAX ; i++){
		SafeRelease(frame_[i]);
		SafeRelease(select_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void MessageWindow::Update(void)
{
	window_->Update();
	title_->Update();

	for(int i = 0 ; i < SELECT_MAX ; i++){
		frame_[i]->Update();
		select_[i]->Update();
	}

	const bool is_move = window_->__move_flag_();

	if(is_move_ == true && is_move == false){
		is_move_ = false;
	}

		//bool show = false;
		//if(window_->__move_flag_()) show = true;
		//if(show == false) is_show_ = false;	}
}

//=============================================================================
// draw
//=============================================================================
void MessageWindow::Draw(void)
{
	window_->Draw();
	title_->Draw();

	for(int i = 0 ; i < SELECT_MAX ; i++){
		frame_[i]->Draw();
		select_[i]->Draw();
	}
}

//=============================================================================
// show
//-----------------------------------------------------------------------------
// —Ç‚¢Š´‚¶‚ÉŠJ‚­
//=============================================================================
void MessageWindow::Show(void)
{
	is_select_ = DEFAULT_SELECT;
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

	// title
	const D3DXVECTOR2 title_position = D3DXVECTOR2(window_position_.x + TITLE_POSITION_OFFSET.x, window_position_.y + TITLE_POSITION_OFFSET.y);
	title_->__position(window_position_);
	title_->__size(DEFAULT_SIZE);
	title_->__color(CLEAR_COLOR);
	title_->__dest_position(title_position);
	title_->__dest_size(title_size_);
	title_->__dest_color(SHOW_COLOR);
	title_->__dest_frame(dest_frame_count_);
	title_->StartMove();

	for(int i = 0 ; i < SELECT_MAX ; i++){

		// frame
		const float x = i * SELECT_POSITION_OFFSET.x * 2.0f;
		const D3DXVECTOR2 select_position = D3DXVECTOR2(window_position_.x - SELECT_POSITION_OFFSET.x + x, window_position_.y + SELECT_POSITION_OFFSET.y);
		frame_[i]->__position(window_position_);
		frame_[i]->__size(DEFAULT_SIZE);
		frame_[i]->__color(CLEAR_COLOR);
		frame_[i]->__dest_position(select_position);
		frame_[i]->__dest_size(select_size_);
		frame_[i]->__dest_color(SHOW_COLOR);
		frame_[i]->__dest_frame(dest_frame_count_);
		if(i != is_select_){
			frame_[i]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
		}else{
			frame_[i]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
		}
		frame_[i]->StartMove();

		// select
		select_[i]->__position(window_position_);
		select_[i]->__size(DEFAULT_SIZE);
		select_[i]->__color(CLEAR_COLOR);
		select_[i]->__dest_position(select_position);
		select_[i]->__dest_size(select_size_);
		select_[i]->__dest_color(SHOW_COLOR);
		select_[i]->__dest_frame(dest_frame_count_);
		select_[i]->StartMove();
	}
}

//=============================================================================
// close
//-----------------------------------------------------------------------------
// —Ç‚¢Š´‚¶‚É•Â‚¶‚é
//=============================================================================
void MessageWindow::Close(void)
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

	// title
	title_->__position(title_->__position());
	title_->__size(title_->__size());
	title_->__color(SHOW_COLOR);
	title_->__dest_position(window_position_);
	title_->__dest_size(DEFAULT_SIZE);
	title_->__dest_color(CLEAR_COLOR);
	title_->__dest_frame(dest_frame_count_);
	title_->StartMove();

	for(int i = 0 ; i < SELECT_MAX ; i++){

		// frame
		frame_[i]->__position(frame_[i]->__position());
		frame_[i]->__size(frame_[i]->__size());
		frame_[i]->__color(SHOW_COLOR);
		frame_[i]->__dest_position(window_position_);
		frame_[i]->__dest_size(DEFAULT_SIZE);
		frame_[i]->__dest_color(CLEAR_COLOR);
		frame_[i]->__dest_frame(dest_frame_count_);
		frame_[i]->StartMove();

		// select
		select_[i]->__position(select_[i]->__position());
		select_[i]->__size(select_[i]->__size());
		select_[i]->__color(SHOW_COLOR);
		select_[i]->__dest_position(window_position_);
		select_[i]->__dest_size(DEFAULT_SIZE);
		select_[i]->__dest_color(CLEAR_COLOR);
		select_[i]->__dest_frame(dest_frame_count_);
		select_[i]->StartMove();
	}
}

//=============================================================================
// SelectUp
//=============================================================================
void MessageWindow::SelectUp(void)
{
	const s32 old_select = is_select_;
	is_select_++;
	if(is_select_ >= SELECT_MAX) is_select_ = SELECT_MAX - 1;
	if(is_select_ == old_select) return;

	_ChangeSelect(is_select_, old_select);
}

//=============================================================================
// SelectDown
//=============================================================================
void MessageWindow::SelectDown(void)
{
	const s32 old_select = is_select_;
	is_select_--;
	if(is_select_ < 0) is_select_ = 0;
	if(is_select_ == old_select) return;

	_ChangeSelect(is_select_, old_select);
}

//=============================================================================
// _ChangeSelect
//=============================================================================
void MessageWindow::_ChangeSelect(const s32& now, const s32& old)
{
	frame_[now]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
	frame_[old]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
}

//=============================================================================
// __title_texture_id_
//=============================================================================
void MessageWindow::__title_texture_id_(const Texture::TEXTURE_ID& texture_id)
{
	title_->__texture_id(texture_id);
}

//---------------------------------- EOF --------------------------------------
