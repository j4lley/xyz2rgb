#include <cstdio>
#include <cmath>
#include "FreeImage.h"

typedef char byte;
typedef unsigned int uint;

inline float Clamp(float v, float a, float b)
{
    float c = fmax(a, v);
    return fmin(c, b);
}

inline void XYZToRGB(const float xyz[3], float rgb[3]) { 
	rgb[0] =  3.240479f*xyz[0] - 1.537150f*xyz[1] - 0.498535f*xyz[2]; 
	rgb[1] = -0.969256f*xyz[0] + 1.875991f*xyz[1] + 0.041556f*xyz[2]; 
	rgb[2] =  0.055648f*xyz[0] - 0.204043f*xyz[1] + 1.057311f*xyz[2]; 
} 
 
inline void RGBToXYZ(const float rgb[3], float xyz[3]) { 
	xyz[0] = 0.412453f*rgb[0] + 0.357580f*rgb[1] + 0.180423f*rgb[2]; 
	xyz[1] = 0.212671f*rgb[0] + 0.715160f*rgb[1] + 0.072169f*rgb[2]; 
	xyz[2] = 0.019334f*rgb[0] + 0.119193f*rgb[1] + 0.950227f*rgb[2]; 
} 

int main(int argc, char** argv)
{
    const char* fi_version = FreeImage_GetVersion();
    printf("xyz2rgb: using FreeImage version %s\n", fi_version);
    printf("xyz2rgb: input image: %s\n", argv[1]);
    printf("xyz2rgb: output image: %s\n", argv[2]);

    FIBITMAP* fi_bitmap = 0;
    fi_bitmap = FreeImage_Load(FIF_EXR, argv[1]);

    uint fi_width = FreeImage_GetWidth(fi_bitmap);
    uint fi_height = FreeImage_GetHeight(fi_bitmap);
    uint fi_bpp = FreeImage_GetBPP(fi_bitmap);
    uint fi_pitch = FreeImage_GetPitch(fi_bitmap);
    printf("xyz2rgb: image resolution: %d x %d (bpp: %d, pitch: %d)\n", fi_width, fi_height, fi_bpp, fi_pitch);

    byte* pBits = (byte*) FreeImage_GetBits(fi_bitmap);

    uint h_offset = (fi_bpp == 96)? 3 : 4;
    uint h_offset_output = (24 == 24)? 3 : 4;

    // do image processing (e.g. xyz to rgb conversion)
    for (int y = 0; y < fi_height; y++)
    {
        float *pPixel = reinterpret_cast<float*>(pBits);
        for (int x = 0; x < fi_width; x++)
        {
            float rgb[3] = { 0.f, 0.f, 0.f };
            float xyz[3] = { pPixel[0], pPixel[1], pPixel[2] };
            XYZToRGB(xyz, &(rgb[0]));
#if 1
            pPixel[0] = Clamp(1.0f - expf(-(rgb[0] * 1/*0.25f*/)), 0.0f, 1000.0f);
	    pPixel[1] = Clamp(1.0f - expf(-(rgb[1] * 1/*0.25f*/)), 0.0f, 1000.0f);
            pPixel[2] = Clamp(1.0f - expf(-(rgb[2] * 1/*0.25f*/)), 0.0f, 1000.0f);
#endif
            pPixel += h_offset;
        }
        pBits += fi_pitch;
    }

    FreeImage_Save(FIF_EXR, fi_bitmap, argv[2]);

    FreeImage_Unload(fi_bitmap);
    return 0;
}