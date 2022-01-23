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
#include "../Math.h"
#include "../Exceptions.h"

namespace WAL::Apps
{
    AppImplementation::AppImplementation(const AppSettings& settings): settings(settings)
    {
    }
    AppImplementation::~AppImplementation()
    {
        delete dir;
        delete encoder;
        delete pixelExtractor;
        delete chunkDispencer;
        delete rawImageConverter;
        delete fileDispencer;
        delete runContext;
        delete initContext;
    }

    void AppImplementation::Run()
    {
        //Loop through all files
        bool isNextFileExist = true;
        while (isNextFileExist)
        {
            File::Interface::IFile* file = this->fileDispencer->GetNextFile(isNextFileExist);
            this->chunkDispencer = new File::FileChunkDispencer(file->GetBuffer(), runContext->fileChunkSize);


            bool isNextFileChunkExist = true;
            while (isNextFileChunkExist)// while isNextFileChunkExist
            {
                bool isFileChunkFull = true; // TODO if not , do something...
                auto currentFileChunk = this->chunkDispencer->GetNextChunk(runContext->fileChunkSize, isFileChunkFull, isNextFileChunkExist);

                this->pixelExtractor = new WAL::PixelExtractors::PixelExtractor<Pixel>(&currentFileChunk, runContext->pixelLenghtInBytes);//TODO get next currentFileChunk return std vector but pixel extractor takes ifstream

                bool isNextPixelExist = true;
                bool isNextPuttable = true;
                while (isNextPixelExist && isNextPuttable)
                {
                    Pixel pixel = this->pixelExtractor->GetNextPixel(isNextPixelExist);
                    this->initContext->rawImage->PutNextPixel(pixel, isNextPuttable);
                    delete this->pixelExtractor;

                    //rawImageConverter = new SomeConverter impl
                    this->encoder->AddAsFrame(rawImageConverter->Convert(*this->initContext->rawImage));
                }
            }
            //TODO last unfilled chunk remain unhandled.
            delete this->chunkDispencer;
        }

        //~Loop through all files
    }

    void AppImplementation::Init()
    {
        SetupRunContext();
        SetupInitContext();
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

    void AppImplementation::SetupRunContext()
    {
        RunContext* runContext = new RunContext(); //dctor
        InitDirectory();
        InitFileDispencer();
        runContext->fileChunkSize = CalculateFileChunkSize();
        auto dirRes = GetDirectoryResolution();
        runContext->pixelLenghtInBytes = CalculatePixelLenghtInBytes(dirRes, GetRawImageResolution(dirRes));
        this->runContext = runContext;
    }

    void AppImplementation::SetupInitContext()
    {
        InitContext* initContext = new InitContext(); //dctor
        initContext->rawImage = CreateRawImage(settings.outImageResolution);
        this->initContext = initContext;
    }

    void AppImplementation::AddImageToEncoder()
    {
        //this->encoder->AddAsFrame();
    }

    void AppImplementation::SaveVideoFile(std::string& path)
    {
        if (!this->encoder) return;
        this->encoder->EncodeFrames();
        this->encoder->SaveAsFile(this->settings.videoPath);
    }

    void AppImplementation::InitDirectory()
    {
        this->dir = new Directory::Directory_Impl(this->settings.directoryPath); //dctor
    }

    Resolution_t AppImplementation::GetDirectoryResolution()
    {
        Directory::DirectoryHandler dirHandle(this->dir);
        size_t dirSize = dirHandle.GetAllFilesSize();
        double aspectRatio =  Math::CalcAspectRatioFromLen(1.77, 2.0, dirSize, 0.001);
        if (aspectRatio < 0) { throw Exceptions::AspectRatioNotFound(); }
        return dirHandle.GetResolution(aspectRatio);
    }
    const Resolution_t AppImplementation::GetRawImageResolution(const Resolution_t& directoryRes)
    {
        //
    }

    void AppImplementation::InitFileDispencer()
    {
        this->fileDispencer = new File::FileDispencer(this->dir->GetPaths()); //dctor //TODO stack instead of heap
    }

    void AppImplementation::InitChunkDispencer()
    {
        //this->chunkDispencer = new FileChunkDispencer(this->fileDispencer->GetNextFile()->GetBuffer());
    }

    void AppImplementation::InitEncoder()
    {
        this->encoder = new Encoders::h256Encoder(); //dctor
    }

    void AppImplementation::InitRawImageConverter()
    {
        this->rawImageConverter = new Converter::RawToPngConverter_Impl<Pixel>(); //dctor
    }
    const size_t AppImplementation::CalculateFileChunkSize(const size_t fileSize, const size_t pixelBytesLen, const size_t maxRam)
    {
        //TODO
        //< fileSize, % pixelBytes, !> 1 GB
        double aspectRatio = Math::CalcAspectRatioFromLen(1.77, 2.0, fileSize, 0.001);
        size_t size;
        size_t pixelCount;
        if (fileSize % pixelBytesLen == 0) { pixelCount = fileSize / pixelBytesLen; }
        else { throw Exceptions::PixelsNotFit(); };
        //maxRam / 
        if (size > maxRam)
        {
            throw Exceptions::ChunkExceedesRam();
        }
        if (size % pixelBytesLen != 0)
        {
            throw Exceptions::PixelsNotFit();
        }

        return size;
    }
    const size_t AppImplementation::CalculatePixelLenghtInBytes(const Resolution_t& directory, const Resolution_t& outputImage)
    {
        // Need integer len. not float
        // If float had got - floor result, directory - result * outputImage, this is how much bytes are left from all dir.
        return (size_t)std::ceil((directory.x * directory.y) / (outputImage.x * outputImage.y)); //TODO ceil or what?
    }
    RawImages::TRawImage<AppImplementation::Pixel, ResolutionType>* AppImplementation::CreateRawImage(const Resolution_t& resolution)
    {
        return new RawImages::TRawImage<Pixel, ResolutionType>(resolution.x, resolution.x);
    }
}