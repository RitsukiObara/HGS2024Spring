//===================================
//
// ���_�w�b�_�[[base.h]
// Author ��������
//
//===================================
#ifndef _BASE_H_
#define _BASE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(CBase)
//-----------------------------------
class CBase : public CModel
{
public:					// �N�ł��A�N�Z�X�ł���

	CBase();				// �R���X�g���N�^
	~CBase();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	void Flowering(const int nPercent);			// �J�ԏ���

	// �Z�b�g�E�Q�b�g�֌W
	void SetPercent(const int nPercent);		// �炫�x���̐ݒ菈��
	int GetPercent(void) const;					// �炫�x���̎擾����

	// �ÓI�����o�֐�
	static CBase* Create(void);		// ��������

private:				// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXVECTOR3* m_pPosVtx;	// ���_�̃|�C���^
	int m_nPercent;			// �炫�x��
	int m_nNumVtx;			// ���_��
	bool* m_bFlowering;		// ���ݍ炢�Ă���ӏ�
};

#endif