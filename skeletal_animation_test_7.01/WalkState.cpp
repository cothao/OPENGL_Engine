#include "WalkState.h"
#include "iostream"
#include "player.h"

WalkState::WalkState()
{
	std::cout << "Current State: Walking" << "\n";
};

State* WalkState::Input(Event event)
{

	switch (event)
	{
	case EFORWARD:
		std::cout << "Walk" << "\n";
        break;
    default:
        std::cout << "Exiting Walk..." << "\n";
        return new IdleState();
        break;
	};

};

void WalkState::Update(float Delta, Player* player)
{
    player->Direction = glm::vec3(cos(player->RotateY), sin(player->RotateY), 0.f);
    glm::vec3 right = glm::vec3(1, 0., 0.);
    glm::vec3 z = glm::vec3(0., 1., 0.);
    float xDot = glm::dot(player->Direction, right);
    float zDot = glm::dot(player->Direction, z);
    std::cout << player->Position.x << "\n";
    if (!player->IsCollision)
    {
        player->Position.x += (zDot * 2.0) * Delta;
        player->Position.z += (xDot * 2.0) * Delta;
    }
}