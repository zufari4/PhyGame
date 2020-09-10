#include "Client.h"

int WinMain(void* hInstance, void* hPrevInstance, wchar_t* lpCmdLine, int nShowCmd)
{
    Client client;
    if (client.Init()) {
        client.Run();
    }
    client.Free();
    return 0;
}
