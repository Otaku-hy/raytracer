#include "Film.hpp"

float filterTable[filterTableWidth * filterTableWidth];

Film::Film(Vector2i resolution, const std::string &fileName, std::shared_ptr<Filter> filter) : fullResolution(resolution), filmColor(fullResolution[0] * fullResolution[1]), pixels(fullResolution[0] * fullResolution[1]), filter(filter), fileName(fileName)
{
    for (int i = 0; i < filterTableWidth; i++)
    {
        for (int j = 0; j < filterTableWidth; j++)
        {
            Vector2f p;
            p[0] = (i + 0.5f) * filter->radius[0] / float(filterTableWidth);
            p[1] = (j + 0.5f) * filter->radius[1] / float(filterTableWidth);
            filterTable[j * filterTableWidth + i] = filter->Evaluate(p);
        }
    }
}

Pixel *Film::getPixel(const int &row, const int &col)
{
    return &pixels[row * fullResolution[0] + col];
}

void Film::addContribution(Vector2f pFilm, Vector3f radiance, float sampleWeight)
{
    Vector2f pOffset = pFilm - Vector2f(0.5, 0.5);
    Vector2f p0 = Ceil(pOffset - filter->radius);
    Vector2f p1 = Floor(pOffset + filter->radius) + Vector2f(1, 1);

    p0 = max(p0, Vector2f(0, 0));
    p1 = min(p1, Vector2f(fullResolution[0], fullResolution[1]));

    int itx[filterTableWidth];
    int ity[filterTableWidth];

    for (int i = p0.x(); i < p1.x(); i++)
    {
        float tx = std::abs(pOffset[0] - i) / filter->radius[0] * filterTableWidth;
        tx = std::min(tx, float(filterTableWidth - 1));
        itx[i - int(p0.x())] = tx;
    }

    for (int j = p0.y(); j < p1.y(); j++)
    {
        float ty = std::abs(pOffset[1] - j) / filter->radius[1] * filterTableWidth;
        ty = std::min(ty, float(filterTableWidth - 1));
        ity[j - int(p0.y())] = ty;
    }

    for (int i = p0.x(); i < p1.x(); i++)
    {
        for (int j = p0.y(); j < p1.y(); j++)
        {
            Vector2f samplePos = pOffset - Vector2f(i, j);
            Pixel *pixel = getPixel(j, i);
            float weight = filterTable[(j - int(p0.y())) * filterTableWidth + i - int(p0.x())];

            pixel->pixelWeightSum += weight;
            pixel->contribuSum += radiance * weight;
        }
    }
}

void Film::imageColor()
{
    for (int j = 0; j < fullResolution[1]; ++j)
    {
        for (int i = 0; i < fullResolution[0]; ++i)
        {
            Pixel *pixel = getPixel(j, i);
            Vector3f value = pixel->contribuSum / pixel->pixelWeightSum;
            value = Clamp(value, Vector3f(0, 0, 0));
            if (pixel->pixelWeightSum == 0)
            {
                filmColor[j * fullResolution[0] + i] = Vector3f(0, 0, 0);
            }
            else
            {
                filmColor[j * fullResolution[0] + i] = value;
            }
        }
    }

    std::ofstream out(fileName);
    out << "P3\n"
        << fullResolution[0] << ' ' << fullResolution[1] << "\n255\n";

    for (int j = 0; j < fullResolution[1]; ++j)
    {
        for (int i = 0; i < fullResolution[0]; ++i)
        {
            // gamma_correct(screen[i][height - 1 - j]);
            int ir = std::min(std::max(static_cast<int>(255.999 * filmColor[(fullResolution[1] - 1 - j) * fullResolution[0] + i].x()), 0), 255);
            int ig = std::min(std::max(static_cast<int>(255.999 * filmColor[(fullResolution[1] - 1 - j) * fullResolution[0] + i].y()), 0), 255);
            int ib = std::min(std::max(static_cast<int>(255.999 * filmColor[(fullResolution[1] - 1 - j) * fullResolution[0] + i].z()), 0), 255);

            out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}

Film::~Film()
{
}
