//==========================================
//
//  春度ゲージ(gauge.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gauge.h"
#include "manager.h"
#include "debugproc.h"
#include "game.h"
#include "base.h"

//==========================================
//  定数定義
//==========================================
namespace
{
	const D3DXVECTOR3 INIT_POLYGON_SIZE = D3DXVECTOR3(0.0f, 20.0f, 0.0f); // 初期サイズ
	const D3DXVECTOR3 INIT_POLYGON_POS = D3DXVECTOR3(50.0f, INIT_POLYGON_SIZE.y * 1.5f, 0.0f); // 初期位置

	const D3DXVECTOR3 MAX_SIZE = D3DXVECTOR3((SCREEN_WIDTH - 100.0f) * 0.5f, 20.0f, 0.0f); // 最大サイズ
}

//==========================================
//  コンストラクタ
//==========================================
CGauge::CGauge(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority)
{

}

//==========================================
//  デストラクタ
//==========================================
CGauge::~CGauge()
{

}

//==========================================
//  初期化処理
//==========================================
HRESULT CGauge::Init()
{
	// 親クラスの初期化
	if (FAILED(CObject2D::Init())) { return E_FAIL; }

	// 座標の設定
	SetPos(INIT_POLYGON_POS);

	// サイズの設定
	SetSize(INIT_POLYGON_SIZE);

	// 角度の設定
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 対角線の長さを算出
	SetLength();

	// 対角線の角度を算出
	SetAngle();

	// 頂点カラーを設定
	SetVtxColor(D3DXCOLOR(1.0f, 0.56f, 0.87f, 1.0f));

	// 頂点情報の初期化
	SetVertex();

	return S_OK;
}

//==========================================
//  終了処理
//==========================================
void CGauge::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  更新処理
//==========================================
void CGauge::Update()
{
	// サイズの計算
	CalcSize();

	// 位置の計算
	CalcPos();

	CObject2D::Update();
}

//==========================================
//  描画処理
//==========================================
void CGauge::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  生成処理
//==========================================
CGauge* CGauge::Create()
{
	// インスタンス生成
	CGauge* gauge = new CGauge;

	// NULLチェック
	if (gauge == nullptr) { return nullptr; }

	// 初期化処理
	if (FAILED(gauge->Init())) { return nullptr; }

	return gauge;
}

//==========================================
//  座標の計算処理
//==========================================
void CGauge::CalcPos()
{
	// 大きさを取得する
	D3DXVECTOR3 size = GetSize();

	// 座標
	D3DXVECTOR3 pos = INIT_POLYGON_POS;

	// 初期位置 + 横幅
	pos.x = INIT_POLYGON_POS.x + size.x;

	// 位置を適用
	SetPos(pos);
}

//==========================================
//  サイズの計算処理
//==========================================
void CGauge::CalcSize()
{
	// 春度を取得
	float spring = (float)CGame::GetBase()->GetPercent();

	// 最大値を補正
	if (spring >= 100.0f)
	{
		spring = 100.0f;
	}

	// 春度を割合の数値に変換
	spring *= 0.01f;

	// 最大サイズに対する春度の割合でサイズの算出
	D3DXVECTOR3 size = GetSize();
	size.x = MAX_SIZE.x * spring;

	// サイズを適用
	SetSize(size);

	// 対角線の長さを算出
	SetLength();

	// 対角線の角度を算出
	SetAngle();
}
