
#include "library2.h"
#include "ds.h"


void *Init(int k){
    if( k<=0 ){
        return NULL;
    }
    DS*  ds = new DS(k);
    return (void*)ds;
}

StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade);

StatusType RemoveEmployee(void *DS, int employeeID);

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor);

StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease);

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade);

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m, void * sumBumpGrade);

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary, void * averageBumpGrade);

StatusType CompanyValue(void *DS, int companyID, void * standing);

StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade);

void Quit(void** DS);


StatusType MergeGroups(void *DS, int GroupID1, int GroupID2)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DSacquireCompany(GroupID1,GroupID2);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DSaddEmployee(PlayerID,GroupID,score);
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DSremoveEmployee(PlayerID);
}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DSemployeeSalaryIncrease(PlayerID,LevelIncrease);
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DSpromoteEmployee(PlayerID,NewScore);
}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel,
                                                int higherLevel, double * players)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DSavregeGradeInBounds(GroupID,score,
                                                 lowerLevel,higherLevel,players);
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    return static_cast<DsManager*>(DS)->DSsumOfGradeTopEmployee(GroupID,m,level);
}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                           int * LowerBoundPlayers, int * HigherBoundPlayers)
{
    if(DS== NULL || LowerBoundPlayers==NULL || HigherBoundPlayers==NULL)
    {
        return INVALID_INPUT;
    }
    return SUCCESS;
}
void Quit(void** DS)
{
    delete (DsManager*)*DS;
    *DS=NULL;
}