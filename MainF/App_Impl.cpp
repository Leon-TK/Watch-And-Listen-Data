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
        
        const Resolution directoryRes = GetDirectoryResolution();

        InitFileDispencer();
        //InitChunkDispencer();

        constexpr size_t fileChunkSize = 2000; //TODO precalculate
        const Resolution outputRes(1920, 1080);
        auto pixelLenghtInBytes = (size_t)std::ceil((directoryRes.x * directoryRes.y) / (outputRes.x * outputRes.y)); //TODO ceil or what?

        //Raw rawImage
        RawImages::TRawImage<Pixel> rawImage(outputRes.x, outputRes.x); //TODO raw rawImage would not be 1920 1080, is will be pixtl type size * 1920*1080
        

        //Loop through all files
        bool isNextFileExist = true;
        while (isNextFileExist)
        {
            File::Interface::IFile* file = this->fileDispencer->GetNextFile(isNextFileExist);
            this->chunkDispencer = new File::FileChunkDispencer(file->GetBuffer(), fileChunkSize);

            bool isFileChunkFull = true;
            
            bool isNextFileChunkExist = true;
            while (isFileChunkFull && isNextPixelExist)// while isNextFileChunkExist
            {
                auto currentFileChunk = this->chunkDispencer->GetNextChunk(fileChunkSize, isFileChunkFull, isNextFileChunkExist);
                this->pixelExtractor = new WAL::PixelExtractors::PixelExtractor<Pixel>(&currentFileChunk, pixelLenghtInBytes);//TODO: delete ptr, TODO get next currentFileChunk return std vector but pixel extractor takes ifstream

                bool isNextPixelExist = true;
                bool isNextPuttable = true;
                Pixel pixel = this->pixelExtractor->GetNextPixel(isNextPixelExist); //TODO pixels type //while isNextPixelExist and isNextPuttable
                rawImage.PutNextPixel(pixel, isNextPuttable);
                delete this->pixelExtractor;

                this->encoder->AddAsFrame(rawImageConverter->Convert(rawImage));// TODO convert raw image to common image;
                //~while isNextPixelExist and isNextPuttable
            }
            //TODO last unfilled chunk remain unhandled.
            delete this->chunkDispencer;
        }
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

    Resolution AppImplementation::GetDirectoryResolution()
    {
        //Directory handler
        Directory::DirectoryHandler dirHandle(this->dir);
        size_t dirSize = dirHandle.GetAllFilesSize();
        float aspectRatio = 16 / 9;
        auto dirRes = dirHandle.GetResolution(aspectRatio);
        Resolution res;
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
}