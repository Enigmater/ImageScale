#include "MyForm.h"
#include <vector>

System::Void ImageScale::MyForm::button_openImage_Click(System::Object^ sender, System::EventArgs^ e)
{
    // Создаем и показываем диалог выбора файла
    OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
    openFileDialog->Filter = "Изображения|*.image;*.jpg;*.jpeg;*.png;*.gif;*.tiff|Все файлы|*.*";
    openFileDialog->Title = "Выберите изображение";

    // Если пользователь выбрал файл, загружаем его
    if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        try {
            // Загружаем изображение по выбранному пути
            image = gcnew Bitmap(openFileDialog->FileName);
            startImage = gcnew Bitmap(image);
            panel_image->Invalidate(); // Перерисовываем groupBox, чтобы отобразить изображение
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка загрузки изображения: " + ex->Message);
        }
    }
}

System::Void ImageScale::MyForm::button_reset_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (startImage) {
        image = gcnew Bitmap(startImage);
        panel_image->Invalidate();
    }
}

System::Void ImageScale::MyForm::panel_image_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
    // Если изображение загружено, рисуем его на форме
    if (image != nullptr) {
        panel_image->Width = image->Width;
        panel_image->Height = image->Height;
        panel1->Width = image->Width;
        panel1->Height = image->Height;
        e->Graphics->DrawImage(image, 0, 0, panel_image->ClientSize.Width, panel_image->ClientSize.Height);
    }
}

System::Void ImageScale::MyForm::trackBar_kernelN_Scroll(System::Object^ sender, System::EventArgs^ e)
{
    label_kernel->Text = "N: " + trackBar_kernelN->Value;
}

System::Void ImageScale::MyForm::trackBar_sigma_Scroll(System::Object^ sender, System::EventArgs^ e)
{
    label_sigma->Text = "Sigma: " + (double)trackBar_sigma->Value / 100;
}

System::Void ImageScale::MyForm::button_gaussian_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (!startImage) return;

    int width = image->Width;
    int height = image->Height;
    Bitmap^ result = gcnew Bitmap(width, height);

    int filterSize = trackBar_kernelN->Value;
    double sigma = trackBar_sigma->Value / 100.0f;

    // Генерация ядра Гаусса
    std::vector<std::vector<double>> kernel(filterSize, std::vector<double>(filterSize, 0));
    double kernelSum = 0;
    int halfFilterSize = filterSize / 2;
    for (int y = -halfFilterSize; y <= halfFilterSize; y++) {
        for (int x = -halfFilterSize; x <= halfFilterSize; x++) {
            double value = exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * sigma * sigma);
            kernel[y + halfFilterSize][x + halfFilterSize] = value;
            kernelSum += value;
        }
    }

    // Нормализуем ядро
    for (int y = 0; y < filterSize; y++) {
        for (int x = 0; x < filterSize; x++) {
            kernel[y][x] /= kernelSum;
        }
    }

    // Применяем фильтр
    for (int y = halfFilterSize; y < height - halfFilterSize; y++) {
        for (int x = halfFilterSize; x < width - halfFilterSize; x++) {
            double rValue = 0;
            double gValue = 0;
            double bValue = 0;

            for (int ky = -halfFilterSize; ky <= halfFilterSize; ky++) {
                for (int kx = -halfFilterSize; kx <= halfFilterSize; kx++) {
                    Color pixelColor = image->GetPixel(x + kx, y + ky);
                    rValue += pixelColor.R * kernel[ky + halfFilterSize][kx + halfFilterSize];
                    gValue += pixelColor.G * kernel[ky + halfFilterSize][kx + halfFilterSize];
                    bValue += pixelColor.B * kernel[ky + halfFilterSize][kx + halfFilterSize];
                }
            }

            int r = std::min(std::max(rValue, 0.0), 255.0);
            int g = std::min(std::max(gValue, 0.0), 255.0);
            int b = std::min(std::max(bValue, 0.0), 255.0);

            result->SetPixel(x, y, Color::FromArgb(r, g, b));
        }
    }

    image = gcnew Bitmap(result);
    delete result;

    panel_image->Invalidate();
}

System::Void ImageScale::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
    label_sigma->Text = "Sigma: " + (double)trackBar_sigma->Value / 100;
    label_kernel->Text = "N: " + trackBar_kernelN->Value;
    label_scale->Text = "Scale: " + (double) trackBar_scale->Value / 10;
}

System::Void ImageScale::MyForm::trackBar_scale_Scroll(System::Object^ sender, System::EventArgs^ e)
{
    label_scale->Text = "Scale: " + (double)trackBar_scale->Value / 10;
}

