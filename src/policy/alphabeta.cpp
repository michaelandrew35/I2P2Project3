#include <cstdlib>
#include <algorithm>
#include "../state/state.hpp"
#include "./alphabeta.hpp"

int evaltree(State *state, int depth, int alpha, int beta, int maximizing)
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
      State* temp = state->next_state(*it);
      temp->player = !temp->player;
      if(!temp->legal_actions.size()) temp->get_legal_actions();
      if(temp->game_state == WIN) continue;
      else temp->player = !temp->player;
      int val = evaltree(temp, depth-1, alpha, beta, 0);
      if(val > value)
      {
        value = val;
      }
      if(value > alpha)
      {
        alpha = value;
        state->ret = *it;
      }
      if(alpha > beta) break;
    }
    return value;
  }
  else
  {
    int value = 1000000000;
    for(auto it = state->legal_actions.begin(); it != state->legal_actions.end(); it++)
    {
      State* temp = state->next_state(*it);
      temp->player = !temp->player;
      if(!temp->legal_actions.size()) temp->get_legal_actions();
      if(temp->game_state == WIN) continue;
      else temp->player = !temp->player;
      int val = evaltree(temp, depth-1, alpha, beta, 1);
      if(val < value)
      {
        value = val;
      }
      if(value < beta)
      {
        beta = value;
        state->ret = *it;
      }
      if(beta < alpha) break;
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
Move AlphaBeta::get_move(State *state, int depth)
{  
  evaltree(state, depth, -1000000000, 1000000000, 1-state->player);
  return state->ret;
}