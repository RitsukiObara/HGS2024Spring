//===================================
//
// 地面ヘッダー[map.h]
// Author 小原立暉
//
//===================================
#ifndef _MAP_H_
#define _MAP_H_

//***********************************
// インクルードファイル
//***********************************
#include "object3D.h"

//-----------------------------------
// クラス定義(CMap)
//-----------------------------------
class CMap : public CObject3D
{
public:

	CMap();				// コンストラクタ
	~CMap();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);				// 情報の設定処理

	// 静的メンバ関数
	static CMap* Create(void);		// 生成処理

private:
};

#endif