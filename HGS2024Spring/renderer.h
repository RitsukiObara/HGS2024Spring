//============================================
//
// レンダラーのヘッダー[renderer.h]
// Author：小原立暉
//
//============================================
#ifndef _RENDERER_H_		//このマクロ定義がされていなかったら
#define _RENDERER_H_		//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAX_VERTEX		(4)			// 頂点数

//--------------------------------------------
// クラス(レンダラークラス)
//--------------------------------------------
class CRenderer
{
public:						// 誰でもアクセスできる

	CRenderer();			// コンストラクタ
	~CRenderer();			// デストラクタ

	// メンバ関数
	HRESULT Init(HWND hWnd, BOOL bWindow);		// 初期化処理
	void Uninit(void);							// 終了処理
	void Update(void);							// 更新処理
	void Draw(void);							// 描画処理

	LPDIRECT3DDEVICE9 GetDevice(void);			// デバイスの取得処理

	void SetFog(const bool bFog, const D3DXCOLOR& col, const float fStartPos, const float fEndPos);				// 霧の設定処理

	// 静的メンバ関数
	static CRenderer* Create(HWND hWnd, BOOL bWindow);		// 生成処理

private:					// 自分だけアクセスできる

	// メンバ変数
	LPDIRECT3D9 m_pD3D;							// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;				// Direct3Dデバイスへのポインタ
};

#endif