//=======================================
//
// 雪玉のメイン処理[snowball.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "snowball.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// 無名名前空間
//=======================================
namespace
{
	const D3DXVECTOR3 SNOWBALL_SIZE = D3DXVECTOR3(30.0f, 30.0f, 0.0f);		// サイズ
	const char* TEXTURE = "data\\TEXTURE\\";		// テクスチャ
}

//=======================================
// マクロ定義
//=======================================


//=========================
// コンストラクタ
//=========================
CSnowBall::CSnowBall() : CBillboard(CObject::TYPE_EFFECT, CObject::PRIORITY_EFFECT)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;		// 移動量
}

//=========================
// デストラクタ
//=========================
CSnowBall::~CSnowBall()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CSnowBall::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CSnowBall::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//=========================
// 更新処理
//=========================
void CSnowBall::Update(void)
{
	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 描画処理
//=========================
void CSnowBall::Draw(void)
{
	// 描画処理
	CBillboard::DrawLightOff();
}

//=========================
// 情報の設定処理
//=========================
void CSnowBall::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// 情報の設定処理
	SetPos(pos);				// 位置
	SetPosOld(pos);				// 前回の位置
	SetSize(SNOWBALL_SIZE);		// サイズ
	SetEnableLookY(true);		// Y軸状況

	// 頂点情報の初期化
	SetVertex();

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));
}

//=========================
// 生成処理
//=========================
CSnowBall* CSnowBall::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CSnowBall* pSnowball = nullptr;		// 雪玉のインスタンスを生成

	if (pSnowball == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pSnowball = new CSnowBall;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pSnowball != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pSnowball->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pSnowball->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 雪玉のポインタを返す
	return pSnowball;
}