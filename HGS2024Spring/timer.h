//==========================================
//
//  タイマー(timer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIMER_H_
#define _TIMER_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CTimer : public CObject2D
{
public:

	// メンバ関数
	CTimer(CObject::TYPE type = TYPE_TIME, PRIORITY priority = PRIORITY_ENTITY);
	~CTimer();

	HRESULT Init() override; // 初期化処理
	void Uninit() override; // 終了処理
	void Update() override; // 更新処理
	void Draw() override; // 描画処理

	// 静的メンバ関数
	static CTimer* Create();

private:

	// メンバ関数
	void CalcTime(); // 経過時間の計算
	void Floating(); // 大きさの浮動

	// メンバ変数
	DWORD m_oldTime; // 前回時間
	float m_time; // 経過時間
	bool m_bPichUp; // ピッチが上がったフラグ

};

#endif
