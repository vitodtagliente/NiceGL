#pragma once

/*
	common debug oprations
	Vito Domenico Tagliente
	math library for games
*/

#include <iostream>
#include "vector.h"
#include "point.h"
#include "matrix.h"

namespace math4games
{
	template <std::size_t N, class T>
	std::ostream& operator<<(std::ostream& os, const base_vector<N, T>& v)
	{
		os << "vector" << v.length << std::endl;
		for (unsigned int i = 0; i < v.length; ++i)
			cout << v[i] << " ";
		os << std::endl;
		return os;
	}

	template <std::size_t N, class T>
	std::ostream& operator<<(std::ostream& os, const base_point<N, T>& p)
	{
		os << "point" << p.length << std::endl;
		for (unsigned int i = 0; i < p.length; ++i)
			cout << p[i] << " ";
		os << std::endl;
		return os;
	}

	template <std::size_t N, std::size_t M, class T>
	std::ostream& operator<<(std::ostream& os, const base_matrix<N, M, T>& m)
	{
		os << "matrix" << " " << m.rows << "x" << m.columns << std::endl;
		for (unsigned int i = 0; i < N; ++i) {
			for (unsigned int j = 0; j < M; ++j)
				os << m(j, i) << "  ";
			os << std::endl;
		}
		return os;
	}
};