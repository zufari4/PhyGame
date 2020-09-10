#include "EventFactory.h"
#include "SDL.h"

namespace EventManager
{
    EventType EventQuit::GetType() const
    {
        return EventType::Quit;
    }

    std::unique_ptr<IEvent> CreateEvent(const SDL_Event& srcEvent)
    {
        std::unique_ptr<IEvent> eventPtr;

        switch (srcEvent.type) {
        case SDL_QUIT: {
            eventPtr = std::unique_ptr<IEvent>(new EventQuit());
        } break;
        case SDL_MOUSEMOTION:
        {
            /*vec2 cursor = s2w(event_.button.x, event_.button.y);
            for (const auto& obj : game_objects_) {
                obj->On_mouse_move(cursor.x, cursor.y);
            }
            if (cb_mouse_move_.func) {
                (cb_mouse_move_.obj->*cb_mouse_move_.func)(cursor.x, cursor.y);
            }*/
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
        {
            /*vec2 cursor = s2w(event_.button.x, event_.button.y);
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
            }*/
        }
        break;
        case SDL_MOUSEBUTTONUP:
        {
            /*vec2 cursor = s2w(event_.button.x, event_.button.y);
            for (const auto& obj : game_objects_)
                obj->On_mouse_up(cursor.x, cursor.y, event_.button.button);
            if (cb_mouse_up_.func) {
                (cb_mouse_up_.obj->*cb_mouse_up_.func)(cursor.x, cursor.y, event_.button.button);
            }*/
        }
        break;
        case SDL_WINDOWEVENT:
        {
            /*if (event_.window.event == SDL_WINDOWEVENT_RESIZED) {
                if (cb_window_resize_.func) {
                    (cb_window_resize_.obj->*cb_window_resize_.func)((float)event_.window.data1, (float)event_.window.data2);
                }
            }*/
        }
        break;
        }
        return eventPtr;
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