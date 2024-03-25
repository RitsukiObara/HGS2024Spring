//===================================
//
// プレイヤーヘッダー[player.h]
// Author 小原立暉
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

	CPlayer();				// コンストラクタ
	~CPlayer();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理

	// 静的メンバ関数
	static CPlayer* Create(void);		// 生成処理

private:				// 自分だけアクセスできる

	// メンバ関数
	void Control(void);		// 操作処理
};

#endif