//==========================================
//
//  チュートリアル画像(tutorial_polygon.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial_polygon.h"
#include "manager.h"
#include "input.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	const D3DXVECTOR3 POLYGON_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

	const char* TEX_PASS[3] =
	{
		"data/TEXTURE/Tutorial_0.png",
		"data/TEXTURE/Tutorial_1.png",
		"data/TEXTURE/Tutorial_2.png"
	}; // テクスチャパス
}

//==========================================
//  コンストラクタ
//==========================================
CTutorialPolygon::CTutorialPolygon(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority),
	m_bEnd(false),
	m_nIdx(0)
{

}

//==========================================
//  デストラクタ
//==========================================
CTutorialPolygon::~CTutorialPolygon()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTutorialPolygon::Init()
{
	// 親クラスの初期化
	if (FAILED(CObject2D::Init())) { return E_FAIL; }

	// 座標の設定
	SetPos(POLYGON_POS);

	// サイズの設定
	SetSize(POLYGON_SIZE);

	// 角度の設定
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 対角線の長さを算出
	SetLength();

	// 対角線の角度を算出
	SetAngle();

	// テクスチャ割り当て
	BindTexture(CManager::Get()->GetTexture()->Regist(TEX_PASS[m_nIdx]));

	// 頂点情報の初期化
	SetVertex();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTutorialPolygon::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTutorialPolygon::Update()
{
	// テクスチャ更新
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0))
	{
		if (!m_bEnd)
		{
			// インデックスを更新
			++m_nIdx;

			// テクスチャ割り当て
			BindTexture(CManager::Get()->GetTexture()->Regist(TEX_PASS[m_nIdx]));

			// チュートリアル完了フラグ
			if (m_nIdx == 2) { m_bEnd = true; }
		}
	}

	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTutorialPolygon::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CTutorialPolygon* CTutorialPolygon::Create()
{
	// インスタンス生成
	CTutorialPolygon* p = new CTutorialPolygon;

	// NULLチェック
	if (p == nullptr) { return nullptr; }

	// 初期化処理
	if (FAILED(p->Init())) { return nullptr; }

	return p;
}
