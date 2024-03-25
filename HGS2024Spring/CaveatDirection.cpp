//==========================================
//
//  �^�C�g�����S�N���X(title_logo.cpp)
//  Author : Kenta Hashimoto
//
//==========================================
#include "CaveatDirection.h"
#include "manager.h"
#include "texture.h"

//==========================================
//  �萔��`
//==========================================
namespace
{
	const float POLYGON_STOP_POS = SCREEN_WIDTH * 0.5f; // �|���S�����W
	const D3DXVECTOR3 POLYGON_POS = D3DXVECTOR3(SCREEN_WIDTH * -0.5f, SCREEN_HEIGHT * 0.2f, 0.0f); // �|���S�����W
	const D3DXVECTOR3 POLYGON_SIZE = D3DXVECTOR3(260.0f, 90.0f, 0.0f); // �|���S�����W
	const char* TEX_PASS = "data/TEXTURE/Direction.png"; // �e�N�X�`���p�X
}

//==========================================
//  �R���X�g���N�^
//==========================================
CCaveatDirection::CCaveatDirection(CObject::TYPE type, PRIORITY priority) :
	CObject2D(type, priority)
{

}

//==========================================
//  �f�X�g���N�^
//==========================================
CCaveatDirection::~CCaveatDirection()
{

}

//==========================================
//  ����������
//==========================================
HRESULT CCaveatDirection::Init(void)
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
void CCaveatDirection::Uninit()
{
	CObject2D::Uninit();
}

//==========================================
//  �X�V����
//==========================================
void CCaveatDirection::Update()
{

	CObject2D::Update();
}

//==========================================
//  �`�揈��
//==========================================
void CCaveatDirection::Draw()
{
	CObject2D::Draw();
}

//==========================================
//  ��������
//==========================================
CCaveatDirection* CCaveatDirection::Create()
{
	// �C���X�^���X����
	CCaveatDirection* Polygon = new CCaveatDirection;

	// NULL�`�F�b�N
	if (Polygon == nullptr) { return nullptr; }

	// ����������
	if (FAILED(Polygon->Init())) { return nullptr; }

	return Polygon;
}