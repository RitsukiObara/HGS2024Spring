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
	const int FLOWERING_POINT = 30;						// 1回で咲く花の数
	const int MAX_PERCENT = 100;						// 咲き度合の最大数
}

//=========================
// オーバーロードコンストラクタ
//=========================
CBase::CBase() : CModel(TYPE_BASE, PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pPosVtx = nullptr;		// 頂点のポインタ
	m_nPercent = 0;				// 咲き度合
	m_nNumVtx = 0;				// 頂点数
	m_bFlowering = nullptr;		// 現在咲いている箇所
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

	// 開花状況を開放する
	delete[] m_bFlowering;

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

	int nNumFlowPoint = 0;		// 開花する場所の総数
	int nNowPoint = 0;			// 現在の頂点
	m_nNumVtx = GetFileData().pMesh->GetNumVertices();	// 総頂点数

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		if (GetPos().y + GetFileData().vtxPos[nCnt].y >= FLOWERPOINT_HEIGHT)
		{ // 一定の頂点数以上の場合

			// 開花ポイントを加算する
			nNumFlowPoint++;
		}
	}

	// 全ての値を設定する
	m_nPercent = 0;				// 咲き度合
	m_pPosVtx = new D3DXVECTOR3[nNumFlowPoint];	// 開花させる頂点
	m_bFlowering = new bool[nNumFlowPoint];		// 開花状況

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		if (GetPos().y + GetFileData().vtxPos[nCnt].y >= FLOWERPOINT_HEIGHT)
		{ // 一定の頂点数以上の場合

			// 開花ポイントを加算する
			m_pPosVtx[nNowPoint] = GetFileData().vtxPos[nCnt];

			// 開花状況を false にする
			m_bFlowering[nNowPoint] = false;

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
void CBase::Flowering(const int nPercent)
{
	for (int nCnt = 0; nCnt < FLOWERING_POINT; nCnt++)
	{
		int nRand = rand() % m_nNumVtx;
		D3DXVECTOR3 shift;

		// ずらす幅を設定
		shift.x = (float)(rand() % 100 - 50);
		shift.y = (float)(rand() % 100 - 50);
		shift.z = (float)(rand() % 100 - 50);

		// 花の生成
		CBaseFlower::Create(GetPos() + shift + m_pPosVtx[nRand]);
	}

	// 咲き度合を加算する
	m_nPercent += nPercent;
}

//=========================
// 咲き度合の設定処理
//=========================
void CBase::SetPercent(const int nPercent)
{
	// 咲き度合を設定する
	m_nPercent = nPercent;
}

//=========================
// 咲き度合の取得処理
//=========================
int CBase::GetPercent(void) const
{
	// 咲き度合を返す
	return m_nPercent;
}