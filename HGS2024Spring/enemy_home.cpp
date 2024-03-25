//=======================================
//
// 敵のホームのメイン処理[enemy_home.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "enemy_home.h"

#include "enemy.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(2.0f, 2.0f, 2.0f);			// 拡大率
	const char* MODEL = "data\\MODEL\\Enemy\\enemy_base.x";				// 敵のホーム
	const int ENEMY_INTERVAL = 600;			// 敵の出る間隔
	const float ENEMY_HEIGHT = 100.0f;		// 敵の高さ
}

//=========================
// オーバーロードコンストラクタ
//=========================
CEnemyHome::CEnemyHome() : CModel(TYPE_ENEMYHOME, PRIORITY_ENTITY)
{

}

//=========================
// デストラクタ
//=========================
CEnemyHome::~CEnemyHome()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEnemyHome::Init(void)
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
void CEnemyHome::Uninit(void)
{
	// 終了
	CModel::Uninit();
}

//=========================
// 更新処理
//=========================
void CEnemyHome::Update(void)
{
	// 敵の出るカウントを加算する
	m_nEnemyCount++;

	if (m_nEnemyCount % ENEMY_INTERVAL == 0)
	{ // 敵の出るカウントが一定数の場合

		D3DXVECTOR3 pos = GetPos();

		// 敵の高さを設定する
		pos.y = ENEMY_HEIGHT;

		// 敵の生成処理
		CEnemy::Create(pos);

		// 敵の出るカウントを0にする
		m_nEnemyCount = 0;
	}
}

//=========================
// 描画処理
//=========================
void CEnemyHome::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CEnemyHome::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// スクロールの設定処理
	SetPos(pos);			// 位置
	SetPosOld(pos);			// 前回の位置
	SetRot(rot);			// 向き
	SetScale(SCALE);		// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
}

//=========================
// 生成処理
//=========================
CEnemyHome* CEnemyHome::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CEnemyHome* pEnemy = nullptr;	// 敵のホームのインスタンスを生成

	if (pEnemy == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEnemy = new CEnemyHome;
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
		pEnemy->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 敵のホームのポインタを返す
	return pEnemy;
}