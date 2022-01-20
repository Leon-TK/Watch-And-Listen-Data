#pragma once
#include "IApp.h"
#include <fstream>
#include <string>
//#include "../Vectors/Vectors.h"
/*    
* Test implementaion
*/    

namespace WAL
{
	namespace AppImplementations
	{
		//Forward decl
		class IDirectory;
		class IVideoEncoder;
		template <typename T>
		class PixelExtractor;
		class FileDispencer;
		class FileChunkDispencer;
		template <typename T>
		class IRawImageConverter;

		template <typename T>
		class TVec3;
		template <typename T>
		class TVec2;

		typedef uint8_t PixelChannelType;
		typedef TVec3<PixelChannelType> Pixel;
		typedef TVec2<uint32_t> Resolution;

		class AppImplementation final : public IApp
		{
		private:

			IDirectory* dir{ nullptr };
			IVideoEncoder* encoder{ nullptr };
			PixelExtractor<PixelChannelType>* pixelExtractor{ nullptr };
			FileDispencer* fileDispencer{ nullptr };
			FileChunkDispencer* chunkDispencer{ nullptr };
			IRawImageConverter<PixelChannelType>* rawImageConverter{ nullptr };

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
			Resolution GetDirectoryResolution();
			void InitFileDispencer();
			void InitChunkDispencer();
			void InitEncoder();
			void InitRawImageConverter();

		public:
			

			AppImplementation() = default;
			~AppImplementation();
			/**
			* Extract all pixels to video step by step, frame by frame
			*/
			virtual void Run() override;
			virtual void Init() override;
			virtual void Shutdown() override;

		};

	}
}