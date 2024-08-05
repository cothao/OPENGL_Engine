#include "engine.h"
#include "vector_direction.h"

Engine::Engine()
{

}

int Engine::initEngine()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    this->window = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT, "Graphics Engine", NULL, NULL);

    if (this->window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
}

void Engine::initObjects()
{

    std::string playerPath = "./assets/player_gun_idle/player_gun_idle.fbx";
    //std::string playerPath = "./assets/player/player.fbx";

    this->shaderDirectory["pShader"] = Shader("./pShader.vs", "./pShader.fs");
    this->shaderDirectory["lShader"] = Shader("./lightShader.vs", "./lightShader.fs");
    this->shaderDirectory["mShader"] = Shader("./modelShader.vs", "./modelShader.fs");

    // Player here
    pObject = *new Player("./assets/player_gun_run/player_gun.fbx", false, glm::vec3(1., 0.0, 4.0), glm::vec3(0.005));

    // Lights here
    this->lights = { *new Light(this->shaderDirectory["lShader"], glm::vec3(6., 2., 3.)) };

    // Models here
    this->models = 
    {
        //*new Model("./assets/donut2/donut.fbx", false, glm::vec3(1., 0.0, 4.0), glm::vec3(5.)),
        *new Model("./assets/test_objs/goblin.fbx", false, glm::vec3(0., 0.0, 0.0), glm::vec3(0.005)),
    };
    // Objects here

    // Planes here
    this->planes = { *new Plane(this->shaderDirectory["pShader"])};
    
    this->Animations = 
    { 
        *new Animation("./assets/player_gun_run/player_idle.fbx", &this->pObject),
        *new Animation("./assets/player_gun_run/player_gun.fbx", &this->pObject),
        *new Animation("./assets/test_objs/goblin.fbx", &this->models[0])
    };
    this->Animators = 
    {
        *new Animator(&this->Animations[0]),
        *new Animator(&this->Animations[1]),
        *new Animator(&this->Animations[2]),
    };

}

void Engine::render(float DeltaTime)
{

    if (this->State == EDIT)
    {

        for (Animator& animator : this->Animators)
        {
            animator.UpdateAnimation(DeltaTime);
        }

        this->projection = glm::perspective(glm::radians(this->camera.Zoom), (float)this->SCR_WIDTH / (float)this->SCR_HEIGHT, 0.1f, 100.f);
        this->view = this->camera.GetViewMatrix();

        for (Light &light : this->lights)
        {
            light.render(this->projection, this->view, glm::vec3(0.3), glm::vec3(6., 0.8, sin(glfwGetTime())), 0.0, glm::vec3(1., 0., 0.), glm::vec3(1., 1., 1.));
        }

        for (Cube &cube : this->cubes)
        {
            cube.render(this->projection, this->view, this->camera.Position, this->lights[0].pos);
        }

        for (Plane plane : this->planes)
        {
            plane.render(this->projection, this->view, glm::vec3(10.0), glm::vec3(1., -5., 1.), 90.0, glm::vec3(1., 0., 0.), glm::vec3(0.8, 0.8, 0.8), this->lights[0].pos, this->camera.Position);
        }

        this->shaderDirectory["mShader"].use();

        auto transforms = this->Animators[2].GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i)
        {
            this->shaderDirectory["mShader"].setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
        }

        for (Model model : this->models)
        {

            model.Draw(this->shaderDirectory["mShader"], this->projection, this->view, this->camera.Position, this->lights[0].pos);

        }
        std::cout << pObject.ActiveState->st << "\n";
        pObject.ActiveState->Update(DeltaTime, &pObject);

         //this stays here until I figure out how to put it into the draw function

        //transforms = this->Animators[pObject.player_state].GetFinalBoneMatrices();
        //for (int i = 0; i < transforms.size(); ++i)
        //{
        //    this->shaderdirectory["mshader"].setmat4("finalbonesmatrices[" + std::to_string(i) + "]", transforms[i]);
        //}

        pObject.Draw(this->shaderDirectory["mShader"], this->projection, this->view, this->camera.Position, this->lights[0].pos);

    }

    camera.Position.x = pObject.Position.x;
    camera.Position.z = pObject.Position.z;
    camera.Position.y = pObject.Position.y + 10.;

}

void Engine::keyInputs(float DeltaTime, bool& IsEditing)
{
    if (this->Keys[GLFW_KEY_E]) {
        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        IsEditing = true;
    }

    if (this->Keys[GLFW_KEY_R])
    {
        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        IsEditing = false;
    }

    if (this->Keys[GLFW_KEY_W])
    {
        if (!IsEditing)
        {
            camera.ProcessKeyboard(FORWARD, DeltaTime);
        }

        for (Cube cube : cubes)
        {
            if (this->pObject.handleCollision(cube))
            {

                Direction dir = VectorDirection(glm::vec2(this->pObject.Direction.x, this->pObject.Direction.y));

                if (dir == TOP || dir == RSIDE)
                {
                this->pObject.Position.x -= 0.2;
                this->pObject.Position.z -= 0.2;
                }
                else if (dir == BOTTOM || dir == LSIDE)
                {
                    this->pObject.Position.x += 0.2;
                    this->pObject.Position.z += 0.2;

                }

                break;
            }
        }
    }

    if (this->Keys[GLFW_KEY_S])
    {
        if (!IsEditing)
        {
            camera.ProcessKeyboard(BACKWARD, DeltaTime);
        }
    }

    if (this->Keys[GLFW_KEY_A])
    {
        if (!IsEditing)
        {
            camera.ProcessKeyboard(LEFT, DeltaTime);
        }
    }

    if (this->Keys[GLFW_KEY_D])
    {
        if (!IsEditing)
        {
            camera.ProcessKeyboard(RIGHT, DeltaTime);

        }
    }

    if (this->Keys[GLFW_KEY_ESCAPE])
    {
        glfwSetWindowShouldClose(window, true);
    }

}

void Engine::processInputs(float DeltaTime, bool &IsEditing)
{
    this->pObject.handleInput(DeltaTime, IsEditing);
    this->keyInputs(DeltaTime, IsEditing);
}