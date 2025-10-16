#include <spdlog/spdlog.h>
#include <entt/entt.hpp>

// 定義兩個組件 位置和速度
struct Position
{
    float x, y;
};

struct Velocity
{
    float dx, dy;
};

int main()
{
    // step1: 創建resgistry
    // entt::registry 是一個用來管理實體和組件的核心類別
    entt::registry registry;

    // step2: 創建實體
    // 實體本身是唯一的標識符(ID)，可以通過 registry.create() 方法創建
    entt::entity player = registry.create();
    entt::entity enemy = registry.create();

    // step3: 添加組件
    // 使用 registry.emplace<ComponentType>(entity, args...) 方法為實體添加組件
    registry.emplace<Position>(player, 10.0f, 20.0f);
    registry.emplace<Velocity>(player, 1.0f, 0.0f);

    registry.emplace<Position>(enemy, 100.0f, 50.0f);

    // step4: 修改組件
    // 獲取組建的引用後，可以直接修改其值
    auto &player_pos = registry.get<Position>(player);
    spdlog::info("Player Position: ({}, {})", player_pos.x, player_pos.y);
    player_pos.x += 5.0f; // 移動玩家位置
    spdlog::info("Player New Position: ({}, {})", player_pos.x, player_pos.y);

    // step5: 移除組件
    // 使用 registry.remove<ComponentType>(entity) 方法移除組件
    registry.remove<Velocity>(player);

    // step6: 銷毀實體
    // 使用 registry.destroy(entity) 方法銷毀實體及其所有組件
    registry.destroy(enemy);

    // step7: 檢查實體是否存在
    if (registry.valid(player))
    {
        spdlog::info("Player entity is valid.");
    }
    if (!registry.valid(enemy))
    {
        spdlog::info("Enemy entity has been destroyed.");
    }
}