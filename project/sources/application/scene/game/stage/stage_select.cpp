//*****************************************************************************
//
// stage select
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_select.h"
#include "stage_factory.h"
#include "stage_manager.h"
#include "application/object/stage_select/select_bg.h"
#include "application/object/stage_region.h"
#include "render/sprite.h"
#include "system/system.h"
#include "scene/game/scene_game.h"
#include "application/object/stage_select/select_arrow.h"
#include "application/object/record.h"
#include "application/object/message_window.h"
#include "scene/factory/scene_factory.h"
#include "application/object/object_player.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 DEST_FRAME_COUNT = 20;						// �E�B���h�E�J�̎���
const f32 REGION_INTERVAL = (850.0f*0.87f)*1.3f;		// ���M�I���̊Ԋu
const f32 REGION_MOVE = 960.f;							// ���M�I���̊Ԋu

//=============================================================================
// constructor
//=============================================================================
StageSelect::StageSelect(void)
		:Stage(TYPE_SELECT)
{
}

//=============================================================================
// destructor
//=============================================================================
StageSelect::~StageSelect(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageSelect::Initialize(void)
{
	//�w�i
	select_bg_ = new SelectBg();
	select_bg_->Initialize();

	//�u���[�j���X
	nas_ = new ObjectPlayer();
	nas_ -> Initialize();
	nas_ -> __position(D3DXVECTOR2(200.f,500.f));
	nas_ -> StartAnimation(ObjectPlayer::ANIMATION_TYPE_WAIT);
	nas_ -> StartAnimation(ObjectPlayer::ANIMATION_TYPE_WAIT);
	nas_->__is_flip(false);

	//���
	select_arrow_ = new SelectArrow();
	select_arrow_ ->Initialize();

	//���R�[�h�ǂݍ��ݏ�����
	record_ = new Record();
	record_->Initialize();

	//���R�[�h�t�@�C���ǂݍ���
	record_->LoadFile("data/stage/record.bin");

	record_->SaveFileClear("data/stage/record.bin",TYPE_MAX-1);

	//���R�[�h�ۑ��i�Ă��Ɓ[�j
	record_->__record(0,6112);
	record_->__record(1,18134);
	record_->__record(2,33356);

	//���R�[�h�t�@�C���o��
	record_->SaveFileClear("data/stage/record.bin",TYPE_MAX-1);


	////�Z���N�g�gx�X�e�[�W��
	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_ = new StageRegion();
		regions_[i].region_->Initialize();
		regions_[i].position_ = D3DXVECTOR2(i*REGION_INTERVAL,0.0f);
		regions_[i].region_->__set_position(regions_[i].position_);
		regions_[i].type_ = ((TYPE)(i+1));
		regions_[i].region_->__set_stage_id(regions_[i].type_);
		regions_[i].region_->__set_time(record_->__record(i));
	}

	// message_window
	message_window_ = new MessageWindow();
	message_window_->Initialize();
	message_window_->__dest_frame_count(DEST_FRAME_COUNT);
	message_window_->__title_texture_id_(Texture::TEXTURE_ID_SELECT_STRING_RETURN_TITLE);
	massage_flag_ = false;

	update_type_ = UPDATE_TYPE_SELECT;

	//���̃X�e�[�W
	current_stage_ = TYPE_TUTORIAL;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageSelect::Uninitialize(void)
{
	SafeRelease(select_bg_);
	SafeRelease(select_arrow_);	
	SafeRelease(message_window_);
	SafeRelease(record_);
	SafeRelease(nas_);
	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		SafeRelease(regions_[i].region_);
	}
}

//=============================================================================
// update
//=============================================================================
void StageSelect::Update(void)
{
	switch(update_type_)
	{
	case UPDATE_TYPE_SELECT:		//�V�т����X�e�[�W��I��
		SelectUpdate();
		break;
	case UPDATE_TYPE_MASSAGE:		//�^�C�g���ɖ߂�H
		MassageUpdate();
		break;
	case UPDATE_TYPE_YORN:			//���̃X�e�[�W�ŗV��?
		YorNUpdate();
		break;
	}
	message_window_->Update();
}

//=============================================================================
// draw
//=============================================================================
void StageSelect::Draw(void)
{
	select_bg_->Draw();

	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_->Draw();
	}

	if(regions_[1].region_->__get_move_falg() == false)
		select_arrow_->Draw();
	nas_->Draw();

	message_window_->Draw();
}

