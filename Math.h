#pragma once
#include "Typedefs.h"
#include <cmath>

namespace WAL
{
	namespace Math
	{
		/*
		* Calculates resolution from given lenght and aspect ration
		*/
		template <typename ResolutionType>
		ResolutionType CalcResolution(double aspectRatio, size_t lenght)
		{
			double x;
			double y;

			y = std::sqrt(lenght / aspectRatio);
			x = aspectRatio * y;

			//TODO ceil or floor x and y for not missing data
			ResolutionType res((typename ResolutionType::type)x, (typename ResolutionType::type)y);

			return res;
		};

		/*
		* Returns true if "std::sqrt(dividable / divider)" expression is integer
		*/
		bool isSqrtDivideInt(const double divider, const size_t dividable)
		{
			double y = std::sqrt(dividable / divider);
			size_t yInt = (size_t)y;
			double diff = y - (double)yInt;
			if (diff <= 0.00001)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		/*
		* Tries to find aspect ratio
		* @param minAspectRatio Should not be less than 0.0
		* @param maxAspectRatio Should not be greater than 3.0
		* @param len
		* @param precision Should be 0.0-0.1
		* @return -1 if cant find
		*/
		double CalcAspectRatioFromLen(double minAspectRatio, const double maxAspectRatio, const size_t len, double precision)
		{
			bool isInt = false;
			while (!isInt)
			{
				minAspectRatio += precision;
				if (minAspectRatio > maxAspectRatio) { return -1; }
				isInt = isSqrtDivideInt(minAspectRatio, len);
			}
			return minAspectRatio;
		}
	}
}