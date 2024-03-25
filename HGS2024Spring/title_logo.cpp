//==========================================
//
//  �^�C�g�����S�N���X(title_logo.cpp)
//  Author : Tomoya Kanazaki
//
//==========================================
#include "title_logo.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const D3DXVECTOR3 POLYGON_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f); // �|���S�����W
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(670.0f, 360.0f, 0.0f); // �|���S�����W
	const char* TEX_PASS = "data/TEXTURE/title.png"; // �e�N�X�`���p�X
}

//==========================================
//  �R���X�g���N�^
//==========================================
CTitleLogo::CTitleLogo(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CTitleLogo::~CTitleLogo()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CTitleLogo::Init(void)
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
	BindTexture(CManager::Get()->GetTexture()->Regist(TEX_PASS));

	// ���_���̏�����
	SetVertex();

	return S_OK;
}

//==========================================
//  �I������
//==========================================
void CTitleLogo::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CTitleLogo::Update()
{
	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CTitleLogo::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CTitleLogo* CTitleLogo::Create()
{
	// �C���X�^���X����
	CTitleLogo* logo = new CTitleLogo;

	// NULL�`�F�b�N
	if (logo == nullptr) { return nullptr; }

	// ����������
	if (FAILED(logo->Init())) { return nullptr; }

	return logo;
}
