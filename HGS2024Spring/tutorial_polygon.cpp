//==========================================
//
//  �`���[�g���A���摜(tutorial_polygon.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "tutorial_polygon.h"
#include "manager.h"
#include "input.h"
#include "texture.h"

//==========================================
//  �萔��`
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
	}; // �e�N�X�`���p�X
}

//==========================================
//  �R���X�g���N�^
//==========================================
CTutorialPolygon::CTutorialPolygon(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority),
	m_bEnd(false),
	m_nIdx(0)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTutorialPolygon::~CTutorialPolygon()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTutorialPolygon::Init()
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

	// �e�N�X�`�����蓖��
	BindTexture(CManager::Get()->GetTexture()->Regist(TEX_PASS[m_nIdx]));

	// ���_���̏�����
	SetVertex();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTutorialPolygon::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTutorialPolygon::Update()
{
	// �e�N�X�`���X�V
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0))
	{
		if (!m_bEnd)
		{
			// �C���f�b�N�X���X�V
			++m_nIdx;

			// �e�N�X�`�����蓖��
			BindTexture(CManager::Get()->GetTexture()->Regist(TEX_PASS[m_nIdx]));

			// �`���[�g���A�������t���O
			if (m_nIdx == 2) { m_bEnd = true; }
		}
	}

	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTutorialPolygon::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CTutorialPolygon* CTutorialPolygon::Create()
{
	// �C���X�^���X����
	CTutorialPolygon* p = new CTutorialPolygon;

	// NULL�`�F�b�N
	if (p == nullptr) { return nullptr; }

	// ����������
	if (FAILED(p->Init())) { return nullptr; }

	return p;
}
