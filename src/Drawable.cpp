
#include "Drawable.hpp"

std::vector<Point> Drawable::getDrawablePoints() {
    Image* img = this->getGameObject()->getCurrentFrame();
    int h = img->getHeight();
    int w = img->getWidth();
    std::vector<Point> out(w * h);
    int p=0;
    for (int i=0; i< w; i++) {
        for (int j=0; j< h; j++) {
            int pixel = img->getPixel(i,j);
            int a = (pixel >> 24) & 0xFF;
            if (a != 0) {
                Point ponto;
                ponto.x = i;
                ponto.y = j;
                out[p] = ponto;
                p++;
            }
        }
    }
    return out;
}
