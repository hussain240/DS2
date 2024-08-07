#include "pirates24b2.h"

oceans_t::oceans_t()
{
	// TODO: Your code goes here
    this->pirates=new hashTable<std::shared_ptr<pirate>>();
    this->fleets=new UnionFind();
}

oceans_t::~oceans_t()
{
	// TODO: Your code goes here
    delete pirates;
    delete fleets;
}


StatusType oceans_t::add_fleet(int fleetId)
{
	// TODO: Your code goes here
    try{
        if(fleetId<=0)
        {
            return StatusType::INVALID_INPUT;
        }
        if(this->fleets->find(fleetId)!= nullptr)
        {
            return StatusType::FAILURE;
        }
        std::shared_ptr<fleet>toInsert(new fleet(fleetId));
        this->fleets->makeSet(fleetId,toInsert);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
	// TODO: Your code goes here
    try{
        if(pirateId<=0 || fleetId<=0)
        {
            return StatusType::INVALID_INPUT;
        }
        NodeHash<std::shared_ptr<fleet>>* wantedFleet=this->fleets->find(fleetId);
        if(wantedFleet== nullptr || this->pirates->find(pirateId)!= nullptr)
        {
            return StatusType::FAILURE;
        }
        if(wantedFleet->fatherId!=fleetId)
        {
            return StatusType::FAILURE;
        }
        ////////////////need to give the pirate the right rank//////////////////////////////
        std::shared_ptr<pirate>toInsert(new pirate(0,pirateId,wantedFleet->value->getNumOfPirate()+1-wantedFleet->rank,wantedFleet->key));
        this->pirates->insert(pirateId,toInsert);
        wantedFleet->value->addNumOfPirate(1);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	// TODO: Your code goes here
    try{
        if(pirateId<=0 || salary<=0)
        {
            return StatusType::INVALID_INPUT;
        }
        if(this->pirates->find(pirateId)== nullptr)
        {
            return StatusType::FAILURE;
        }
        NodeHash<std::shared_ptr<pirate>>* toPay=this->pirates->find(pirateId);
        toPay->value->paySalary(salary);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
    // TODO: Your code goes here
    try{
        if(fleetId<=0)
        {
            return output_t<int>(StatusType::INVALID_INPUT);
        }
        NodeHash<std::shared_ptr<fleet>>* wantedFleet=this->fleets->find(fleetId);
        if(wantedFleet== nullptr)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        if(wantedFleet->fatherId!=fleetId)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        return output_t<int>(wantedFleet->size);
    }
    catch (const std::bad_alloc& bad)
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

    return 2008;
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
    // TODO: Your code goes here
    try{
        if(pirateId<=0)
        {
            return output_t<int>(StatusType::INVALID_INPUT);
        }
        NodeHash<std::shared_ptr<pirate>>* toGet=this->pirates->find(pirateId);
        if(toGet== nullptr)
        {
            return output_t<int>(StatusType::FAILURE);
        }
        return output_t<int>(toGet->value->getSalary());
    }
    catch (const std::bad_alloc& bad)
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
	// TODO: Your code goes here
    try{
        if(fleetId1<=0 || fleetId2<=0 || fleetId1==fleetId2)
        {
            return StatusType::INVALID_INPUT;
        }
        NodeHash<std::shared_ptr<fleet>>* fleet1=this->fleets->find(fleetId1);
        NodeHash<std::shared_ptr<fleet>>* fleet2=this->fleets->find(fleetId2);
        if(fleet1== nullptr || fleet2== nullptr)
        {
            return StatusType::FAILURE;
        }
        if(fleet1->fatherId!=fleetId1 || fleet2->fatherId!=fleetId2)
        {
            return StatusType::FAILURE;
        }
        if(fleet1->value->getNumOfPirate()==0 || fleet2->value->getNumOfPirate()==0)
        {
            return StatusType::FAILURE;
        }
        this->fleets->Union(fleetId1,fleetId2);
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
    // TODO: Your code goes here
    try{
        if(pirateId1<=0 || pirateId2<=0 ||pirateId2==pirateId1)
        {
            return StatusType::INVALID_INPUT;
        }
        NodeHash<std::shared_ptr<pirate>>*pirate1=this->pirates->find(pirateId1);
        NodeHash<std::shared_ptr<pirate>>*pirate2=this->pirates->find(pirateId2);
        if(pirate1== nullptr || pirate2== nullptr)
        {
            return StatusType::FAILURE;
        }
        ////////////////////neeed to complete/////////////////
        int pirate1Rank=this->fleets->findRank(pirate1->value->getFleetId())+pirate1->value->getRank();
        int pirate2Rank=this->fleets->findRank(pirate2->value->getFleetId())+pirate2->value->getRank();
        if(pirate1Rank<pirate2Rank)
        {
            pirate1->value->paySalary(pirate2Rank-pirate1Rank);
            pirate2->value->paySalary(pirate1Rank-pirate2Rank);
        }
        else
        {
            pirate2->value->paySalary(pirate1Rank-pirate2Rank);
            pirate1->value->paySalary(pirate2Rank-pirate1Rank);
        }
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& bad)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}
