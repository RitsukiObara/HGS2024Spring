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
	const D3DXVECTOR3 MAX_SCALE = D3DXVECTOR3(3.0f, 3.0f, 3.0f);	// 拡大率の最大値
	const D3DXVECTOR3 MIN_SCALE = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 拡大率の最小値
	const char* LEAF_MODEL = "data\\MODEL\\leaf.x";					// 葉のモデル
	const float SCALE_MOVE = 0.005f;			// 拡大率の移動量
	const D3DXVECTOR3 GET_SCALE_SUB = D3DXVECTOR3(0.1f, 0.1f, 0.1f);	// 拡大率の取得時の減算量
}

//=========================
// オーバーロードコンストラクタ
//=========================
CMobTreeLeaf::CMobTreeLeaf() : CModel(TYPE_NONE, PRIORITY_ENTITY)
{

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
	// 成長処理
	Growth();
}

//=========================
// 描画処理
//=========================
void CMobTreeLeaf::Draw(void)
{
	// 描画処理
	CModel::Draw();
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
	SetScale(MIN_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(LEAF_MODEL));
}

//=========================
// 雪玉との衝突時判定
//=========================
void CMobTreeLeaf::SnowBallHit(void)
{
	// 拡大率を取得
	D3DXVECTOR3 scale = GetScale();

	if (scale.x > MIN_SCALE.x)
	{ // 拡大率が一定数以上の場合

		// 拡大率を最小にする
		SetScale(GetScale() - GET_SCALE_SUB);
	}
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

//=========================
// 成長処理
//=========================
void CMobTreeLeaf::Growth(void)
{
	// 拡大率を取得
	D3DXVECTOR3 scale = GetScale();

	// 均等な補正処理
	useful::FrameCorrect(MAX_SCALE.x, &scale.x, SCALE_MOVE);
	useful::FrameCorrect(MAX_SCALE.y, &scale.y, SCALE_MOVE);
	useful::FrameCorrect(MAX_SCALE.z, &scale.z, SCALE_MOVE);

	// 拡大率の適用
	SetScale(scale);
}