System::Void ImageScale::MyForm::button_bilinear_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (!startImage) return;

    int width = image->Width;
    int height = image->Height;

    double scale = trackBar_scale->Value / 10.0f;

    int newWidth = (int)(width * scale);
    int newHeight = (int)(height * scale);

    Bitmap^ result = gcnew Bitmap(newWidth, newHeight);

    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            // Исходные координаты пикселя
            float gx = x / scale;
            float gy = y / scale;

            // Округляем для поиска ближайших соседей
            int x0 = (int)gx;
            int y0 = (int)gy;
            int x1 = Math::Min(x0 + 1, width - 1);
            int y1 = Math::Min(y0 + 1, height - 1);

            // Получаем цвета четырех ближайших пикселей
            Color c00 = image->GetPixel(x0, y0);
            Color c10 = image->GetPixel(x1, y0);
            Color c01 = image->GetPixel(x0, y1);
            Color c11 = image->GetPixel(x1, y1);

            // Вычисление нормализованных отклонений
            float tx = gx - x0;
            float ty = gy - y0;

            // Билинейная интерполяция для каждого канала (R, G, B)
            int r = (int)((1 - tx) * (1 - ty) * c00.R + tx * (1 - ty) * c10.R + (1 - tx) * ty * c01.R + tx * ty * c11.R);
            int g = (int)((1 - tx) * (1 - ty) * c00.G + tx * (1 - ty) * c10.G + (1 - tx) * ty * c01.G + tx * ty * c11.G);
            int b = (int)((1 - tx) * (1 - ty) * c00.B + tx * (1 - ty) * c10.B + (1 - tx) * ty * c01.B + tx * ty * c11.B);

            // Ограничиваем значение в пределах [0, 255]
            r = Math::Min(Math::Max(r, 0), 255);
            g = Math::Min(Math::Max(g, 0), 255);
            b = Math::Min(Math::Max(b, 0), 255);

            // Устанавливаем полученный цвет в новый пиксель
            result->SetPixel(x, y, Color::FromArgb(r, g, b));
        }
    }

    image = gcnew Bitmap(result);
    delete result;

    panel_image->Invalidate();
}

// Функция бикубической интерполяции для получения значения пикселя
System::Drawing::Color ImageScale::MyForm::BicubicInterpolation(float x, float y, Bitmap^ bitmap)
{
    int x0 = (int)x;
    int y0 = (int)y;

    // Используем управляемый массив для хранения пикселей
    array<array<Color>^>^ pixels = gcnew array<array<Color>^>(4);
    for (int i = 0; i < 4; ++i)
    {
        pixels[i] = gcnew array<Color>(4);
    }

    // Сбор пикселей (16 ближайших)
    for (int i = -1; i <= 2; ++i)
    {
        for (int j = -1; j <= 2; ++j)
        {
            int ix = Math::Min(Math::Max(x0 + i, 0), bitmap->Width - 1);
            int iy = Math::Min(Math::Max(y0 + j, 0), bitmap->Height - 1);
            pixels[i + 1][j + 1] = bitmap->GetPixel(ix, iy);
        }
    }

    // Интерполяция по X для каждого цвета
    float rx[4], gx[4], bx[4];
    for (int i = 0; i < 4; ++i)
    {
        rx[i] = CubicInterpolate(pixels[i][0].R, pixels[i][1].R, pixels[i][2].R, pixels[i][3].R, x - x0);
        gx[i] = CubicInterpolate(pixels[i][0].G, pixels[i][1].G, pixels[i][2].G, pixels[i][3].G, x - x0);
        bx[i] = CubicInterpolate(pixels[i][0].B, pixels[i][1].B, pixels[i][2].B, pixels[i][3].B, x - x0);
    }

    // Интерполяция по Y для каждого цвета
    int r = (int)CubicInterpolate(rx[0], rx[1], rx[2], rx[3], y - y0);
    int g = (int)CubicInterpolate(gx[0], gx[1], gx[2], gx[3], y - y0);
    int b = (int)CubicInterpolate(bx[0], bx[1], bx[2], bx[3], y - y0);

    // Ограничиваем значение в пределах [0, 255]
    r = Math::Min(Math::Max(r, 0), 255);
    g = Math::Min(Math::Max(g, 0), 255);
    b = Math::Min(Math::Max(b, 0), 255);

    return Color::FromArgb(r, g, b);
}

// Кубическая интерполяция для одного измерения
float ImageScale::MyForm::CubicInterpolate(float p0, float p1, float p2, float p3, float t)
{
    float a0, a1, a2, a3, t2, t3;

    t2 = t * t;
    t3 = t2 * t;

    a0 = -0.5f * p0 + 1.5f * p1 - 1.5f * p2 + 0.5f * p3;
    a1 = p0 - 2.5f * p1 + 2.0f * p2 - 0.5f * p3;
    a2 = -0.5f * p0 + 0.5f * p2;
    a3 = p1;

    return a0 * t3 + a1 * t2 + a2 * t + a3;
}

System::Void ImageScale::MyForm::button_bicubic_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (!startImage) return;

    int width = image->Width;
    int height = image->Height;

    double scale = trackBar_scale->Value / 10.0f;

    int newWidth = (int)(width * scale);
    int newHeight = (int)(height * scale);

    Bitmap^ result = gcnew Bitmap(newWidth, newHeight);

    // Применяем бикубическую интерполяцию для масштабирования
    for (int y = 0; y < newHeight; y++)
    {
        for (int x = 0; x < newWidth; x++)
        {
            // Находим соответствующие координаты в исходном изображении
            double srcX = x / scale;
            double srcY = y / scale;

            // Вычисляем значение пикселя на основе бикубической интерполяции
            Color interpolatedColor = BicubicInterpolation(srcX, srcY, image);

            // Устанавливаем цвет пикселя на новое изображение
            result->SetPixel(x, y, interpolatedColor);
        }
    }


    image = gcnew Bitmap(result);
    delete result;

    panel_image->Invalidate();
}

