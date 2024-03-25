//==========================================
//
//  チュートリアル画像(tutorial_polygon.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TUTORIAL_POLYGON_H_
#define _TUTORIAL_POLYGON_H_
#include "object2D.h"

//==========================================
//  クラス定義
//==========================================
class CTutorialPolygon : public CObject2D
{
public:

	// メンバ関数
	CTutorialPolygon(CObject::TYPE type = TYPE_TUTORIAL, PRIORITY priority = PRIORITY_ENTITY);
	~CTutorialPolygon();

	HRESULT Init() override; // 初期化処理
	void Uninit() override; // 終了処理
	void Update() override; // 更新処理
	void Draw() override; // 描画処理

	bool GetEnd() { return m_bEnd; } // チュートリアル終了フラグの取得

	// 静的メンバ関数
	static CTutorialPolygon* Create();

private:

	// メンバ変数
	bool m_bEnd;
	int m_nIdx;

};

#endif
