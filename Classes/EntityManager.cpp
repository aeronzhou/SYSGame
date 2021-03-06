#include "EntityManager.h"
#include "Hero.h"
#include "Monster.h"
#include "Queue.h"
#include "FirstStage.h"
#include "FireBall.h"
#include "GameInfo.h"

EntityManager& EntityManager::instance()
{
	static EntityManager inst;
	return inst;
}

EntityManager::EntityManager()
{
	m_pAllMonsters = CCArray::create();
	m_pAllEffects = CCArray::create();
	m_pAllHeros = CCArray::create();	
	m_pAllGoods = CCArray::create();
	m_pAllMonsters->retain();
	m_pAllEffects->retain();
	m_pAllHeros->retain();	
	m_pAllGoods->retain();
}

EntityManager::~EntityManager()
{
	m_pAllMonsters->release();
	m_pAllEffects->release();
	m_pAllHeros->release();	
	m_pAllGoods->release();
}

Hero* EntityManager::addAHero(CCPoint pos)
{
	if (GI.Game)
	{
		Hero* pHero = Hero::create(GI.PathOfHero.c_str());
		GI.Game->addChild(pHero);
		pHero->setPosition(pos);
		m_pAllHeros->addObject(pHero);
		return pHero;
	}

	return NULL;
}

Monster* EntityManager::addAMonster(CCPoint pos)
{
	if (GI.Game)
	{
		Monster* pMonster = Monster::create(GI.PathOfMonster.c_str());
		GI.Game->addChild(pMonster);
		pMonster->setPosition(pos);
		m_pAllMonsters->addObject(pMonster);
		return pMonster;
	}

	return NULL;
}

BaseEntity* EntityManager::findEntityInRange(BaseEntity* pMe, float range, EEntityType type)
{
	BaseEntity* ret = NULL;
	float min_dist = range * range;
	CCObject* tObject;	

	CCARRAY_FOREACH(getArrayByType(type), tObject)
	{
		BaseEntity* tEntity = (BaseEntity*)(tObject);
		if (tEntity != pMe && tEntity->getType() == type)
		{
			float dist_sqrt = pMe->getPosition().getDistanceSq(tEntity->getPosition());
			if (dist_sqrt < range * range + 1e-6)
			{
				ret = tEntity;
			}
		}
	}

	return ret;
}

Hero* EntityManager::findHeroNotInQueue(BaseEntity* pMe, float range)
{
	Hero* ret = NULL;
	CCObject* tObject;	

	CCARRAY_FOREACH(m_pAllHeros, tObject)
	{
		Hero* tEntity = (Hero*)(tObject);
		if (tEntity != pMe && tEntity->getType() == ET_Hero)
		{
			// 没有加进队伍中
			if (!tEntity->getQueue())
			{
				float dist_sqrt = pMe->getPosition().getDistanceSq(tEntity->getPosition());
				if (dist_sqrt < range * range + 1e-6)
				{
					ret = tEntity;
				}
			}
		}
	}

	return ret;
}

CCArray* EntityManager::findAllEntitiesInRange(BaseEntity* pMe, float range, EEntityType type)
{
	CCArray* ret = CCArray::create();
	CCObject* tObject;

	CCArray* all_entities = getArrayByType(type);

	CCARRAY_FOREACH(all_entities, tObject)
	{
		BaseEntity* tEntity = (BaseEntity*)(tObject);
		if (tEntity != pMe && tEntity->getType() == type)
		{
			float dist_sqrt = pMe->getPosition().getDistanceSq(tEntity->getPosition());
			if (dist_sqrt < range * range + 1e-6)
			{
				ret->addObject(tEntity);
			}
		}
	}
	return ret;
}

void EntityManager::removeAnEntity(BaseEntity* entity, EEntityType type)
{
	if (!entity)
	{
		return;
	}

	CCArray* objects = getArrayByType(type);
	if (objects)
	{
		objects->removeObject(entity);
	}	

	if (entity->getParent() != NULL)
	{
		entity->removeFromParentAndCleanup(true);
	}
}

CCArray* EntityManager::getArrayByType(EEntityType type) const
{
	CCArray* ret = NULL;

	switch (type)
	{
	case ET_Hero:
		ret = m_pAllHeros;
		break;

	case ET_Monster:
		ret = m_pAllMonsters;
		break;

	case ET_Goods:
		ret = m_pAllGoods;
		break;

	case ET_Effect:
		ret = m_pAllEffects;
		break;

	default:
		break;
	}

	return ret;
}

Effect* EntityManager::addAnEffect(CCPoint pos, EEffectType type, CCPoint target_pos)
{
	Effect* eft = NULL;

	switch (type)
	{
	case EET_FireBall:
		eft = FireBall::create("FireBall_1.png");
		eft->setTarget(target_pos);
		break;

	default:
		break;
	}

	if (GI.Game)
	{
		GI.Game->addChild(eft);
		eft->setPosition(pos);
		m_pAllEffects->addObject(eft);
	}

	return eft;
}