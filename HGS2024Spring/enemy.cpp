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
#include "anim_reaction.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(2.5f, 2.5f, 2.5f);	// 拡大率
	const char* MODEL = "data\\MODEL\\ENEMY\\enemy.x";			// 敵のモデル
	const float MOVE_CORRECT = 0.001f;							// 移動量の補正数
	const int LIFE = 5;											// 体力
	const D3DXCOLOR DAMAGE_COL = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		// ダメージの時の色
	const int DAMAGE_COUNT = 6;				// ダメージ状態のカウント数
	const D3DXVECTOR3 EXPLOSION_SIZE = D3DXVECTOR3(80.0f, 80.0f, 0.0f);	// 爆発のサイズ
	const int CATCH_COUNT = 60;				// キャッチ状態のカウント
	const int MAX_CATCH_PERCENT = 5;		// キャッチする度合の最大数
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
	m_nLife = LIFE;					// 体力
	m_nCatchPercent = 0;			// キャッチする度合
	m_nDamageCount = 0;				// ダメージカウント中
	m_nStateCount = 0;				// 状態カウント
	m_bDamage = false;				// ダメージ状況

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

		// 状態カウントを加算する
		m_nStateCount++;

		if (m_nStateCount % (CATCH_COUNT * m_nCatchPercent) == 0)
		{ // 状態カウントが一定数になった場合

			// 状態カウントを0にする
			m_nStateCount = 0;

			// キャッチ処理
			Catch();

			// 帰還状態にする
			m_state = STATE_RETURN;
		}

		break;

	case CEnemy::STATE_RETURN:			// 帰還状態

		if (Return() == true)
		{ // 帰還し終わった場合

			// 終了処理
			Uninit();

			// この先の処理を行わない
			return;
		}

		break;

	default:
		
		// 停止
		assert(false);

		break;
	}

	if (m_bDamage == true)
	{ // ダメージ状況が true の場合

		// ダメージカウントを加算する
		m_nDamageCount++;

		if (m_nDamageCount >= DAMAGE_COUNT)
		{ // ダメージカウントが一定数以上になった場合

			// ダメージカウントを0にする
			m_nDamageCount = 0;

			// ダメージ状況を false にする
			m_bDamage = false;
		}
	}
}

//=========================
// 描画処理
//=========================
void CEnemy::Draw(void)
{
	if (m_bDamage == true)
	{ // ダメージ状況が true の場合

		// 描画処理
		CModel::Draw(DAMAGE_COL);
	}
	else
	{ // 上記以外

		// 描画処理
		CModel::Draw();
	}
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
	m_nLife = LIFE;					// 体力
	m_nDamageCount = 0;				// ダメージカウント中
	m_nCatchPercent = rand() % MAX_CATCH_PERCENT + 1;			// キャッチする度合
	m_nStateCount = 0;				// 状態カウント
	m_bDamage = false;				// ダメージ状況

	// 拠点のポインタを取得
	CBase* pBase = CGame::GetBase();

	if (pBase != nullptr)
	{ // 拠点が存在する場合

		// 移動量の設定処理
		MoveSet(pBase->GetPos());
	}
}

//=========================
// ヒット処理
//=========================
void CEnemy::Hit(void)
{
	// 体力を減算する
	m_nLife--;

	if (m_nLife <= 0)
	{ // 体力が0以下になった場合

		// 爆発を生成
		CAnimReaction::Create(GetPos(), EXPLOSION_SIZE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), CAnimReaction::TYPE::TYPE_EXPLOSION, 4, 1);

		// 終了処理
		Uninit();

		// この先の処理を行わない
		return;
	}
	else
	{ // 上記以外

		// ダメージ状況を true にする
		m_bDamage = true;				// ダメージ状況
	}
}

//=========================
// ダメージ状況の取得処理
//=========================
bool CEnemy::IsDamage(void) const
{
	// ダメージ状況を返す
	return m_bDamage;
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

//=======================================
// キャッチ処理
//=======================================
void CEnemy::Catch(void)
{
	CGame::GetBase()->GetPercent();
}

//=======================================
// 帰還処理
//=======================================
bool CEnemy::Return(void)
{
	// 位置を取得する
	D3DXVECTOR3 posDest = D3DXVECTOR3(-700.0f, 0.0f, 300.0f);
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// 向きを設定する
	rot.y = atan2f(posDest.x - pos.x, posDest.z - pos.z);

	if (useful::FrameCorrect(posDest.x, &pos.x, m_move.x) == true ||
		useful::FrameCorrect(posDest.z, &pos.z, m_move.z) == true)
	{ // 到着した場合

		// true を返す
		return true;
	}

	// 位置と向きを適用
	SetPos(pos);
	SetRot(rot);

	// false を返す
	return false;
}