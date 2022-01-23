#pragma once
#include "IVideoEncoder.h"

namespace WAL
{
	namespace Images
	{
		namespace Interface
		{
			class IImage;
		}
	}
	
	namespace Encoders
	{
		class h256Encoder final : public Interface::IVideoEncoder
		{
		private:
			std::vector<Images::Interface::IImage*> images;
		public:

			/**
			* Saves encoded video. Encoding must be done before
			* @param path
			*/
			void SaveAsFile(const std::string& path);

			/**
			* Adds image as frame
			* @param img
			*/
			void AddAsFrame(Images::Interface::IImage* img);

			/**
			* Encodes all images to video
			*/
			void EncodeFrames();

			/**
			* Adds bulk of images as frames
			* @param imgs
			*/
			void AddAsFrames(std::vector<Images::Interface::IImage*>& imgs);

		};
	}
	
}