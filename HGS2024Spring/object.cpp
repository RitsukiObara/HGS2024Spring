//============================================
//
// オブジェクトのメイン処理[object.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "object.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "camera.h"
#include "pause.h"

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CObject* CObject::m_apTop[DIM_MAX][PRIORITY_MAX] = {};	// 先頭のオブジェクトへのポインタ
CObject* CObject::m_apCur[DIM_MAX][PRIORITY_MAX] = {};	// 最後尾オブジェクトへのポインタ
int CObject::m_nNumAll = 0;								// オブジェクトの総数

//=========================================
// オーバーロードコンストラクタ
//=========================================
CObject::CObject(TYPE type, DIM dim, PRIORITY priority)
{
	// 全ての値を初期化する
	m_pPrev = nullptr;			// 前のオブジェクトへのポインタ
	m_pNext = nullptr;			// 次のオブジェクトへのポインタ
	m_type = type;				// 種類
	m_priority = priority;		// オブジェクトの優先順位
	m_dim = dim;				// 次元
	m_bDeath = false;			// 死亡フラグ

	if (m_apTop[dim][priority] == nullptr)
	{ // オブジェクトが NULL の場合

		// 先頭のポインタに自分自身を代入
		m_apTop[dim][priority] = this;

		// 最後尾のポインタに自分自身を代入
		m_apCur[dim][priority] = this;

		// 種類を設定する
		m_type = type;

		// オブジェクトの優先順位を設定する
		m_priority = priority;

		// 前のオブジェクトへのポインタを設定する
		m_pPrev = nullptr;

		// 次のオブジェクトへのポインタを設定する
		m_pNext = nullptr;

		// 総数をカウントアップ
		m_nNumAll++;
	}
	else
	{ // 上記以外

		// ローカルポインタを宣言
		CObject* pObject = m_apTop[dim][priority];			// 次のオブジェクト

		while (pObject->m_pNext != nullptr)
		{ // オブジェクトがある限り回る

			// 次のオブジェクトを代入する
			pObject = pObject->m_pNext;
		}

		// 比較オブジェクトの次のオブジェクトに自分自身を代入する
		pObject->m_pNext = this;

		// 次のオブジェクトに NULL を入れる
		m_pNext = nullptr;

		// 現在の比較オブジェクトを自分の前のオブジェクトに設定する
		m_pPrev = pObject;

		// 種類を設定する
		m_type = type;

		// オブジェクトの優先順位を設定する
		m_priority = priority;

		// 自分自身を最後尾のオブジェクトに設定する
		m_apCur[dim][priority] = this;

		// 総数をカウントアップ
		m_nNumAll++;
	}
}

//=========================================
// デストラクタ
//=========================================
CObject::~CObject()
{

}

#if 0

//===========================================
// オブジェクトの初期化処理
//===========================================
HRESULT CObject::Init(void)
{

}

//===========================================
// オブジェクトの終了処理
//===========================================
void CObject::Uninit(void)
{

}

//===========================================
// オブジェクトの更新処理
//===========================================
void CObject::Update(void)
{

}

//===========================================
// オブジェクトの描画処理
//===========================================
void CObject::Draw(void)
{

}

#endif

//===========================================
// オブジェクトの取得処理
//===========================================
CObject* CObject::GetTop(DIM dim, PRIORITY priority)
{
	// オブジェクトの情報を渡す
	return m_apTop[dim][priority];
}

//===========================================
// 次のポインタの取得処理
//===========================================
CObject* CObject::GetNext(void)
{
	// 次のオブジェクトを返す
	return m_pNext;
}

//===========================================
// 種類の設定処理
//===========================================
void CObject::SetType(const TYPE type)
{
	// 種類を設定する
	m_type = type;
}

//===========================================
// 種類の取得処理
//===========================================
CObject::TYPE CObject::GetType(void) const
{
	// 種類を返す
	return m_type;
}

