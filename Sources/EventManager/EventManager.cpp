#include "EventManager.h"
#include "IEventObserver.h"
#include "EventFactory.h"
#include "SDL.h"
#include <map>
#include <list>
#include <mutex>
#include <memory>

namespace EventManager {
    using tdObservers = std::list<IEventObserver*>;
    using tdEvents = std::map<EventType, tdObservers>;
    tdEvents eventsObservers_;
    std::recursive_mutex observerMutex_;

    LIB_API void ProcessEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            {
                std::lock_guard<std::recursive_mutex> g(observerMutex_);
                if (eventsObservers_.find(GetEventType(event)) == eventsObservers_.end()) continue;
            }
            auto newEvent = CreateEvent(event);
            if (newEvent) {
                {
                    std::lock_guard<std::recursive_mutex> g(observerMutex_);
                    for (auto observer : eventsObservers_[newEvent->GetType()]) {
                        observer->EventHandling(*newEvent);
                    }
                }
            }
        }
    }

    LIB_API void PushObserver(IEventObserver* observer, EventType evType)
    {
        std::lock_guard<std::recursive_mutex> g(observerMutex_);

        if (std::find(eventsObservers_[evType].begin(), eventsObservers_[evType].end(), observer) == eventsObservers_[evType].end()) {
            eventsObservers_[evType].push_back(observer);
        }
    }

    LIB_API void PopObserver(IEventObserver* observer, EventType evType)
    {
        std::lock_guard<std::recursive_mutex> g(observerMutex_);
        tdEvents::iterator it = eventsObservers_.begin();

        while (it != eventsObservers_.end()) {
            tdObservers& observers = it->second;
            tdObservers::iterator subIt = observers.begin();
            while (subIt != observers.end()) {
                if ((*subIt) == observer) {
                    subIt = observers.erase(subIt);
                }
                else {
                    ++subIt;
                }
            }
            if (observers.empty()) {
                it = eventsObservers_.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}


