#pragma once
#include <string>
#include <vector>

namespace WAL
{
	class IImage;

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
		virtual void SaveAsFile(std::string& path) = 0;

		/**
		* Adds image as frame
		* @param img
		*/
		virtual void AddAsFrame(IImage* img) = 0;

		/**
		* Encodes all images to video
		*/
		virtual void EncodeFrames() = 0;

		/**
		* Adds bulk of images as frames
		* @param imgs
		*/
		virtual void AddAsFrames(std::vector<IImage*>& imgs) = 0;

	};
}