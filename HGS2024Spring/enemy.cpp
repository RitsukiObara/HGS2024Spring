//=======================================
//
// 敵のメイン処理[enemy.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "enemy.h"
#include "useful.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(2.5f, 2.5f, 2.5f);		// 拡大率
	const char* MODEL = "data\\MODEL\\ENEMY\\enemy.x";		// 敵のモデル
}

//=========================
// オーバーロードコンストラクタ
//=========================
CEnemy::CEnemy() : CModel(TYPE_PLAYER, PRIORITY_PLAYER)
{

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
}

//=========================
// 更新処理
//=========================
void CEnemy::Update(void)
{

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