#ifndef Film_H
#define Film_H

#include "../pbrt.hpp"
#include "../Filter/MitchellFilter.hpp"
#include "../Filter/GaussianFilter.hpp"

using namespace Eigen;

struct Pixel
{
    float pixelWeightSum = 0;
    Vector3f contribuSum = Vector3f(0, 0, 0);
};

class Film
{
private:
    /* data */
public:
    Film() = default;
    Film(Vector2i resolution, const std::string &fileName, std::shared_ptr<Filter> filter);
    ~Film();

    void addContribution(Vector2f pFilm, Vector3f radiance, float sampleWeight);
    void imageColor();
    Pixel *getPixel(const int &row, const int &col);

    std::string fileName;
    Vector2i fullResolution;
    std::vector<Vector3f> filmColor;
    std::shared_ptr<Filter> filter;

    std::vector<Pixel> pixels;
    float filterTable[filterTableWidth * filterTableWidth];
};

#endif