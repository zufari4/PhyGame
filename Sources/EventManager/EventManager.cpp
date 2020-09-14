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
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (eventsObservers_.find(GetEventType(event)) == eventsObservers_.end()) continue;
            auto newEvent = CreateEvent(event);
            if (newEvent) {
                for (auto observer : eventsObservers_[newEvent->GetType()]) {
                    observer->EventHandling(*newEvent);
                }
            }
        }

        std::lock_guard<std::recursive_mutex> guardEvents(eventsMutex_);
        std::unique_ptr<IEvent> userEvent;
        while (!events_.empty()) {
            userEvent = std::move(events_.front());
            events_.pop();
            if (eventsObservers_.find(userEvent->GetType()) == eventsObservers_.end()) continue;
            for (auto observer : eventsObservers_[userEvent->GetType()]) {
                observer->EventHandling(*userEvent);
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


