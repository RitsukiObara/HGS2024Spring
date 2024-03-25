//===================================
//
// �n�ʃw�b�_�[[map.h]
// Author ��������
//
//===================================
#ifndef _MAP_H_
#define _MAP_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object3D.h"

//-----------------------------------
// �N���X��`(CMap)
//-----------------------------------
class CMap : public CObject3D
{
public:

	CMap();				// �R���X�g���N�^
	~CMap();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CMap* Create(void);		// ��������

private:
};

#endif