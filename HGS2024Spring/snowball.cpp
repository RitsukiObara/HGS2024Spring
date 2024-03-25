//=======================================
//
// 雪玉のメイン処理[snowball.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "snowball.h"
#include "collision.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// 無名名前空間
//=======================================
namespace
{
	const D3DXVECTOR3 SNOWBALL_SIZE = D3DXVECTOR3(40.0f, 40.0f, 0.0f);		// サイズ
	const char* TEXTURE = "data\\TEXTURE\\snow.jpg";		// テクスチャ
	const float SPEED = 30.0f;			// 速度
	const int LIFE = 30;				// 寿命
}

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------
CListManager<CSnowBall*> CSnowBall::m_list = {};			// リスト情報

//=========================
// コンストラクタ
//=========================
CSnowBall::CSnowBall() : CBillboard(CObject::TYPE_SNOWBALL, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_nLife = LIFE;					// 寿命

	// リストに追加する
	m_list.Regist(this);
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

	// 引き抜き処理
	m_list.Pull(this);
}

//=========================
// 更新処理
//=========================
void CSnowBall::Update(void)
{
	// 寿命を下げる
	m_nLife--;

	// 移動処理
	Move();

	if (m_nLife <= 0 ||
		collision::TreeHit(GetPos(), GetSize()) == true)
	{ // 寿命が 0 以下になるか、木に当たった場合

		// 終了処理
		Uninit();

		// この先の処理を行わない
		return;
	}

	// 頂点座標の設定処理
	SetVertex();

	// 敵との当たり判定
	collision::EnemyToSnowBallHit(GetPos(), GetSize());
}

//=========================
// 描画処理
//=========================
void CSnowBall::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//αブレンディングを加算処理に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画処理
	CBillboard::DrawLightOff();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
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

	// 移動量を設定する
	m_move.x = sinf(rot.y) * SPEED;
	m_move.y = 0.0f;
	m_move.z = cosf(rot.y) * SPEED;
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

//=======================================
// リストの取得処理
//=======================================
CListManager<CSnowBall*> CSnowBall::GetList(void)
{
	// リスト構造の情報を返す
	return m_list;
}

//=========================
// 移動処理
//=========================
void CSnowBall::Move(void)
{
	// 位置を取得
	D3DXVECTOR3 pos = GetPos();

	// 移動
	pos += m_move;

	// 位置を適用
	SetPos(pos);
}