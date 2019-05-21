#include "../include/miner.h"

Miner::Miner(Room* position, unsigned int mine_size)
{
    this->_position = position;
    this->_mine_size = mine_size;
    this->_battery = pow(mine_size, BATTERY_POWER);
    this->_problem = Problem(mine_size, State(_position, _battery, 0));
}

Miner::Miner(Room* position, unsigned int mine_size, Heuristic* heuristic)
{
    this->_position = position;
    this->_mine_size = mine_size;
    this->_battery = pow(mine_size, BATTERY_POWER);
    this->_problem = Problem(mine_size, State(_position, _battery, 0), heuristic);
}

const Room* Miner::position() const
{
    return this->_position;
}

unsigned int Miner::battery() const
{
    return this->_battery;
}

unsigned int Miner::gold() const
{
    return this->_gold;
}

bool Miner::is_goal_state(const State& state) const
{
    return _problem.goal(state);
}

unsigned int Miner::number_explored_rooms() const
{
    return _explored_rooms;
}

Miner::Result Miner::execute(Miner::SearchStrategy strategy, unsigned int parameter)
{
    auto [result, state, actions] = search(strategy, parameter);

    if (result && is_goal_state(state))
        explore(actions);


    return {result, score(), _explored_rooms, actions};
}

const Room* Miner::left()
{
    Room* next_room = _position->left();
    if (next_room)
        return move(next_room);

    return nullptr;
}

const Room* Miner::right()
{
    Room* next_room = _position->right();
    if (next_room)
        return move(next_room);

    return nullptr;
}

const Room* Miner::up()
{
    Room* next_room = _position->up();
    if (next_room)
        return move(next_room);

    return nullptr;
}

const Room* Miner::down()
{
    Room* next_room = _position->down();
    if (next_room)
        return move(next_room);

    return nullptr;
}

Room* Miner::move(Room* next_room)
{
    if (next_room->condition() == Room::FENCE)
        return nullptr;

    if (_battery || buy_battery())
    {
        _position = next_room;
        --_battery;
    }
    
    return next_room;
}

bool Miner::pick_gold()
{
    if (_position->pick_gold())
    {
        ++_gold;
        return true;
    }
    return false;
}

bool Miner::buy_battery()
{
    if (_gold)
    {
        --_gold;
        _battery += 5 * pow(_mine_size, BATTERY_POWER);
        return true;
    }
    return false;
}

Miner::Answer Miner::search(SearchStrategy strategy, unsigned int parameter)
{
    switch (strategy)
    {
    case Miner::DEEP_FIRST_SEARCH_ITERATIVE:
        return dfs_iterative(parameter);
    
    case Miner::DEEP_FIRST_SEARCH_LIMITED:
        return dfs_limited(parameter);
    
    case Miner::A_STAR:
        return A_star();

    default:
        return dfs_limited(parameter);
    }
}

void Miner::explore(std::list<State::Action> actions)
{
    for (State::Action action : actions)
    {
        if      (action & State::LEFT)  left();
        else if (action & State::RIGHT) right();
        else if (action & State::UP)    up();
        else if (action & State::DOWN)  down();
        if (action & State::PICK_GOLD)  pick_gold();

        ++_actions_count;
    }
}

int Miner::score() const
{
    unsigned int p_dimension = pow(_mine_size,_mine_size);
    // return 10*_battery + 50*_gold + (factorial(_mine_size)/_explored_rooms) + (p_dimension/_actions_count);
    return _gold * (_battery+1) + (p_dimension/_actions_count) + (p_dimension/_explored_rooms);// + (p_dimension/_actions_count);
}

Miner::Answer Miner::dfs_limited(const unsigned int maxl)
{
    std::list<State::Action> actions;
    std::unordered_map<std::string, bool> explored;
    std::list<const Room*> mined;
    
    State state = dfs_limited(0, maxl, _problem.initial_state(), actions, explored);

    if (_problem.goal(state))
    {
        return {true, state, actions};
    }

    return {false, state, actions};
}

Miner::Answer Miner::A_star()
{
    State q = _problem.initial_state();

    /* conjunto de nós a serem pesquisados. */
    std::list<State> open_set;
    open_set.push_back(q);

    std::unordered_map<std::string, bool> closed_set;
    std::map<std::string, State> came_from;

    int counter = 0;

    while (!open_set.empty())
    {
        // a
        State current = open_set.front();

        if (_problem.goal(current))
            return {true, current, reconstruct_path(came_from, current)};

        _explored_rooms++;

        //b
        open_set.pop_front();
        closed_set[current.hash()] = true;

        //d
        for (State neighbor : _problem.successors(current))
        {
            if (closed_set[neighbor.hash()])
                continue;

            unsigned int tentative_g_score = current.g() + _problem.path_cost();

            if (std::find(open_set.begin(), open_set.end(), neighbor) == open_set.end())
            {
                open_set.push_back(neighbor);
                open_set.sort();
            }

            if (tentative_g_score > neighbor.g())
                continue;

            /* This path is the best until now. Record it! */            
            came_from[neighbor.hash()] = current;
        }
    }

    return {false, q, reconstruct_path(came_from, q)};
}

std::list<State::Action> Miner::reconstruct_path(std::map<std::string, State> came_from, State position)
{
    std::list<State::Action> actions;
    State current = position;

    while (came_from.count(current.hash()))
    {
        actions.push_front(current.action());
        current = came_from[current.hash()];
    }

    return actions;    
}


unsigned int counter = 0;
State Miner::dfs_limited(const unsigned int curl, const unsigned int maxl, State& state, std::list<State::Action>& actions, std::unordered_map<std::string, bool>& explored)
{
    _explored_rooms++;

    if (_problem.goal(state))
    {
        actions.push_front(state.action());
        return state;
    }

    if (curl+1 == maxl)
        return state;
    else
    {
        explored[state.hash()] = true;

        for (State s : _problem.successors(state))
        {
            if (!explored[s.hash()])
            {   
                State result = dfs_limited(curl+1, maxl, s, actions, explored);

                if (_problem.goal(result))
                {
                    actions.push_front(state.action());
                    return result;
                }           
            }
        }
    }
    return state;
}

Miner::Answer Miner::dfs_iterative(const unsigned int iterations)
{
    for (size_t i = 0; i < iterations; i++)
    {
        auto [result, state, actions] = dfs_limited(i+1);
        if (result && _problem.goal(state))
            return {result, state, actions};
    }
    return {false, State(), std::list<State::Action>()};
}