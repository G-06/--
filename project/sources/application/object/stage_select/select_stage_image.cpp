//*****************************************************************************
//
// �I�΂��X�e�[�W�̂܂Ƃ܂�
//	���S���W		player_->__point(
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "select_stage_image.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 StageImage::STAGE_SIZE = D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH * 2.0f,(f32)DEFAULT_SCREEN_HEIGHT);
const D3DXVECTOR2 StageImage::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.464f);
const D3DXVECTOR2 StageImage::DEFAULT_SIZE = D3DXVECTOR2(690.0f,415.0f);

//=============================================================================
// constructor
//=============================================================================
StageImage::StageImage(void)
	:size_(STAGE_SIZE)
	,offset_position_(0.0f,0.0f)
	,image_(nullptr)
{
}

//=============================================================================
// destructor
//=============================================================================
StageImage::~StageImage(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageImage::Initialize(void)
{
	image_ = new Sprite();

	if(!SafeInitialize(image_))
	{
		return false;
	}

	image_->__size(DEFAULT_SIZE);
	image_->__position(DEFAULT_POSITION);
	image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_1);
	image_->__index((u32)0);
	image_->__point(Sprite::POINT_CENTER);
	image_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageImage::Uninitialize(void)
{
	SafeRelease(image_);
}

//=============================================================================
// update
//=============================================================================
void StageImage::Update(void)
{
	//�ʒu�̍X�V
	image_->__position(D3DXVECTOR2(DEFAULT_POSITION.x + offset_position_.x,DEFAULT_POSITION.y + offset_position_.y));
	image_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void StageImage::Draw(void)
{
	image_->Draw();
}

//=============================================================================
//�X�e�[�W�C���[�W�e�N�X�`���̐ݒ�
//=============================================================================
void StageImage::__set_image_texture(Stage::TYPE stage)
{
	switch(stage)
	{
	case Stage::TYPE_TUTORIAL:	//�`���[�g���A��
	case Stage::TYPE_MAX:
	default:
		//�X�e�[�W�C���[�W���悭�킩��Ȃ����̂̎��͂��ׂăe�X�g�e�N�X�`���ŕ\��
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_TUTORIAL);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE1:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_1);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE2:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_2);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE3:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_3);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE4:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_4);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE5:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_5);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE6:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_6);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE7:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_7);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE8:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_8);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE9:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_9);
		image_->SetParameter();
		break;
	case Stage::TYPE_STAGE10:
		image_->__texture_id(Texture::TEXTURE_ID_SELECT_IMAGE_STAGE_10);
		image_->SetParameter();
		break;
	}
}

//---------------------------------- EOF --------------------------------------
