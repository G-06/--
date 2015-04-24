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
	// Direct3Dオブジェクトの作成
	direct3d_ = Direct3DCreate9(D3D_SDK_VERSION);

	// Direct3Dオブジェクトの失敗
	if(direct3d_ == nullptr)
	{
		ASSERT("Direct3Dオブジェクトの生成に失敗しました");
		return false;
	}

	// 現在のディスプレイモードを取得
	if(FAILED(direct3d_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddisplaymode_)))
	{
		ASSERT("ディスプレイモードの取得に失敗しました");
		return false;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpresent_parameters_,sizeof(d3dpresent_parameters_));

	// バックバッファの数
	d3dpresent_parameters_.BackBufferCount = 1;

	// ゲーム画面サイズ(幅)
	d3dpresent_parameters_.BackBufferWidth = window_->__width();

	// ゲーム画面サイズ(高さ)
	d3dpresent_parameters_.BackBufferHeight = window_->__height();

	// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpresent_parameters_.BackBufferFormat = d3ddisplaymode_.Format;

	// 映像信号に同期してフリップする
	d3dpresent_parameters_.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// ウィンドウモード
	d3dpresent_parameters_.Windowed = true;

	// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpresent_parameters_.EnableAutoDepthStencil = TRUE;

	// デプスバッファとして16bitを使う
	d3dpresent_parameters_.AutoDepthStencilFormat = D3DFMT_D16;

	// ウィンドウモード
	if(d3dpresent_parameters_.Windowed)
	{
		// リフレッシュレート
		d3dpresent_parameters_.FullScreen_RefreshRateInHz = 0;

		// インターバル
		d3dpresent_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	// フルスクリーンモード
	else
	{
		// バックバッファ
		d3dpresent_parameters_.BackBufferFormat = D3DFMT_R5G6B5;

		// リフレッシュレート
		d3dpresent_parameters_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		// インターバル
		d3dpresent_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// デバイスオブジェクトの生成
	if(FAILED(direct3d_->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,window_->__hwnd(),D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,&d3dpresent_parameters_,&direct3ddevice_)))
	{
		ASSERT("デバイスの生成に失敗しました");
		return false;
	}

	D3DXMATRIX view_matrix;

	// プロジェクション行列
	D3DXMATRIX projection_matrix
		(
		2.0f / DEFAULT_SCREEN_WIDTH,0.0f,0.0f,0.0f,
		0.0f,-2.0f / DEFAULT_SCREEN_HEIGHT,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		-1.0f,1.0f,0.0f,1.0f
		);

	direct3ddevice_->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

	D3DXMatrixIdentity(&view_matrix);

	// ビュー行列の設定
	direct3ddevice_->SetTransform(D3DTS_VIEW,&view_matrix);

	// 射影行列の設定
	direct3ddevice_->SetTransform(D3DTS_PROJECTION,&projection_matrix);

	// 
	if(FAILED(direct3ddevice_->CreateVertexDeclaration(VERTEXELEMENT_,&direct3dvertexdeclaration_)))
	{
		ASSERT("failed create vertex declaraton");
		return false;
	}

	// 
	direct3ddevice_->SetVertexDeclaration(direct3dvertexdeclaration_);

	// レンダーステートの設定
	SetDefaultRenderState();

	// サンプラーステートの設定
	SetDefaultSamplerState();

	// テクスチャーステージステートの設定
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

	// Direct3DDeviceの開放
	SafeRelease(direct3ddevice_);

	// Direct3Dの開放
	SafeRelease(direct3d_);
}

//=============================================================================
// 描画開始
//=============================================================================
bool Directx9::BeginDraw(void)
{
	HRESULT hresult;
	// バックバッファ＆Ｚバッファのクリア
	direct3ddevice_->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DXCOLOR(1.0f,1.0f,0.0f,1.0f), 1.0f, 0);

	hresult = direct3ddevice_->BeginScene();
	// 描画開始
	if(hresult == D3DERR_DEVICELOST)
	{
		// 復旧出来るか調べる
		if(direct3ddevice_->TestCooperativeLevel() != D3DERR_DEVICENOTRESET)
		{
			return false;
		}

		// リセット
		if(direct3ddevice_->Reset(&d3dpresent_parameters_) != D3D_OK)
		{
			ASSERT("デバイスの復旧に失敗しました");
			return false;
		}
	}

	return true;
}

//=============================================================================
// 描画終了
//=============================================================================
void Directx9::EndDraw(void)
{
	// 描画終了
	direct3ddevice_->EndScene();

	// フリップ
	direct3ddevice_->Present(NULL,NULL,NULL,NULL);
}

//=============================================================================
// スクリーンショット
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
// スクリーンショット
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
// デフォルトレンダーステートの設定
//=============================================================================
void Directx9::SetDefaultRenderState(void)
{
	// light off
	direct3ddevice_->SetRenderState(D3DRS_LIGHTING,FALSE);
	direct3ddevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// 裏面をカリング
	direct3ddevice_->SetRenderState(D3DRS_ZENABLE, TRUE);							// Zバッファを使用
	direct3ddevice_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	direct3ddevice_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	direct3ddevice_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
}

//=============================================================================
// デフォルトサンプラーステートの設定
//=============================================================================
void Directx9::SetDefaultSamplerState(void)
{
	direct3ddevice_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャアドレッシング方法(U値)を設定
	direct3ddevice_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// テクスチャアドレッシング方法(V値)を設定
	direct3ddevice_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// テクスチャ縮小フィルタモードを設定
	direct3ddevice_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// テクスチャ拡大フィルタモードを設定
}

//=============================================================================
// デフォルトテクスチャステージステートの設定
//=============================================================================
void Directx9::SetDefaultTextureStageState(void)
{
	direct3ddevice_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	direct3ddevice_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	direct3ddevice_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
}

//---------------------------------- EOF --------------------------------------
