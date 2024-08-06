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
        if(this->fleets[fleetId]!= nullptr)
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
        if(this->fleets[fleetId]== nullptr || this->pirates[pirateId]!= nullptr)
        {
            return StatusType::FAILURE;
        }
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
        if(this->pirates[pirateId]== nullptr)
        {
            return StatusType::FAILURE;
        }
        NodeHash<std::shared_ptr<pirate>>* toPay=this->pirates[pirateId];
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
        NodeHash<std::shared_ptr<pirate>>* toGet=this->pirates[pirateId];
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
        if(fleetId1<=0 || fleetId2<=0)
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

    return StatusType::SUCCESS;
}
