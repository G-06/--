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
#include "stage_select/select_bg.h"
#include "stage_region.h"
#include "render/sprite.h"
#include "system/system.h"
#include "scene/game/scene_game.h"
#include "stage_select/select_arrow.h"
#include "message_window.h"

//*****************************************************************************
// constant definition
//*****************************************************************************


const u32 DEST_FRAME_COUNT = 20;				// �E�B���h�E�J�̎���
const f32 REGIONS_INTERVAL = 600.0f;			// ���M�I�����m�̊Ԋu x����


//=============================================================================
// constructor
//=============================================================================
StageSelect::StageSelect(void)
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
	if(!SafeInitialize(select_bg_))
	{
		return false;
	}

	//�u���[�j���X

	//�Z���N�g���
	select_arrow_ = new SelectArrow();
	if(!SafeInitialize(select_arrow_))
	{
		return false;
	}


	//�Z���N�g�gx�X�e�[�W��
	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		//�܂Ƃ܂�����
		regions_[i] = new StageRegion();
		if(!SafeInitialize(regions_[i]))
		{
			return false;
		}
		//�܂Ƃ܂�ɃX�e�[�W����^����
		regions_[i]->__set_stage_id((STAGE_ID)i);
		regions_[i]->__set_region_distpos(D3DXVECTOR2(i*REGIONS_INTERVAL,0.0f));
	}

	//�X�R�A�^�C�����蓖�āi�b��j
	regions_[0]->__set_time(0);
	regions_[1]->__set_time(234);
	regions_[2]->__set_time(181);

	// message_window
	message_window_ = new MessageWindow();
	message_window_->Initialize();
	message_window_->__dest_frame_count(DEST_FRAME_COUNT);

	massage_flag_ = false;

	update_type_ = UPDATE_TYPE_SELECT;

	//���̃X�e�[�W
	current_stage_ = 0;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageSelect::Uninitialize(void)
{
	SafeRelease(select_bg_);
	SafeRelease(select_arrow_);	

	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		SafeRelease(regions_[i]);
	}
	SafeRelease(message_window_);

}

//=============================================================================
// update
//=============================================================================
void StageSelect::Update(void)
{
	switch(update_type_)
	{
	case UPDATE_TYPE_SELECT:
		SelectUpdate();
		break;
	case UPDATE_TYPE_MASSAGE:
		MassageUpdate();
		break;
	case UPDATE_TYPE_YORN:

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

	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		regions_[i]->Draw();
	}

	select_arrow_->Draw();

	message_window_->Draw();
}

//=============================================================================
// �X�e�[�W��I��ł�Ƃ��̍X�V
//=============================================================================
void StageSelect::SelectUpdate()
{
	//�I�𒆂̃X�e�[�W���E�[����Ȃ��Ƃ�
	if(current_stage_ !=STAGE_ID_MAX-1)
	{
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_RIGHT))
		{
			for(u32 i=0;i<STAGE_ID_MAX;i++)
			{
				regions_[i]->__set_region_distpos(D3DXVECTOR2(-REGIONS_INTERVAL,0.0f));
			}
			current_stage_++;
		}
	}
	//�I�𒆂̃X�e�[�W�����[����Ȃ��Ƃ�
	if(current_stage_!=0)
	{
		if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_LEFT))
		{
			for(u32 i=0;i<STAGE_ID_MAX;i++)
			{
				regions_[i]->__set_region_distpos(D3DXVECTOR2(REGIONS_INTERVAL,0.0f));
			}
			current_stage_--;
		}
	}

	//����������ꂽ�Ƃ��I�𒆂̃X�e�[�W��`����
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_RETURN))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Show();
		}
		update_type_ = UPDATE_TYPE_YORN;

	}
	//���ɑI�𒆂̃X�e�[�W��`���čX�V
	select_arrow_->__set_stage_id((STAGE_ID)current_stage_);
	select_arrow_ ->Update();

	//�܂Ƃ܂�ɍX�V��������
	for(u32 i=0;i<STAGE_ID_MAX;i++)
	{
		regions_[i]->Update();
	}
	//�L�����Z�������ꂽ�Ƃ����b�Z�[�W�\��
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Show();
		}
		update_type_ = UPDATE_TYPE_MASSAGE;
	}

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
	if(GET_DIRECT_INPUT->CheckPress(INPUT_EVENT_RETURN))
	{
		//�C�G�X�̎�
		if(message_window_->__is_select() == 0)
		{
			// �^�C�g���ɖ߂�
			SceneGame::__next_stage(STAGE_ID_END);
		}
		//�m�[�̎�
		if(message_window_->__is_select() == 1)
		{
			//�E�B���h�E�����
			if(message_window_->__is_move() == false)
			{
				message_window_->Close();
			}
			update_type_ = UPDATE_TYPE_SELECT;
		}
	}

	//�L�����Z�������ꂽ�Ƃ����b�Z�[�W�\��
	if(GET_DIRECT_INPUT->CheckTrigger(INPUT_EVENT_VIRTUAL_CANCEL))
	{
		if(message_window_->__is_move() == false)
		{
			message_window_->Close();
		}
		update_type_ = UPDATE_TYPE_SELECT;
	}
}

//=============================================================================
// �z���g�ɂ��̃X�e�[�W�ŗV�Ԃ������Ă�Ƃ��̍X�V
//=============================================================================
void StageSelect::YorNUpdate()
{
	SceneGame::__next_stage((STAGE_ID)current_stage_);

}



//---------------------------------- EOF --------------------------------------
