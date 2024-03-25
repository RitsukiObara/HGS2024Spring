//============================================
//
// チュートリアル画面のメイン処理[tutorial.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "tutorial.h"
#include "fade.h"
#include "renderer.h"
#include "tutorial_polygon.h"

// マクロ定義
#define TRANS_COUNT				(120)									// 遷移までのカウント数

//==========================================
//  静的メンバ変数宣言
//==========================================
CTutorialPolygon* CTutorial::m_pPolygon = nullptr;

//=========================================
// コンストラクタ
//=========================================
CTutorial::CTutorial()
{
	// 全ての情報をクリアする
	m_nEndCount = 0;			// 終了までのカウント
}

//=========================================
// デストラクタ
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CTutorial::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// 画像を生成
	m_pPolygon = CTutorialPolygon::Create();

	// 全ての値をクリアする
	m_nEndCount = 0;			// 終了までのカウント

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CTutorial::Uninit(void)
{
	// ポリゴンの終了
	if (m_pPolygon != nullptr)
	{
		m_pPolygon = nullptr;
	}

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CTutorial::Update(void)
{
	// 終了カウントを加算する
	m_nEndCount++;

	if (m_nEndCount >= TRANS_COUNT && m_pPolygon->GetEnd())
	{ // スキップ時または、終了時の場合

		// ゲームモードにする
		CManager::Get()->GetFade()->SetFade(MODE_GAME);
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// 更新処理
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//描画処理
//======================================
void CTutorial::Draw(void)
{

}

//======================================
// 情報の設定処理
//======================================
void CTutorial::SetData(const MODE mode)
{
	// 情報の設定処理
	CScene::SetData(mode);
}