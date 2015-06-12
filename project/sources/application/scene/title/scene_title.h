//*****************************************************************************
//
// scene title
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "scene/scene.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class TitleBg;
class TitleLogo;
class TitlePushStart;
class TitleSelect;
class MessageWindow;
class Option;

//*****************************************************************************
// class definition
//*****************************************************************************
class SceneTitle : public Scene
{
public:
	// constructor
	SceneTitle(void);

	// destructor
	virtual ~SceneTitle(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// create factory
	SceneFactory* CreateFactory(void)const;

	// �I�������
	enum SELECT_TYPE{
		SELECT_START = 0,
		SELECT_OPTION,
		SELECT_END,
		SELECT_MAX
	};

	// ���[�h���
	enum MODE{
		MODE_NONE = -1,
		MODE_PUSH,
		MODE_SELECT,
		MODE_MESSAGE,
		MODE_MAX
	};

private:

	static const u32 GO_LOGO_FRAME;

	typedef struct _TITLE_SELECT{
		TitleSelect*	select_;
		TitleSelect*	frame_;
	} TITLE_SELECT;

	// ���[�h��Update
	void _UpdatePush(void);
	void _UpdateSelect(void);
	void _UpdateMessage(void);

	// bg
	TitleBg* bg_;

	// tittle_logo
	TitleLogo* logo_;

	// title push_shtart
	TitlePushStart* push_;
	TitlePushStart* push_frame_;

	// select
	TITLE_SELECT select_[SELECT_MAX];

	// message_window
	MessageWindow* message_window_;

	// ���S�ɖ߂�J�E���^�[
	u32 frame_count_;

	// �I�𒆂̑I����
	s32 current_select_;

	// ���݂̃��[�h
	MODE mode_;

	Option* option_;
};

#endif	// _SCENE_TITLE_H_

//---------------------------------- EOF --------------------------------------
