#ifndef MODEL_H
#define MODEL_H

#define MAX_NUM_BONES_PER_VERTEX 4

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "assimpglmhelpers.h"
#include "shader.h"
#include "mesh.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "animdata.h"
// ANIMATION_H BUG HERE

using uint = unsigned int;

unsigned int TextureFromFile(const char* path, const string& directory, bool flip, bool gamma = false);

unsigned int TextureFromData(unsigned char* data, int width, int height, int nrComponents, bool flip);

class Model
{
public:
    // model data 
    std::map<string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;
    vector<Texture>     textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>        meshes;
    string              directory;
    bool                flip;
    bool                gammaCorrection;
    static inline int   id_generator{ 0 };
    int                 ID{};
    float				RotateX = 0.0;
    float				RotateY = 0.0;
    float				RotateZ = 0.0;
    float               Yaw = 0.0;
    glm::vec3			Scale;
    glm::vec3			Position;
    glm::vec3			LightPosition;
    glm::vec3			RotateDirX = glm::vec3(1., 0., 0.);
    glm::vec3			RotateDirY = glm::vec3(0., 1., 0.);
    glm::vec3			RotateDirZ = glm::vec3(0., 0., 1.);
    glm::vec3           Up = glm::vec3(0., 1., 0.);
    glm::vec3           Right = glm::vec3(1., 0., 0.);
    glm::vec3           Color = glm::vec3(1.);
    glm::vec3           Direction = glm::vec3(cos(RotateY), sin(RotateY), 0.f);
    float               xDot = glm::dot(Direction, Right);
    float               zDot = glm::dot(Direction, Up);

    Model();

    // constructor, expects a filepath to a 3D model.
    Model(string const& path, bool flip = true, glm::vec3 pos = glm::vec3(1.0), glm::vec3 scale = glm::vec3(1.0), bool gamma = false);


    // draws the model, and thus all its meshes
    void Draw(Shader& shader, glm::mat4 projection, glm::mat4 view, glm::vec3 camera, glm::vec3 lightPos);

    std::string getPosition();
    auto& GetBoneInfoMap() { return m_BoneInfoMap; }
    int& GetBoneCount() { return m_BoneCounter; }

protected:
    //loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const& path);

    //processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);


    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    //checks all material textures of a given type and loads the textures if they're not loaded yet.
    //the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const aiScene* scene, string typeName);


    
    void SetVertexBoneDataToDefault(Vertex& vertex);

    void SetVertexBoneData(Vertex& vertex, int boneID, float weight);

    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);

};
#endif