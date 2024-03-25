//=======================================
//
// モブ木のメイン処理[mob_tree.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "mob_tree.h"
#include "useful.h"

#include "mob_tree_leaf.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(3.0f, 3.0f, 3.0f);	// 拡大率
	const D3DXVECTOR3 LEAF_SHIFT = D3DXVECTOR3(0.0f, 230.0f, 0.0f);			// 葉のずらす幅
	const char* TREE_MODEL = "data\\MODEL\\wood.x";				// 木のモデル
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CMobTree*> CMobTree::m_list = {};			// リスト情報

//=========================
// オーバーロードコンストラクタ
//=========================
CMobTree::CMobTree() : CModel(TYPE_TREE, PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pLeaf = nullptr;		// 葉のモデル
	m_nFloweringCount = 0;	// 咲くまでのカウント

	// リストに追加する
	m_list.Regist(this);
}

//=========================
// デストラクタ
//=========================
CMobTree::~CMobTree()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CMobTree::Init(void)
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
void CMobTree::Uninit(void)
{
	if (m_pLeaf != nullptr)
	{ // 葉が NULL じゃない場合

		// 終了処理
		m_pLeaf->Uninit();
		m_pLeaf = nullptr;
	}

	// 終了
	CModel::Uninit();

	// 引き抜き処理
	m_list.Pull(this);
}

//=========================
// 更新処理
//=========================
void CMobTree::Update(void)
{
	if (m_nFloweringCount <= 0)
	{ // 開花カウントが0以下の場合

		if (m_pLeaf != nullptr)
		{ // 葉っぱが NULL じゃない場合

			// 更新処理
			m_pLeaf->Update();
		}
	}
	else
	{ // 上記以外

		// 開花カウントを減算する
		m_nFloweringCount--;
	}
}

//=========================
// 描画処理
//=========================
void CMobTree::Draw(void)
{
	// 描画処理
	CModel::Draw();

	if (m_pLeaf != nullptr)
	{ // 葉が NULL じゃない場合

		// 描画処理
		m_pLeaf->Draw();
	}
}

//=========================
// 情報の設定処理
//=========================
void CMobTree::SetData(const D3DXVECTOR3& pos, const int nCount)
{
	// スクロールの設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(SCALE);				// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(TREE_MODEL));

	// 全ての値を設定する
	if (m_pLeaf == nullptr)
	{ // 葉が NULL の場合

		// 葉を生成
		m_pLeaf = CMobTreeLeaf::Create(pos + LEAF_SHIFT);
	}
	m_nFloweringCount = nCount;	// 咲くまでのカウント
}

//=========================
// プレイヤーとの衝突時判定
//=========================
void CMobTree::SnowBallHit(void)
{
	if (m_pLeaf != nullptr)
	{ // 葉が NULL じゃない場合

		// 雪玉との衝突時判定
		m_pLeaf->SnowBallHit();
	}
}

//=========================
// 生成処理
//=========================
CMobTree* CMobTree::Create(const D3DXVECTOR3& pos, const int nCount)
{
	// ローカルオブジェクトを生成
	CMobTree* pTree = nullptr;	// 木のインスタンスを生成

	if (pTree == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pTree = new CMobTree;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTree != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pTree->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTree->SetData(pos, nCount);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 木のポインタを返す
	return pTree;
}

//=======================================
// リストの取得処理
//=======================================
CListManager<CMobTree*> CMobTree::GetList(void)
{
	// リスト構造の情報を返す
	return m_list;
}