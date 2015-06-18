//*****************************************************************************
//
// mesh sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include"mesh_sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DCOLOR MeshSprite::DEFAULT_COLOR = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
const D3DXVECTOR2 MeshSprite::DEFAULT_POSITION = D3DXVECTOR2(0.0f,0.0f);

//=============================================================================
// constructor
//=============================================================================
MeshSprite::MeshSprite(u32 width_count,u32 height_count)
	:device_(nullptr)
	,vertex_buffer_(nullptr)
	,texture_(nullptr)
	,position_(DEFAULT_POSITION)
	,color_(DEFAULT_COLOR)
	,left_(0.0f)
	,right_(1.0f)
	,top_(0.0f)
	,bottom_(1.0f)
	,rotation_(0.0f)
	,scale_(1.0f,1.0f)
	,texture_id_(Texture::TEXTURE_ID_NONE)
	,index_(-1)
	,division_width_(1)
	,division_height_(1)
	,is_flip_(false)
	,width_count_(width_count)
	,height_count_(height_count)
{
}

//=============================================================================
// destructor
//=============================================================================
MeshSprite::~MeshSprite(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool MeshSprite::Initialize(void)
{
	device_ = GET_DIRECTX9_DEVICE;

	vertex_count_ = 4 * width_count_ * height_count_;

	index_count_ = 4 * width_count_ * height_count_ + 2 * (width_count_ - 1) * height_count_ + 2 * (height_count_ - 1);

	indexs_ = new u32[width_count_ * height_count_];

	memset(indexs_,0,sizeof(u32) * width_count_ * height_count_);

	// create vertex buffer
	if(FAILED(device_->CreateVertexBuffer(sizeof(Directx9::VERTEX) * vertex_count_,D3DUSAGE_WRITEONLY,D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,D3DPOOL_MANAGED,&vertex_buffer_,NULL)))
	{
		return false;
	}

	// create index buffer
	if(FAILED(device_->CreateIndexBuffer(sizeof(u32) * index_count_,D3DUSAGE_WRITEONLY,D3DFMT_INDEX32,D3DPOOL_MANAGED,&index_buffer_,NULL)))
	{
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void MeshSprite::Uninitialize (void)
{
	// relase vertex buffer
	SafeRelease(vertex_buffer_);

	SafeRelease(index_buffer_);

	SafeDeleteArray(indexs_);
}

//=============================================================================
// draw
//=============================================================================
void MeshSprite::Draw(void)
{
	D3DXMATRIX matrix;

	D3DXMatrixIdentity(&matrix);

	Draw(matrix);
}

//=============================================================================
// draw
//=============================================================================
void MeshSprite::Draw(const D3DXMATRIX& matrix)
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

	device_->SetIndices(index_buffer_);

	// •`‰æ
	device_->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,vertex_count_,0,index_count_ - 2);
}

//=============================================================================
// set parameter
//=============================================================================
void MeshSprite::SetParameter(void)
{
	Directx9::VERTEX* vertex = nullptr;
	u32* index = nullptr;
	u32 rect_count = vertex_count_ / 4;

	// lock
	vertex_buffer_->Lock(0,0,(void**)&vertex,0);

	for(u32 i = 0;i < height_count_;++i)
	{
		for(u32 j = 0;j < width_count_;++j)
		{
			float left   = 1.0f / division_width_  * ((indexs_[i * width_count_ + j] % division_width_) + 0);
			float right  = 1.0f / division_width_  * ((indexs_[i * width_count_ + j] % division_width_) + 1);
			float top    = 1.0f / division_height_ * ((indexs_[i * width_count_ + j] / division_width_) + 0);
			float bottom = 1.0f / division_height_ * ((indexs_[i * width_count_ + j] / division_width_) + 1);

			vertex[(i * width_count_ + j) * 4 + 0]._position = D3DXVECTOR3(width_ * (j + 0) - 0.5f,height_ * (i + 1) - 0.5f,0.0f);
			vertex[(i * width_count_ + j) * 4 + 1]._position = D3DXVECTOR3(width_ * (j + 0) - 0.5f,height_ * (i + 0) - 0.5f,0.0f);
			vertex[(i * width_count_ + j) * 4 + 2]._position = D3DXVECTOR3(width_ * (j + 1) - 0.5f,height_ * (i + 1) - 0.5f,0.0f);
			vertex[(i * width_count_ + j) * 4 + 3]._position = D3DXVECTOR3(width_ * (j + 1) - 0.5f,height_ * (i + 0) - 0.5f,0.0f);

			vertex[(i * width_count_ + j) * 4 + 0]._color = color_;
			vertex[(i * width_count_ + j) * 4 + 1]._color = color_;
			vertex[(i * width_count_ + j) * 4 + 2]._color = color_;
			vertex[(i * width_count_ + j) * 4 + 3]._color = color_;

			vertex[(i * width_count_ + j) * 4 + 0]._texcoord = D3DXVECTOR2(left,bottom);
			vertex[(i * width_count_ + j) * 4 + 1]._texcoord = D3DXVECTOR2(left,top);
			vertex[(i * width_count_ + j) * 4 + 2]._texcoord = D3DXVECTOR2(right,bottom);
			vertex[(i * width_count_ + j) * 4 + 3]._texcoord = D3DXVECTOR2(right,top);
		}
	}

	// unlock
	vertex_buffer_->Unlock();

	u32 count = 0;

	index_buffer_->Lock(NULL,NULL,(void**)&index,NULL);

	for(u32 i = 0;i < height_count_;++i)
	{
		for(u32 j = 0;j < width_count_;++j)
		{
			index[count + 0] = (i * width_count_ + j) * 4 + 0;
			index[count + 1] = (i * width_count_ + j) * 4 + 1;
			index[count + 2] = (i * width_count_ + j) * 4 + 2;
			index[count + 3] = (i * width_count_ + j) * 4 + 3;

			count += 4;

			if(j != (width_count_ - 1))
			{
				index[count + 0] = (i * width_count_ + j) * 4 + 3;
				index[count + 1] = (i * width_count_ + j) * 4 + 4;
				count += 2;
			}
			else if(i != (height_count_ - 1))
			{
				index[count + 0] = (i * width_count_ + j) * 4 + 3;
				index[count + 1] = ((i + 1) * width_count_) * 4 + 0;
				count += 2;
			}
		}
	}

	index_buffer_->Unlock();

	if(texture_id_ != Texture::TEXTURE_ID_NONE)
	{
		// get texture
		texture_ = GET_DIRECTX9->GetTexture(texture_id_);
	}
}

void MeshSprite::SetIndex(u32 x,u32 y,u32 index)
{
	indexs_[y * width_count_ + x] = index;
}

//---------------------------------- EOF --------------------------------------
