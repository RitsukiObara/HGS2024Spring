//============================================
//
// ゲームのメイン処理[game.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"
#include "texture.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "objectElevation.h"
#include "ocean.h"
#include "map.h"
#include "mob_tree.h"
#include "player.h"
#include "enemy.h"
#include "enemy_home.h"
#include "base.h"
#include "skybox.h"
#include "gauge.h"
#include "timer.h"
#include "CaveatDirection.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define TRANS_COUNT		(80)		// 成功時の遷移カウント

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// ポーズの情報
CPlayer* CGame::m_pPlayer = nullptr;						// プレイヤーの情報
CBase* CGame::m_pBase = nullptr;							// 拠点の情報
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// ゲームの進行状態
int CGame::m_nFinishCount = 0;								// 終了カウント
bool CGame::m_bPause = false;								// ポーズ状況

//=========================================
// コンストラクタ
//=========================================
CGame::CGame()
{
	// 全ての値をクリアする
	m_pPause = nullptr;			// ポーズ
	m_pPlayer = nullptr;		// プレイヤー
	m_pBase = nullptr;			// 拠点
	m_nFinishCount = 0;			// 終了カウント
	m_GameState = STATE_START;	// 状態
	m_bPause = false;			// ポーズ状況
}

//=========================================
// デストラクタ
//=========================================
CGame::~CGame()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CGame::Init(void)
{
	// スカイボックスの生成処理
	CSkyBox::Create();

	// 海の生成
	COcean::Create();

	// マップの生成
	CMap::Create();

	// 木の生成
	CMobTree::Create(D3DXVECTOR3(-1700.0f, 0.0f, -1820.0f), 0, 1);
	CMobTree::Create(D3DXVECTOR3(-1230.0f, 0.0f, -1200.0f), 1000, 1);
	CMobTree::Create(D3DXVECTOR3(-690.0f, 0.0f, -980.0f), 2000, 1);
	CMobTree::Create(D3DXVECTOR3(-800.0f, 0.0f, -625.0f), 3000, 2);
	CMobTree::Create(D3DXVECTOR3(-130.0f, 0.0f, -740.0f), 4000, 2);
	CMobTree::Create(D3DXVECTOR3(345.0f, 0.0f, -520.0f), 5000, 2);
	CMobTree::Create(D3DXVECTOR3(735.0f, 0.0f, 75.0f), 6000, 3);

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	// 拠点の生成
	m_pBase = CBase::Create();

	// 敵の拠点の生成
	CEnemyHome::Create(D3DXVECTOR3(-900.0f, 200.0f, 800.0f), D3DXVECTOR3(0.0f, -0.5f, D3DX_PI * -0.6f));
	CEnemyHome::Create(D3DXVECTOR3(1700.0f, 200.0f, 100.0f), D3DXVECTOR3(0.0f, -1.4f, D3DX_PI * -0.6f));

	// ゲージの生成
	CGauge::Create();

	// タイマーの生成
	CTimer::Create();

	CCaveatDirection::Create();

	// シーンの初期化
	CScene::Init();

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
	m_GameState = STATE_START;		// 状態
	m_bPause = false;				// ポーズ状況

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CGame::Uninit(void)
{
	// ポインタを NULL にする
	if (m_pPause != nullptr)
	{ // ポーズが NULL じゃない場合

		// ポーズの終了処理
		m_pPause->Uninit();
	}

	m_pPlayer = nullptr;		// プレイヤー
	m_pBase = nullptr;			// 拠点

	// 情報を初期化する
	m_bPause = false;			// ポーズ状況

	// 終了カウントを初期化する
	m_nFinishCount = 0;

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CGame::Update(void)
{
	switch (m_GameState)
	{
	case CGame::STATE_START:

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_PLAY:

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_CLEAR:

		// 遷移処理
		Transition();

		break;

	case CGame::STATE_GAMEOVER:

		// 遷移処理
		Transition();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	//if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
	//	CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
	//	CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
	//{ // ENTERキーを押した場合

	//	// リザルトに遷移する
	//	CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);

	//	// この先の処理を行わない
	//	return;
	//}

	if (m_bPause == true)
	{ // ポーズ状況が true の場合

		// 更新処理
		m_pPause->Update();
	}
	else
	{ // 上記以外

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // レンダラーが NULL じゃない場合

			// レンダラーの更新
			CManager::Get()->GetRenderer()->Update();
		}
	}

	CManager::Get()->GetDebugProc()->Print("状態：%d", m_GameState);
}

//======================================
//描画処理
//======================================
void CGame::Draw(void)
{
	if (m_pPause != nullptr &&
		m_bPause == true)
	{ // ポーズ中の場合

		// 描画処理
		m_pPause->Draw();
	}
}

//======================================
// 情報の設定処理
//======================================
void CGame::SetData(const MODE mode)
{
	// 情報の設定処理
	CScene::SetData(mode);

	// 全ての値を設定する
	m_GameState = STATE_START;	// スタート状態にする
	m_bPause = false;			// ポーズ状況

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
}

//======================================
// ポーズ処理
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true)
	{ // Pキーを押した場合

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // フェード無し状態かつ、終了以外の場合

			if (m_bPause == false)
			{ // ポーズが false だった場合

				if (m_pPause == nullptr)
				{ // ポーズへのポインタが NULL の場合

					// ポーズの生成処理
					m_pPause = CPause::Create();
				}
				else
				{ // 上記以外
					
					// 停止
					assert(false);
				}

				// ポーズ状況を true にする
				m_bPause = true;
			}
			else
			{ // ポーズが true だった場合

				if (m_pPause != nullptr)
				{ // ポーズへのポインタが NULL じゃない場合

					// 終了処理
					m_pPause->Uninit();
					m_pPause = nullptr;
				}

				// ポーズ状況を false にする
				m_bPause = false;
			}

			// 決定音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// 遷移処理
//======================================
void CGame::Transition(void)
{
	// 終了カウントを加算する
	m_nFinishCount++;

	if (m_nFinishCount % TRANS_COUNT == 0)
	{ // 終了カウントが一定数を超えた場合

		// リザルトに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// ポーズ状況の設定処理
//======================================
void CGame::SetEnablePause(const bool bPause)
{
	// ポーズ状況を設定する
	m_bPause = bPause;
}

//======================================
// ポーズ状況の取得処理
//======================================
bool CGame::IsPause(void)
{
	// ポーズ状況を取得する
	return m_bPause;
}

//======================================
// ゲームの進行状態の設定処理
//======================================
void CGame::SetState(const STATE state)
{
	// ゲームの進行状態を設定する
	m_GameState = state;
}

//======================================
// ゲームの進行状態の取得処理
//======================================
CGame::STATE CGame::GetState(void)
{
	// ゲームの進行状態を返す
	return m_GameState;
}

//======================================
// プレイヤーの取得処理
//======================================
CPlayer* CGame::GetPlayer(void)
{
	// プレイヤーの情報を返す
	return m_pPlayer;
}

//======================================
// 拠点の取得処理
//======================================
CBase* CGame::GetBase(void)
{
	// 拠点の情報を返す
	return m_pBase;
}

//======================================
// ポーズのNULL化処理
//======================================
void CGame::DeletePause(void)
{
	// ポーズのポインタを NULL にする
	m_pPause = nullptr;
}

//======================================
// プレイヤーのNULL化処理
//======================================
void CGame::DeletePlayer(void)
{
	// プレイヤーのポインタを NULL にする
	m_pPlayer = nullptr;
}

//======================================
// 拠点のNULL化処理
//======================================
void CGame::DeleteBase(void)
{
	// 拠点を NULL にする
	m_pBase = nullptr;
}