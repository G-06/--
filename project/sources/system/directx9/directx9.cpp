//*****************************************************************************
//
// directx9
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "directx9.h"
#include "../window/window.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DVERTEXELEMENT9 Directx9::VERTEXELEMENT_[] =
{
	{0,0,                                     D3DDECLTYPE_FLOAT3,  D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
	{0,sizeof(D3DXVECTOR3),                   D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,   0},
	{0,sizeof(D3DXVECTOR3) + sizeof(D3DCOLOR),D3DDECLTYPE_FLOAT2,  D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
	D3DDECL_END()
};

//=============================================================================
// constructor
//=============================================================================
Directx9::Directx9(Window* window) :
window_(nullptr),
direct3d_(nullptr),
d3ddisplaymode_(),
d3dpresent_parameters_(),
direct3dvertexdeclaration_(nullptr),
direct3ddevice_(nullptr)
{
	window_ = window;
}

//=============================================================================
// destructor
//=============================================================================
Directx9::~Directx9(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool Directx9::Initialize(void)
{
	// Direct3D�I�u�W�F�N�g�̍쐬
	direct3d_ = Direct3DCreate9(D3D_SDK_VERSION);

	// Direct3D�I�u�W�F�N�g�̎��s
	if(direct3d_ == nullptr)
	{
		ASSERT("Direct3D�I�u�W�F�N�g�̐����Ɏ��s���܂���");
		return false;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(direct3d_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddisplaymode_)))
	{
		ASSERT("�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂���");
		return false;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpresent_parameters_,sizeof(d3dpresent_parameters_));

	// �o�b�N�o�b�t�@�̐�
	d3dpresent_parameters_.BackBufferCount = 1;

	// �Q�[����ʃT�C�Y(��)
	d3dpresent_parameters_.BackBufferWidth = window_->__width();

	// �Q�[����ʃT�C�Y(����)
	d3dpresent_parameters_.BackBufferHeight = window_->__height();

	// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpresent_parameters_.BackBufferFormat = d3ddisplaymode_.Format;

	// �f���M���ɓ������ăt���b�v����
	d3dpresent_parameters_.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// �E�B���h�E���[�h
	d3dpresent_parameters_.Windowed = true;

	// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpresent_parameters_.EnableAutoDepthStencil = TRUE;

	// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpresent_parameters_.AutoDepthStencilFormat = D3DFMT_D16;

	// �E�B���h�E���[�h
	if(d3dpresent_parameters_.Windowed)
	{
		// ���t���b�V�����[�g
		d3dpresent_parameters_.FullScreen_RefreshRateInHz = 0;

		// �C���^�[�o��
		d3dpresent_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	// �t���X�N���[�����[�h
	else
	{
		// �o�b�N�o�b�t�@
		d3dpresent_parameters_.BackBufferFormat = D3DFMT_R5G6B5;

		// ���t���b�V�����[�g
		d3dpresent_parameters_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		// �C���^�[�o��
		d3dpresent_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	if(FAILED(direct3d_->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,window_->__hwnd(),D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,&d3dpresent_parameters_,&direct3ddevice_)))
	{
		ASSERT("�f�o�C�X�̐����Ɏ��s���܂���");
		return false;
	}

	D3DXMATRIX view_matrix;

	// �v���W�F�N�V�����s��
	D3DXMATRIX projection_matrix
		(
		2.0f / DEFAULT_SCREEN_WIDTH,0.0f,0.0f,0.0f,
		0.0f,-2.0f / DEFAULT_SCREEN_HEIGHT,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		-1.0f,1.0f,0.0f,1.0f
		);

	direct3ddevice_->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

	D3DXMatrixIdentity(&view_matrix);

	// �r���[�s��̐ݒ�
	direct3ddevice_->SetTransform(D3DTS_VIEW,&view_matrix);

	// �ˉe�s��̐ݒ�
	direct3ddevice_->SetTransform(D3DTS_PROJECTION,&projection_matrix);

	// 
	if(FAILED(direct3ddevice_->CreateVertexDeclaration(VERTEXELEMENT_,&direct3dvertexdeclaration_)))
	{
		ASSERT("failed create vertex declaraton");
		return false;
	}

	// 
	direct3ddevice_->SetVertexDeclaration(direct3dvertexdeclaration_);

	// �����_�[�X�e�[�g�̐ݒ�
	SetDefaultRenderState();

	// �T���v���[�X�e�[�g�̐ݒ�
	SetDefaultSamplerState();

	// �e�N�X�`���[�X�e�[�W�X�e�[�g�̐ݒ�
	SetDefaultTextureStageState();

	// create texture
	texture_ = new Texture();

	// initialize texture
	if(!SafeInitialize(texture_))
	{
		return false;
	}

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void Directx9::Uninitialize(void)
{
	// release vertex declaration
	SafeRelease(direct3dvertexdeclaration_);

	// release texture
	SafeRelease(texture_);

	// Direct3DDevice�̊J��
	SafeRelease(direct3ddevice_);

	// Direct3D�̊J��
	SafeRelease(direct3d_);
}

//=============================================================================
// �`��J�n
//=============================================================================
bool Directx9::BeginDraw(void)
{
	HRESULT hresult;
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	direct3ddevice_->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DXCOLOR(1.0f,1.0f,0.0f,1.0f), 1.0f, 0);

	hresult = direct3ddevice_->BeginScene();
	// �`��J�n
	if(hresult == D3DERR_DEVICELOST)
	{
		// �����o���邩���ׂ�
		if(direct3ddevice_->TestCooperativeLevel() != D3DERR_DEVICENOTRESET)
		{
			return false;
		}

		// ���Z�b�g
		if(direct3ddevice_->Reset(&d3dpresent_parameters_) != D3D_OK)
		{
			ASSERT("�f�o�C�X�̕����Ɏ��s���܂���");
			return false;
		}
	}

	return true;
}

//=============================================================================
// �`��I��
//=============================================================================
void Directx9::EndDraw(void)
{
	// �`��I��
	direct3ddevice_->EndScene();

	// �t���b�v
	direct3ddevice_->Present(NULL,NULL,NULL,NULL);
}

//=============================================================================
// �X�N���[���V���b�g
//=============================================================================
void Directx9::ScreenShot(void)
{
	time_t now = time(nullptr);
	struct tm *now_time = localtime(&now);
	s8 temp[_MAX_PATH];

	sprintf_s(temp,"screenshot/%d_%02d_%02d_%02d_%02d_%02d.bmp",now_time->tm_year + 1900,now_time->tm_mon + 1,now_time->tm_mday,now_time->tm_hour,now_time->tm_min,now_time->tm_sec);

	ScreenShot(temp);
}

//=============================================================================
// �X�N���[���V���b�g
//=============================================================================
void Directx9::ScreenShot(const s8* filename)
{
	LPDIRECT3DSURFACE9 surface = nullptr;
	RECT rect =
	{
		0,0,window_->__width(),window_->__height()
	};

	//GetClientRect(window_->__hwnd(),&rect);

	direct3ddevice_->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&surface);

	D3DXSaveSurfaceToFile(filename,D3DXIFF_BMP,surface,NULL,&rect);

	SafeRelease(surface);
}

//=============================================================================
// get texture
//=============================================================================
LPDIRECT3DTEXTURE9 Directx9::GetTexture(const Texture::TEXTURE_ID& texture_id)
{
	return texture_->GetTexture(texture_id);
}

//=============================================================================
// �f�t�H���g�����_�[�X�e�[�g�̐ݒ�
//=============================================================================
void Directx9::SetDefaultRenderState(void)
{
	// light off
	direct3ddevice_->SetRenderState(D3DRS_LIGHTING,FALSE);
	direct3ddevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// ���ʂ��J�����O
	direct3ddevice_->SetRenderState(D3DRS_ZENABLE, TRUE);							// Z�o�b�t�@���g�p
	direct3ddevice_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	direct3ddevice_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	direct3ddevice_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��
}

//=============================================================================
// �f�t�H���g�T���v���[�X�e�[�g�̐ݒ�
//=============================================================================
void Directx9::SetDefaultSamplerState(void)
{
	direct3ddevice_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	direct3ddevice_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	direct3ddevice_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���k���t�B���^���[�h��ݒ�
	direct3ddevice_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// �e�N�X�`���g��t�B���^���[�h��ݒ�
}

//=============================================================================
// �f�t�H���g�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
//=============================================================================
void Directx9::SetDefaultTextureStageState(void)
{
	direct3ddevice_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	direct3ddevice_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	direct3ddevice_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
}

//---------------------------------- EOF --------------------------------------
