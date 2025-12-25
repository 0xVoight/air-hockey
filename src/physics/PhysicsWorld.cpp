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

    // Функция затухания скорости
    auto applyPhysicsSettings = [&](Vec2& vel, float massFactor) {
        float speed = glm::length(vel);
        if (speed > 0.001f) {
            float drag = (m_friction * speed + (m_friction * 0.5f) * speed * speed) * massFactor;
            float newSpeed = std::max(0.0f, speed - drag * fDt);
            vel = glm::normalize(vel) * newSpeed;
        } else {
            vel = Vec2(0.0f);
        }
    };

    applyPhysicsSettings(world.puck.velocity, 1.0f);

    world.puck.position += world.puck.velocity * fDt;
    world.leftPaddle.position += world.leftPaddle.velocity * fDt;
    world.rightPaddle.position += world.rightPaddle.velocity * fDt;
}

void PhysicsWorld::handleCollisions(World& world)
{
    auto handlePuckPaddleCollision = [&](Paddle& paddle) {
        Vec2& puckPos = world.puck.position;
        Vec2& puckVel = world.puck.velocity;

        Vec2 delta = puckPos - paddle.position;
        float distSq = glm::dot(delta, delta);
        float rSum = world.puck.radius + paddle.radius;

        if (distSq < rSum * rSum) {
            float dist = std::sqrt(distSq);
            if (dist < 1e-4f) dist = 1e-4f;
            Vec2 normal = delta / dist;

            puckPos += normal * (rSum - dist);

            Vec2 relativeVelocity = puckVel - paddle.velocity;
            float velAlongNormal = glm::dot(relativeVelocity, normal);

            if (velAlongNormal < 0) {
                float j = -(1.0f + m_restitution) * velAlongNormal;
                puckVel += (j * normal) + (paddle.velocity * m_paddleInfluence);
            }

            if (glm::length(puckVel) > m_maxPuckSpeed) {
                puckVel = glm::normalize(puckVel) * m_maxPuckSpeed;
            }
        }
    };

    handlePuckPaddleCollision(world.leftPaddle);
    handlePuckPaddleCollision(world.rightPaddle);

    const auto& rink = world.rink;
    const float r = world.puck.radius;

    // Горизонтальные борта
    if (world.puck.position.x - r < rink.left) {
        world.puck.position.x = rink.left + r;
        world.puck.velocity.x = std::abs(world.puck.velocity.x) * m_restitution;
    }
    else if (world.puck.position.x + r > rink.right) {
        world.puck.position.x = rink.right - r;
        world.puck.velocity.x = -std::abs(world.puck.velocity.x) * m_restitution;
    }

    // Вертикальные борта
    if (world.puck.position.y - r < rink.bottom) {
        world.puck.position.y = rink.bottom + r;
        world.puck.velocity.y = std::abs(world.puck.velocity.y) * m_restitution;
    }
    else if (world.puck.position.y + r > rink.top) {
        world.puck.position.y = rink.top - r;
        world.puck.velocity.y = -std::abs(world.puck.velocity.y) * m_restitution;
    }
}

void PhysicsWorld::processPaddleMovement(Paddle &paddle, const PlayerInput &pInput, const Rink &rink, bool isLeft, float dt)
{
    Vec2 dir{0.f, 0.f};

    if(pInput.up)    dir.y += 1.f;
    if(pInput.down)  dir.y -= 1.f;
    if(pInput.left)  dir.x -= 1.f;
    if(pInput.right) dir.x += 1.f;

    if (glm::length(dir) > 0.0001f) {
        paddle.velocity = glm::normalize(dir) * m_paddleSpeed;
    } else {
        paddle.velocity = Vec2(0.0f);
    }

    //paddle.position += paddle.velocity * dt;

    // Расчет границ
    const float r = paddle.radius;

    // Y-границы
    paddle.position.y = glm::clamp(paddle.position.y, rink.bottom + r, rink.top - r);

    // X-границы
    if (isLeft) {
        paddle.position.x = glm::clamp(paddle.position.x, rink.left + r, 0.0f - r);
    } else {
        paddle.position.x = glm::clamp(paddle.position.x, 0.0f + r, rink.right - r);
    }
}

void PhysicsWorld::applyPlayerInput(World &world, const InputState &input, double dt)
{
    const float fDt = static_cast<float>(dt);

    processPaddleMovement(world.leftPaddle, input.player1, world.rink, true, fDt);
    processPaddleMovement(world.rightPaddle, input.player2, world.rink, false, fDt);
}

