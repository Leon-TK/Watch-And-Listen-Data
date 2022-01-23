#pragma once
#include "IApp.h"
#include <fstream>
#include <string>
#include "../Typedefs.h"
//#include "../Vectors/Vectors.h"
/*    
* Test implementaion
*/    

namespace WAL
{
	namespace Directory
	{
		namespace Interface
		{
			class IDirectory;
		}
	};

	namespace Encoders
	{
		namespace Interface
		{
			class IVideoEncoder;
		}
	};

	namespace File
	{
		class FileDispencer;
		class FileChunkDispencer;
	};

	namespace Converter
	{
		namespace Interface
		{
			template <typename T>
			class IRawImageConverter;
		}
	};
	
	namespace Vectors
	{
		template <typename T>
		class TVec3;
		template <typename T>
		class TVec2;
	};

	namespace PixelExtractors
	{
		template <typename T>
		class PixelExtractor;
	};
	namespace Pixels
	{
		template <typename>
		struct TRgbPixel;
	};
	namespace RawImages
	{
		template <typename, typename>
		class TRawImage;
	}
	namespace Apps
	{
		

		class AppImplementation final : public Interface::IApp
		{

		public:
			typedef uint8_t PixelChannelType;
			typedef Pixels::TRgbPixel<PixelChannelType> Pixel;

		public:
			struct AppSettings
			{
				AppSettings(const std::string directoryPath,
							const std::string videoPath,
							const Resolution_t outImageResolution) :
				directoryPath(directoryPath), videoPath(videoPath), outImageResolution(outImageResolution) {};

				const std::string directoryPath; 
				const std::string videoPath;
				const Resolution_t outImageResolution;
			};
		private:
			struct RunContext
			{
				size_t fileChunkSize;
				size_t pixelLenghtInBytes;
			};
			struct InitContext
			{
				~InitContext() { delete rawImage; }
				RawImages::TRawImage<typename AppImplementation::Pixel, ResolutionType>* rawImage;
			};

		private:
			Directory::Interface::IDirectory* dir = nullptr;
			Encoders::Interface::IVideoEncoder* encoder = nullptr;
			PixelExtractors::PixelExtractor<Pixel>* pixelExtractor = nullptr;
			File::FileDispencer* fileDispencer = nullptr;
			File::FileChunkDispencer* chunkDispencer = nullptr;
			Converter::Interface::IRawImageConverter<Pixel>* rawImageConverter = nullptr;

		private:
			AppSettings settings; //ctor init
			const RunContext* runContext = nullptr;
			const InitContext* initContext = nullptr;

		private:
			void SetupRunContext();
			void SetupInitContext();
			/**
			* Checks if next pixel exist
			*/
			bool isNextPixel();

			/**
			* Extract one raw pixel form binary data
			*/
			void ExtractNextPixel();

			/**
			* Saves pixel to image or raw image
			*/
			void SavePixel();

			/**
			* To specified format. Etheir standart like PNG or TIFF or format that can encoder can understand
			*/
			void ConvertImage();

			/**
			* Encoder handles image with added pixel as one frame of video
			*/
			void AddImageToEncoder();

			void SaveVideoFile(std::string& path);
			//std::ifstream* GetFileBuffer();

			void InitDirectory();
			Resolution_t GetDirectoryResolution();
			void InitFileDispencer();
			void InitChunkDispencer();
			void InitEncoder();
			void InitRawImageConverter();

			const size_t CalculateFileChunkSize();
			const size_t CalculatePixelLenghtInBytes(const Resolution_t& directory, const Resolution_t& outputImage);
			RawImages::TRawImage<Pixel, ResolutionType>* CreateRawImage(const Resolution_t& resolution);

		public:
			AppImplementation(const AppSettings& settings);
			~AppImplementation();
			/**
			* Extract all pixels to video step by step, frame by frame
			*/
			virtual void Run() override final;
			virtual void Init() override final;
			virtual void Shutdown() override final;

		};
	};
}