#pragma once
#include "IApp.h"
#include <fstream>
#include <string>

/*    
* Test implementaion
*/    

namespace WAL
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

	
	class AppImplementation final : public IApp
	{
	private:
		typedef uint8_t PixelType;
		typedef TVec3<PixelType> Pixel;
		typedef TVec2<uint16_t> Resolution;

		IDirectory* dir{nullptr};
		IVideoEncoder* encoder{ nullptr };
		PixelExtractor<uint16_t>* pixelExtractor{ nullptr };
		FileDispencer* fileDispencer{ nullptr };
		FileChunkDispencer* chunkDispencer{ nullptr };
		IRawImageConverter<uint16_t>* rawImageConverter{nullptr};

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