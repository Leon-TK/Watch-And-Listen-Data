#pragma once
#include <string>
#include <vector>

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
		namespace Interface
		{
			

			/*
			* Client side interface. Has few implementations, e.g. h256.
			* Add needed frames - encode - save
			*/

			class IVideoEncoder
			{
			public:
				virtual ~IVideoEncoder() {};
				/**
				* Saves encoded video. Encoding must be done before
				* @param path
				*/
				virtual void SaveAsFile(const std::string& path) = 0;

				/**
				* Adds image as frame
				* @param img
				*/
				virtual void AddAsFrame(Images::Interface::IImage* img) = 0;

				/**
				* Encodes all images to video
				*/
				virtual void EncodeFrames() = 0;

				/**
				* Adds bulk of images as frames
				* @param imgs
				*/
				virtual void AddAsFrames(std::vector<Images::Interface::IImage*>& imgs) = 0;

			};
		}
	}
	
}