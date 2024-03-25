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

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 100.0f, 0.0f); // �|���S�����W
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(300.0f, 75.0f, 0.0f); // �|���S���T�C�Y

	const float LIMIT_TIME = 120.0f; // �Q�[������
}

//==========================================
//  �R���X�g���N�^
//==========================================
CTimer::CTimer(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority),
	m_oldTime(0),
	m_time(0.0f)
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

	// ���_�J���[��ݒ�
	//SetVtxColor(D3DXCOLOR(1.0f, 0.56f, 0.87f, 1.0f));

	// ���_���̏�����
	SetVertex();
	
	// ���ݎ��Ԃ̎擾
	m_oldTime = timeGetTime();

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

	CManager::Get()->GetDebugProc()->Print("�o�ߎ��� : %f", m_time);
}
