#pragma once
#include "App_Impl.h"
#include "../Directory/IDirectory.h"
#include "../Directory/Directory_Impl.h"
#include "../Directory/DirectoryHandler.h"
#include "../Encoders/IVideoEncoder.h"
#include "../Encoders/h256_Impl.h"
#include "../PixelExtractor/PixelExtractor.h"
#include "../FileDispencer.h"
#include "../FileChunkDispencer.h"
#include "../File/IFile.h"
#include "../RawImage/RawImage.h"
#include "../RawImage/IRawImageConverter.h"
#include "../RawImage/RawToPngConverter_Impl.h"
#include "../Vectors/Vectors.h"

namespace WAL::Apps
{
    AppImplementation::~AppImplementation()
    {
        delete this->dir;
        delete this->encoder;
        delete this->pixelExtractor;
        delete this->chunkDispencer;
        delete this->rawImageConverter;
        delete this->fileDispencer;
    }

    void AppImplementation::Run()
    {
        //extract one pixel, moprh to 1 rawImage, send rawImage to encoder, repeat until isNextPixel() is true
        while (isNextPixel())
        {
            this->ExtractNextPixel();
            this->SavePixel();
            this->ConvertImage();
            this->AddImageToEncoder();
        }
        std::string path = "C:\\Users\\leon2\\Desktop\\Garbage";
        this->SaveVideoFile(path);

        //OLD for each file extract enough pixels to fill one frame with defined resolution, then send it to encoder for handle it as one frame.
    }

    void AppImplementation::Init()
    {
        

        InitDirectory();
        
        const Resolution_t directoryRes = GetDirectoryResolution();

        InitFileDispencer();
        //InitChunkDispencer();

        const size_t fileChunkSize = this->CalculateFileChunkSize();
        const Resolution_t outputRes(1920, 1080);
        auto pixelLenghtInBytes = CalculatePixelLenghtInBytes(directoryRes, outputRes);

        //Raw rawImage
        RawImages::TRawImage<Pixel, ResolutionType>* rawImage = CreateRawImage(outputRes);
        

        //Loop through all files
        bool isNextFileExist = true;
        while (isNextFileExist)
        {
            File::Interface::IFile* file = this->fileDispencer->GetNextFile(isNextFileExist);
            this->chunkDispencer = new File::FileChunkDispencer(file->GetBuffer(), fileChunkSize);

            
            bool isNextFileChunkExist = true;
            while (isNextFileChunkExist)// while isNextFileChunkExist
            {
                bool isFileChunkFull = true; // if not , do something...
                auto currentFileChunk = this->chunkDispencer->GetNextChunk(fileChunkSize, isFileChunkFull, isNextFileChunkExist);

                this->pixelExtractor = new WAL::PixelExtractors::PixelExtractor<Pixel>(&currentFileChunk, pixelLenghtInBytes);//TODO get next currentFileChunk return std vector but pixel extractor takes ifstream

                bool isNextPixelExist = true;
                bool isNextPuttable = true;
                while (isNextPixelExist && isNextPuttable)
                {
                    Pixel pixel = this->pixelExtractor->GetNextPixel(isNextPixelExist);
                    rawImage->PutNextPixel(pixel, isNextPuttable);
                    delete this->pixelExtractor;

                    //rawImageConverter = new SomeConverter impl
                    this->encoder->AddAsFrame(rawImageConverter->Convert(*rawImage));
                }
            }
            //TODO last unfilled chunk remain unhandled.
            delete this->chunkDispencer;
        }

        delete rawImage;
        //~Loop through all files
        
        //save video file
        std::string outputPath = "C:\\Users\\leon2\\Desktop\\Garbage";
        this->encoder->SaveAsFile(outputPath);

        //Add rawImage to encoder

        //Loop until no pixels

        //save

    }

    void AppImplementation::Shutdown()
    {

    }

    bool AppImplementation::isNextPixel()
    {
        return true;
    }

    void AppImplementation::ExtractNextPixel()
    {
    }

    void AppImplementation::SavePixel()
    {

    }

    void AppImplementation::ConvertImage()
    {

    }

    void AppImplementation::AddImageToEncoder()
    {
        //this->encoder->AddAsFrame();
    }

    void AppImplementation::SaveVideoFile(std::string& path)
    {
        if (!this->encoder) return;
        this->encoder->EncodeFrames();
        this->encoder->SaveAsFile(path);
    }

    void AppImplementation::InitDirectory()
    {
        std::string path = "C:\\Users\\leon2\\Desktop\\Garbage";
        this->dir = new Directory::Directory_Impl(path);
    }

    Resolution_t AppImplementation::GetDirectoryResolution()
    {
        //Directory handler
        Directory::DirectoryHandler dirHandle(this->dir);
        size_t dirSize = dirHandle.GetAllFilesSize();
        float aspectRatio = 16 / 9;
        auto dirRes = dirHandle.GetResolution(aspectRatio);
        Resolution_t res;
        res.x = dirRes.x;
        res.y = dirRes.y;
        return res;
    }

    void AppImplementation::InitFileDispencer()
    {
        this->fileDispencer = new File::FileDispencer(this->dir->GetPaths());
    }

    void AppImplementation::InitChunkDispencer()
    {
        //this->chunkDispencer = new FileChunkDispencer(this->fileDispencer->GetNextFile()->GetBuffer());
    }

    void AppImplementation::InitEncoder()
    {
        this->encoder = new Encoders::h256Encoder();
    }

    void AppImplementation::InitRawImageConverter()
    {
        this->rawImageConverter = new Converter::RawToPngConverter_Impl<Pixel>();
    }
    const size_t AppImplementation::CalculateFileChunkSize()
    {
        //TODO
        //< fileSize, % pixelBytes, !> 1 GB
        return size_t();
    }
    const size_t AppImplementation::CalculatePixelLenghtInBytes(const Resolution_t& directory, const Resolution_t& outputImage)
    {
        auto res = (size_t)std::ceil((directory.x * directory.y) / (outputImage.x * outputImage.y)); //TODO ceil or what?
        return res;
    }
    RawImages::TRawImage<AppImplementation::Pixel, ResolutionType>* AppImplementation::CreateRawImage(const Resolution_t& resolution)
    {
        return new RawImages::TRawImage<Pixel, ResolutionType>(resolution.x, resolution.x);
    }
}