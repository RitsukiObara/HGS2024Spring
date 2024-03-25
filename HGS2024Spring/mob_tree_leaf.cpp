//=======================================
//
// モブ木葉のメイン処理[mob_tree_leaf.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "mob_tree_leaf.h"
#include "useful.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(3.0f, 3.0f, 3.0f);	// 拡大率
	const D3DXCOLOR IMMATURE_COL = D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f);		// 未熟状態の葉の色
	const char* LEAF_MODEL = "data\\MODEL\\leaf.x";				// 葉のモデル
}

//=========================
// オーバーロードコンストラクタ
//=========================
CMobTreeLeaf::CMobTreeLeaf() : CModel(TYPE_NONE, PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_col = IMMATURE_COL;		// 色
}

//=========================
// デストラクタ
//=========================
CMobTreeLeaf::~CMobTreeLeaf()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CMobTreeLeaf::Init(void)
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
void CMobTreeLeaf::Uninit(void)
{
	// 終了
	CModel::Uninit();
}

//=========================
// 更新処理
//=========================
void CMobTreeLeaf::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CMobTreeLeaf::Draw(void)
{
	// 描画処理
	CModel::Draw(m_col);
}

//=========================
// 情報の設定処理
//=========================
void CMobTreeLeaf::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(SCALE);				// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(LEAF_MODEL));

	// 全ての値を設定する
	m_col = IMMATURE_COL;		// 色
}

//=========================
// 生成処理
//=========================
CMobTreeLeaf* CMobTreeLeaf::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CMobTreeLeaf* pLeaf = nullptr;	// 葉のインスタンスを生成

	if (pLeaf == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pLeaf = new CMobTreeLeaf;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pLeaf != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pLeaf->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pLeaf->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 葉のポインタを返す
	return pLeaf;
}