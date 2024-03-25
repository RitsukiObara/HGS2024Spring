//==========================================
//
//  タイトルロゴクラス(title_logo.h)
//  Author : Kenta Hashimoto
//
//==========================================
#ifndef _CAVEAT_DIRECTION_H_
#define _CAVEAT_DIRECTION_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CCaveatDirection : CObject2D
{
public:

	// メンバ関数
	CCaveatDirection(CObject::TYPE type = TYPE_LOGOMARK, PRIORITY priority = PRIORITY_ENTITY);
	~CCaveatDirection();

	HRESULT Init() override; // 初期化処理
	void Uninit() override; // 終了処理
	void Update() override; // 更新処理
	void Draw() override; // 描画処理

	// 静的メンバ関数
	static CCaveatDirection* Create(); // 生成処理

	void move(void);

private:

};

#endif
#pragma once
