#include "EventManager.h"
#include "IEventObserver.h"
#include "EventType.h"
#include "EventUnknown.h"
#include "EventQuit.h"
#include "EventWindowResize.h"
#include "EventMouseUp.h"
#include "EventMouseDown.h"
#include "EventMouseMove.h"
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
    const IEvent& GetSystemEvent(const SDL_Event& srcEvent);
    EventType GetEventType(const SDL_Event& srcEvent);

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

    LIB_API void PushEvent(std::unique_ptr<IEvent> event)
    {
        std::lock_guard<std::recursive_mutex> g(eventsMutex_);
        events_.push(std::move(event));
    }

    const IEvent& GetSystemEvent(const SDL_Event& srcEvent)
    {
        static EventUnknow eventUnknown_;
        static EventQuit eventQuit_;
        static EventWindowResize eventWindowResize_;
        static EventMouseUp eventMouseUp_;
        static EventMouseDown eventMouseDown_;
        static EventMouseMove eventMouseMove_;

        switch (srcEvent.type) {
        case SDL_QUIT: {
            return eventQuit_;
        } break;
        case SDL_MOUSEMOTION: {
            eventMouseMove_.SetX(srcEvent.button.x);
            eventMouseMove_.SetY(srcEvent.button.y);
            return eventMouseMove_;
        } break;
        case SDL_MOUSEBUTTONDOWN: {
            eventMouseDown_.SetX(srcEvent.button.x);
            eventMouseDown_.SetY(srcEvent.button.y);
            eventMouseDown_.SetButton(srcEvent.button.button);
            return eventMouseDown_;
        } break;
        case SDL_MOUSEBUTTONUP: {
            eventMouseUp_.SetX(srcEvent.button.x);
            eventMouseUp_.SetY(srcEvent.button.y);
            eventMouseUp_.SetButton(srcEvent.button.button);
            return eventMouseUp_;
        } break;
        case SDL_WINDOWEVENT: {
            if (srcEvent.window.event == SDL_WINDOWEVENT_RESIZED) {

                eventWindowResize_.SetWindowWidth((int)srcEvent.window.data1);
                eventWindowResize_.SetWindowWidth((int)srcEvent.window.data2);
                return eventWindowResize_;
            }
            else {
                return eventUnknown_;
            }
        } break;
        default: return eventUnknown_;
        }
    }

    EventType GetEventType(const SDL_Event& srcEvent)
    {
        switch (srcEvent.type) {
        case SDL_QUIT: return EventType::Quit;
        case SDL_MOUSEMOTION: return EventType::MouseMove;
        case SDL_MOUSEBUTTONDOWN: return EventType::MouseDown;
        case SDL_MOUSEBUTTONUP: return EventType::MouseUp;
        case SDL_WINDOWEVENT:
            if (srcEvent.window.event == SDL_WINDOWEVENT_RESIZED) return EventType::WindowResize;
            else return EventType::Undefined;
        default: return EventType::Undefined;
        }
    }
}


