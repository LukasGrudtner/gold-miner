#include "../include/problem.h"

Problem::Problem() {}

Problem::Problem(unsigned int problem_size, State initial_state)
{
    this->_problem_size = problem_size;
    this->_initial_state = initial_state;
}

Problem::Problem(unsigned int problem_size, State initial_state, Heuristic* heuristic)
{
    this->_problem_size = problem_size;
    this->_heuristic = heuristic;
    
    _initial_state = State(initial_state.position(), initial_state.battery(), initial_state.gold(), initial_state.action(), initial_state.mined_rooms(), heuristic->value(initial_state.position()), initial_state.g(), heuristic->value(initial_state.position()));
}

std::list<const State> Problem::successors(State& state)
{
    std::list<const State> successors;
    const Room* position = state.position();

    /* Build down successor. */
    if (position->down() && position->down()->condition() != Room::FENCE)
    {
        if (state.battery() || position->down()->condition() == Room::GOLD)
        {
            State down = build_state(state, position->down(), State::DOWN);
            down.coordinate(position->down()->coordinate());
            successors.push_back(down);
        }
    }

    /* Build right successor. */
    if (position->right() && position->right()->condition() != Room::FENCE)
    {   
        if (state.battery() || position->right()->condition() == Room::GOLD)
        {
            State right = build_state(state, position->right(), State::RIGHT);
            right.coordinate(position->right()->coordinate());
            successors.push_back(right);
        }
    }

    /* Build left successor. */
    if (position->left() && position->left()->condition() != Room::FENCE)
    {
        if (state.battery() || position->left()->condition() == Room::GOLD)
        {
            State left = build_state(state, position->left(), State::LEFT);
            left.coordinate(position->left()->coordinate());
            successors.push_back(left);
        }
    }
    
    /* Build up successor. */
    if (position->up() && position->up()->condition() != Room::FENCE)
    {
        if (state.battery() || position->up()->condition() == Room::GOLD)
        {
            State up = build_state(state, position->up(), State::UP);
            up.coordinate(position->up()->coordinate());
            successors.push_back(up);
        }
    }

    if (_heuristic)
        successors.sort();
            
    return successors;
}

bool Problem::goal(const State& state) const
{
    return state.gold() == _problem_size/3 && state.position() == _initial_state.position();
}

unsigned int Problem::path_cost() const
{
    return 1;
}

State& Problem::initial_state()
{
    return this->_initial_state;
}

Problem::Attributes Problem::handle_attributes(unsigned int battery, unsigned int gold, const Room* position, std::list<const Room*>& mined)
{
    unsigned int _battery = battery, _gold = gold;
    State::Action _action = 0;

    if (position->condition() == Room::GOLD && std::find(mined.begin(), mined.end(), position) == mined.end())
    {
        _gold++;
        _action = State::PICK_GOLD;
        mined.push_back(position);
    }

    if (!_battery)
    {
        if (_gold)
        {
            _battery += 5 * pow(_problem_size, BATTERY_POWER);
            _gold--;

            return {_battery, _gold, _action};
        }

        return {0, 0, _action};
    }

    _battery -= path_cost();

    return {_battery, _gold, _action};
}

State Problem::build_state(State& father, Room* new_position, State::Action action)
{
    std::list<const Room*> _mined = father.mined_rooms();
    auto [_battery, _gold, _action] = handle_attributes(father.battery(), father.gold(), new_position, _mined);

    if (_heuristic)
        return State(new_position, _battery, _gold, action | _action, _mined, _heuristic->value(new_position), father.g()+path_cost(),_heuristic->value(new_position) + father.g()+path_cost());
    
    return State(new_position, _battery, _gold, action | _action, _mined);
}