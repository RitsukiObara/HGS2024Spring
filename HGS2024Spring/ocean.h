//===================================
//
// 海ヘッダー[ocean.h]
// Author 小原立暉
//
//===================================
#ifndef _OCEAN_H_
#define _OCEAN_H_

//***********************************
// インクルードファイル
//***********************************
#include "object3D.h"

//-----------------------------------
// クラス定義(COcean)
//-----------------------------------
class COcean : public CObject3D
{
public:

	COcean();				// コンストラクタ
	~COcean();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);				// 情報の設定処理

	// 静的メンバ関数
	static COcean* Create(void);	// 生成処理

private:
};

#endif