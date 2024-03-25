//=======================================
//
// 敵のメイン処理[enemy.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "enemy.h"
#include "useful.h"

#include "game.h"
#include "base.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(2.5f, 2.5f, 2.5f);	// 拡大率
	const char* MODEL = "data\\MODEL\\ENEMY\\enemy.x";			// 敵のモデル
	const float MOVE_CORRECT = 0.001f;							// 移動量の補正数
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CEnemy*> CEnemy::m_list = {};			// リスト情報

//=========================
// オーバーロードコンストラクタ
//=========================
CEnemy::CEnemy() : CModel(TYPE_PLAYER, PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_state = STATE_PROGRESS;		// 状態
	m_move = NONE_D3DXVECTOR3;		// 移動量

	// リストに追加する
	m_list.Regist(this);
}

//=========================
// デストラクタ
//=========================
CEnemy::~CEnemy()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEnemy::Init(void)
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
void CEnemy::Uninit(void)
{
	// 終了
	CModel::Uninit();

	// 引き抜き処理
	m_list.Pull(this);
}

//=========================
// 更新処理
//=========================
void CEnemy::Update(void)
{
	switch (m_state)
	{
	case CEnemy::STATE_PROGRESS:		// 進行状態

		// 進行状態
		Progress();

		break;

	case CEnemy::STATE_CATCH:			// キャッチ状態

		break;

	case CEnemy::STATE_RETURN:			// 帰還状態


		break;

	default:
		
		// 停止
		assert(false);

		break;
	}
}

//=========================
// 描画処理
//=========================
void CEnemy::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CEnemy::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(SCALE);						// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));

	// 全ての値を設定する
	m_state = STATE_PROGRESS;		// 状態

	// 拠点のポインタを取得
	CBase* pBase = CGame::GetBase();

	if (pBase != nullptr)
	{ // 拠点が存在する場合

		// 移動量の設定処理
		MoveSet(pBase->GetPos());
	}
}

//=========================
// 生成処理
//=========================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CEnemy* pEnemy = nullptr;	// 敵のインスタンスを生成

	if (pEnemy == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEnemy = new CEnemy;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEnemy != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEnemy->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEnemy->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 敵のポインタを返す
	return pEnemy;
}

//=======================================
// リストの取得処理
//=======================================
CListManager<CEnemy*> CEnemy::GetList(void)
{
	// リスト構造の情報を返す
	return m_list;
}

//=======================================
// 移動量の設定処理
//=======================================
void CEnemy::MoveSet(const D3DXVECTOR3& posDest)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 移動量を設定
	m_move.x = (posDest.x - pos.x) * MOVE_CORRECT;
	m_move.z = (posDest.z - pos.z) * MOVE_CORRECT;
}

//=======================================
// 進行処理
//=======================================
void CEnemy::Progress(void)
{
	// 拠点のポインタを取得
	CBase* pBase = CGame::GetBase();

	if (pBase != nullptr)
	{ // 拠点が存在する場合

		// 位置を取得する
		D3DXVECTOR3 posDest = pBase->GetPos();
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();

		// 向きを設定する
		rot.y = atan2f(posDest.x - pos.x, posDest.z - pos.z);

		if (useful::FrameCorrect(posDest.x, &pos.x, m_move.x) == true ||
			useful::FrameCorrect(posDest.z, &pos.z, m_move.z) == true)
		{ // 到着した場合

			// キャッチ状態にする
			m_state = STATE_CATCH;
		}

		// 位置と向きを適用
		SetPos(pos);
		SetRot(rot);
	}
}