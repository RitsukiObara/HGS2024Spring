//=======================================
//
// 拠点の花処理[base_flower.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "base_flower.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 FLOWER_SIZE = D3DXVECTOR3(20.0f, 20.0f, 0.0f);		// 花のサイズ
	const char* TEXTURE = "data\\TEXTURE\\Flower.png";						// テクスチャ
}

//=========================
// コンストラクタ
//=========================
CBaseFlower::CBaseFlower() : CBillboard(CObject::TYPE_BASEFLOWER, CObject::PRIORITY_ENTITY)
{

}

//=========================
// デストラクタ
//=========================
CBaseFlower::~CBaseFlower()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CBaseFlower::Init(void)
{
	if (FAILED(CBillboard::Init()))
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
void CBaseFlower::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//=========================
// 更新処理
//=========================
void CBaseFlower::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CBaseFlower::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// 描画処理
	CBillboard::DrawLightOff();
}

//=========================
// 情報の設定処理
//=========================
void CBaseFlower::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);			// 位置
	SetPosOld(pos);			// 前回の位置
	SetSize(FLOWER_SIZE);	// サイズ
	SetEnableLookY(false);	// Y軸状況

	// 頂点情報の初期化
	SetVertex();

	// 色の設定処理
	SetVtxColor(D3DXCOLOR(1.0f, 0.5f, 1.0f, 1.0f));

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// 生成処理
//=========================
CBaseFlower* CBaseFlower::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CBaseFlower* pBaseFlower = nullptr;	// プレイヤーのインスタンスを生成

	if (pBaseFlower == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pBaseFlower = new CBaseFlower;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBaseFlower != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBaseFlower->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBaseFlower->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// オブジェクト2Dのポインタを返す
	return pBaseFlower;
}