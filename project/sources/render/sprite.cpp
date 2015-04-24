//*****************************************************************************
//
// sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include"sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 Sprite::DEFAULT_SIZE = D3DXVECTOR2(100.0f,100.0f);
const D3DCOLOR Sprite::DEFAULT_COLOR = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
const D3DXVECTOR2 Sprite::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
const Sprite::POINT Sprite::DEFAULT_POINT = Sprite::POINT_LEFT_UP;

//=============================================================================
// constructor
//=============================================================================
Sprite::Sprite(void) :
device_(nullptr),
vertex_buffer_(nullptr),
texture_(nullptr),
position_(DEFAULT_POSITION),
size_(DEFAULT_SIZE),
color_(DEFAULT_COLOR),
point_(DEFAULT_POINT),
left_(0.0f),
right_(1.0f),
top_(0.0f),
bottom_(1.0f),
rotation_(0.0f),
scale_(1.0f,1.0f),
texture_id_(Texture::TEXTURE_ID_NONE)
{
}

//=============================================================================
// destructor
//=============================================================================
Sprite::~Sprite(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Sprite::Initialize(void)
{
	device_ = GET_DIRECTX9_DEVICE;

	// create vertex buffer
	if(FAILED(device_->CreateVertexBuffer(sizeof(Directx9::VERTEX) * 4,D3DUSAGE_WRITEONLY,D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,D3DPOOL_MANAGED,&vertex_buffer_,NULL)))
	{
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Sprite::Uninitialize (void)
{
	// relase vertex buffer
	SafeRelease(vertex_buffer_);
}

//=============================================================================
// draw
//=============================================================================
void Sprite::Draw(void)
{
	D3DXMATRIX matrix;

	D3DXMatrixIdentity(&matrix);

	Draw(matrix);
}

//=============================================================================
// draw
//=============================================================================
void Sprite::Draw(const D3DXMATRIX& matrix)
{
	D3DXMATRIX scale_matrix;
	D3DXMATRIX rotation_matrix;
	D3DXMATRIX tranlation_matrix;
	D3DXMATRIX world_matrix;

	D3DXMatrixIdentity(&world_matrix);

	D3DXMatrixMultiply(&world_matrix,&world_matrix,&matrix);

	// scale matrix
	D3DXMatrixIdentity(&scale_matrix);
	D3DXMatrixScaling(&scale_matrix,scale_.x,scale_.y,0.0f);
	D3DXMatrixMultiply(&world_matrix,&world_matrix,&scale_matrix);

	// rotation matrix
	D3DXMatrixIdentity(&rotation_matrix);
	D3DXMatrixRotationYawPitchRoll(&rotation_matrix,0.0f,0.0f,rotation_);
	D3DXMatrixMultiply(&world_matrix,&world_matrix,&rotation_matrix);

	// tranlation matrix
	D3DXMatrixIdentity(&tranlation_matrix);
	D3DXMatrixTranslation(&tranlation_matrix,position_.x,position_.y,0.0f);
	D3DXMatrixMultiply(&world_matrix,&world_matrix,&tranlation_matrix);

	device_->SetTransform(D3DTS_WORLD,&world_matrix);

	device_->SetTexture(0,texture_);

	device_->SetStreamSource(0,vertex_buffer_,0,sizeof(Directx9::VERTEX));

	device_->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// set parameter
//=============================================================================
void Sprite::SetParameter(void)
{
	Directx9::VERTEX* vertex = nullptr;

	// lock
	vertex_buffer_->Lock(0,0,(void**)&vertex,0);

	switch(point_)
	{
		case POINT_LEFT_UP:
		{
			vertex[0]._position = D3DXVECTOR3(   0.0f,   0.0f,0.0f);
			vertex[1]._position = D3DXVECTOR3(size_.x,   0.0f,0.0f);
			vertex[2]._position = D3DXVECTOR3(   0.0f,size_.y,0.0f);
			vertex[3]._position = D3DXVECTOR3(size_.x,size_.y,0.0f);
			break;
		}
		case POINT_LEFT_MIDDLE:
		{
			vertex[0]._position = D3DXVECTOR3(   0.0f,-size_.y * 0.5f,0.0f);
			vertex[1]._position = D3DXVECTOR3(size_.x,-size_.y * 0.5f,0.0f);
			vertex[2]._position = D3DXVECTOR3(   0.0f, size_.y * 0.5f,0.0f);
			vertex[3]._position = D3DXVECTOR3(size_.x, size_.y * 0.5f,0.0f);
			break;
		}
		case POINT_LEFT_DOWN:
		{
			vertex[0]._position = D3DXVECTOR3(   0.0f,-size_.y,0.0f);
			vertex[1]._position = D3DXVECTOR3(size_.x,-size_.y,0.0f);
			vertex[2]._position = D3DXVECTOR3(   0.0f,    0.0f,0.0f);
			vertex[3]._position = D3DXVECTOR3(size_.x,    0.0f,0.0f);
			break;
		}
		case POINT_MIDDLE_UP:
		{
			vertex[0]._position = D3DXVECTOR3(-size_.x * 0.5f,   0.0f,0.0f);
			vertex[1]._position = D3DXVECTOR3( size_.x * 0.5f,   0.0f,0.0f);
			vertex[2]._position = D3DXVECTOR3(-size_.x * 0.5f,size_.y,0.0f);
			vertex[3]._position = D3DXVECTOR3( size_.x * 0.5f,size_.y,0.0f);
			break;
		}
		case POINT_CENTER:
		{
			vertex[0]._position = D3DXVECTOR3(-size_.x * 0.5f,-size_.y * 0.5f,0.0f);
			vertex[1]._position = D3DXVECTOR3( size_.x * 0.5f,-size_.y * 0.5f,0.0f);
			vertex[2]._position = D3DXVECTOR3(-size_.x * 0.5f, size_.y * 0.5f,0.0f);
			vertex[3]._position = D3DXVECTOR3( size_.x * 0.5f, size_.y * 0.5f,0.0f);
			break;
		}
		case POINT_MIDDLE_DOWN:
		{
			vertex[0]._position = D3DXVECTOR3(-size_.x * 0.5f,-size_.y,0.0f);
			vertex[1]._position = D3DXVECTOR3( size_.x * 0.5f,-size_.y,0.0f);
			vertex[2]._position = D3DXVECTOR3(-size_.x * 0.5f,    0.0f,0.0f);
			vertex[3]._position = D3DXVECTOR3( size_.x * 0.5f,    0.0f,0.0f);
			break;
		}
		case POINT_RIGHT_UP:
		{
			vertex[0]._position = D3DXVECTOR3(-size_.x,   0.0f,0.0f);
			vertex[1]._position = D3DXVECTOR3(    0.0f,   0.0f,0.0f);
			vertex[2]._position = D3DXVECTOR3(-size_.x,size_.y,0.0f);
			vertex[3]._position = D3DXVECTOR3(    0.0f,size_.y,0.0f);
			break;
		}
		case POINT_RIGHT_MIDDLE:
		{
			vertex[0]._position = D3DXVECTOR3(-size_.x,-size_.y * 0.5f,0.0f);
			vertex[1]._position = D3DXVECTOR3(0.0f,-size_.y * 0.5f,0.0f);
			vertex[2]._position = D3DXVECTOR3(-size_.x,size_.y * 0.5f,0.0f);
			vertex[3]._position = D3DXVECTOR3(0.0f,size_.y * 0.5f,0.0f);
			break;
		}
		case POINT_RIGHT_DOWN:
		{
			vertex[0]._position = D3DXVECTOR3(-size_.x,-size_.y,0.0f);
			vertex[1]._position = D3DXVECTOR3(    0.0f,-size_.y,0.0f);
			vertex[2]._position = D3DXVECTOR3(-size_.x,    0.0f,0.0f);
			vertex[3]._position = D3DXVECTOR3(    0.0f,    0.0f,0.0f);
			break;
		}
	}

	// texcoord
	vertex[0]._texcoord = D3DXVECTOR2( left_,top_);
	vertex[1]._texcoord = D3DXVECTOR2(right_,top_);
	vertex[2]._texcoord = D3DXVECTOR2( left_,bottom_);
	vertex[3]._texcoord = D3DXVECTOR2(right_,bottom_);

	// color
	vertex[0]._color = color_;
	vertex[1]._color = color_;
	vertex[2]._color = color_;
	vertex[3]._color = color_;

	// unlock
	vertex_buffer_->Unlock();

	if(texture_id_ != Texture::TEXTURE_ID_NONE)
	{
		// get texture
		texture_ = GET_DIRECTX9->GetTexture(texture_id_);
	}
}

//---------------------------------- EOF --------------------------------------
