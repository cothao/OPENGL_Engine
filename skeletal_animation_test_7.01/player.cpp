#include "player.h"

Player::Player()
    :Model()
{

}

Player::Player(string const& path, bool flip, glm::vec3 pos, glm::vec3 scale, bool gamma)
    :
    Model(path, flip, pos, scale, gamma)
{
    loadModel(path);
    std::cout << this->ID << "\n";
};

void Player::handleInput(float DeltaTime, bool& IsEditing)
{



    if (this->Keys[GLFW_KEY_W])
    {

        ActiveState->Input(EFORWARD);
        if (IsEditing)
        {
            //player_state = WALK;
            //Direction = glm::vec3(cos(this->RotateY), sin(this->RotateY), 0.f);
            //glm::vec3 right = glm::vec3(1, 0., 0.);
            //glm::vec3 z = glm::vec3(0., 1., 0.);
            //float xDot = glm::dot(Direction, right);
            //float zDot = glm::dot(Direction, z);

            //if (!IsCollision)
            //{
            //    this->Position.x += (zDot * 2.0) * DeltaTime;
            //    this->Position.z += (xDot * 2.0) * DeltaTime;
            //}
        }
    }

    if (this->Keys[GLFW_KEY_A])
    {
        ActiveState->Input(EIDLE);

        if (IsEditing)
        {
            this->RotateY += 3.0f * DeltaTime;
        }
    }
    if (this->Keys[GLFW_KEY_D])
    {
        if (IsEditing)
        {
            this->RotateY -= 3.0f * DeltaTime;
        }

    }
}

void Player::handleMouseInput(float DeltaTime, bool& isEditing)
{

}

bool Player::handleCollision(Cube cube)
{
        return 
            (
            cube.Position.x + .5 >= this->Position.x - .1 &&
            cube.Position.x - .5 <= this->Position.x + .1 &&
            //cube.Position.y + cube.Scale.y >= this->Position.y &&
            //cube.Position.y <= this->Position.y + this->Scale.y &&
            cube.Position.z + .5 >= this->Position.z - .1 &&
            cube.Position.z - .5 <= this->Position.z + .1 
            );
}