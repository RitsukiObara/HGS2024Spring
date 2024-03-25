//==========================================
//
//  タイトルロゴクラス(title_logo.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CTitleLogo : CObject2D
{
public:

	// メンバ関数
	CTitleLogo(CObject::TYPE type = TYPE_LOGOMARK, PRIORITY priority = PRIORITY_ENTITY);
	~CTitleLogo();

	HRESULT Init(); // 初期化処理
	void Uninit(); // 終了処理
	void Update(); // 更新処理
	void Draw(); // 描画処理

	// 静的メンバ関数
	static CTitleLogo* Create(); // 生成処理

private:

};

#endif