//===========================================
// 全てのオブジェクトの破棄
//===========================================
void CObject::ReleaseAll(void)
{
	// オブジェクトのポインタを宣言
	CObject* pObj = nullptr;			// 現在のオブジェクト
	CObject* pObjNext = nullptr;		// 次のオブジェクト

	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{
		for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
		{
			// 現在のオブジェクトに先頭のオブジェクトを代入する
			pObj = m_apTop[nCntDim][nCntPri];

			while (pObj != nullptr)
			{ // オブジェクトが NULL じゃない限り回す

				// 次のオブジェクトを代入する
				pObjNext = pObj->m_pNext;

				if (pObj->m_type != TYPE_NONE)
				{ // 種類無し以外の場合

					// 終了処理
					pObj->Uninit();
				}

				// 次のオブジェクトを設定する
				pObj = pObjNext;
			}

			for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
			{
				// 死亡判定処理
				DeathDecision(nCntDim, nCnt);
			}
		}
	}
}

//======================================
// 汎用的な全消去処理
//======================================
void CObject::AnyAllClear(const TYPE type)
{
	// オブジェクトのポインタを宣言
	CObject* pObj = nullptr;			// 現在のオブジェクト
	CObject* pObjNext = nullptr;		// 次のオブジェクト

	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{
		for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
		{
			// 現在のオブジェクトに先頭のオブジェクトを代入する
			pObj = m_apTop[nCntDim][nCntPri];

			while (pObj != nullptr)
			{ // オブジェクトが NULL じゃない限り回す

				// 次のオブジェクトを代入する
				pObjNext = pObj->m_pNext;

				if (pObj->GetType() == type)
				{ // 指定された種類だった場合

					// 終了処理
					pObj->Uninit();
				}

				// 次のオブジェクトを設定する
				pObj = pObjNext;
			}

			for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
			{
				// 死亡判定処理
				DeathDecision(nCntDim, nCnt);
			}
		}
	}
}

//===========================================
// 汎用的な全消去処理
//===========================================
void CObject::AnyAllClear(const DIM dim, const PRIORITY priority, const TYPE type)
{
	// オブジェクトのポインタを宣言
	CObject* pObj = nullptr;			// 現在のオブジェクト
	CObject* pObjNext = nullptr;		// 次のオブジェクト

	// 現在のオブジェクトに先頭のオブジェクトを代入する
	pObj = m_apTop[dim][priority];

	while (pObj != nullptr)
	{ // オブジェクトが NULL じゃない限り回す

		// 次のオブジェクトを代入する
		pObjNext = pObj->m_pNext;

		if (pObj->GetType() == type)
		{ // 指定された種類だった場合

			// 終了処理
			pObj->Uninit();
		}

		// 次のオブジェクトを設定する
		pObj = pObjNext;
	}

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// 死亡判定処理
		DeathDecision(dim, nCnt);
	}
}

//===========================================
// 全ての更新処理
//===========================================
void CObject::UpdateAll(void)
{
	// ローカル変数宣言
	CObject* pObj = nullptr;		// 現在のオブジェクトのポインタ
	CObject* pObjNext = nullptr;	// 次のオブジェクトのポインタ

	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{
		for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
		{
			// オブジェクトを代入する
			pObj = m_apTop[nCntDim][nCntPri];

			while (pObj != nullptr)
			{ // オブジェクトが NULL じゃない限り回す

				// 次のオブジェクトを代入する
				pObjNext = pObj->m_pNext;

				if (pObj->GetType() != TYPE_NONE &&
					pObj->m_bDeath == false)
				{ // オブジェクトの種類が NONEとPAUSE以外かつ、死亡フラグがfalseの場合

					// オブジェクトの更新
					pObj->Update();

					if (pObj != nullptr &&
						pObj->m_pNext == nullptr)
					{ // 次のオブジェクトが NULL の場合

						// 次のオブジェクトを NULL にする
						pObjNext = nullptr;
					}
				}

				// 次のオブジェクトを代入する
				pObj = pObjNext;
			}
		}

		for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
		{
			// 死亡判定処理
			DeathDecision(nCntDim, nCnt);
		}
	}
}

//===========================================
// 全ての描画処理
//===========================================
void CObject::DrawAll(void)
{
	// カメラの設定処理
	CManager::Get()->GetCamera()->Set();

	// ローカル変数宣言
	CObject* pObj = nullptr;		// 現在のオブジェクトのポインタ

	for (int nCntDim = 0; nCntDim < DIM_MAX; nCntDim++)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			// 先頭のオブジェクトを設定する
			pObj = m_apTop[nCntDim][nCntPriority];

			while (pObj != nullptr)
			{ // オブジェクトが NULL じゃない限り回す

				if (pObj->GetType() != TYPE_NONE)
				{ // 種類が 無し・ポーズ 以外の場合

					// オブジェクトの描画
					pObj->Draw();
				}

				// 次のオブジェクトを代入
				pObj = pObj->m_pNext;
			}
		}
	}
}

