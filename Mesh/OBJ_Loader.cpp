#include "OBJ_Loader.hpp"

Loader::Loader(const std::string &_fileName) : fileName(_fileName)
{
    std::ifstream is(fileName);
    std::string line;

    while (std::getline(is, line))
    {
        std::stringstream lstream(line);
        std::string word;
        lstream >> word;

        if (word == "v")
        {
            Vector3f tmpPos;
            lstream >> tmpPos.x() >> tmpPos.y() >> tmpPos.z();
            pos.push_back(tmpPos);
        }
        else if (word == "vn")
        {
            hasNorm = true;

            Vector3f tmpNorm;
            lstream >> tmpNorm.x() >> tmpNorm.y() >> tmpNorm.z();
            tmpNorm.normalize();
            norm.push_back(tmpNorm);
        }
        else if (word == "vt")
        {
            hasUv = true;

            Vector2f tmpUv;
            lstream >> tmpUv.x() >> tmpUv.y();
            uv.push_back(tmpUv);
        }
        else if (word == "f")
        {
            while (lstream >> word)
            {
                if (!hasNorm)
                {
                    int posId = std::stoi(word);

                    posIndex.push_back(posId);
                }

                else
                {
                    size_t fPos = word.find_first_not_of("0123456789");
                    size_t lPos = word.find_last_not_of("0123456789");

                    int posId, normId, uvId;

                    posId = std::stoi(word.substr(0, fPos));
                    if (fPos + 1 != lPos)
                    {
                        uvId = std::stoi(word.substr(fPos + 1, lPos - fPos - 1));
                    }
                    normId = std::stoi(word.substr(lPos + 1));

                    posIndex.push_back(posId);
                    if (fPos + 1 != lPos)
                    {
                        uvIndex.push_back(uvId);
                    }
                    normIndex.push_back(normId);
                }
            }
        }
    }
}

Loader::~Loader()
{
}

void Loader::CreateTriangleMesh(std::shared_ptr<TriangleMesh> &mesh)
{
    if (hasNorm == true && hasUv == true)
    {
        mesh = std::make_shared<TriangleMesh>(posIndex.size() / 3, pos, norm, uv, posIndex, normIndex, uvIndex);
    }
    else if (hasNorm == true)
    {
        mesh = std::make_shared<TriangleMesh>(posIndex.size() / 3, pos, norm, posIndex, normIndex);
    }
    else
    {
        mesh = std::make_shared<TriangleMesh>(posIndex.size() / 3, pos, posIndex);
    }
    return;
}
