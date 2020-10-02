#ifndef _GENAUTO_
#define _GENAUTO_

#include <queue>
#include <map>
#include "vex.h"

typedef bool (*state_ptr)();

class GenericAuto
{
  public:

  /**
  * The method that runs the autonomous. If 'blocking' is true, then
  * this method will run through every state until it finished.
  *
  * If blocking is false, then assuming every state is also non-blocking,
  * the method will run through the current state in the list and return
  * immediately.
  *
  * @param blocking
  *     Whether or not to block the thread until all states have run
  * @returns
  *     true after all states have finished.
  */
  bool run(bool blocking);

  void add(state_ptr);

  private:

  std::queue<state_ptr> state_list;

};

#endif