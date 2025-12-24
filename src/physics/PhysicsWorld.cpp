#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld() = default;

void PhysicsWorld::simulate(World& world, double dt)
{
    moveObjects(world, dt);
    handleCollisions(world);
}

void PhysicsWorld::moveObjects(World& world, double dt)
{
    const float fDt = static_cast<float>(dt);
    const float frictionFactor = 1.0f - m_friction;

    world.puck.position += world.puck.velocity * fDt;
    world.leftPaddle.position += world.leftPaddle.velocity * fDt;
    world.rightPaddle.position += world.rightPaddle.velocity * fDt;

    world.puck.velocity *= frictionFactor;
    world.leftPaddle.velocity *= frictionFactor;
    world.rightPaddle.velocity *= frictionFactor;
}

void PhysicsWorld::handleCollisions(World& world)
{
    // шайба и борта
    if (world.puck.position.x - world.puck.radius < world.rink.left ||
        world.puck.position.x + world.puck.radius > world.rink.right) {
        world.puck.velocity.x = -world.puck.velocity.x * m_restitution;
        // корректируем позицию
        if (world.puck.position.x - world.puck.radius < world.rink.left)
            world.puck.position.x = world.rink.left + world.puck.radius;
        else
            world.puck.position.x = world.rink.right - world.puck.radius;
    }

    if (world.puck.position.y - world.puck.radius < world.rink.bottom ||
        world.puck.position.y + world.puck.radius > world.rink.top) {
        world.puck.velocity.y = -world.puck.velocity.y * m_restitution;
        if (world.puck.position.y - world.puck.radius < world.rink.bottom)
            world.puck.position.y = world.rink.bottom + world.puck.radius;
        else
            world.puck.position.y = world.rink.top - world.puck.radius;
    }

    auto handleCircleCollision = [this](Vec2& pos1, Vec2& vel1, const Vec2& pos2, float r1, float r2) {
        Vec2 delta = pos1 - pos2;
        float distSq = glm::dot(delta, delta);
        float rSum = r1 + r2;

        if (distSq < rSum * rSum) {
            float dist = std::sqrt(distSq);
            if (dist < 1e-4f) dist = 1e-4f;

            Vec2 normal = delta / dist;
            float overlap = rSum - dist;

            pos1 += normal * overlap;

            float dotProduct = glm::dot(vel1, normal);
            if (dotProduct < 0) {
                vel1 = (vel1 - 2.0f * dotProduct * normal) * m_restitution;
            }
        }
    };

    handleCircleCollision(world.puck.position, world.puck.velocity, world.leftPaddle.position, world.puck.radius, world.leftPaddle.radius);
    handleCircleCollision(world.puck.position, world.puck.velocity, world.rightPaddle.position, world.puck.radius, world.rightPaddle.radius);
}

void PhysicsWorld::processPaddleMovement(Paddle &paddle, const PlayerInput &pInput, const Rink &rink, bool isLeft, float dt)
{
    const float speed = 1.0f;
    Vec2 dir{0.f, 0.f};

    if(pInput.up)    dir.y += 1.f;
    if(pInput.down)  dir.y -= 1.f;
    if(pInput.left)  dir.x -= 1.f;
    if(pInput.right) dir.x += 1.f;

    if (glm::length(dir) > 0.0001f) {
        paddle.velocity = glm::normalize(dir) * speed;
    } else {
        paddle.velocity = Vec2(0.0f);
    }

    paddle.position += paddle.velocity * dt;

    // Расчет границ (Clamping)
    const float r = paddle.radius;

    // Y-границы одинаковы для всех
    paddle.position.y = glm::clamp(paddle.position.y, rink.bottom + r, rink.top - r);

    // X-границы зависят от стороны
    if (isLeft) {
        paddle.position.x = glm::clamp(paddle.position.x, rink.left + r, 0.0f - r);
    } else {
        paddle.position.x = glm::clamp(paddle.position.x, 0.0f + r, rink.right - r);
    }
}

void PhysicsWorld::applyPlayerInput(World &world, const InputState &input, double dt)
{
    const float fDt = static_cast<float>(dt);

    // Обрабатываем обе ракетки независимо
    processPaddleMovement(world.leftPaddle, input.player1, world.rink, true, fDt);
    processPaddleMovement(world.rightPaddle, input.player2, world.rink, false, fDt);
}

