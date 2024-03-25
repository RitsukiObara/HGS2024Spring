//===================================
//
// 拠点ヘッダー[base.h]
// Author 小原立暉
//
//===================================
#ifndef _BASE_H_
#define _BASE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(CBase)
//-----------------------------------
class CBase : public CModel
{
public:					// 誰でもアクセスできる

	CBase();				// コンストラクタ
	~CBase();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理

	void Flowering(const int nPercent);			// 開花処理

	// セット・ゲット関係
	void SetPercent(const int nPercent);		// 咲き度合の設定処理
	int GetPercent(void) const;					// 咲き度合の取得処理

	// 静的メンバ関数
	static CBase* Create(void);		// 生成処理

private:				// 自分だけアクセスできる

	// メンバ変数
	D3DXVECTOR3* m_pPosVtx;	// 頂点のポインタ
	int m_nPercent;			// 咲き度合
	int m_nNumVtx;			// 頂点数
	bool* m_bFlowering;		// 現在咲いている箇所
};

#endif