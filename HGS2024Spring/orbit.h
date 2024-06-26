//=====================================================================================
//
//	軌跡ヘッダー [orbit.h]
//	Author：小原立暉
//
//=====================================================================================
#ifndef _ORBIT_H_			// このマクロ定義がされていない場合
#define _ORBIT_H_			// 二重インクルード防止のマクロを定義する

//*************************************************************************************
// インクルードファイル
//*************************************************************************************
#include "object.h"

//-------------------------------------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------------------------------------
#define MAX_ORBIT_VTX		(128)			// 軌跡の最高頂点数

//-------------------------------------------------------------------------------------
// クラス定義(軌跡)
//-------------------------------------------------------------------------------------
class COrbit : CObject
{
public:			// 誰でもアクセスできる

	//-------------------------------------------------------------------------------------
	//	列挙型定義 (MATRIXPLACE)
	//-------------------------------------------------------------------------------------
	typedef enum
	{
		MATRIXPLACE_BOTTOM = 0,		// 下
		MATRIXPLACE_TOP,			// 上
		MATRIXPLACE_MAX				// この列挙型の総数
	}MATRIXPLACE;

	COrbit();						// コンストラクタ
	virtual ~COrbit();				// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void);		// 更新処理
	virtual void Draw(void);		// 描画処理

	void SetData(D3DXMATRIX *mtx, D3DXVECTOR3 pos, const float fSize, const int nTexIdx);				// 情報の設定処理
	void SetData(D3DXMATRIX *mtx, D3DXVECTOR3 pos, const float fSize, const char* pTextureName);		// 情報の設定処理
	void BindTexture(int nIdx);		// テクスチャの割り当て処理

	// 静的メンバ関数
	static COrbit* Create(D3DXMATRIX *mtx, D3DXVECTOR3 pos, const float fSize, const int nTexIdx);			// 生成処理(テクスチャ番号)
	static COrbit* Create(D3DXMATRIX *mtx, D3DXVECTOR3 pos, const float fSize, const char* pTextureName);	// 生成処理(テクスチャの名前)

private:		// 自分だけアクセスできる

	// メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// 頂点バッファへのポインタ
	D3DXMATRIX* m_pMtxParent;						// 親のマトリックスへのポインタ
	D3DXVECTOR3 m_aOffset[MATRIXPLACE_MAX];			// 両端のオフセット
	D3DXCOLOR m_aCol[MATRIXPLACE_MAX];				// 両端の基準の色
	D3DXMATRIX m_aMtxWorldPoint[MATRIXPLACE_MAX];	// 両端のワールドマトリックス
	D3DXVECTOR3 m_aPosPoint[MAX_ORBIT_VTX];			// 計算後の各頂点座標
	D3DXCOLOR m_aColPoint[MAX_ORBIT_VTX];			// 計算後の各頂点カラー
	float m_fSize;		// サイズ
	int m_nTexIdx;		// テクスチャのインデックス
};

#endif