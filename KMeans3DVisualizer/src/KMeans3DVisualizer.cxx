#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkScalarToRGBColormapImageFilter.h"

constexpr unsigned int Dimension = 3;
using PixelType = unsigned short;
using ImageType = itk::Image<PixelType, Dimension>;
using RGBPixelType = itk::RGBPixel<unsigned char>;
using RGBImageType = itk::Image<RGBPixelType, Dimension>;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0];
        std::cerr << " inputLabelMap outputColorImage" << std::endl;
        return EXIT_FAILURE;
    }

    const char *inputFilename = argv[1];
    const char *outputFilename = argv[2];

    // Read the label map
    using ReaderType = itk::ImageFileReader<ImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(inputFilename);

    // Create the colormap filter
    using ColormapFilterType = itk::ScalarToRGBColormapImageFilter<ImageType, RGBImageType>;
    ColormapFilterType::Pointer colormapFilter = ColormapFilterType::New();
    
    // Set the colormap to your preference (modify this part to suit your colormap choice)
    colormapFilter->SetColormap(itk::Hot);
    
    // Connect the input image
    colormapFilter->SetInput(reader->GetOutput());

    // Write the RGB output image
    using WriterType = itk::ImageFileWriter<RGBImageType>;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(outputFilename);
    writer->SetInput(colormapFilter->GetOutput());

    try
    {
        writer->Update();
    }
    catch (const itk::ExceptionObject &error)
    {
        std::cerr << "Error: " << error << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Output image saved as " << outputFilename << std::endl;

    return EXIT_SUCCESS;
}