//=============================================================================
// �X�e�[�W��I��ł�Ƃ��̍X�V
//=============================================================================
void StageSelect::SelectUpdate()
{
	if(regions_[0].region_->__get_move_falg() == false)	//���M�I���������ĂȂ��Ƃ�
	{
		//�K�v�ȏ�ɉE�ɍs���Ȃ�
		if(current_stage_ !=TYPE_MAX-1)
		{
			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RIGHT))
			{
				for(u32 i=0;i<TYPE_MAX-1;i++)
				{
					regions_[i].region_->__set_region_distpos(D3DXVECTOR2(-REGION_MOVE,0.0f));
					select_bg_->__set_distmove(-0.06f);
				}
				current_stage_++;
				nas_->__is_flip(false);
			}
		}

		//�K�v�ȏ�ɍ��ɍs���Ȃ�
		if(current_stage_!=TYPE_TUTORIAL)
		{
			if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_LEFT))
			{
				for(u32 i=0;i<TYPE_MAX-1;i++)
				{
					regions_[i].region_->__set_region_distpos(D3DXVECTOR2(REGION_MOVE,0.0f));
					select_bg_->__set_distmove(0.06f);
				}
				current_stage_--;
				nas_->__is_flip(true);
			}
		}

		//���艟���ꂽ�Ƃ�
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RETURN))
		{
			if(message_window_->__is_move() == false)
			{
				message_window_->Show();
				update_type_ = UPDATE_TYPE_YORN;
			}
		}
		//�L�����Z�������ꂽ�Ƃ����b�Z�[�W�\��
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
		{
			if(message_window_->__is_move() == false)
			{
				message_window_->Show();
				update_type_ = UPDATE_TYPE_MASSAGE;
			}
		}
	}
	//�w�i�X�V
	select_bg_->Update();

	//���X�V
	select_arrow_->__set_stage_id((Stage::TYPE)current_stage_);
	select_arrow_ ->Update();

	//�܂Ƃ܂�ɍX�V��������
	for(u32 i=0;i<TYPE_MAX-1;i++)
	{
		regions_[i].region_->Update();
	}

	//�j���X�X�V
	if(regions_[0].region_->__get_move_falg() == false)
	{
		nas_->__is_flip(false);
		nas_ -> StartAnimation(ObjectPlayer::ANIMATION_TYPE_WAIT);
	}
	else if(regions_[0].region_->__get_move_falg() == true)
	{
		nas_ -> StartAnimation(ObjectPlayer::ANIMATION_TYPE_RUN);
	}
	nas_->Update();

}

//=============================================================================
// ���b�Z�[�W�E�B���h�E���o�Ă�Ƃ��̍X�V
//=============================================================================
void StageSelect::MassageUpdate()
{
	//�\���L�[���͎�
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
	{
		message_window_->SelectDown();
	}
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		message_window_->SelectUp();
	}
	//����L�[�����ꂽ�Ƃ�
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RETURN))
	{
		//�C�G�X�̎�
		if(message_window_->__is_select() == 0)
		{
			// �^�C�g���ɖ߂�
			if(next_scene_factory_ == nullptr)
			{
				next_scene_factory_ = new TitleFactory();
			}
		}
		//�m�[�̎�
		if(message_window_->__is_select() == 1)
		{
			//�E�B���h�E�����
			if(message_window_->__is_move() == false)
			{
				message_window_->Close();
				update_type_ = UPDATE_TYPE_SELECT;
			}
		}
	}

	//�L�����Z�������ꂽ�Ƃ����b�Z�[�W����
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Close();
			update_type_ = UPDATE_TYPE_SELECT;
		}
	}
}

//=============================================================================
// �z���g�ɂ��̃X�e�[�W�ŗV�Ԃ������Ă�Ƃ��̍X�V
//=============================================================================
void StageSelect::YorNUpdate()
{
	//�\���L�[���͎�
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
	{
		message_window_->SelectDown();
	}
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
	{
		message_window_->SelectUp();
	}

	//����L�[�����ꂽ�Ƃ�
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RETURN))
	{
		//�C�G�X�̎�
		if(message_window_->__is_select() == 0)
		{
			if(next_stage_factory_ == nullptr)
			{
				//�Q�[���Ɉڂ�
				switch(current_stage_)
				{
				case TYPE_TUTORIAL:		//�`���[�g���A���s����
				default:
						next_stage_factory_ = new TutorialFactory();
					break;
				case TYPE_STAGE1:
					next_stage_factory_ = new TutorialFactory();
					break;
				case TYPE_STAGE2:
					next_stage_factory_ = new TutorialFactory();
					break;
				}
			}
		}
		//���b�Z�[�W�����
		if(message_window_->__is_select() == 1)
		{	
			if(message_window_->__is_move() == false)
			{
				message_window_->Close();
				update_type_ = UPDATE_TYPE_SELECT;
			}
		}
	}

	//�L�����Z�������ꂽ�Ƃ����b�Z�[�W����
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Close();
			update_type_ = UPDATE_TYPE_SELECT;
		}
	}
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageSelect::CreateFactory(void)const
{
	return new SelectFactory();
}

//---------------------------------- EOF --------------------------------------
