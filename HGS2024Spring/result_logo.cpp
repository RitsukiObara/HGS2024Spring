//=======================================
//
// 2Dエフェクトのメイン処理[effect2D.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "result_logo.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

#include "game.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// 位置
	const D3DXVECTOR3 POLY_SIZE = D3DXVECTOR3(530.0f, 140.0f, 0.0f);		// サイズ
	const char* CLEAR_TEXTURE = "data\\TEXTURE\\gameclear00.png";		// ゲームクリア
	const char* GAMEOVER_TEXTURE = "data\\TEXTURE\\gameover00.png";	// ゲームオーバー
}

//=========================
// コンストラクタ
//=========================
CResultLogo::CResultLogo() : CObject2D(CObject2D::TYPE_RESULTLOGO, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CResultLogo::~CResultLogo()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CResultLogo::Init(void)
{
	if (FAILED(CObject2D::Init()))
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
void CResultLogo::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CResultLogo::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CResultLogo::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CResultLogo::SetData(void)
{
	// スクロールの設定処理
	SetPos(POS);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(POLY_SIZE);			// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// 頂点情報の初期化
	SetVertex();

	switch (CGame::GetState())
	{
	case CGame::STATE_CLEAR:

		// テクスチャの読み込み処理
		BindTexture(CManager::Get()->GetTexture()->Regist(CLEAR_TEXTURE));

		break;

	case CGame::STATE_GAMEOVER:

		// テクスチャの読み込み処理
		BindTexture(CManager::Get()->GetTexture()->Regist(GAMEOVER_TEXTURE));

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=========================
// 生成処理
//=========================
CResultLogo* CResultLogo::Create(void)
{
	// ローカルオブジェクトを生成
	CResultLogo* pLogo = nullptr;	// プレイヤーのインスタンスを生成

	if (pLogo == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pLogo = new CResultLogo;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pLogo != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pLogo->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pLogo->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// オブジェクト2Dのポインタを返す
	return pLogo;
}