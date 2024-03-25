//==========================================
//
//  �t�x�Q�[�W(gauge.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CGauge : public CObject2D
{
public:

	// �����o�֐�
	CGauge(CObject::TYPE type = TYPE_GAUGE, PRIORITY priority = PRIORITY_ENTITY);
	~CGauge();

	HRESULT Init() override; // ����������
	void Uninit() override; // �I������
	void Update() override; // �X�V����
	void Draw() override; // �`�揈��

	// �ÓI�����o�֐�
	static CGauge* Create();

private:

	// �����o�֐�
	void CalcPos(); // �ʒu�̌v�Z
	void CalcSize(); // �T�C�Y�̌v�Z

};

#endif
