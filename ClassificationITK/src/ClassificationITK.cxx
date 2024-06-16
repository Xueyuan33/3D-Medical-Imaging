


#include <iostream>
#include <string>
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkOtsuThresholdImageFilter.h>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_image_path> <output_image_path>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputImagePath = argv[1];
    std::string outputImagePath = argv[2];

    // Define the image types
    using InputImageType = itk::Image<short, 3>;
    using OutputImageType = itk::Image<unsigned char, 3>;

    // Define the reader for the input image
    using ReaderType = itk::ImageFileReader<InputImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(inputImagePath);
    reader->Update();

    // Create the Otsu threshold filter
    using OtsuFilterType = itk::OtsuThresholdImageFilter<InputImageType, OutputImageType>;
    OtsuFilterType::Pointer otsuFilter = OtsuFilterType::New();
    otsuFilter->SetInput(reader->GetOutput());
    otsuFilter->SetNumberOfHistogramBins(5); // Set the number of histogram bins

    // Update the Otsu filter
    otsuFilter->Update();

    // Get the Otsu binary labels image
    OutputImageType::Pointer otsuLabels = otsuFilter->GetOutput();

    // Write the Otsu binary labels image to the specified output file path
    using WriterType = itk::ImageFileWriter<OutputImageType>;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName(outputImagePath);
    writer->SetInput(otsuLabels);
    writer->Update();

    return EXIT_SUCCESS;
}
