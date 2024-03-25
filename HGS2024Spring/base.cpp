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
#include "base_flower.h"

//=======================================
// 定数定義
//=======================================
namespace
{
	const D3DXVECTOR3 POS = D3DXVECTOR3(1100.0f, 0.0f, 1300.0f);		// 位置
	const char* MODEL = "data\\MODEL\\ayakasi.x";		// モデル
	const float FLOWERPOINT_HEIGHT = 500.0f;			// 花が咲く高さ
}

//=========================
// オーバーロードコンストラクタ
//=========================
CBase::CBase() : CModel(TYPE_BASE, PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pPosVtx = nullptr;		// 頂点のポインタ
	m_nNumVtx = 0;				// 頂点数
	m_nNowFlowPoint = 0;		// 現在咲いているポイント
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
	// 開花ポイントを破棄する
	delete[] m_pPosVtx;

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
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CManager::Get()->GetXFile()->Regist(MODEL));

	// モデルの頂点数を取得
	int nNumFlowPoint = 0;
	int nNowPoint = 0;
	m_nNumVtx = GetFileData().pMesh->GetNumVertices();

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		if (GetPos().y + GetFileData().vtxPos[nCnt].y >= FLOWERPOINT_HEIGHT)
		{ // 一定の頂点数以上の場合

			// 開花ポイントを加算する
			nNumFlowPoint++;
		}
	}

	// 全ての値を設定する
	m_pPosVtx = new D3DXVECTOR3[nNumFlowPoint];	// 開花させる頂点

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		if (GetPos().y + GetFileData().vtxPos[nCnt].y >= FLOWERPOINT_HEIGHT)
		{ // 一定の頂点数以上の場合

			// 開花ポイントを加算する
			m_pPosVtx[nNowPoint] = GetFileData().vtxPos[nCnt];

			// 現在のポイントを加算する
			nNowPoint++;
		}
	}

	// 頂点数を再設定する
	m_nNumVtx = nNumFlowPoint;
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

//=========================
// 開花処理
//=========================
void CBase::Flowering(void)
{
	for (int nCnt = m_nNowFlowPoint; nCnt < m_nNowFlowPoint + 170; nCnt++)
	{
		// 花の生成
		CBaseFlower::Create(GetPos() + m_pPosVtx[nCnt]);
	}

	// 現在咲いているポイントを加算する
	m_nNowFlowPoint += 170;
}