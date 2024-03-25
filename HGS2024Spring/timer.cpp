//==========================================
//
//  �^�C�}�[(timer.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "timer.h"
#include "manager.h"
#include "debugproc.h"
#include "game.h"
#include "fade.h"
#include "texture.h"
#include "sound.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT - 50.0f, 0.0f); // �|���S�����W
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(250.0f, 62.5f, 0.0f); // �|���S���T�C�Y
	const float POLYGON_RATE = POLYGON_SIZE.y / POLYGON_SIZE.x; // �|���S���T�C�Y
	const float FLOATING_SIZE = 50.0f; // ��������T�C�Y�̔{��

	const float LIMIT_TIME = 120.0f; // �Q�[������
	const float SWICH_TIME_APRIL = LIMIT_TIME / 3.0f; // �Q�[������
	const float SWICH_TIME_MAY = (LIMIT_TIME / 3.0f) * 2.0f; // �Q�[������

	const char* MARCH_PASS = "data/TEXTURE/March.png"; // �e�N�X�`���p�X
	const char* APRIL_PASS = "data/TEXTURE/April.png"; // �e�N�X�`���p�X
	const char* MAY_PASS = "data/TEXTURE/May.png"; // �e�N�X�`���p�X
}

//==========================================
//  �R���X�g���N�^
//==========================================
CTimer::CTimer(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority),
	m_oldTime(0),
	m_time(0.0f),
	m_bPichUp(false)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTimer::~CTimer()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTimer::Init()
{
	// �e�N���X�̏�����
	if (FAILED(CObject2D::Init())) { return E_FAIL; }

	// ���W�̐ݒ�
	SetPos(POLYGON_POS);

	// �T�C�Y�̐ݒ�
	SetSize(POLYGON_SIZE);

	// �p�x�̐ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �Ίp���̒������Z�o
	SetLength();

	// �Ίp���̊p�x���Z�o
	SetAngle();

	// ���_���̏�����
	SetVertex();
	
	// ���ݎ��Ԃ̎擾
	m_oldTime = timeGetTime();

	// �e�N�X�`�����蓖��
	BindTexture(CManager::Get()->GetTexture()->Regist(MARCH_PASS));

	// �s�b�`��ύX
	CManager::Get()->GetSound()->SetFrequency(CSound::SOUND_LABEL_BGM_GAME, 1.0f);

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTimer::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTimer::Update()
{
	// �o�ߎ��Ԃ̌v�Z
	CalcTime();

	// �傫����ς���
	Floating();

	// ���Ԍo�߂Ō����ς��
	if (m_time >= SWICH_TIME_APRIL)
	{
		// �e�N�X�`�����蓖��
		BindTexture(CManager::Get()->GetTexture()->Regist(APRIL_PASS));
	}
	if (m_time >= SWICH_TIME_MAY)
	{
		// �e�N�X�`�����蓖��
		BindTexture(CManager::Get()->GetTexture()->Regist(MAY_PASS));

		// �s�b�`���グ��
		if (!m_bPichUp)
		{
			// �s�b�`��ύX
			 CManager::Get()->GetSound()->SetFrequency(CSound::SOUND_LABEL_BGM_GAME, 1.1f);

			// �t���O�𗧂Ă�
			m_bPichUp = true;
		}
	}

	// �������Ԃ𒴂�����
	if (m_time >= LIMIT_TIME)
	{
		// �`���[�g���A���ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}

	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTimer::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CTimer* CTimer::Create()
{
	// �C���X�^���X����
	CTimer* time = new CTimer;

	// NULL�`�F�b�N
	if (time == nullptr) { return nullptr; }

	// ����������
	if (FAILED(time->Init())) { return nullptr; }

	return time;
}

//==========================================
//  �o�ߎ��Ԃ̉��Z
//==========================================
void CTimer::CalcTime()
{
	// ���ݎ��Ԃ̎擾
	DWORD time = timeGetTime();

	// �O�񎞊ԂƂ̍����Z�o(�~���b)
	float difference = (float)(time - m_oldTime) * 0.001f;

	// �o�ߎ��Ԃɍ��������Z
	if (!CGame::IsPause())
	{
		m_time += difference;
	}

	// �O�񎞊Ԃ����ݎ��Ԃŏ㏑��
	m_oldTime = time;

}

//==========================================
//  �傫���̕���
//==========================================
void CTimer::Floating()
{
	// �����̗ʂ��Z�o
	float floating = sinf(m_time) * FLOATING_SIZE;

	// �T�C�Y���Z�o
	D3DXVECTOR3 size = POLYGON_SIZE;
	size += D3DXVECTOR3(floating, floating * POLYGON_RATE, 0.0f);

	// �T�C�Y��K�p
	SetSize(size);

	// �Ίp���̒������Z�o
	SetLength();

	// �Ίp���̊p�x���Z�o
	SetAngle();
}
