//===================================
//
// 敵ヘッダー[enemy.h]
// Author 小原立暉
//
//===================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "list_manager.h"

//-----------------------------------
// クラス定義(CEnemy)
//-----------------------------------
class CEnemy : public CModel
{
public:					// 誰でもアクセスできる

	// 列挙型定義
	enum STATE
	{
		STATE_PROGRESS = 0,		// 進行状態
		STATE_CATCH,			// キャッチ状態
		STATE_RETURN,			// 帰還状態
		STATE_MAX				// この列挙型の総数
	};

	CEnemy();				// コンストラクタ
	~CEnemy();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

	void Hit(void);			// ヒット処理

	// セット・ゲット関係
	bool IsDamage(void) const;		// ダメージ状況の取得処理

	// 静的メンバ関数
	static CEnemy* Create(const D3DXVECTOR3& pos);	// 生成処理

	static CListManager<CEnemy*> GetList(void);		// リストの取得処理

private:				// 自分だけアクセスできる

	// メンバ関数
	void MoveSet(const D3DXVECTOR3& posDest);		// 移動量の設定処理
	void Progress(void);	// 進行処理
	void Catch(void);		// キャッチ処理
	bool Return(void);		// 帰還処理

	// メンバ変数
	D3DXVECTOR3 m_move;		// 移動量
	STATE m_state;			// 状態
	int m_nCatchPercent;	// キャッチする度合
	int m_nLife;			// 体力
	int m_nDamageCount;		// ダメージカウント中
	int m_nStateCount;		// 状態カウント
	bool m_bDamage;			// ダメージ状況

	// 静的メンバ変数
	static CListManager<CEnemy*> m_list;		// リスト情報
};

#endif