//*****************************************************************************
//
// scene factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SCENE_FACTORY_H_
#define _SCENE_FACTORY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "scene/scene.h"

#include "scene/logo/scene_logo.h"
#include "scene/title/scene_title.h"
#include "scene/game/scene_game.h"


//*****************************************************************************
// class definition
//*****************************************************************************
class SceneFactory
{
public:
	// constructor
	SceneFactory(const Scene::TYPE& type) { type_ = type; }

	// destructor
	virtual ~SceneFactory(void){}

	// create
	virtual Scene* Create(void)const = 0;

	// accessor
	const Scene::TYPE& __type(void)const{return type_;}
private:
	Scene::TYPE type_;
};

//*****************************************************************************
// logo factory
//*****************************************************************************
class LogoFactory : public SceneFactory
{
public:
	// constructor
	LogoFactory(void) : SceneFactory(Scene::TYPE_LOGO){}

	// destructor
	virtual ~LogoFactory(void){}

	// create
	Scene* Create(void)const { return new SceneLogo(); }
};


//*****************************************************************************
// title factory
//*****************************************************************************
class TitleFactory : public SceneFactory
{
public:
	// constructor
	TitleFactory(void) : SceneFactory(Scene::TYPE_TITLE){}

	// destructor
	virtual ~TitleFactory(void){}

	// create
	Scene* Create(void)const { return new SceneTitle(); }
};

//*****************************************************************************
// game factory
//*****************************************************************************
class GameFactory : public SceneFactory
{
public:
	// constructor
	GameFactory(void) : SceneFactory(Scene::TYPE_TITLE) {}

	// destructor
	virtual ~GameFactory(void) {}

	// create
	Scene* Create(void)const { return new SceneGame(); }
};

#endif	// _SCENE_FACTORY_H_

//---------------------------------- EOF --------------------------------------
