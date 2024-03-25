//==========================================
//
//  タイマー(timer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "timer.h"
#include "manager.h"
#include "debugproc.h"
#include "game.h"
#include "fade.h"
#include "texture.h"
#include "sound.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 50.0f, 0.0f); // ポリゴン座標
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(250.0f, 62.5f, 0.0f); // ポリゴンサイズ
	const float POLYGON_RATE = POLYGON_SIZE.y / POLYGON_SIZE.x; // ポリゴンサイズ
	const float FLOATING_SIZE = 50.0f; // 浮動するサイズの倍率

	const float LIMIT_TIME = 120.0f; // ゲーム時間
	const float SWICH_TIME_APRIL = LIMIT_TIME / 3.0f; // ゲーム時間
	const float SWICH_TIME_MAY = (LIMIT_TIME / 3.0f) * 2.0f; // ゲーム時間

	const char* MARCH_PASS = "data/TEXTURE/March.png"; // テクスチャパス
	const char* APRIL_PASS = "data/TEXTURE/April.png"; // テクスチャパス
	const char* MAY_PASS = "data/TEXTURE/May.png"; // テクスチャパス
}

//==========================================
//  コンストラクタ
//==========================================
CTimer::CTimer(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority),
	m_oldTime(0),
	m_time(0.0f),
	m_bPichUp(false)
{

}

//==========================================
//  デストラクタ
//==========================================
CTimer::~CTimer()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTimer::Init()
{
	// 親クラスの初期化
	if (FAILED(CObject2D::Init())) { return E_FAIL; }

	// 座標の設定
	SetPos(POLYGON_POS);

	// サイズの設定
	SetSize(POLYGON_SIZE);

	// 角度の設定
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 対角線の長さを算出
	SetLength();

	// 対角線の角度を算出
	SetAngle();

	// 頂点情報の初期化
	SetVertex();
	
	// 現在時間の取得
	m_oldTime = timeGetTime();

	// テクスチャ割り当て
	BindTexture(CManager::Get()->GetTexture()->Regist(MARCH_PASS));

	// ピッチを変更
	CManager::Get()->GetSound()->SetFrequency(CSound::SOUND_LABEL_BGM_GAME, 1.0f);

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTimer::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTimer::Update()
{
	// 経過時間の計算
	CalcTime();

	// 大きさを変える
	Floating();

	// 時間経過で月が変わる
	if (m_time >= SWICH_TIME_APRIL)
	{
		// テクスチャ割り当て
		BindTexture(CManager::Get()->GetTexture()->Regist(APRIL_PASS));
	}
	if (m_time >= SWICH_TIME_MAY)
	{
		// テクスチャ割り当て
		BindTexture(CManager::Get()->GetTexture()->Regist(MAY_PASS));

		// ピッチを上げる
		if (!m_bPichUp)
		{
			// ピッチを変更
			 CManager::Get()->GetSound()->SetFrequency(CSound::SOUND_LABEL_BGM_GAME, 1.1f);

			// フラグを立てる
			m_bPichUp = true;
		}
	}

	// 制限時間を超えたら
	if (m_time >= LIMIT_TIME)
	{
		// チュートリアルに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}

	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTimer::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CTimer* CTimer::Create()
{
	// インスタンス生成
	CTimer* time = new CTimer;

	// NULLチェック
	if (time == nullptr) { return nullptr; }

	// 初期化処理
	if (FAILED(time->Init())) { return nullptr; }

	return time;
}

//==========================================
//  経過時間の加算
//==========================================
void CTimer::CalcTime()
{
	// 現在時間の取得
	DWORD time = timeGetTime();

	// 前回時間との差を算出(ミリ秒)
	float difference = (float)(time - m_oldTime) * 0.001f;

	// 経過時間に差分を加算
	if (!CGame::IsPause())
	{
		m_time += difference;
	}

	// 前回時間を現在時間で上書き
	m_oldTime = time;

}

//==========================================
//  大きさの浮動
//==========================================
void CTimer::Floating()
{
	// 増減の量を算出
	float floating = sinf(m_time) * FLOATING_SIZE;

	// サイズを算出
	D3DXVECTOR3 size = POLYGON_SIZE;
	size += D3DXVECTOR3(floating, floating * POLYGON_RATE, 0.0f);

	// サイズを適用
	SetSize(size);

	// 対角線の長さを算出
	SetLength();

	// 対角線の角度を算出
	SetAngle();
}
