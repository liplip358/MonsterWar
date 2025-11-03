#pragma once

namespace engine::scene
{
    class Scene;
}

namespace engine::utils
{
    struct QuitEvent
    {
    };
    struct PopSceneEvent
    {
    };
    struct PushSceneEvent
    {
        std::unique_ptr<engine::scene::Scene> scene;
    };
    struct ReplaceSceneEvent
    {
        std::unique_ptr<engine::scene::Scene> scene;
    };

}