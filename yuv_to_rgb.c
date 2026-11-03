#include <stdint.h>

// 将 YUV 转换为 RGBA
void yuv_to_rgb(uint8_t *yBuffer, uint8_t *uvBuffer, uint8_t *rgba, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int yIndex = y * width + x;
            int uvIndex = (y / 2) * (width / 2) * 2 + (x / 2) * 2;

            uint8_t Y = yBuffer[yIndex];
            int16_t U = uvBuffer[uvIndex] - 128;
            int16_t V = uvBuffer[uvIndex + 1] - 128;

            int16_t R = Y + 1.402 * V;
            int16_t G = Y - 0.344136 * U - 0.714136 * V;
            int16_t B = Y + 1.772 * U;

            int rgbaIndex = yIndex * 4;
            rgba[rgbaIndex] = R < 0 ? 0 : (R > 255 ? 255 : R);
            rgba[rgbaIndex + 1] = G < 0 ? 0 : (G > 255 ? 255 : G);
            rgba[rgbaIndex + 2] = B < 0 ? 0 : (B > 255 ? 255 : B);
            rgba[rgbaIndex + 3] = 255; // Alpha
        }
    }
}

void yuv_to_rgb_resized(uint8_t *yBuffer, uint8_t *uvBuffer, uint8_t *rgba, int width, int height, int newWidth, int newHeight) {
    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            // 计算原图像的对应像素位置
            int origY = y * height / newHeight;
            int origX = x * width / newWidth;

            int yIndex = origY * width + origX;
            int uvIndex = (origY / 2) * (width / 2) * 2 + (origX / 2) * 2;

            uint8_t Y = yBuffer[yIndex];
            int16_t U = uvBuffer[uvIndex] - 128;
            int16_t V = uvBuffer[uvIndex + 1] - 128;

            int16_t R = Y + 1.402 * V;
            int16_t G = Y - 0.344136 * U - 0.714136 * V;
            int16_t B = Y + 1.772 * U;

            int rgbaIndex = y * newWidth * 4 + x * 4;
            rgba[rgbaIndex] = R < 0 ? 0 : (R > 255 ? 255 : R);
            rgba[rgbaIndex + 1] = G < 0 ? 0 : (G > 255 ? 255 : G);
            rgba[rgbaIndex + 2] = B < 0 ? 0 : (B > 255 ? 255 : B);
            rgba[rgbaIndex + 3] = 255; // Alpha
        }
    }
}
