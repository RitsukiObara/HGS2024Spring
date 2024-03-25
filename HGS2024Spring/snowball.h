//============================================
//
// 雪玉ヘッダー[snowball.h]
// Author：小原立暉
//
//============================================
#ifndef _SNOWBALL_H_					// このマクロ定義がされていなかったら
#define _SNOWBALL_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "objectbillboard.h"

//--------------------------------------------
// クラス定義(雪玉)
//--------------------------------------------
class CSnowBall : public CBillboard
{
public:				// 誰でもアクセスできる

	CSnowBall();			// コンストラクタ
	~CSnowBall();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// 情報の設定処理

	// 静的メンバ変数
	static CSnowBall* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// 生成処理

private:			// 自分だけアクセスできる

	// メンバ関数
	void Move(void);		// 移動処理

	// メンバ変数
	D3DXVECTOR3 m_move;		// 移動量
};

#endif