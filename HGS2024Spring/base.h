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

	// �ÓI�����o�֐�
	static CBase* Create(void);		// ��������

private:				// ���������A�N�Z�X�ł���

};

#endif