//===========================================
//
// �����蔻��̃��C������[collision.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "game.h"
#include "collision.h"
#include "shadowCircle.h"
#include "objectElevation.h"
#include "useful.h"

#include "mob_tree.h"
#include "player.h"
#include "enemy.h"
#include "base.h"
#include "mob_tree_leaf.h"

//===============================
// �}�N����`
//===============================
namespace
{
	const float COLLISION_ADD_DIFF_LENGTH = 0.01f;	// �͂��Ȍ덷�𖄂߂邽�߂̃}�N����`(�˂�������h�~)

	const D3DXVECTOR3 PLAYER_MAX = D3DXVECTOR3(60.0f, 130.0f, 60.0f);
	const D3DXVECTOR3 PLAYER_MIN = D3DXVECTOR3(-60.0f, 0.0f, -60.0f);

	const D3DXVECTOR3 TREE_MAX = D3DXVECTOR3(40.0f, 300.0f, 40.0f);
	const D3DXVECTOR3 TREE_MIN = D3DXVECTOR3(-40.0f, 0.0f, -40.0f);
}

//===============================
// �N���n�ʂ͈̔͊O�̓����蔻��
//===============================
bool collision::ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth)
{
	// ���[�J���ϐ��錾
	bool bCollision = false;									// �����蔻���
	CListManager<CElevation*> list = CElevation::GetList();
	CElevation* pElev = nullptr;			// �擪�̏���
	CElevation* pElevEnd = nullptr;		// �����̒l
	int nIdx = 0;

	if (list.IsEmpty() == false)
	{ // �󔒂���Ȃ��ꍇ

		// �擪�̒l���擾����
		pElev = list.GetTop();

		// �����̒l���擾����
		pElevEnd = list.GetEnd();

		while (true)
		{ // �������[�v

			if (pElev->GetPos().z + (pElev->GetSize().z * 0.5f) >= pPos->z &&
				pElev->GetPos().z - (pElev->GetSize().z * 0.5f) <= pPos->z &&
				pElev->GetPos().y > pPos->y)
			{ // �N���n�ʂ�艺�ɂ���ꍇ

				if (posOld.x + fWidth <= pElev->GetPos().x - (pElev->GetSize().x * 0.5f) &&
					pPos->x + fWidth >= pElev->GetPos().x - (pElev->GetSize().x * 0.5f))
				{ // ���̓����蔻��

					// �ʒu��ݒ肷��
					pPos->x = pElev->GetPos().x - (pElev->GetSize().x * 0.5f) - fWidth;

					// �����蔻��󋵂� true �ɂ���
					bCollision = true;
				}
				else if (posOld.x - fWidth >= pElev->GetPos().x + (pElev->GetSize().x * 0.5f) &&
					pPos->x - fWidth <= pElev->GetPos().x + (pElev->GetSize().x * 0.5f))
				{ // �E�̓����蔻��

					// �ʒu��ݒ肷��
					pPos->x = pElev->GetPos().x + (pElev->GetSize().x * 0.5f) + fWidth;

					// �����蔻��󋵂� true �ɂ���
					bCollision = true;
				}
			}

			if (pElev == pElevEnd)
			{ // �����ɒB�����ꍇ

				// while���𔲂��o��
				break;
			}

			// ���̃I�u�W�F�N�g��������
			pElev = list.GetData(nIdx + 1);

			// �C���f�b�N�X�����Z����
			nIdx++;
		}
	}

	// �����蔻��󋵂�Ԃ�
	return bCollision;
}

//===============================
// �؂̃q�b�g����
//===============================
bool collision::TreeHit(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ���[�J���ϐ��錾
	CListManager<CMobTree*> list = CMobTree::GetList();
	CMobTree* pTree = nullptr;				// �؂̃|�C���^
	int nNum = list.GetNumData();			// ����

	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		// �؂̃|�C���^����
		pTree = list.GetData(nCnt);

		if (pTree->GetLeaf()->GetScale().x >= 1.0f &&
			useful::RectangleCollisionXZ(pos, pTree->GetPos(), size, pTree->GetFileData().vtxMax, -size, pTree->GetFileData().vtxMin) == true)
		{ // �؂ɓ��������ꍇ

			// ��ʂƂ̏Փˎ�����
			pTree->SnowBallHit();

			// �J�ԏ���
			CGame::GetBase()->Flowering(pTree->GetPercent());

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//===============================
// �G�Ɛ�ʂ̓����蔻��
//===============================
bool collision::EnemyToSnowBallHit(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ���[�J���ϐ��錾
	CListManager<CEnemy*> list = CEnemy::GetList();
	CEnemy* pEnemy = nullptr;				// �G�̃|�C���^
	int nNum = list.GetNumData();			// ����

	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		// �G�̃|�C���^����
		pEnemy = list.GetData(nCnt);

		if (pEnemy->IsDamage() == false &&
			useful::RectangleCollisionXZ(pos, pEnemy->GetPos(), size, pEnemy->GetFileData().vtxMax, -size, pEnemy->GetFileData().vtxMin) == true)
		{ // �G�ɓ��������ꍇ

			// �q�b�g����
			pEnemy->Hit();

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

/*
* @brief �Z�ʑ̂̓����蔻��
* @param pos [out] �Ώۂ̈ʒu
* @param posBlock [in] �u���b�N�̈ʒu
* @param posOld [in] �Ώۂ̑O��̈ʒu
* @param posOldBlock [in] �u���b�N�̑O��̈ʒu
* @param min [in] �ŏ��l
* @param minBlock [in] �u���b�N�̍ŏ��l
* @param max [in] �ő�l
* @param maxBlock [in] �u���b�N�̍ő�l
* @return bool �Ԃ��������ǂ���
*/
bool collision::HexahedronCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // �E�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // ��ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

/*
* @brief �Z�ʑ̂̓����蔻��(�ǂ̖ʂɏ�������̔���t��)
* @param pos [out] �Ώۂ̈ʒu
* @param posBlock [in] �u���b�N�̈ʒu
* @param posOld [in] �Ώۂ̑O��̈ʒu
* @param posOldBlock [in] �u���b�N�̑O��̈ʒu
* @param min [in] �ŏ��l
* @param minBlock [in] �u���b�N�̍ŏ��l
* @param max [in] �ő�l
* @param maxBlock [in] �u���b�N�̍ő�l
* @return SCollision �Z�ʑ̂̓����蔻��
*/
collision::SCollision collision::HexahedronClush(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	// �����蔻��̕ϐ���錾
	SCollision collision = { false,false,false,false,false,false };

	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // �E�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// �E�̓����蔻��� true �ɂ���
			collision.bRight = true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bLeft = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bFar = true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// ��O�̓����蔻��� true �ɂ���
			collision.bNear = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // ��ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// ��̓����蔻��� true �ɂ���
			collision.bTop = true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bBottom = true;
		}
	}

	// �����蔻��̕ϐ���Ԃ�
	return collision;
}