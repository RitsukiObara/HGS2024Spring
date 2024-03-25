//==========================================
//
//  �^�C�g�����S�N���X(title_logo.h)
//  Author : Kenta Hashimoto
//
//==========================================
#ifndef _CAVEAT_DIRECTION_H_
#define _CAVEAT_DIRECTION_H_
#include "object2D.h"

//==========================================
//  �N���X��`
//==========================================
class CCaveatDirection : CObject2D
{
public:

	// �����o�֐�
	CCaveatDirection(CObject::TYPE type = TYPE_LOGOMARK, PRIORITY priority = PRIORITY_ENTITY);
	~CCaveatDirection();

	HRESULT Init() override; // ����������
	void Uninit() override; // �I������
	void Update() override; // �X�V����
	void Draw() override; // �`�揈��

	// �ÓI�����o�֐�
	static CCaveatDirection* Create(); // ��������

	void move(void);

private:

};

#endif
#pragma once
