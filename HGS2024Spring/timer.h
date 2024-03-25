//==========================================
//
//  �^�C�}�[(timer.h)
//  Author : Tomoya Kanazaki
//
//==========================================
#ifndef _TIMER_H_
#define _TIMER_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CTimer : public CObject2D
{
public:

	// �����o�֐�
	CTimer(CObject::TYPE type = TYPE_TIME, PRIORITY priority = PRIORITY_ENTITY);
	~CTimer();

	HRESULT Init() override; // ����������
	void Uninit() override; // �I������
	void Update() override; // �X�V����
	void Draw() override; // �`�揈��

	// �ÓI�����o�֐�
	static CTimer* Create();

private:

	// �����o�֐�
	void CalcTime(); // �o�ߎ��Ԃ̌v�Z
	void Floating(); // �傫���̕���

	// �����o�ϐ�
	DWORD m_oldTime; // �O�񎞊�
	float m_time; // �o�ߎ���
	bool m_bPichUp; // �s�b�`���オ�����t���O

};

#endif
