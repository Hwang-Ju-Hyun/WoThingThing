#pragma once
#include "header.h"

class BaseComponent;

class GameObject
{
	bool active{ true };

public:
	GameObject() = delete;
	GameObject(std::string _name);
	~GameObject();

	//boss용 이렇게 하면 안되는데 막날이어서 그냥 하는중	<- 나중에 시간나면 정리하겠누 ㅋ(황주현)
public:
	int m_id;
	float AttackDelay;
	int m_hp = 20;//	
	bool IsSturn = false;
	float SturnAccTime = 0.f;
	float TakeDamageCoolTime = 0.f;
	bool BossTakeDamage = true;
	AEVec2 KnockBackChase = { 0.f,0.f };
	AEVec2 unitKnockBackChase = { 0.f,0.f };
	float KnockBackAccTime = 0.f;
public:
	void SetBossTakeDamage(bool _damage) { BossTakeDamage = _damage; }
	bool GetBossTakeDamage() { return BossTakeDamage; }
	void SetSturn(bool _sturn) { IsSturn = _sturn; }
	bool GetSturn() { return IsSturn; }
public:
	enum weapon
	{
		rifle,
		shotgun
	};
	int randWeapon[2];
	
public:		
	void SetID(int id) { m_id = id; }
	int GetID() { return m_id; }
private:
	std::string m_sName;	
public:
	void AddHP(int _hp);
	void SetHP(int hp);
	int GetHP();
public:
	void SetName(const std::string& _name) { m_sName = _name; }
	const std::string& GetName()const { return m_sName; }
private:
	std::map<std::string, BaseComponent*> m_mapComp;
public:
	BaseComponent* AddComponent(const std::string& _name, BaseComponent* _comp);
	BaseComponent* FindComponent(const std::string& _name);	
	void DeleteComponent(const std::string& _name);

	void SetActive(bool sw);
	bool GetActive();

public:
	std::map<std::string, BaseComponent*> GetAllComp()
	{
		return m_mapComp;
	}

//Node Info
private:
	int m_nodeCost;
	int m_nodeID;
public:
	void SetNodeCost(int _cost) { m_nodeCost = _cost; }
	int GetNodeCost()const		{ return m_nodeCost; }
public:
	friend class BaseComponent;
};

