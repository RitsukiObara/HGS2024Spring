//===================================
//
// ���_�̉ԃw�b�_�[[base_effect.h]
// Author ��������
//
//===================================
#ifndef _BASE_EFFECT_H_
#define _BASE_EFFECT_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// �N���X��`(CBaseFlower)
//-----------------------------------
class CBaseFlower : public CBillboard
{
public:

	CBaseFlower();			// �R���X�g���N�^
	~CBaseFlower();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CBaseFlower* Create(const D3DXVECTOR3& pos);		// ��������

private:

};

#endif