//===================================
//
// モブ木の葉っぱヘッダー[mod_tree_leaf.h]
// Author 小原立暉
//
//===================================
#ifndef _MOB_TREE_LEAF_H_
#define _MOB_TREE_LEAF_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(CMobTreeLeaf)
//-----------------------------------
class CMobTreeLeaf : public CModel
{
public:					// 誰でもアクセスできる

	CMobTreeLeaf();			// コンストラクタ
	~CMobTreeLeaf();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

	void SnowBallHit(void);		// 雪玉との衝突時判定

	// 静的メンバ関数
	static CMobTreeLeaf* Create(const D3DXVECTOR3& pos);		// 生成処理

private:				// 自分だけアクセスできる

	// メンバ関数
	void Growth(void);		// 成長処理
};

#endif