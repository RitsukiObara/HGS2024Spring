//===================================
//
// �C�w�b�_�[[ocean.h]
// Author ��������
//
//===================================
#ifndef _OCEAN_H_
#define _OCEAN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object3D.h"

//-----------------------------------
// �N���X��`(COcean)
//-----------------------------------
class COcean : public CObject3D
{
public:

	COcean();				// �R���X�g���N�^
	~COcean();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static COcean* Create(void);	// ��������

private:
};

#endif