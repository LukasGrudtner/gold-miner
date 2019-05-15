#include "../include/problem.h"

Problem::Problem() {}

Problem::Problem(unsigned int problem_size, State initial_state)
{
    this->_problem_size = problem_size;
    this->_initial_state = initial_state;
}

int myrandom(int i)
{
    return std::rand()%i;
}

std::list<const State> Problem::successors(State& state)
{
    std::list<const State> successors;
    std::vector<std::string> aux;
    std::list<const State> aux_state;

    const Room* position = state.position();

    std::list<const Room*> mined = state.mined_list();
    auto [battery, gold, action] = handle_attributes(state.battery(), state.gold(), position, mined);

    if (battery)
    {
        if (position->down() && position->down()->goal() != Room::FENCE)
        {
            State down = State(position->down(), action | State::DOWN, battery-path_cost(), gold, mined);

            down._coord = position->down()->coordenada();
            aux.push_back(down.to_string());
            aux_state.push_back(down);
            successors.push_back(down);
        }

        if (position->right() && position->right()->goal() != Room::FENCE)
        {   
            State right = State(position->right(), action | State::RIGHT, battery-path_cost(), gold, mined);

            right._coord = position->right()->coordenada();
            aux.push_back(right.to_string());
            aux_state.push_back(right);
            successors.push_back(right);
        }

        if (position->left() && position->left()->goal() != Room::FENCE)
        {

            State left = State(position->left(), action | State::LEFT, battery-path_cost(), gold, mined);

            left._coord = position->left()->coordenada();
            aux.push_back(left.to_string());
            aux_state.push_back(left);
            successors.push_back(left);
        }
        
        if (position->up() && position->up()->goal() != Room::FENCE)
        {
            State up = State(position->up(), action | State::UP, battery-path_cost(), gold, mined);
            
            up._coord = position->up()->coordenada();
            aux.push_back(up.to_string());
            aux_state.push_back(up);
            successors.push_back(up);
        }

        // srand(time(NULL));
        // std::random_shuffle(aux.begin(), aux.end());

        // for (std::string str : aux)
        // {
        //     for (const State state : aux_state)
        //     {
        //         if (state.to_string() == str)
        //         {
        //             successors.push_back(state);
        //             break;
        //         }
        //     }   
        // }
            
    }
    return successors;
}

bool Problem::goal(const State& state) const
{
    // return state.gold() == _problem_size/2;
    return state.gold() >= 2;
}

unsigned int Problem::path_cost() const
{
    return 1;
}

State& Problem::initial_state()
{
    return this->_initial_state;
}

std::tuple<unsigned int, unsigned int, State::Action> Problem::handle_attributes(unsigned int battery, unsigned int gold, const Room* position, std::list<const Room*>& mined)
{
    unsigned int _battery = battery, _gold = gold;
    State::Action _action = 0;

    if (position->goal() == Room::GOLD && std::find(mined.begin(), mined.end(), position) == mined.end())
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
            // _battery += 6;
            _gold--;

            return {_battery, _gold, _action};
        }

        return {0, 0, _action};
    }

    return {_battery, _gold, _action};
}