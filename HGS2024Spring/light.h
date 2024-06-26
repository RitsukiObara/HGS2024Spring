//===================================
//
// ライトヘッダー[light.h]
// Author 小原立暉
//
//===================================
#ifndef _LIGHT_H_			// このマクロ定義がされていなかったら
#define _LIGHT_H_			// 2重インクルード防止のマクロを定義する

//***********************************
// インクルードファイル
//***********************************
#include "main.h"

//-----------------------------------
// クラス定義
//-----------------------------------
class CLight
{
public:			// 誰でもアクセスできる

	CLight();			// コンストラクタ
	~CLight();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理

	void ResetCol(void);	// 色のリセット処理

	void SetLightInfo(const int nIdx, const D3DLIGHT9& light);		// ライトの設定処理
	D3DLIGHT9 GetLightInfo(const int nIdx) const;		// ライトの取得処理

	void SetLightCamera(const D3DLIGHT9& light);		// カメラ追従ライトの設定処理
	D3DLIGHT9 GetLightCamera(void) const;				// カメラ追従ライトの取得処理

	// 静的メンバ関数
	static CLight* Create(void);		// 生成処理

	// 定数定義
	static const int NUM_LIGHT = 3;		// ライトの数

private:		// 誰でもアクセスできる

	// メンバ変数
	D3DLIGHT9 m_aLight[NUM_LIGHT];		// ライトの情報
	D3DLIGHT9 m_lightCamera;			// カメラに追従するライト
};

#endif