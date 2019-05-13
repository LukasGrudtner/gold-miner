#include "../include/problem.h"

Problem::Problem() {}

Problem::Problem(const State& initial_state)
{
    this->_initial_state = initial_state;
}

int myrandom(int i)
{
    return std::rand()%i;
}

std::list<const State> Problem::successors(const State& state) const
{
    std::list<const State> successors;
    std::vector<std::string> aux;
    std::list<const State> aux_state;

    const Room* position = state.position();

    if (state.battery())
    {
        if (position->right() && position->right()->goal() != Room::FENCE)
        {
            State right = State(position->right(), State::RIGHT, state.battery()-path_cost(), state.gold());
            aux.push_back(right.to_string());
            aux_state.push_back(right);
        }

        if (position->down() && position->down()->goal() != Room::FENCE)
        {
            State down = State(position->down(), State::DOWN, state.battery()-path_cost(), state.gold());
            aux.push_back(down.to_string());
            aux_state.push_back(down);
        }

        if (position->left() && position->left()->goal() != Room::FENCE)
        {
            State left = State(position->left(), State::LEFT, state.battery()-path_cost(), state.gold());
            aux.push_back(left.to_string());
            aux_state.push_back(left);
        }
        
        if (position->up() && position->up()->goal() != Room::FENCE)
        {
            State up = State(position->up(), State::UP, state.battery()-path_cost(), state.gold());
            aux.push_back(up.to_string());
            aux_state.push_back(up);
        }

        srand(time(NULL));
        std::random_shuffle(aux.begin(), aux.end());

        for (std::string str : aux)
        {
            for (const State state : aux_state)
            {
                if (state.to_string() == str)
                {
                    successors.push_back(state);
                    break;
                }
            }   
        }
            
    }

    
    return successors;
}

bool Problem::goal(const State& state) const
{
    return state.position()->goal() == Room::GOLD;
    // return state.gold() == 2;
}

unsigned int Problem::path_cost() const
{
    return 1;
}

const State& Problem::initial_state() const
{
    return this->_initial_state;
}