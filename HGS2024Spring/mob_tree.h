//===================================
//
// モブ木ヘッダー[mod_tree.h]
// Author 小原立暉
//
//===================================
#ifndef _MOB_TREE_H_
#define _MOB_TREE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "list_manager.h"

// 前方宣言
class CMobTreeLeaf;		// モブ木の葉

//-----------------------------------
// クラス定義(CMobTree)
//-----------------------------------
class CMobTree : public CModel
{
public:					// 誰でもアクセスできる

	CMobTree();				// コンストラクタ
	~CMobTree();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nCount);		// 情報の設定処理

	void SnowBallHit(void);	// 雪玉との衝突時判定

	// 静的メンバ関数
	static CMobTree* Create(const D3DXVECTOR3& pos, const int nCount);		// 生成処理

	static CListManager<CMobTree*> GetList(void);			// リストの取得処理

private:				// 自分だけアクセスできる

	// メンバ変数
	CMobTreeLeaf* m_pLeaf;		// 葉っぱの情報
	int m_nFloweringCount;		// 咲くまでのカウント

	// 静的メンバ変数
	static CListManager<CMobTree*> m_list;		// リスト情報
};

#endif