/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Copyright (c) Innovation First 2016-2019, All rights reserved.          */
/*                                                                            */
/*    Module:     vex_task.h                                                  */
/*    Author:     James Pearman                                               */
/*    Created:    22 Nov 2016                                                 */
/*                                                                            */
/*    Revisions:                                                              */
/*                V1.00     TBD - Initial release                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef   VEX_TASK_CLASS_H
#define   VEX_TASK_CLASS_H

// In case we have ROBOTC definitions
#ifdef task
#undef task
#endif

/*-----------------------------------------------------------------------------*/
/** @file    vex_task.h
  * @brief   Header for task control class
*//*---------------------------------------------------------------------------*/

namespace vex {
  /** 
    * @prog_lang{cpp|pro}
    * @brief Use this class to create and control tasks.
  */
  class task  {
    friend class competition;

    private:
      static  int   _labelId;
      void         *_callback;
      int           _callbackId;
        
    protected:
      static int32_t _index( int (* callback)(void) );
      static void    _stopAll();
      static void    _dump();
      
    public:
      task();
      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::task Task = vex::task(callbackFunction);}
      * @brief Constructs a task with a function callback.
      * @param callback A reference to a function.
      */
      task( int (* callback)(void) );
      
      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @brief Constructs a task with a function callback.
      * @param callback A reference to a function.
      * @param arg A void pointer that is passed to the callback.
      */
      task( int (* callback)(void *), void *arg );

      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{constructor}
      * @block_sig{vex::task Task = vex::task(callbackFunction, vex::task::taskPriorityNormal);}
      * @brief Constructs a task with a function callback and a priority.
      * @param callback A reference to a function.
      * @param priority Sets the priority of the task.
      */
      task( int (* callback)(void), int32_t priority );
      
      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{none}
      * @brief Constructs a task with a function callback and a priority.
      * @param callback A reference to a function.
      * @param arg A void pointer that is passed to the callback.
      * @param priority Sets the priority of the task.
      */
      task( int (* callback)(void *), void *arg, int32_t priority );
      ~task();

      static const int32_t taskPrioritylow    =  1;
      static const int32_t taskPriorityNormal =  7;
      static const int32_t taskPriorityHigh   = 15;
      
      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{vex::task::stop(taskref);}
      * @brief Stops the specified task.
      * @param t The task to be stopped.
      */
      static void stop( const task &t );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{vex::task::suspend(taskref);}
      * @brief Suspends the specified task for later use.
      * @param t The task to be suspended.
      */
      static void suspend( const task &t );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{vex::task::resume(taskref);}
      * @brief Resumes a specified task that has been suspended.
      * @param t The task to be resumed.
      */
      static void resume( const task &t );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{vex::task::priority(taskref)}
      * @brief Gets the priority of a task.
      * @return Returns an integer that represents the current priority of the specified task.
      * @param t The task to get priority of.
      */
      static int32_t priority( const task &t ) ;

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{vex::task::setPriority(taskref,priority);}
      * @brief Sets the priority of the specified task.
      * @param t The task to set the priority on.
      * @param priority The priority level of a task.
      */
      static void setPriority( const task &t, int32_t priority ) ;

      // these act on this task
      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{Task.stop();}
      * @brief Stops the task.
      */
      void        stop();

      /**
      * @prog_lang{pro}
      * @drawer_cat{action}
      * @block_sig{Task.suspend();}
      * @brief Suspends the task until the task is told to resume.
      */
      void        suspend();

      /**
      * @prog_lang{pro}
      * @drawer_cat{action}
      * @block_sig{Task.resume();}
      * @brief Resumes the previously suspended task.
      */
      void        resume();

      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{sensing}
      * @block_sig{Task.priority()}
      * @brief Gets the priority of the task.
      * @return Returns an integer that represents the priority of the task.
      */
      int32_t     priority();

      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{setting}
      * @block_sig{Task.setPriority(1);}
      * @brief Sets the priority of the task.
      * @param priority The priority level of the task.
      */
      void        setPriority( int32_t priority );

      /**
      * @prog_lang{none}
      * @drawer_cat{none}
      * @block_sig{Task.index()}
      * @brief Gets the task's index.
      * @return Returns an integer that represents the index of the task.
      */
      int32_t     index( void );


      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{vex::task::sleep(1000);}
      * @brief Sets the task to sleep for the specified amount of time (in milliseconds).
      * @param time The number of milliseconds for the task to sleep.
      */
      static void sleep( uint32_t time );

      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{vex::task::yield();}
      * @brief return control to the scheduler and allow other tasks to run.
      */
      static void yield();

      /**
      * @prog_lang{cpp|pro}
      * @drawer_cat{action}
      * @block_sig{vex::task::stop(callbackFunction);}
      * @brief Stops the task of the passed in function.
      * @param callback A reference to a function. 
      */
      static void stop( void *callback, int callbackId = 0 );      

      static void stopAll();
  };
};

namespace vex {
  /**
    * @prog_lang{pro} 
    * @brief Use this class to synchronize access to resources.
  */
  class semaphore  {
    private:
      static  bool   _initialized;
      uint32_t       _sem;
        
    protected:
    
    public:
      semaphore();
      ~semaphore();
      

      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @block_sig{Semaphore.lock();}
      * @brief Attempts to lock the semaphore. If the semaphore is previously locked, it will block until the semaphore is unlocked.
      */
      void        lock();

      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @block_sig{Semaphore.lock(300);}
      * @brief Attempts to lock the semaphore. If the semaphore is previously locked, it will block until the timeout has expired or the semaphore is unlocked.
      * @param time The maximum amount of time to wait for the semaphore to be unlocked in milliseconds.
      */
      void        lock( uint32_t time );

      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @block_sig{Semaphore.unlock();}
      * @brief Unlocks a locked semaphore.
      */
      void        unlock();

      /**
      * @prog_lang{pro}
      * @drawer_cat{none}
      * @block_sig{Semaphore.owner()}
      * @brief Checks to see if the semaphore was locked and is owned by the current task.
      * @return Returns a true Boolean if the semaphore was locked and is owned by the current task.
      */
      bool        owner();      
  };
};

#endif // VEX_TASK_CLASS_H
