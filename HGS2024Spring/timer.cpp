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

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 100.0f, 0.0f); // ポリゴン座標
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(300.0f, 75.0f, 0.0f); // ポリゴンサイズ

	const float LIMIT_TIME = 120.0f; // ゲーム時間
}

//==========================================
//  コンストラクタ
//==========================================
CTimer::CTimer(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority),
	m_oldTime(0),
	m_time(0.0f)
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

	// 頂点カラーを設定
	//SetVtxColor(D3DXCOLOR(1.0f, 0.56f, 0.87f, 1.0f));

	// 頂点情報の初期化
	SetVertex();
	
	// 現在時間の取得
	m_oldTime = timeGetTime();

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

	CManager::Get()->GetDebugProc()->Print("経過時間 : %f", m_time);
}
