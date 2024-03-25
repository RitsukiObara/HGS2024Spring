//===================================
//
// プレイヤーヘッダー[player.h]
// Author 小原立暉
// adder : 金崎朋弥
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(CPlayer)
//-----------------------------------
class CPlayer : public CModel
{
public:					// 誰でもアクセスできる

	// 列挙型定義
	enum STATE
	{
		STATE_NONE = 0,		// 通常状態
		STATE_CARRY,		// 運送状態
		STATE_MAX			// この先の処理を行わない
	};

	CPlayer();				// コンストラクタ
	~CPlayer();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理

	void TreeHit(void);		// 木とのヒット判定

	// 静的メンバ関数
	static CPlayer* Create(void);		// 生成処理

private:				// 自分だけアクセスできる

	// メンバ関数
	void Control(void);		// 操作処理
	void Camera(void);		// カメラ操作
	void Shot(void);		// 射撃処理
	D3DXVECTOR3 Limit(D3DXVECTOR3& pos); // 移動制限 : 金崎

	// メンバ変数
	STATE m_state;			// 状態
};

#endif