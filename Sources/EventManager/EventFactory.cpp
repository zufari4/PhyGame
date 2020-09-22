#include "EventFactory.h"
#include "EventQuit.h"
#include "SDL.h"
#include "EventUnknown.h"
#include "EventButtonClick.h"
#include "EventWindowResize.h"
#include "EventMouseUp.h"

namespace EventManager
{
    const IEvent& GetSystemEvent(const SDL_Event& srcEvent)
    {
        static EventUnknow eventUnknown_;
        static EventQuit eventQuit_;
        static EventWindowResize eventWindowResize_;
        static EventMouseUp eventMouseUp_;

        switch (srcEvent.type) {
        case SDL_QUIT: {
            return eventQuit_;
        } break;
        /*case SDL_MOUSEMOTION:
        {
            /*vec2 cursor = s2w(event_.button.x, event_.button.y);
            for (const auto& obj : game_objects_) {
                obj->On_mouse_move(cursor.x, cursor.y);
            }
            if (cb_mouse_move_.func) {
                (cb_mouse_move_.obj->*cb_mouse_move_.func)(cursor.x, cursor.y);
            }
        }
        break;*/
        /*case SDL_MOUSEBUTTONDOWN:
        {
            vec2 cursor = s2w(event_.button.x, event_.button.y);
            if (phy_pause_)
            {
                for (const auto& obj : game_objects_) {
                    if (obj->Cursor_enter(cursor)) {
                        Select_object(obj);
                        break;
                    }
                    else {
                        obj->Set_selected(false);
                    }
                }
            }
            for (const auto& obj : game_objects_) {
                obj->On_mouse_down(cursor.x, cursor.y, event_.button.button);
            }
            if (cb_mouse_down_.func) {
                (cb_mouse_down_.obj->*cb_mouse_down_.func)(cursor.x, cursor.y, event_.button.button);
            }
        }
        break;*/
        case SDL_MOUSEBUTTONUP: {
            eventMouseUp_.SetX(srcEvent.button.x);
            eventMouseUp_.SetY(srcEvent.button.y);
            eventMouseUp_.SetButton(srcEvent.button.button);
            return eventMouseUp_;

        } break;
        case SDL_WINDOWEVENT:
        {
            if (srcEvent.window.event == SDL_WINDOWEVENT_RESIZED) {

                eventWindowResize_.SetWindowWidth((int)srcEvent.window.data1);
                eventWindowResize_.SetWindowWidth((int)srcEvent.window.data2);
                return eventWindowResize_;
            }
            else {
                return eventUnknown_;
            }
        } break;
        default:
            return eventUnknown_;
        }
    }

    std::unique_ptr<IEvent> CreateEvent(EventType type, const std::string& sender)
    {
        std::unique_ptr<IEvent> res;
        switch (type)
        {
        case EventManager::EventType::ButtonClick:
            res = std::unique_ptr<IEvent>(new EventButtonClick(sender));
            break;
        default:
            break;
        }

        return res;
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