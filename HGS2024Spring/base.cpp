//=======================================
//
// 拠点のメイン処理[base.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "base.h"
#include "useful.h"

#include "game.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(1100.0f, 0.0f, 1300.0f);		// 位置
	const D3DXVECTOR3 SCALE = D3DXVECTOR3(7.0f, 7.0f, 7.0f);		// 拡大率
	const char* MODEL = "data\\MODEL\\wood.x";		// モデル
}

//=========================
// オーバーロードコンストラクタ
//=========================
CBase::CBase() : CModel(TYPE_BASE, PRIORITY_ENTITY)
{

}

//=========================
// デストラクタ
//=========================
CBase::~CBase()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CBase::Init(void)
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
void CBase::Uninit(void)
{
	// 終了
	CModel::Uninit();

	// 拠点のNULL化処理
	CGame::DeleteBase();
}

//=========================
// 更新処理
//=========================
void CBase::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CBase::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CBase::SetData(void)
{
	// スクロールの設定処理
	SetPos(POS);					// 位置
	SetPosOld(POS);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(SCALE);				// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));
}

//=========================
// 生成処理
//=========================
CBase* CBase::Create(void)
{
	// ローカルオブジェクトを生成
	CBase* pTree = nullptr;	// 木のインスタンスを生成

	if (pTree == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pTree = new CBase;
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
		pTree->SetData();
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