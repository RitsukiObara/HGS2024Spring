//==========================================
//
//  �t�x�Q�[�W(gauge.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "gauge.h"
#include "manager.h"
#include "debugproc.h"
#include "game.h"
#include "base.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 INIT_POLYGON_SIZE = D3DXVECTOR3(0.0f, 20.0f, 0.0f); // �����T�C�Y
	const D3DXVECTOR3 INIT_POLYGON_POS = D3DXVECTOR3(50.0f, INIT_POLYGON_SIZE.y * 1.5f, 0.0f); // �����ʒu

	const D3DXVECTOR3 MAX_SIZE = D3DXVECTOR3((SCREEN_WIDTH - 100.0f) * 0.5f, 20.0f, 0.0f); // �ő�T�C�Y
}

//==========================================
//  �R���X�g���N�^
//==========================================
CGauge::CGauge(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CGauge::~CGauge()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CGauge::Init()
{
	// �e�N���X�̏�����
	if (FAILED(CObject2D::Init())) { return E_FAIL; }

	// ���W�̐ݒ�
	SetPos(INIT_POLYGON_POS);

	// �T�C�Y�̐ݒ�
	SetSize(INIT_POLYGON_SIZE);

	// �p�x�̐ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �Ίp���̒������Z�o
	SetLength();

	// �Ίp���̊p�x���Z�o
	SetAngle();

	// ���_�J���[��ݒ�
	SetVtxColor(D3DXCOLOR(1.0f, 0.56f, 0.87f, 1.0f));

	// ���_���̏�����
	SetVertex();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CGauge::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CGauge::Update()
{
	// �T�C�Y�̌v�Z
	CalcSize();

	// �ʒu�̌v�Z
	CalcPos();

	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CGauge::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CGauge* CGauge::Create()
{
	// �C���X�^���X����
	CGauge* gauge = new CGauge;

	// NULL�`�F�b�N
	if (gauge == nullptr) { return nullptr; }

	// ����������
	if (FAILED(gauge->Init())) { return nullptr; }

	return gauge;
}

//==========================================
//  ���W�̌v�Z����
//==========================================
void CGauge::CalcPos()
{
	// �傫�����擾����
	D3DXVECTOR3 size = GetSize();

	// ���W
	D3DXVECTOR3 pos = INIT_POLYGON_POS;

	// �����ʒu + ����
	pos.x = INIT_POLYGON_POS.x + size.x;

	// �ʒu��K�p
	SetPos(pos);
}

//==========================================
//  �T�C�Y�̌v�Z����
//==========================================
void CGauge::CalcSize()
{
	// �t�x���擾
	float spring = (float)CGame::GetBase()->GetPercent();

	// �ő�l��␳
	if (spring >= 100.0f)
	{
		spring = 100.0f;
	}

	// �t�x�������̐��l�ɕϊ�
	spring *= 0.01f;

	// �ő�T�C�Y�ɑ΂���t�x�̊����ŃT�C�Y�̎Z�o
	D3DXVECTOR3 size = GetSize();
	size.x = MAX_SIZE.x * spring;

	// �T�C�Y��K�p
	SetSize(size);

	// �Ίp���̒������Z�o
	SetLength();

	// �Ίp���̊p�x���Z�o
	SetAngle();
}
