//===================================
//
// ���U���g���S�w�b�_�[[result_logo.h]
// Author ��������
//
//===================================
#ifndef _RESULT_LOGO_H_
#define _RESULT_LOGO_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CResultLogo)
//-----------------------------------
class CResultLogo : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CResultLogo();			// �R���X�g���N�^
	~CResultLogo();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CResultLogo* Create(void);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif