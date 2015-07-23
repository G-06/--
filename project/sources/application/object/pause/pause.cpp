//*****************************************************************************
//
// pause
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "pause.h"
#include "system/system.h"
#include "sprite_smooth.h"
#include "system/directx9/texture/texture.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 Pause::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 Pause::DEFAULT_SIZE = D3DXVECTOR2(0.0f, 0.0f);

// frame count
const u32 DEST_FRAME_COUNT = 15;
const f32 FRAME_COUNT_RATE = 0.4f;

// defalt select
const s32 DEFAULT_SELECT = 0;

// color
const D3DXCOLOR CLEAR_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
const D3DXCOLOR SHOW_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR BACKGROUND_COLOR = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.35f);
const D3DXCOLOR BACKGROUND_CLEAR_COLOR = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

// size
const D3DXVECTOR2 TITLE_SIZE = D3DXVECTOR2(512.0f, 128.0f);
const f32 SELECT_SIZE_SCALE = 1.0f;
const D3DXVECTOR2 SELECT_SIZE = D3DXVECTOR2(256.0f * SELECT_SIZE_SCALE, 64.0f * SELECT_SIZE_SCALE);
const D3DXVECTOR2 BACKGROUND_SIZE = D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH, (f32)DEFAULT_SCREEN_HEIGHT);

// position offset
const D3DXVECTOR2 TITLE_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, 120.0f);
const D3DXVECTOR2 SELECT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, 250.0f);
const D3DXVECTOR2 SELECT_POSITION_OFFSET = D3DXVECTOR2(0.0f, 90.0f);

// frame size
const D3DXVECTOR2 FRAME_SIZE = D3DXVECTOR2(324.0f,71.0f);

// string texture_id
const Texture::TEXTURE_ID SELECT_STRING_TEXTURE[Pause::SELECT_TYPE_MAX] = {
	Texture::TEXTURE_ID_PAUSE_STRING_PAUSE_RETURN,
	Texture::TEXTURE_ID_PAUSE_STRING_PAUSE_RETRY,
	Texture::TEXTURE_ID_PAUSE_STRING_PAUSE_SELECT_BACK,
	Texture::TEXTURE_ID_PAUSE_STRING_PAUSE_OPTION,
};

