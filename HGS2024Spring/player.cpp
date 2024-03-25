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

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	const char* MODEL = "data\\MODEL\\Platform\\Ripple.x";		// モデル
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
}

//=========================
// 更新処理
//=========================
void CPlayer::Update(void)
{
	if (CManager::Get()->GetInputGamePad()->GetConnect() == true)
	{ // コントローラーが繋がっている場合

		// 操作処理
		Control();
	}
	else
	{ // 上記以外

		// キーボード処理
		Keyboard();
	}

	// 射撃処理
	Shot();
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
	SetPos(POS);								// 位置
	SetPosOld(POS);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(NONE_SCALE);						// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
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
// キーボード処理
//=========================
void CPlayer::Keyboard(void)
{
	// ローカル変数を宣言する
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き
	float fMoveX = 0.0f;			// X軸の移動量
	float fMoveZ = 0.0f;			// Z軸の移動量
	float fStickRot = 0.0f;			// 向き

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // Wキーを押した場合

		// Z軸の移動量を設定する
		fMoveZ = 1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // Sキーを押した場合

		// Z軸の移動量を設定する
		fMoveZ = -1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // Aキーを押した場合

		// X軸の移動量を設定する
		fMoveX = -1.0f;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // Dキーを押した場合

		// X軸の移動量を設定する
		fMoveX = 1.0f;
	}

	if (fMoveX != 0 ||
		fMoveZ != 0)
	{ // 右スティックをどっちかに倒した場合

		// スティックの向きを設定する
		fStickRot = atan2f(fMoveX, fMoveZ);

		// 向きの正規化
		useful::RotNormalize(&fStickRot);

		// 移動させる
		pos.x += sinf(fStickRot) * SPEED;
		pos.z += cosf(fStickRot) * SPEED;

		// 向きを設定する
		rot.y = fStickRot;
	}

	// 位置と向きを設定する
	SetPos(pos);
	SetRot(rot);
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
		CSnowBall::Create(GetPos(), GetRot());
	}
}