#include "app/Application.h"

#ifdef EMSCRIPTEN
#include "platform/WebFactory.h"
#else
#include "platform/DesktopFactory.h"
#endif

int main()
{
    std::unique_ptr<PlatformFactory> factory;
#ifdef EMSCRIPTEN
    factory = std::make_unique<WebFactory>();
#else
    factory = std::make_unique<DesktopFactory>();
#endif

    Application app(std::move(factory));
    return app.run();
}
