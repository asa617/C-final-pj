/*
* \file Monster.h 
* \date 2016_06_10
* 
* \author Xuan_32
*
* \brief ����ʵ����
*/

#ifndef Monster_H
#define Monster_H
#include "cocos2d.h"
USING_NS_CC;
class Hero;
class MyMap;

/*
*	This is an object of Monster
*
*/
class Monster :public Node{
public:
	Monster(void);
	~Monster(void);

	//��������

	//�ж��Ƿ����ܶ���
	bool IsRunning;
	//�ж��Ƿ��ڹ�������
	bool IsAttack;
	//�ж��Ƿ������˶���
	bool IsHurt;
	//�ж��Ƿ�����
	bool IsDead;
	//������˶����� falseΪ�� trueΪ��
	bool MonsterDirection;

	//����
	//����ͼƬ�����������ʱ����Ѫ��
	void InitMonsterSprite(char* name, char* attack, char* die, char*walk, char*dieLast, int m_iLevel);
	//���ض���
	Sprite* GetSprite();
	//�����߶�������numΪͼƬ��Ŀ��run_directionΪ����������false����,name_eachΪname_png��ÿһС��ͼƬ�Ĺ������Ʋ���
	void SetAnimation(const char *name_each, bool run_directon, float delay, int iLoops);
	//ֹͣ�߶�����
	void StopAnimation();

	//��������
	void AttackAnimation(const char *name_each, bool run_directon, float delay, int iLoops);
	//������������
	void AttackEnd();

	//���˶���
	void HurtAnimation(const char *name_each, bool run_directon, float delay, int iLoops);
	//���˶�������
	void HurtEnd();

	//��������
	void DeadAnimation(const char *name_each, bool run_directon, float delay, int iLoops);
	//������������
	void DeadEnd();

	//����������˸����
	void BlinkEnd();

	//�ڿ��ӷ�Χ�ڣ��������Ӣ���˶�
	void FollowRun(Hero* m_hero);
	//�ж��Ƿ񹥻�
	void JudegeAttack(float dt);


	//������������Ӣ��
	void StartListen(Hero* m_hero);
	//��������,ÿ��3�����£�����Ӣ�������ľ���
	void updateMonster(float delta);
	//���º��������Ӣ���ڿ��ӷ�Χ�ڣ����ϴ���
	void update(float delta);

	CREATE_FUNC(Monster);

private:
	Sprite* m_MonsterSprite; // ���ﾫ��
	char *Monster_name;      // ���������ʼ״̬�ľ���ͼƬ����
	char *Monster_attack;    // ���﹥��֡
	char *Monster_die;       // ����֡
	char *Monster_walk;      // ����֡
	char *Die_name;

	Hero* my_hero;           // ��ǰӢ��
	float dis_x;			// ��ǰ�����Ӣ�۵ĺ������
	float dis_y;			//��ǰ�����Ӣ�۵��������
	int   m_iHP;

};
#endif // !1

