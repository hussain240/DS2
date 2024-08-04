#include "pirates24b2.h"

oceans_t::oceans_t()
{
	// TODO: Your code goes here
    this->pirates=new hashTable<std::shared_ptr<pirate>>();
    this->fleets=new UnionFind<std::shared_ptr<fleet>>();
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
	return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
    // TODO: Your code goes here
    return 2008;
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}