//=============================================================================
// constructor
//=============================================================================
Pause::Pause(void)
	:title_(nullptr)
	,bg_(nullptr)
	,dest_frame_count_(DEST_FRAME_COUNT)
	,is_show_(false)
	,is_move_(false)
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
Pause::~Pause(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Pause::Initialize(void)
{
	// back ground
	bg_ = new SpriteSmooth();
	bg_->Initialize();
	bg_->__color(BACKGROUND_CLEAR_COLOR);

	// title
	//title_ = new SpriteSmooth();
	//title_->Initialize();
	//title_->__texture_id(Texture::TEXTURE_ID_PAUSE_STRING_PAUSE);

	for(int i = 0 ; i < SELECT_MAX ; i++){

		// frame
		frame_[i] = new SpriteSmooth();
		frame_[i]->Initialize();
		frame_[i]->__size(FRAME_SIZE);
		if(i != is_select_){
			frame_[i]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
		}else{
			frame_[i]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
		}

		// select
		select_[i] = new SpriteSmooth();
		select_[i]->Initialize();
		select_[i]->__texture_id(SELECT_STRING_TEXTURE[i]);
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Pause::Uninitialize(void)
{
//	SafeRelease(title_);
	SafeRelease(bg_);
	
	for(int i = 0 ; i < SELECT_MAX ; i++){
		SafeRelease(frame_[i]);
		SafeRelease(select_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void Pause::Update(void)
{
	bg_->Update();
//	title_->Update();

	for(int i = 0 ; i < SELECT_MAX ; i++){
		frame_[i]->Update();
		select_[i]->Update();
	}

	if(is_move_ == true && select_[0]->__is_move() == false){
		is_move_ = false;
	}
}

//=============================================================================
// draw
//=============================================================================
void Pause::Draw(void)
{
	if(is_move_ == false && is_show_ == false) return;

	// bg
	bg_->Draw();

	// titole
//	title_->Draw();

	// select
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
void Pause::Show(void)
{
	is_select_ = DEFAULT_SELECT;
	is_show_ = true;
	is_move_ = true;

	GET_SE->Play(SE::SE_ID_PAUSE);

	// bg
	const u32 frame_count = dest_frame_count_ -u32(dest_frame_count_ * FRAME_COUNT_RATE);
	bg_->__position(DEFAULT_POSITION);
	bg_->__size(BACKGROUND_SIZE);
	bg_->__color(BACKGROUND_CLEAR_COLOR);
	bg_->__dest_position(DEFAULT_POSITION);
	bg_->__dest_size(BACKGROUND_SIZE);
	bg_->__dest_color(BACKGROUND_COLOR);
	bg_->__dest_frame(frame_count);
	bg_->StartMove();

	// title
	//const D3DXVECTOR2 title_position = D3DXVECTOR2(TITLE_POSITION.x, TITLE_POSITION.y);
	//title_->__position(DEFAULT_POSITION);
	//title_->__size(DEFAULT_SIZE);
	//title_->__color(CLEAR_COLOR);
	//title_->__dest_position(title_position);
	//title_->__dest_size(title_size_);
	//title_->__dest_color(SHOW_COLOR);
	//title_->__dest_frame(dest_frame_count_);
	//title_->StartMove();

	for(int i = 0 ; i < SELECT_MAX ; i++){

		// frame
		const D3DXVECTOR2 select_position = D3DXVECTOR2(SELECT_POSITION.x,
														(SELECT_POSITION_OFFSET.y * i) + SELECT_POSITION.y);
		frame_[i]->__position(DEFAULT_POSITION);
		frame_[i]->__size(DEFAULT_SIZE);
		frame_[i]->__color(CLEAR_COLOR);
		frame_[i]->__dest_position(select_position);
		frame_[i]->__dest_size(FRAME_SIZE);
		frame_[i]->__dest_color(SHOW_COLOR);
		frame_[i]->__dest_frame(dest_frame_count_);
		if(i != is_select_){
			frame_[i]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
		}else{
			frame_[i]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
		}
		frame_[i]->StartMove();

		// select
		select_[i]->__position(DEFAULT_POSITION);
		select_[i]->__size(DEFAULT_SIZE);
		select_[i]->__color(CLEAR_COLOR);
		select_[i]->__dest_position(select_position);
//		select_[i]->__dest_size(select_size_);
		select_[i]->__dest_color(SHOW_COLOR);
		select_[i]->__dest_frame(dest_frame_count_);

		if(i == SELECT_TYPE_RETRY || i == SELECT_TYPE_OPTION){
			const f32 select_size_scale = 0.9f;
			select_[i]->__dest_size(select_size_ * select_size_scale);
		}else{
			select_[i]->__dest_size(select_size_);
		}
		select_[i]->StartMove();
	}
}

//=============================================================================
// close
//-----------------------------------------------------------------------------
// —Ç‚¢Š´‚¶‚É•Â‚¶‚é
//=============================================================================
void Pause::Close(void)
{
	is_show_ = false;
	is_move_ = true;

	GET_SE->Play(SE::SE_ID_PAUSE);

	// bg
	const u32 frame_count = dest_frame_count_ -u32(dest_frame_count_ * FRAME_COUNT_RATE);
	bg_->__position(DEFAULT_POSITION);
	bg_->__size(BACKGROUND_SIZE);
	bg_->__color(BACKGROUND_COLOR);
	bg_->__dest_position(DEFAULT_POSITION);
	bg_->__dest_size(BACKGROUND_SIZE);
	bg_->__dest_color(BACKGROUND_CLEAR_COLOR);
	bg_->__dest_frame(frame_count);
	bg_->StartMove();

	// title
	//title_->__position(title_->__position());
	//title_->__size(title_->__size());
	//title_->__color(SHOW_COLOR);
	//title_->__dest_position(DEFAULT_POSITION);
	//title_->__dest_size(DEFAULT_SIZE);
	//title_->__dest_color(CLEAR_COLOR);
	//title_->__dest_frame(dest_frame_count_);
	//title_->StartMove();

	for(int i = 0 ; i < SELECT_MAX ; i++){

		// frame
		frame_[i]->__position(frame_[i]->__position());
		frame_[i]->__size(frame_[i]->__size());
		frame_[i]->__color(SHOW_COLOR);
		frame_[i]->__dest_position(DEFAULT_POSITION);
		frame_[i]->__dest_size(DEFAULT_SIZE);
		frame_[i]->__dest_color(CLEAR_COLOR);
		frame_[i]->__dest_frame(dest_frame_count_);
		frame_[i]->StartMove();

		// select
		select_[i]->__position(select_[i]->__position());
		select_[i]->__size(select_[i]->__size());
		select_[i]->__color(SHOW_COLOR);
		select_[i]->__dest_position(DEFAULT_POSITION);
		select_[i]->__dest_size(DEFAULT_SIZE);
		select_[i]->__dest_color(CLEAR_COLOR);
		select_[i]->__dest_frame(dest_frame_count_);
		select_[i]->StartMove();
	}
}

//=============================================================================
// SelectUp
//=============================================================================
void Pause::SelectUp(void)
{
	const s32 old_select = is_select_;
	is_select_++;
	if(is_select_ >= SELECT_MAX) is_select_ = 0;
	if(is_select_ == old_select) return;

	_ChangeSelect(is_select_, old_select);
}

//=============================================================================
// SelectDown
//=============================================================================
void Pause::SelectDown(void)
{
	const s32 old_select = is_select_;
	is_select_--;
	if(is_select_ < 0) is_select_ = SELECT_MAX - 1;
	if(is_select_ == old_select) return;

	_ChangeSelect(is_select_, old_select);
}

//=============================================================================
// _ChangeSelect
//=============================================================================
void Pause::_ChangeSelect(const s32& now, const s32& old)
{
	frame_[now]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_001);
	frame_[old]->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);
	GET_SE->Play(SE::SE_ID_CURSOR);
}

//=============================================================================
// __title_texture_id_
//=============================================================================
void Pause::__title_texture_id_(const Texture::TEXTURE_ID& texture_id)
{
	title_->__texture_id(texture_id);
}

//=============================================================================
// __title_texture_id_
//=============================================================================
bool Pause::__select_texture_id_(const s32& select_number, const Texture::TEXTURE_ID& texture_id)
{
	if(select_number >= SELECT_MAX){
		return false;
	}

	frame_[select_number]->__texture_id(texture_id);
	return true;
}


//---------------------------------- EOF --------------------------------------
