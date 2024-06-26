//=============================================================================
//
// サウンド処理 [sound.h]
// Author 小原立暉
//
//=============================================================================
#ifndef _SOUND_H_					//このマクロ定義がされていなかったら
#define _SOUND_H_					//2重インクルード防止のマクロを定義する

#include "main.h"

// クラス定義(CSound)
class CSound
{
public:			// 誰でもアクセス出来る

	//-------------------------------------------------------------------------
	// サウンド一覧
	//-------------------------------------------------------------------------
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,		// タイトルBGM
		SOUND_LABEL_BGM_GAME,			// ゲームBGM
		SOUND_LABEL_BGM_CLEAR,			// リザルトクリアBGM
		SOUND_LABEL_BGM_GAMEOVER,		// リザルトゲームオーバーBGM
		SOUND_LABEL_BGM_RANKING,		// ランキングBGM
		SOUND_LABEL_SE_RUN,				// 走行音
		SOUND_LABEL_SE_RUNSTART,		// 走り始め音
		SOUND_LABEL_SE_JUMP,			// ジャンプ音
		SOUND_LABEL_SE_SELECT,			// 選択音
		SOUND_LABEL_SE_DECIDE,			// 決定音
		SOUND_LABEL_SE_NEWRECORD,		// 新記録の音
		SOUND_LABEL_SE_HOVER,			// ホバージェット
		SOUND_LABEL_SE_LANDING,			// 着地音
		SOUND_LABEL_SE_JETDASH,			// ジェットダッシュ
		SOUND_LABEL_SE_STEPPING,		// 踏みつけ音
		SOUND_LABEL_SE_ENEMYBREAK,		// 敵の破壊音
		SOUND_LABEL_SE_SMASH,			// 吹き飛ばし音
		SOUND_LABEL_SE_SMASHFLY,		// 吹き飛び中の音
		SOUND_LABEL_SE_GETITEM,			// アイテム取得音
		SOUND_LABEL_SE_CANNON,			// 大砲の音
		SOUND_LABEL_SE_GROUNDQUAKE,		// グラウンドクエイク音
		SOUND_LABEL_SE_STUN,			// 気絶音
		SOUND_LABEL_SE_DAMAGE,			// ダメージ音
		SOUND_LABEL_SE_SHOT,			// 発射音
		SOUND_LABEL_MAX					// この列挙型の総数
	};

	//-----------------------------------------------------------------------------
	// サウンド情報の構造体定義
	//-----------------------------------------------------------------------------
	struct SOUNDINFO
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	};

	CSound();			// コンストラクタ
	~CSound();			// デストラクタ

	// メンバ関数
	HRESULT Init(HWND hWnd);											// 初期化処理
	void Uninit(void);													// 終了処理
	HRESULT Play(const SOUND_LABEL label);								// 再生処理
	void Stop(const SOUND_LABEL label);									// 停止(ラベル指定)
	void Stop(void);													// 停止(全停止)

	// セット・ゲット関係
	void SetVolume(const SOUND_LABEL label, const float fVolume);		// ボリュームの設定処理
	float GetVolume(const SOUND_LABEL label) const;						// ボリュームの取得処理
	void SetFrequency(const SOUND_LABEL label, const float fFrequency);	// 周波数の設定処理
	float GetFrequency(const SOUND_LABEL label) const;					// 周波数の取得処理

	// 静的メンバ関数
	static CSound* Create(HWND hWnd);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// メンバ変数
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static SOUNDINFO m_aSoundInfo[CSound::SOUND_LABEL_MAX];	// サウンドの情報
};

#endif
