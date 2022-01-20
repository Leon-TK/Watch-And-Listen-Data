#pragma once
#include "IVideoEncoder.h"

namespace WAL
{
	class IImage;

	class h256Encoder final : public IVideoEncoder
	{
	private:
		std::vector<IImage*> images;
	public:

		/**
		* Saves encoded video. Encoding must be done before
		* @param path
		*/
		void SaveAsFile(std::string& path);

		/**
		* Adds image as frame
		* @param img
		*/
		void AddAsFrame(IImage* img);

		/**
		* Encodes all images to video
		*/
		void EncodeFrames();

		/**
		* Adds bulk of images as frames
		* @param imgs
		*/
		void AddAsFrames(std::vector<IImage*>& imgs);

	};
}