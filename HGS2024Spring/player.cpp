//=======================================
//
// プレイヤーのメイン処理[player.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "input.h"
#include "player.h"
#include "useful.h"

#include "snowball.h"
#include "game.h"
#include "camera.h"
#include "collision.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	const D3DXVECTOR3 INIT_CAMERA_ROT = D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f);		// カメラの初期向き
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(4.0f, 4.0f, 4.0f);		// 拡大率
	const float CAMERA_ROT_CORRECT = 0.0000020f;		// カメラの向きの補正処理
	const D3DXVECTOR3 SNOWBALL_POS = D3DXVECTOR3(0.0f, 100.0f, 0.0f);	// 雪玉の出る位置
	const char* MODEL = "data\\MODEL\\Player\\player.x";			// モデル
	const float SPEED = 10.0f;					// 速度
}

//=========================
// オーバーロードコンストラクタ
//=========================
CPlayer::CPlayer() : CModel(TYPE_PLAYER, PRIORITY_PLAYER)
{

}

//=========================
// デストラクタ
//=========================
CPlayer::~CPlayer()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// カメラの向き設定
	CManager::Get()->GetCamera()->SetRot(INIT_CAMERA_ROT);

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CPlayer::Uninit(void)
{
	// 終了
	CModel::Uninit();

	// プレイヤーの終了処理
	CGame::DeletePlayer();
}

//=========================
// 更新処理
//=========================
void CPlayer::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 操作処理
	Control();

	// カメラの操作処理
	Camera();

	// 射撃処理
	Shot();

	//木との当たり判定
	collision::TreeHit(this);
}

//=========================
// 描画処理
//=========================
void CPlayer::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CPlayer::SetData(void)
{
	// スクロールの設定処理
	SetPos(INIT_POS);							// 位置
	SetPosOld(INIT_POS);						// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(SCALE);							// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
}

//=========================
// 木とのヒット判定
//=========================
void CPlayer::TreeHit(void)
{
	if (m_state != STATE_CARRY)
	{ // 運び状態じゃない場合

		// 運び状態にする
		m_state = STATE_CARRY;
	}
}

//=========================
// 生成処理
//=========================
CPlayer* CPlayer::Create(void)
{
	// ローカルオブジェクトを生成
	CPlayer* pPlayer = nullptr;	// プレイヤーのインスタンスを生成

	if (pPlayer == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pPlayer = new CPlayer;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pPlayer != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pPlayer->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pPlayer->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}

//=========================
// 操作処理
//=========================
void CPlayer::Control(void)
{
	// ローカル変数を宣言する
	D3DXVECTOR3 pos = GetPos();	// 位置
	D3DXVECTOR3 rot = GetRot();	// 向き
	float fStickRotX = 0.0f;	// スティックのX座標
	float fStickRotY = 0.0f;	// スティックのY座標
	float fStickRot = 0.0f;		// スティックの向き

	// スティックの向きを取る
	fStickRotY = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLYPress(0));
	fStickRotX = (float)(CManager::Get()->GetInputGamePad()->GetGameStickLXPress(0));

	if (fStickRotY != 0 ||
		fStickRotX != 0)
	{ // 右スティックをどっちかに倒した場合

		// スティックの向きを設定する
		fStickRot = atan2f(fStickRotX, fStickRotY);

		// カメラの向きを加算する
		fStickRot += CManager::Get()->GetCamera()->GetRot().y;

		// 向きの正規化
		useful::RotNormalize(&fStickRot);

		// 移動させる
		pos.x += sinf(fStickRot) * SPEED;
		pos.z += cosf(fStickRot) * SPEED;

		// 向きを設定する
		rot.y = fStickRot;
	}

	// 位置を向きを適用
	SetPos(pos);
	SetRot(rot);
}

//=========================
// カメラ操作
//=========================
void CPlayer::Camera(void)
{
	D3DXVECTOR3 CameraRot = CManager::Get()->GetCamera()->GetRot();		// カメラの向きを取得する
	float fStickRotX, fStickRotY;		// スティックの向き

	// 右スティックの傾け度を取得する
	fStickRotX = CManager::Get()->GetInputGamePad()->GetGameStickRXPress(0);
	fStickRotY = CManager::Get()->GetInputGamePad()->GetGameStickRYPress(0);

	// カメラの向きを加算する
	CameraRot.y += (fStickRotX * CAMERA_ROT_CORRECT);

	// 向きの正規化
	useful::RotNormalize(&CameraRot.y);

	// 向きを適用する
	CManager::Get()->GetCamera()->SetRot(CameraRot);
}

//=========================
// 射撃処理
//=========================
void CPlayer::Shot(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
		CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // 射撃する

		// 雪玉の生成
		CSnowBall::Create(GetPos() + SNOWBALL_POS, GetRot());
	}
}