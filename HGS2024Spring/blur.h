//===================================
//
// モーションブラーヘッダー[blur.h]
// Author 小原立暉
//
//===================================
#ifndef _BLUR_H_
#define _BLUR_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(CBlur)
//-----------------------------------
class CBlur : public CModel
{
public:					// 誰でもアクセスできる

	CBlur(PRIORITY priority = PRIORITY_EFFECT);		// オーバーロードコンストラクタ
	~CBlur();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const CXFile::SXFile& filedata, const int nLife, const float fAlpha);		// 情報の設定処理

	// セット・ゲット関数
	float GetSub(void) const;			// 減算量の取得処理

private:				// 自分だけアクセスできる

	// メンバ変数
	int m_nLife;			// 寿命
	float m_fSub;			// 減算量
};

#endif