//=======================================
//
// 海処理[ocean.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "ocean.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

// 定数定義
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, -5.0f, 0.0f);					// 位置
	const D3DXVECTOR3 OCEAN_SIZE = D3DXVECTOR3(5000.0f, 0.0f, 5000.0f);		// サイズ
	const char* TEXTURE = "data\\TEXTURE\\Ocean.png";						// テクスチャ
}

//=========================
// コンストラクタ
//=========================
COcean::COcean() : CObject3D(CObject::TYPE_OCEAN, CObject::PRIORITY_BG)
{

}

//=========================
// デストラクタ
//=========================
COcean::~COcean()
{

}

//=========================
// 初期化処理
//=========================
HRESULT COcean::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void COcean::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//=========================
// 更新処理
//=========================
void COcean::Update(void)
{
	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 描画処理
//=========================
void COcean::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// カリングの設定をOFFにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画処理
	CObject3D::DrawLightOff();

	// カリングの設定をONにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
// 情報の設定処理
//=========================
void COcean::SetData(void)
{
	// スクロールの設定処理
	SetPos(POS);					// 位置
	SetPosOld(NONE_D3DXVECTOR3);	// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetSize(OCEAN_SIZE);			// サイズ

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));

	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 生成処理
//=========================
COcean* COcean::Create(void)
{
	// ローカルオブジェクトを生成
	COcean* pMap = nullptr;	// マップのインスタンスを生成

	if (pMap == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pMap = new COcean;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pMap != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pMap->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pMap->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// マップのポインタを返す
	return pMap;
}