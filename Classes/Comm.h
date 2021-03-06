#ifndef SYS_COMM
#define SYS_COMM

#include <string>
#include <vector>
#include <map>
using namespace std;

// -------------------------------- 常量 --------------------------------


// -------------------------------- 枚举 --------------------------------
// 物品类型枚举
enum EItemType
{
	kMoney = 1, // 金币
	kStageItem = 2, // 场景道具
	kOthers = 3 // 其他
};

// 游戏模式枚举
enum EGameMode
{
	kEndlessMode = 1, // 无尽模式
	kLevelMode = 2 // 过关模式
};

// 特效类型
enum EEffectType
{
	EET_FireBall	=	1,	// 火球
};

// 物品类型
enum EGoodType
{
	EGT_Coin		=	1,	// 金币
	EGT_BloodSupply	=	2,	// 血包
};


// -------------------------------- 公共结构 --------------------------------
// 物品结构
struct TItem
{
	string sItemName; // 物品名称
	string sDescribe; // 物品描述
	EItemType eType; // 物品类型
	int iDuration; // 物品效果持续时间
	int iExistTime; // 场景道具在场景中保留的时间
	int iValue; // 价值
	string sResourcePath; // 物品对应的图片资源路径(有多个文件的话,用;分隔)
};

// 怪物奖励结构
struct TReward
{
	TItem stItem; // 掉落的物品
	int iWeight; // 掉落物品的权重
};

// 技能结构
struct TSkill
{
	string sSkillName; // 技能名称
	int iDamage; // 技能上海
	int iSkillCD; // 技能CD
	string sResourcePath; // 技能对应的图片资源路径(有多个文件的话,用;分隔)
};

// 怪物结构
struct TMonster
{
	string sMonsterName; // 怪物名称
	int iMoveSpeed; // 移动速度
	int iHP; // 生命值
	TSkill stSkill; // 技能
	string sResourcePath; // 怪物对应的图片资源路径(有多个文件的话,用;分隔)
	vector<TReward> vReward; // 奖励列表
	int iAttackRange; // 攻击范围
};

// 英雄结构
struct THero
{
	string sHeroName; // 英雄名称
	int iMoveSpeed; // 移动速度
	int iHP; // 生命值
	TSkill stSkill; // 技能
	string sResourcePath; // 技能对应的图片资源路径(有多个文件的话,用;分隔)
	int iAttackRange; // 攻击范围
};

// 刷怪频率结构
struct TFrequency
{
	EGameMode eGameMode; // 游戏模式
	int iMonsterMin; // 击杀怪物条件的下限
	int iMonsterMax; // 击杀怪物条件的上限
	int iRefreshInterval; // 刷新时间间隔(单位:s)
	int iRefreshNum; // 刷新时间间隔内刷怪的数量
};

// 地图结构
struct TMap
{
	string sMapName; // 地图名称
	int iNeedKillNum; // 闯关模式通关需要杀怪的数量
	string sResourcePath; // 对应的地图资源路径
	vector<TFrequency> vFrequency; // 地图刷怪
};

// 配置结构
struct TConfig
{
	int iMapSize; // 地图单行(列)的个数
	int iMaxMoveSpeed; // 最大移动速度
	int iSpeedIncrement; // 每增加一个英雄,要增加的速度
	int iLifeNum; // 闯关模式时的生命数
	int iRebornCost; // 闯关模式重生消耗的金币数
	float fTimeCoefficient; // 时间得分系数
	float fCoinCoefficient; // 金币得分系数
	float fMonsterCoefficient; // 怪物得分系数
};

// 用户结构
struct TUser
{
	int iMoney; // 用户拥有的金币数
	int iKillNum; // 用户杀怪的数量
};


#endif