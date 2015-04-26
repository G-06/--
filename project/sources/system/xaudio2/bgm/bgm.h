//*****************************************************************************
//
// bgm
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BGM_H_
#define _BGM_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// class definition
//*****************************************************************************
class BGM : public Basic
{
public:
	enum BGM_ID
	{
		BGM_ID_NONE = -1,
		BGM_ID_TEST,
		BGM_ID_MAX,
	};

	// constructor
	BGM(void);

	// destructor
	virtual ~BGM(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// play
	bool Play(const BGM_ID& bgm_id);

	// stop
	void Stop(void);

	// accessor
	const BGM_ID& __current_bgm(void)const{ return current_bgm_; }
	void __is_loop(const bool& is_loop){ is_loop_ = is_loop; }

private:
	static const s8* BGM_NAME[BGM_ID_MAX];

	BGM_ID current_bgm_;
	bool is_loop_;
};

#endif // _BGM_H_

//---------------------------------- EOF --------------------------------------
