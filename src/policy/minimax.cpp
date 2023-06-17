#include <cstdlib>
#include <algorithm>
#include "../state/state.hpp"
#include "./minimax.hpp"

int evalTree(State *state, int depth, int maximizing)
{
  if(!state->legal_actions.size()) state->get_legal_actions();
  if(depth == 0 || !state->legal_actions.size())
  {
    return state->evaluate();
  }
  if(maximizing)
  {
    int value = -1000000000;
    for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); it++)
    {
      State* temp = new State(state->board, state->player);
      int val = evalTree(temp->next_state(*it), depth-1, 0);
      if(val >= value)
      {
        value = val;
        state->ret = *it;
        state->score = value;
      }
    }
    return value;
  }
  else
  {
    int value = 1000000000;
    for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); it++)
    {
      State* temp = new State(state->board, state->player);
      int val = evalTree(temp->next_state(*it), depth-1, 1);
      if(val <= value)
      {
        value = val;
        state->ret = *it;
        state->score = value;
      }
    }
    return value;
  }
}


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move MiniMax::get_move(State *state, int depth)
{  
  evalTree(state, depth, 1-state->player);
  return state->ret;
}