//===========================================
// オブジェクトの破棄処理
//===========================================
void CObject::Release(void)
{
	// 死亡フラグを立てる
	m_bDeath = true;
}

//===========================================
// 死亡処理
//===========================================
void CObject::Death(void)
{
	// ローカル変数を宣言
	int nPriority = m_priority;		// 優先順位の保存変数
	int nDim = m_dim;				// 次元の保存変数
	CObject* pObjNext = nullptr;	// 次のオブジェクト
	CObject* pObjPrev = nullptr;	// 前のオブジェクト

	if (m_apTop[nDim][nPriority] == this)
	{ // 先頭のオブジェクトだった場合

		if (m_apTop[nDim][nPriority]->m_pNext != nullptr)
		{ // 次のオブジェクトが存在した場合

			// 次のオブジェクトを設定する
			pObjNext = m_apTop[nDim][nPriority]->m_pNext;
		}

		// 前のオブジェクトは存在しないので NULL にする
		pObjPrev = nullptr;

		// オブジェクトに設定する
		m_apTop[nDim][nPriority] = pObjNext;

		if (m_apCur[nDim][nPriority] == this)
		{ // 最後尾も自分自身だった場合

			// 最後尾を NULL にする
			m_apCur[nDim][nPriority] = nullptr;
		}

		// メモリを開放する
		delete this;

		if (pObjNext != nullptr)
		{ // 次のオブジェクトが存在した場合

			// 次のオブジェクトの前のオブジェクト(自分自身)を NULL にする
			pObjNext->m_pPrev = nullptr;
		}

		// 総数をカウントダウンする
		m_nNumAll--;
	}
	else if (m_apCur[nDim][nPriority] == this)
	{ // 最後尾のオブジェクトだった場合

		// 次のオブジェクトは存在しないので NULL にする
		pObjNext = nullptr;

		// 前のオブジェクトを設定する
		pObjPrev = m_apCur[nDim][nPriority]->m_pPrev;

		// オブジェクトに設定する
		m_apCur[nDim][nPriority] = pObjPrev;

		// メモリを開放する
		delete this;

		// 前のオブジェクトの次のオブジェクト(自分自身)を NULL にする
		pObjPrev->m_pNext = nullptr;

		// 総数をカウントダウンする
		m_nNumAll--;
	}
	else
	{ // 上記以外(中間のオブジェクト)の場合

		// 次のオブジェクトは存在しないので NULL にする
		pObjNext = m_pNext;

		// 前のオブジェクトを設定する
		pObjPrev = m_pPrev;

		// 前のオブジェクトの次のオブジェクトを置き換える
		pObjPrev->m_pNext = pObjNext;

		// 次のオブジェクトの前のオブジェクトを置き換える
		pObjNext->m_pPrev = pObjPrev;

		// メモリを開放する
		delete this;

		// 総数をカウントダウンする
		m_nNumAll--;
	}
}

//===========================================
// 死亡判別処理
//===========================================
void CObject::DeathDecision(const int dim, const int nCnt)
{
	// ローカル変数宣言
	CObject* pObj = nullptr;		// 現在のオブジェクトのポインタ
	CObject* pObjNext = nullptr;	// 次のオブジェクトのポインタ

	// オブジェクトを代入する
	pObj = m_apTop[dim][nCnt];

	while (pObj != nullptr)
	{ // オブジェクトが NULL じゃない限り回す

		// 次のオブジェクトを代入する
		pObjNext = pObj->m_pNext;

		if (pObj->m_bDeath == true)
		{ // オブジェクトに死亡フラグが立っていた場合

			if (pObj->m_pPrev != nullptr)
			{ // 前のオブジェクトが NULL じゃない場合

				// リスト構造から自分を抜き出す
				pObj->m_pPrev->m_pNext = pObj->m_pNext;
			}

			if (pObj->m_pNext != nullptr)
			{ // 次のオブジェクトが NULL じゃない場合

				// リスト構造か.ら自分を抜き出す
				pObj->m_pNext->m_pPrev = pObj->m_pPrev;
			}

			// 死亡(破棄)処理
			pObj->Death();
			pObj = nullptr;
		}

		// 次のオブジェクトを代入する
		pObj = pObjNext;
	}
}