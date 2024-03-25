//==========================================
//
//  春度ゲージ(gauge.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CGauge : public CObject2D
{
public:

	// メンバ関数
	CGauge(CObject::TYPE type = TYPE_GAUGE, PRIORITY priority = PRIORITY_ENTITY);
	~CGauge();

	HRESULT Init() override; // 初期化処理
	void Uninit() override; // 終了処理
	void Update() override; // 更新処理
	void Draw() override; // 描画処理

	// 静的メンバ関数
	static CGauge* Create();

private:

	// メンバ関数
	void CalcPos(); // 位置の計算
	void CalcSize(); // サイズの計算

};

#endif
