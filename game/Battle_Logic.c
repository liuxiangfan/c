#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//----------------------------------------
//有的函数里可能缺少形参
//----------------------------------------

int Medicine_cd;//药水冷却时间
int My_Round;//我方回合数
int Enemy_Round;//敌方回合数

typedef struct 
{
    int damage_up;//伤害提升百分比
    int damage_down;//伤害降低百分比
    int attack_up;//攻击提升百分比
    int defense_up;//防御提升百分比
    int speed_value_up;//速度提升点数
    int speed_up;//速度提升百分比
    int crit_rate_up;//暴击率提升百分比
    int crit_damage_up;//暴击伤害提升百分比 
}buff;
typedef struct 
{
    int heal_dwon;//治疗效果降低百分比
    int defense_down;//防御降低百分比
    int be_attacked_up;//受到伤害提升百分比
    int no_round;//无法行动
}debuff;



//出伤机制
int Damage([技能伤害])
{
    srand(time(NULL)); // 初始化随机种子
    float critical_chance = [暴击率]; // 暴击概率
    float random_value = (float)rand() / RAND_MAX; // 生成0到1之间的随机数
    if(random_value < critical_chance)
    {
        return [技能伤害] * [暴击伤害]-[对方防御]; // 暴击伤害
    }
    else
    {
        return [技能伤害]-[对方防御]; // 普通伤害
    }
}

/*回复机制*/
//蓝量回复机制
void MP_Heal(int [回复蓝量])
{
    if([我方蓝量]+[回复蓝量]>=[我方最大蓝量])
    {
        [我方蓝量]=[我方最大蓝量];
    }
    else
    {
        [我方蓝量]+=[回复蓝量];
    }
}

//能量回复机制
void EP_Heal(int [回复能量])
{
    if([我方能量]+[回复能量]>=[我方最大能量])
    {
        [我方能量]=[我方最大能量];
    }
    else
    {
        [我方能量]+=[回复能量];
    }
}

//药水冷却时间减少机制
void Medicine_Cd_Reduce()
{
    if(Medicine_cd>0)
    {
        Medicine_cd--;
    }
}

//药水回复机制
void Medicine()
{
    if(Medicine_cd==0)
    {
        if([血瓶])
        {
            HP_Heal([回复血量]);
            Medicine_cd=3;
        }
        else if([蓝瓶])
        {
            MP_Heal([回复蓝量]);
            Medicine_cd=3;
        }
    }
}

//行动选择机制
void Action_Choice()
{

    Medicine_Cd_Reduce();
    int choice;
    printf("请选择行动:\n");
    printf("1. 技能\n");
    printf("2. 药\n");
    printf("3.逃跑 ");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            Fight();  //战斗逻辑  
            break;
        case 2:
            Medicine();    //药逻辑
            break;
        case 3:
            Espace();   //逃跑逻辑
            break;
    }
}

//逃跑机制
void Espace()
{
    printf("逃跑成功，战斗结束\n");
    exit(0);
}

//战斗结束机制,进行死亡判定
void Death()
{
    if([我方血量]<=0)
    {
        printf("Debeat");//死亡处理
        exit(0);
    }
    else if([敌方血量]<=0)
    {
        printf("Victory");//胜利处理
        exit(0);
    }
}

//战斗机制
//效果:造成伤害，消耗蓝量/能量，增加能量，特殊buff/debuff效果等
void Fight()
{
    while(1)
    {
        if([选择]==[普攻])
        {
                    
            
            
                    //普攻效果
            break;
        }
        else if([选择]==[战技1])
        {
            if([我方蓝量]<[战技1消耗])
            {
                printf("蓝量不足，请重新选择\n");
                continue;
            }
                
            
            
            
                    //技能1效果
            break;
        }
        else if([选择]==[技能2])
        {
            if ([我方蓝量]<[战技2消耗])
            {
                printf("蓝量不足，请重新选择\n");
                continue;
            }
                    
            
            
            
                    //技能2效果
            break;
        }
        else if([选择]==[大招])
        {
            if ([我方能量]<[能量最大值])
            {
                printf("能量不足，请重新选择\n");
                continue;
            }
            
            
            
            
                    //大招效果
            break;
        }
        else
        {
            printf("选择错误，请重新选择\n");
        }
    }
    int damage = Damage([技能伤害]);
    [敌方血量] -= damage;
    Death();
    printf("敌方受到%d点伤害,当前血量为%d\n", damage, [敌方血量]);
}


//受攻击机制
void Be_Attacked([敌方技能伤害])
{
    int damage = Damage([敌方技能伤害]);
    [我方血量] -= damage;
    Death();
    printf("我方受到%d点伤害,当前血量为%d\n", damage, [我方血量]);
}

int main(void)
{
    while(1)
    {
        [我方速度条]+=[我方速度];
        [敌方速度条]+=[敌方速度];
        while([我方速度条]==100)
        {
            My_Round++;
            Action_Choice();
            [我方速度条]=0;
        }
        while([敌方速度条]==100)
        {
            Enemy_Round++;
                    //敌方行动逻辑
            [敌方速度条]=0;
        }
    }
    return 0;
}