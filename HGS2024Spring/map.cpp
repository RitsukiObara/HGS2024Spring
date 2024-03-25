//=======================================
//
// マップ処理[map.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "map.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

// 定数定義
namespace
{
	const D3DXVECTOR3 MAP_SIZE = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f);	// サイズ
	const char* TEXTURE = "data\\TEXTURE\\Map.png";						// テクスチャ
}

//=========================
// コンストラクタ
//=========================
CMap::CMap() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

//=========================
// デストラクタ
//=========================
CMap::~CMap()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CMap::Init(void)
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
void CMap::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//=========================
// 更新処理
//=========================
void CMap::Update(void)
{
	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 描画処理
//=========================
void CMap::Draw(void)
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
void CMap::SetData(void)
{
	// スクロールの設定処理
	SetPos(NONE_D3DXVECTOR3);		// 位置設定
	SetPosOld(NONE_D3DXVECTOR3);	// 位置設定
	SetRot(NONE_D3DXVECTOR3);		// 向き設定
	SetSize(MAP_SIZE);				// サイズ設定

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));

	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 生成処理
//=========================
CMap* CMap::Create(void)
{
	// ローカルオブジェクトを生成
	CMap* pMap = nullptr;	// マップのインスタンスを生成

	if (pMap == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pMap = new CMap;
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