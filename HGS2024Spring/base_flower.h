//===================================
//
// 拠点の花ヘッダー[base_effect.h]
// Author 小原立暉
//
//===================================
#ifndef _BASE_EFFECT_H_
#define _BASE_EFFECT_H_

//***********************************
// インクルードファイル
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// クラス定義(CBaseFlower)
//-----------------------------------
class CBaseFlower : public CBillboard
{
public:

	CBaseFlower();			// コンストラクタ
	~CBaseFlower();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// 静的メンバ関数
	static CBaseFlower* Create(const D3DXVECTOR3& pos);		// 生成処理

private:

};

#endif