//==========================================
//
//  タイトルロゴクラス(title_logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title_logo.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f); // ポリゴン座標
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(670.0f, 360.0f, 0.0f); // ポリゴン座標
	const char* TEX_PASS = "data/TEXTURE/title.png"; // テクスチャパス
}

//==========================================
//  コンストラクタ
//==========================================
CTitleLogo::CTitleLogo(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority)
{

}

//==========================================
//  デストラクタ
//==========================================
CTitleLogo::~CTitleLogo()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CTitleLogo::Init(void)
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
	BindTexture(CManager::Get()->GetTexture()->Regist(TEX_PASS));

	// 頂点情報の初期化
	SetVertex();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CTitleLogo::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CTitleLogo::Update()
{
	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CTitleLogo::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CTitleLogo* CTitleLogo::Create()
{
	// インスタンス生成
	CTitleLogo* logo = new CTitleLogo;

	// NULLチェック
	if (logo == nullptr) { return nullptr; }

	// 初期化処理
	if (FAILED(logo->Init())) { return nullptr; }

	return logo;
}
