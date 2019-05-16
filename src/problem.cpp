#include "../include/problem.h"

Problem::Problem() {}

Problem::Problem(unsigned int problem_size, State initial_state)
{
    this->_problem_size = problem_size;
    this->_initial_state = initial_state;
}

std::list<const State> Problem::successors(State& state)
{
    std::list<const State> successors;
    std::vector<std::string> aux;
    std::list<const State> aux_state;

    const Room* position = state.position();

    std::list<const Room*> mined = state.mined_rooms();
    {
        /* Build down successor. */
        if (position->down() && position->down()->condition() != Room::FENCE)
        {
            State down = build_state(state, position->down(), State::DOWN);

            down.coordinates() = position->down()->coordinates();
            aux.push_back(down.hash());
            aux_state.push_back(down);
            successors.push_back(down);
        }

        /* Build right successor. */
        if (position->right() && position->right()->condition() != Room::FENCE)
        {   
            State right = build_state(state, position->right(), State::RIGHT);

            right.coordinates() = position->right()->coordinates();
            aux.push_back(right.hash());
            aux_state.push_back(right);
            successors.push_back(right);
        }

        /* Build left successor. */
        if (position->left() && position->left()->condition() != Room::FENCE)
        {
            State left = build_state(state, position->left(), State::LEFT);

            left.coordinates() = position->left()->coordinates();
            aux.push_back(left.hash());
            aux_state.push_back(left);
            successors.push_back(left);
        }
        
        /* Build up successor. */
        if (position->up() && position->up()->condition() != Room::FENCE)
        {
            State up = build_state(state, position->up(), State::UP);
            
            up.coordinates() = position->up()->coordinates();
            aux.push_back(up.hash());
            aux_state.push_back(up);
            successors.push_back(up);
        }

        /* Shuffles successors order. */
#ifdef RANDOM_SUCCESSORS_CHOICE
        srand(time(NULL));
        std::random_shuffle(aux.begin(), aux.end());
        successors.clear();

        for (std::string str : aux)
        {
            for (const State state : aux_state)
            {
                if (state.hash() == str)
                {
                    successors.push_back(state);
                    break;
                }
            }   
        }
#endif
            
    }
    return successors;
}

bool Problem::goal(const State& state) const
{
    return state.gold() == _problem_size/2;
    // return state.gold() == 5;
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

    return State(new_position, _battery, _gold, action | _action, _mined);
}