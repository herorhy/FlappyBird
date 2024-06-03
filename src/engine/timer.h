#ifndef SG_ENGINE_TIMER_H_
#define SG_ENGINE_TIMER_H_

#include <cstdint>
#include <SDL.h>

class Timer {
public:
    Timer() { Restart(); }

    void Restart() {
        ticks_ = SDL_GetTicks();
        L = 0;
    }

    void Pause() {
        pause_time = SDL_GetTicks();
    }
    void Resume() {
        L += SDL_GetTicks() - pause_time;
    }
    bool CheckInterval(uint32_t interval) {
        return (SDL_GetTicks() - ticks_-L ) >= interval;
    }
    
private:
    uint32_t ticks_;
    uint32_t pause_time;
    uint32_t L;

};

#endif // SG_ENGINE_TIMER_H_
