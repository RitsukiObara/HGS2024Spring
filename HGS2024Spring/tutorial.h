//============================================
//
// チュートリアル画面ヘッダー[tutorial.h]
// Author：小原立暉
//
//============================================
#ifndef _TUTORIAL_H_			//このマクロ定義がされていなかったら
#define _TUTORIAL_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "scene.h"

//==========================================
//  前方宣言
//==========================================
class CTutorialPolygon;

//--------------------------------------------
// クラス(チュートリアルクラス)
//--------------------------------------------
class CTutorial : public CScene
{
public:				// 誰でもアクセスできる

	CTutorial();		// コンストラクタ
	~CTutorial();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	void SetData(const MODE mode);		// 情報の設定処理

private:			// 自分だけアクセスできる

	// メンバ変数
	int m_nEndCount;					// 終了までのカウント

	// 静的メンバ変数
	static CTutorialPolygon* m_pPolygon;
};

#endif