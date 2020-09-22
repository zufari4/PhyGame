#include "EventManager.h"
#include "IEventObserver.h"
#include "EventFactory.h"
#include "SDL.h"
#include <map>
#include <list>
#include <mutex>
#include <memory>
#include <queue>

namespace EventManager {
    using tdObservers = std::list<IEventObserver*>;
    using tdEvents = std::map<EventType, tdObservers>;
    tdEvents eventsObservers_;
    std::recursive_mutex observerMutex_;
    std::recursive_mutex eventsMutex_;
    std::queue<std::unique_ptr<IEvent>> events_;

    LIB_API void ProcessEvents()
    {
        std::lock_guard<std::recursive_mutex> g(observerMutex_);

        // System events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (eventsObservers_.find(GetEventType(event)) == eventsObservers_.end()) continue;
            const auto& newEvent = GetSystemEvent(event);

            for (auto observer : eventsObservers_[newEvent.GetType()]) {
                observer->EventHandling(newEvent);
            }
        }

        // Application events
        std::lock_guard<std::recursive_mutex> guardEvents(eventsMutex_);
        std::unique_ptr<IEvent> appEvent;
        while (!events_.empty()) {
            appEvent = std::move(events_.front());
            events_.pop();
            if (eventsObservers_.find(appEvent->GetType()) == eventsObservers_.end()) continue;
            for (auto observer : eventsObservers_[appEvent->GetType()]) {
                observer->EventHandling(*appEvent);
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

    LIB_API void PushEvent(EventType evType, const std::string& sender)
    {
        auto event = CreateEvent(evType, sender);
        std::lock_guard<std::recursive_mutex> g(eventsMutex_);
        events_.push(std::move(event));
    }

}


