//=====================================================
//
// メッシュドーナツヘッダー [mesh_donut.h]
// Author：小原立暉
//
//=====================================================
#ifndef _MESH_DONUT_H_			// このマクロ定義がされていない場合
#define _MESH_DONUT_H_			// 二重インクルード防止のマクロを定義する

//*****************************************************
// インクルードファイル
//*****************************************************
#include "Objectmesh.h"

//-----------------------------------------------------
// クラス定義(メッシュドーナツ)
//-----------------------------------------------------
class CMeshDonut : public CMesh
{
public:		// 誰でもアクセスできる

	CMeshDonut(CObject::PRIORITY priority = PRIORITY_BG);			// オーバーロードコンストラクタ
	virtual ~CMeshDonut();		// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void);		// 更新処理
	virtual void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fWidth, const float fCircum, const SGrid& Divi);			// 情報の設定処理
	void SetVertex(void);	// 頂点の設定処理

	// 静的メンバ関数
	static CMeshDonut* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fWidth, const float fCircum, const SGrid& Divi, const PRIORITY priority);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	float m_fCircumSize;		// 円周のサイズ
	float m_fWidthSize;			// 幅のサイズ
	float m_fWidthDiviSize;		// 1分割数当たりの幅のサイズ
};


#endif